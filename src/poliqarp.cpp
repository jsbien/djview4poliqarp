/****************************************************************************
*   Copyright (C) 2012 by Michal Rudolf <michal@rudolf.waw.pl>              *
****************************************************************************/

#include <QtXml>
#include "poliqarp.h"
#include "version.h"


Poliqarp::Poliqarp(QObject *parent) :
	QObject(parent)
{
	m_network = new QNetworkAccessManager(this);
	connect(m_network, SIGNAL(finished(QNetworkReply*)), this,
			  SLOT(replyFinished(QNetworkReply*)));

	m_lastConnection = 0;
	m_lastQuery = 0;
	m_lastSource = 0;
	m_matchesFound = 0;
	m_currentSource = 0;
}

void Poliqarp::connectToServer(const QUrl &url)
{
	m_serverUrl = url;
	m_sources.clear();
	m_lastConnection = m_network->get(QNetworkRequest(url));
	m_queries.clear();
	m_matchesFound = 0;
	m_pendingQuery.clear();
}

void Poliqarp::setCurrentSource(int index)
{
	if (index < -1 || index >= m_sources.count())
		index = -1;
	m_queries.clear();
	m_matchesFound = 0;
	m_currentSource = index;
	m_pendingQuery.clear();
	if (index != -1) {
		QUrl url = m_serverUrl.resolved(m_sources[index]);
		m_lastSource = m_network->get(QNetworkRequest(url));
	}
}

void Poliqarp::runQuery(const QString &text)
{
	m_lastQueryText = text;
	m_pendingQuery.clear();
	m_queries.clear();
	m_matchesFound = 0;
	QUrl url = m_serverUrl.resolved(m_sources[m_currentSource] + "query/");
	QByteArray args("query=");
	args.append(QUrl::toPercentEncoding(text));
	QNetworkRequest request(url);
	request.setHeader(QNetworkRequest::ContentTypeHeader, "application/octet-stream");
	m_lastQuery = m_network->post(request, args);
}

void Poliqarp::fetchMore()
{
	if (hasMore()) {
		QString moreMatches = QString("%1+/").arg(m_queries.count());
		QUrl url = m_nextQueries.resolved(moreMatches);
		m_lastQuery = m_network->get(QNetworkRequest(url));
	}
}

void Poliqarp::replyFinished(QNetworkReply *reply)
{
	QUrl redirection = reply->attribute(QNetworkRequest::RedirectionTargetAttribute).toUrl();

	if (reply == m_lastConnection) {
		if (redirection.isValid())
			m_lastConnection = m_network->get(QNetworkRequest(redirection));
		else connectionFinished(reply);
	}
	else if (reply == m_lastSource) {
		if (redirection.isValid())
			m_lastSource = m_network->get(QNetworkRequest(redirection));
		else selectSourceFinished(reply);
	}
	else if (reply == m_lastQuery) {
		if (redirection.isValid())
			m_lastQuery = m_network->get(QNetworkRequest(redirection));
		else if (!queryFinished(reply)) {
			QString refresh = QString::fromUtf8(reply->rawHeader("Refresh"));
			if (!refresh.isEmpty()) {
				int msec = refresh.section(';', 0, 0).toInt();
				m_pendingQuery = m_serverUrl.resolved(refresh.section('=', 1));
				if (msec > 0 && m_pendingQuery.isValid())
					QTimer::singleShot(qMin(1000, msec), this, SLOT(rerunQuery()));
			}
		}
	}
	reply->deleteLater();
}

void Poliqarp::rerunQuery()
{
	if (m_pendingQuery.isValid())
		m_lastQuery = m_network->get(QNetworkRequest(m_pendingQuery));
}


void Poliqarp::connectionFinished(QNetworkReply *reply)
{
	if (reply->error())
		emit connectionError(tr("Could not connect to the server.\nPlease check the URL."));
	else if (!parseSources(reply))
		emit connectionError(tr("This does not look like a Poliqarp server."));
}

bool Poliqarp::queryFinished(QNetworkReply *reply)
{
	if (parseQuery(reply)) {
		emit queryFinished();
		return true;
	}
	return false;
}

void Poliqarp::selectSourceFinished(QNetworkReply *reply)
{
	QString body = QString::fromUtf8(reply->readAll());
	QString info = textBetweenTags(body, "<div class='corpus-info'>", "</div>");
	info.append(textBetweenTags(body, "<div class='corpus-info-suffix'>", "</div>"));
	emit sourceSelected(info);
}

bool Poliqarp::parseSources(QIODevice* reply)
{
	QDomDocument document;
	QString errorMessage;
	QString body = QString::fromUtf8(reply->readAll());
	if (!document.setContent(body, false, &errorMessage))
		return false;

	QDomElement title = document.elementsByTagName("title").at(0).toElement();
	if (!title.firstChild().toText().nodeValue().contains("Poliqarp"))
		return false;

	QDomElement list = document.elementsByTagName("ul").at(1).toElement();
	if (list.isNull())
		return false;

	QDomNodeList sources = list.elementsByTagName("a");
	QStringList sourceList;
	for (int i = 0; i < sources.count(); i++) {
		QDomElement element = sources.at(i).toElement();
		if (element.isNull())
			continue;
		QString tag = element.attribute("href");
		QString label = element.firstChild().toText().nodeValue();
		if (!tag.isEmpty() && !label.isEmpty()) {
			sourceList.append(label);
			m_sources.append(tag);
		}
	}
	if (m_sources.isEmpty())
		return false;

	emit connected(sourceList);
	return true;
}

bool Poliqarp::parseQuery(QIODevice *device)
{
	QDomDocument document;
	QString body = QString::fromUtf8(device->readAll());
	QString errorMessage;
	int line, column;

	if (!document.setContent(body, false, &errorMessage, &line, &column)) {
		qDebug() << errorMessage << "Line: "<< line << "column: "<< column << '\n' << body;
		return false;
	}

	QDomNodeList rows = document.elementsByTagName("tr");
	for (int i = 0; i < rows.count(); i++) {
		DjVuLink item;
		QDomNodeList fields = rows.at(i).toElement().elementsByTagName("td");
		if (fields.count() != 4)
			continue;
		item.setLeftContext(fields.at(0).toElement().text());
		item.setWord(fields.at(1).toElement().text());
		item.setRightContext(fields.at(2).toElement().text());
		QUrl link = fields.at(3).firstChildElement("a").attribute("href");
		item.setLink(link);
		m_queries.append(item);
	}

	QDomNodeList paragraphs = document.elementsByTagName("p");
	for (int i = 0; i < paragraphs.count(); i++)
		if (m_nextQueries.isEmpty() && paragraphs.at(i).toElement().attribute("class") == "next_page") {
			QDomElement a = paragraphs.at(i).firstChildElement();
			QString next = a.attribute("href");
			next.truncate(next.count() - 4);
			m_nextQueries = m_serverUrl.resolved(next);
		}


	QDomNodeList spans = document.elementsByTagName("span");
	for (int i = 0; i < spans.count(); i++) {
		QString id = spans.at(i).toElement().attribute("id");
		if (id.startsWith("matches"))
			m_matchesFound = spans.at(i).toElement().text().toInt();
		else if (id == "wait")
			return false;
	}
	return true;
}

QNetworkRequest Poliqarp::request(const QUrl& url) const
{
	QNetworkRequest r(url);
	r.setRawHeader("User-Agent", QString("DjVuPoliqarp %1 (build %2)")
						.arg(Version::versionText())
						.arg(Version::buildText()).toAscii());
	return r;
}

QString Poliqarp::textBetweenTags(const QString& body, const QString &startTag,
											 const QString &endTag)
{
	int start = body.indexOf(startTag);
	int end =  body.indexOf(endTag, start + startTag.count() + 1);
	if (start != -1 && end != -1)
		return body.mid(start + startTag.count(),
							 end - start - startTag.count());
	else return QString();
}

DjVuLink Poliqarp::query(int index) const
{
	if (index >= 0 && index < m_queries.count())
		return m_queries[index];
	else return DjVuLink();
}








/****************************************************************************
*   Copyright (C) 2012-2013 by Michal Rudolf <michal@rudolf.waw.pl>              *
*   This software is subject to, and may be distributed under, the
*   GNU General Public License, either version 2 of the license,
*   or (at your option) any later version. The license should have
*   accompanied the software or you may obtain a copy of the license
*   from the Free Software Foundation at http://www.fsf.org .

*   This program is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
****************************************************************************/

#ifndef POLIQARPWIDGET_H
#define POLIQARPWIDGET_H

#include "ui_poliqarpwidget.h"

class DjVuLink;
class Poliqarp;

class PoliqarpWidget : public QWidget
{
	  Q_OBJECT
public:
	 explicit PoliqarpWidget(QWidget *parent = 0);
	 ~PoliqarpWidget();
	/** @return log items. */
	QStringList logs() const;
public slots:
	 void connectToServer();
	 void clear();
	 void configure();
	 bool exportResults(const QString& filename);
	 void hideCurrentItem();

	 // File index
	 /** Add new entry. */
	 void addEntry(const QString& word, const QUrl& link);
	 /** Update current entry. */
	 void updateCurrentEntry(const QUrl& link);
private slots:
	 // Server and corpus
	 void configureCorpus();
	 void doSelectSource();
	 void doSearch();
	 void connected(const QStringList& sources);
	 void showError(const QString& message);
	 void corpusChanged();

	 // Metadata
	 void metadataReceived();
	 void metadataRequested();
	 void metadataLinkOpened(const QUrl &url);
	 void nextMetadata();
	 void previousMetadata();

	 void updateQueries(const QString& message);

	 // Main panel
	 void showDocument(const QModelIndex& index);
	 /** Show server description as parsed by Poliqarp. */
	 void showServerDescription();
	 /** Show server description as parsed by Poliqarp. */
	 void showCorpusDescription();
	 /** Fetch metadata if the metadata tab is active. */
	 void fetchMetadata();

	 void synchronizeSelection();
	 /** Test external URL for redirection. */
	 void openUrl();
signals:
	 void documentRequested(const DjVuLink& link);
	 void corpusSelected(const QString& name);
	 /** Information in HTML format (server or corpus description) was requested. */
	 void informationReceived(const QString& html);
	 /** Index file was open. */
	 void indexOpened();
	 /** Index file was closed. */
	 void indexClosed();


private:
	 void setSearching(bool enabled);
	 bool isSearching() const;
	 void updateTextQueries();
	 void updateGraphicalQueries();
	 Ui::PoliqarpWidget ui;
	 Poliqarp* m_poliqarp;
};

#endif // POLIQARPWIDGET_H

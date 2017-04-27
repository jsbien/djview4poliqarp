/****************************************************************************
*   Copyright (C) 2013 by Michal Rudolf <michal@rudolf.waw.pl>              *
****************************************************************************/

#include "fileindex.h"

FileIndex::FileIndex()
{
	m_modified = false;
}

bool FileIndex::open(const QString &filename)
{
	clear();

	QFile file(filename);
	if (!file.open(QIODevice::ReadOnly))
		return false;
	QTextStream stream(&file);
	stream.setCodec("UTF-8");
	while (!stream.atEnd()) {
		Entry entry = Entry::parse(stream.readLine());
		if (entry.isValid()) {
			m_sortOrder.append(m_entries.count());
			m_entries.append(entry);
		}
	}
	if (m_entries.isEmpty())
		return false;
	m_filename = filename;
	m_modified = false;
	return true;
}

bool FileIndex::save()
{
	const QString backup = m_filename + ".bak";
	if (QFile::exists(m_filename) && !m_backedUp.contains(m_filename)) {
		m_backedUp.insert(m_filename);
		if (QFile::exists(backup))
			QFile::remove(backup);
		QFile::rename(m_filename, backup);
	}

	QFile file(m_filename);
	if (file.open(QIODevice::WriteOnly)) {
		QTextStream stream(&file);
		stream.setCodec("UTF-8");
		QList<Entry> entries;
		for (int i = 0; i < m_entries.count(); i++)
			if (!m_entries[i].isDeleted()) {
				stream << m_entries[i].toString();
				entries.append(m_entries[i]);
			}
		std::swap(m_entries, entries);
		sort();
		m_modified = false;
		return true;
	}
	else {
		if (QFile::exists(backup))
			QFile::rename(backup, m_filename);
		return false;
	}
}

void FileIndex::clear()
{
	m_sortOrder.clear();
	m_entries.clear();
	m_filename.clear();
	m_modified = false;
}

void FileIndex::sort(SortOrder order)
{
	m_sortOrder.clear();
	for (int i = 0; i < m_entries.count(); i++)
		m_sortOrder.append(i);

	switch (order) {
	case AlphabeticOrder:
		qSort(m_sortOrder.begin(), m_sortOrder.end(), AlphabeticComparator(m_entries));
		break;
	case AtergoOrder:
		qSort(m_sortOrder.begin(), m_sortOrder.end(), AtergoComparator(m_entries));
		break;
	case LetterOrder:
		qSort(m_sortOrder.begin(), m_sortOrder.end(), LetterComparator(m_entries));
		break;
	case OriginalOrder:
		break;
	}
}

QUrl FileIndex::link(int index) const
{
	return entry(index).link;
}

void FileIndex::setLink(int index, const QUrl &link)
{
	Entry e = entry(index);
	e.link = link;
	setEntry(index, e);
}

QString FileIndex::comment(int index) const
{
	return entry(index).comment;
}

void FileIndex::setComment(int index, const QString &comment)
{
	Entry e = entry(index);
	e.comment = comment;
	setEntry(index, e);
}

bool FileIndex::appendEntry(const Entry& entry)
{
	m_sortOrder.append(m_entries.count());
	m_entries.append(entry);
	m_modified = true;
	return true;
}

Entry FileIndex::entry(int index) const
{
	if (index >= 0 && index < m_sortOrder.count())
		return m_entries[m_sortOrder[index]];
	else return Entry();
}

void FileIndex::setEntry(int index, const Entry& entry)
{
	if (index >= 0 && index < m_sortOrder.count()) {
		m_entries[m_sortOrder[index]] = entry;
		m_modified = true;
	}
}

QString FileIndex::AtergoComparator::atergo(const QString& s) const
{
	QString t;
	t.reserve(s.count());
	for (int i = s.count() - 1; i >= 0; i--)
		t.append(s[i]);
	return t;
}

QString FileIndex::LetterComparator::letters(const QString& s) const
{
	QString t;
	t.reserve(s.count());
	for (int i = 0; i < s.count(); i++)
		if (s[i].isLetterOrNumber())
			t.append(s[i]);
	return t;
}

QSet<QString> FileIndex::m_backedUp;

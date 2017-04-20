/****************************************************************************
*   Copyright (C) 2014 by Michal Rudolf <michal@rudolf.waw.pl>              *
****************************************************************************/

#ifndef ENTRY_H
#define ENTRY_H

#include <QtCore>

class Entry {
public:
	Entry() {}
	Entry(const QString& w) {word = w.trimmed();}
	bool isVisible() const {return !comment.startsWith('!');}
	bool isValid() const {return !word.isEmpty();}
	void hide() {if (isVisible()) comment.prepend('!');}
	void show() {if (!isVisible()) comment = comment.mid(1);}
	QString formattedWord() const {return link.isValid() ? word : word + ' ';}
	QString formattedComment() const {return isVisible() ? comment : comment.mid(1);}
	QString toString();
	bool operator==(const Entry& e) {return word == e.word;}
	bool operator<(const Entry& e) {return word < e.word;}
	QUrl validLink() const;

	QString word;
	QUrl link;
	QString comment;

	/** Parse string. */
	static Entry parse(const QString& line);
	/** CSV row to string list. */
	static QStringList csvToStringList(const QString& row);
	/** String list to CSV row. */
	static QString stringListToCsv(const QStringList& columns);

};


#endif // ENTRY_H
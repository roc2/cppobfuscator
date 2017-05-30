/** @file
  * @author Yunkin Ilya.
  */
#ifndef STRINGSPLITTER_H
#define STRINGSPLITTER_H

#include <QString>

class StringSplitter
{
    StringSplitter();
    StringSplitter(StringSplitter&);
    const QString &line;
    QString::const_iterator it;
public:
    StringSplitter(const QString &line);
    QString getSymbol();
    bool isEnd();
    bool isTwoCharEcsSecond(const QChar &c);
    bool isHexOrUnicodeSecond(const QChar &c);
    bool isHexDigit(const QChar &c);
};

#endif // STRINGSPLITTER_H

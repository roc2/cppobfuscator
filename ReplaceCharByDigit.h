#ifndef REPLACECHARBYDIGIT_H
#define REPLACECHARBYDIGIT_H

#include <QTextStream>

class ReplaceCharByDigit
{
public:
public:
    /// Trailing spacers should be deleted before calling this operator.
    void operator()(QTextStream &sourceStream,
                    QTextStream &destinationStream);
    QString getReplacer(QChar currentChar, QChar previousChar);
    QString replaceBetween(const QString &sourceLine, char quote);
};

#endif // REPLACECHARBYDIGIT_H

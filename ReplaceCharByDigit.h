#ifndef REPLACECHARBYDIGIT_H
#define REPLACECHARBYDIGIT_H

#include <QTextStream>

struct ReplaceCharByDigitPrivate;
class ReplaceCharByDigit
{
    ReplaceCharByDigitPrivate *privateMembers;
public:
    /// Trailing spacers should be deleted before calling this operator.
    void operator()(QTextStream &sourceStream,
                    QTextStream &destinationStream);
    QString getReplacer(QString symbol);
    QString replaceBetween(const QString &sourceLine, char quote);
};

#endif // REPLACECHARBYDIGIT_H

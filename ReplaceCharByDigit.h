/** @file
  * @author Yunkin Ilya.
  */
#ifndef REPLACECHARBYDIGIT_H
#define REPLACECHARBYDIGIT_H

#include <QTextStream>

struct ReplaceCharByDigitPrivate;
class ReplaceCharByDigit
{
    ReplaceCharByDigitPrivate *privateMembers;
public:
    ReplaceCharByDigit();
    ~ReplaceCharByDigit();
    /// Trailing spacers should be deleted before calling this operator.
    void operator()(QTextStream &sourceStream,
                    QTextStream &destinationStream);
    QString getReplacer(QChar symbol);
    QString getReplacer(const QString &symbol);
    QString replaceBetween(const QString &sourceLine, char quote);
};

#endif // REPLACECHARBYDIGIT_H

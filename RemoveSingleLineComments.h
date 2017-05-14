/** @file
  * @author Yunkin Ilya.
  */
#ifndef REMOVESINGLELINECOMMENTS_H
#define REMOVESINGLELINECOMMENTS_H

#include <QTextStream>

class RemoveSingleLineComments
{
public:
    void operator()(QTextStream &sourceStream,
                    QTextStream &destinationStream);
    QString removeSingleLineCommentsFromLine(const QString &sourceLine);
};

#endif // REMOVESINGLELINECOMMENTS_H

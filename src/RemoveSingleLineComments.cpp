/** @file
  * @author Yunkin Ilya.
  */
#include "RemoveSingleLineComments.h"

#include <assert.h>

void RemoveSingleLineComments::operator()(QTextStream &sourceStream,
                            QTextStream &destinationStream)
{
    QString sourceLine;

    do{
        sourceLine = sourceStream.readLine();
        if(!sourceLine.isNull()){
            destinationStream << removeSingleLineCommentsFromLine(sourceLine);
        }
    }while(!sourceLine.isNull());
}

QString RemoveSingleLineComments::removeSingleLineCommentsFromLine(
        const QString &sourceLine)
{
    QStringList list = sourceLine.split("//");

    assert(!list.isEmpty());

    QString outputLine = list[0] + "\r\n";

    return outputLine;
}

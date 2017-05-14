/** @file
  * @author Yunkin Ilya.
  */
#include "RemoveEmptyStrings.h"

void RemoveEmptyStrings::operator()(QTextStream &sourceStream,
                            QTextStream &destinationStream)
{
    QString sourceLine;

    do{
        sourceLine = sourceStream.readLine();
        if(!sourceLine.isEmpty()){
            destinationStream << sourceLine << "\r\n";
        }
    }while(!sourceLine.isNull());
}

/** @file
  * @author Yunkin Ilya.
  */
#include "RemoveLineFeed.h"

void RemoveLineFeed::operator()(QTextStream &sourceStream,
                           QTextStream &destinationStream)
{
    QString sourceLine;

    do{
        sourceLine = sourceStream.readLine();
        if((!sourceLine.isNull()) && (!sourceLine.isEmpty())){
            destinationStream << sourceLine;

            bool isMacro = (sourceLine[0] == '#') ||
                    (sourceLine.left(3) == "\?\?=");
            if(isMacro) {
                destinationStream <<"\r\n";
            }else{
            }
        }
    }while(!sourceLine.isNull());
}

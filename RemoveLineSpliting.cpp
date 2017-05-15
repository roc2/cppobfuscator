/** @file
  * @author Yunkin Ilya.
  */
#include "RemoveLineSpliting.h"

void RemoveLineSpliting::operator()(QTextStream &sourceStream,
                                    QTextStream &destinationStream)
{
    QString sourceLine;

    do{
        sourceLine = sourceStream.readLine();
        if((!sourceLine.isNull()) && (!sourceLine.isEmpty())){
            int length = sourceLine.length();
            if(sourceLine[length - 1] == '\\'){
                sourceLine = sourceLine.left(length - 1);
                destinationStream << sourceLine;
            }else{
                destinationStream << sourceLine << "\r\n";
            }
        }
    }while(!sourceLine.isNull());
}

/** @file
  * @author Yunkin Ilya.
  */
#include "RemoveTrailingSpacers.h"

void RemoveTrailingSpacers::operator()(QTextStream &sourceStream,
                                       QTextStream &destinationStream)
{
    QString sourceLine;

    do{
        sourceLine = sourceStream.readLine();
        if(!sourceLine.isNull()){
            int length = sourceLine.length();
            int lastSignificantChar = length - 1;
            while(lastSignificantChar >= 0){
                static const QString spacers("\t ");

                if(!spacers.contains(sourceLine[lastSignificantChar])){
                    break;
                }
                lastSignificantChar--;
            }
            destinationStream << sourceLine.left(lastSignificantChar + 1)
                              << "\r\n";
        }
    }while(!sourceLine.isNull());
}

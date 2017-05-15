/** @file
  * @author Yunkin Ilya.
  */
#include "RemoveLeadingSpacers.h"

void RemoveLeadingSpacers::operator()(QTextStream &sourceStream,
                                       QTextStream &destinationStream)
{
    QString sourceLine;

    do{
        sourceLine = sourceStream.readLine();
        if(!sourceLine.isNull()){
            int length = sourceLine.length();
            int firstSignificantChar = 0;
            while(firstSignificantChar < length){
                static const QString spacers("\t ");

                if(!spacers.contains(sourceLine[firstSignificantChar])){
                    break;
                }
                firstSignificantChar++;
            }
            destinationStream << sourceLine.mid(firstSignificantChar)
                              << "\r\n";
        }
    }while(!sourceLine.isNull());
}

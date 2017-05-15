#include "RemoveLeadingSpacers.h"

void RemoveLeadingSpacers::operator()(QTextStream &sourceStream,
                                       QTextStream &destinationStream)
{
    static const QString spacers("\t ");
    QString sourceLine;

    do{
        sourceLine = sourceStream.readLine();
        if(!sourceLine.isNull()){
            int length = sourceLine.length();
            int firstSignificantChar = 0;
            while(firstSignificantChar < length){
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

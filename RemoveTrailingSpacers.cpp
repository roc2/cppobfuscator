#include "RemoveTrailingSpacers.h"

void RemoveTrailingSpacers::operator()(QTextStream &sourceStream,
                                       QTextStream &destinationStream)
{
    static const QString spacers("\t ");
    QString sourceLine;

    do{
        sourceLine = sourceStream.readLine();
        if(!sourceLine.isNull()){
            int length = sourceLine.length();
            int lastSignificantChar = length - 1;
            while(lastSignificantChar >= 0){
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

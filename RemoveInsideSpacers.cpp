/** @file
  * @author Yunkin Ilya.
  */
#include "RemoveInsideSpacers.h"

void RemoveInsideSpacers::operator()(QTextStream &sourceStream,
                                     QTextStream &destinationStream)
{
    QString sourceLine;

    do{
        sourceLine = sourceStream.readLine();
        if(!sourceLine.isNull()){
            QString outLine;
            int length = sourceLine.length();
            QChar prev(' ');
            QChar cur = prev;
            QChar next = prev;
            for(int i = 0; i < length; i++){
                prev = cur;
                cur = sourceLine[i];
                if(i < length - 1){
                    next = sourceLine[i + 1];
                }else{
                    next = ' ';
                }

                static const QString spacers("\t ");
                static const QString operators("<>+-/=");
                static const QString separators(operators +
                                                spacers+
                                                "*&.,;");
                if(spacers.contains(cur)){
                    bool bothSideOperators = operators.contains(prev) &&
                            operators.contains(next);
                    bool bothAreNotSeparators = (!separators.contains(prev)) &&
                            (!separators.contains(next));

                    if(bothSideOperators || bothAreNotSeparators){
                        outLine+=cur;
                    }
                }else{
                    outLine+= cur;
                }
            }

            destinationStream << outLine << "\r\n";
        }
    }while(!sourceLine.isNull());
}

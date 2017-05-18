#include "ReplaceCharByDigit.h"

void ReplaceCharByDigit::operator()(QTextStream &sourceStream,
                                    QTextStream &destinationStream)
{
    QString sourceLine;

    do{
        sourceLine = sourceStream.readLine();
        if((!sourceLine.isNull()) && (!sourceLine.isEmpty())){
            QString outString;
            bool inQuotes = false;
            QChar previousChar = ' ';
            foreach (QChar c, sourceLine) {
                QString replacer = c;
                if(inQuotes){
                    bool isNotEscape = previousChar != '\\';
                    bool isNotSlash = c != '\\';

                    if(isNotSlash && isNotEscape){
                        if(c == '\"'){
                            inQuotes = false;
                        }else{
                            replacer = QString("\\") +
                                    QString::number(int(c.toLatin1()), 8);
                        }
                    }else{
                    }
                }else{
                    if(c == '\"'){
                        inQuotes = true;
                    }
                }

                outString+= replacer;
                previousChar = c;
            }
            destinationStream << outString;
        }else{
            destinationStream << sourceLine;
        }
        destinationStream << "\r\n";
    }while(!sourceLine.isNull());
}

#include "ReplaceByTrigraphs.h"

ReplaceByTrigraphs::ReplaceByTrigraphs()
{
    trigraphsMap.insert('#', "\?\?=");
    trigraphsMap.insert('\\', "\?\?/");
    trigraphsMap.insert('^', "\?\?'");
    trigraphsMap.insert('[', "\?\?(");
    trigraphsMap.insert(']', "\?\?)");
    trigraphsMap.insert('|', "\?\?!");
    trigraphsMap.insert('{', "\?\?<");
    trigraphsMap.insert('}', "\?\?>");
    trigraphsMap.insert('~', "\?\?-");
}

void ReplaceByTrigraphs::operator()(QTextStream &sourceStream,
                                    QTextStream &destinationStream)
{
    QString sourceLine;

    do{
        sourceLine = sourceStream.readLine();
        if(!sourceLine.isNull()){
            int length = sourceLine.length();
            QChar previousChar(' ');
            QChar c(' ');

            QString outputLine;
            bool inQuotes = false;
            for(int i = 0; i < length; i++){
                previousChar = c;
                c = sourceLine[i];
                QString replacer = c;
                if(inQuotes){
                    bool isNotEscape = previousChar != '\\';
                    bool isNotSlash = c != '\\';

                    if(isNotSlash && isNotEscape){
                        if((c == '\"') || (c == '\'')){
                            inQuotes = false;
                        }else{
                        }
                    }
                }else{
                    if((c == '\"') || (c == '\'')){
                        inQuotes = true;
                    }else{
                        QMap<QChar, QString> ::iterator it =
                                trigraphsMap.find(c);
                        bool found = it != trigraphsMap.end();

                        if(found){
                            replacer = *it;
                        }else{
                        }
                    }
                }

                outputLine+= replacer;
            }
            destinationStream << outputLine << "\r\n";
        }
    }while(!sourceLine.isNull());
}

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
            QChar previous(' ');
            QChar current(' ');
            bool inQuotes = false;

            QString outputLine;
            for(int i = 0; i < length; i++){
                previous = current;
                current = sourceLine[i];

                if(!inQuotes){
                    if(current == '\"'){
                        inQuotes = true;
                        outputLine+= current;
                    }else{
                        QMap<QChar, QString> ::iterator it =
                                trigraphsMap.find(current);
                        bool found = it != trigraphsMap.end();

                        if(found){
                            outputLine+= *it;
                        }else{
                            outputLine+= current;
                        }
                    }

                }else{
                    if(current == '\"'){
                        inQuotes = false;
                    }
                    outputLine+= current;
                }
            }
            destinationStream << outputLine << "\r\n";
        }
    }while(!sourceLine.isNull());
}

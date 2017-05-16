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

            QString outputLine;
            for(int i = 0; i < length; i++){
                previous = current;
                current = sourceLine[i];

                QMap<QChar, QString> ::iterator it =
                        trigraphsMap.find(current);
                bool found = it != trigraphsMap.end();

                if(found){
                    outputLine+= *it;
                }else{
                    outputLine+= current;
                }

            }
            destinationStream << outputLine << "\r\n";
        }
    }while(!sourceLine.isNull());
}

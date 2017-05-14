/** @file
  * @author Yunkin Ilya.
  */
#include "RemoveMultyLineComments.h"

void RemoveMultyLineComments::operator()(QTextStream &sourceStream,
                                         QTextStream &destinationStream)
{
    bool inComment = false;
    QString sourceLine;
    do{
        sourceLine = sourceStream.readLine();
        if(!sourceLine.isNull()){
            QString outputLine = sourceLine;

            removeMultyLineCommentsR(outputLine, inComment);
            destinationStream << outputLine << "\r\n";
        }
    }while(!sourceLine.isNull());
}

bool RemoveMultyLineComments::removeMultyLineCommentsR(QString &sourceLine,
                                                       bool &inComment)
{
    bool found = false;
    QString commentBegin("/*");
    QString commentEnd("*/");
    QString outputLine;
    if(!inComment){
        if(sourceLine.contains(commentBegin)){
            found = true;
            inComment = true;
            int index = sourceLine.indexOf(commentBegin);

            outputLine+= sourceLine.left(index);
            QString least = sourceLine.mid(index);
            removeMultyLineCommentsR(least, inComment);
            outputLine+= least;
            sourceLine = outputLine;
        }else{
            outputLine = sourceLine;
        }
    }else{
        if(sourceLine.contains(commentEnd)){
            found = true;
            inComment = false;
            int index = sourceLine.indexOf(commentEnd);

            outputLine+= sourceLine.mid(index + commentEnd.length());

            sourceLine = outputLine;

        }else{
            sourceLine.clear();
        }
    }
    if(found){
        removeMultyLineCommentsR(sourceLine, inComment);
    }
    return found;
}

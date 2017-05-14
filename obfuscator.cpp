#include "obfuscator.h"

#include <QFile>
#include <QTextStream>

#include <QDebug>

#include <assert.h>

class RemoveMultyLineComments
{
public:
    void operator()(QTextStream &sourceStream,
                    QTextStream &destinationStream);
    /**
     * @brief Recursive function. It works with one text line.
     * @param sourceLine - Text to modyfying.
     * @param inComment - true if sourceLine begins in comment.
     * @return true if comment tags found.
     */
    bool removeMultyLineCommentsR(QString &sourceLine, bool &inComment);

};

class RemoveSingleLineComments
{
public:
    void operator()(QTextStream &sourceStream,
                    QTextStream &destinationStream);
    QString removeSingleLineCommentsFromLine(const QString &sourceLine);
};


class RemoveEmptyStrings
{
public:
    void operator()(QTextStream &sourceStream,
                    QTextStream &destinationStream);
};

Obfuscator::Obfuscator()
{
}

void Obfuscator::operator()(QStringList &sourceList)
{
    foreach (const QString &source, sourceList) {
        run(source, RemoveMultyLineComments());
        run(source, RemoveSingleLineComments());
        run(source, RemoveEmptyStrings());
    }
}

QString Obfuscator::getTmpFilename(const QString &source)
{
    QString tmpSuffix("~");
    QString tmpFileName(source + tmpSuffix);

    // Find free file name
    while(QFile(tmpFileName).exists()){
        tmpFileName+= tmpSuffix;
    }

    return tmpFileName;
}

template <class Functor>
void Obfuscator::run(const QString &source, Functor f)
{
    QString tmpFileName = getTmpFilename(source);
    QFile destinationFile(tmpFileName);
    QFile sourceFile(source);

    assert(!destinationFile.exists());
    assert(sourceFile.exists());

    bool destinationOpened = destinationFile.open(QFile::WriteOnly);
    bool sourceOpened = sourceFile.open(QFile::ReadOnly);

    assert(destinationOpened);
    assert(sourceOpened);

    QTextStream sourceStream(&sourceFile);
    QTextStream destinationStream(&destinationFile);

    f(sourceStream, destinationStream);

    destinationFile.close();
    sourceFile.close();

    sourceFile.remove();
    destinationFile.rename(source);
}


void RemoveSingleLineComments::operator()(QTextStream &sourceStream,
                            QTextStream &destinationStream)
{
    QString sourceLine;

    do{
        sourceLine = sourceStream.readLine();
        if(!sourceLine.isNull()){
            destinationStream << removeSingleLineCommentsFromLine(sourceLine);
        }
    }while(!sourceLine.isNull());
}

QString RemoveSingleLineComments::removeSingleLineCommentsFromLine(
        const QString &sourceLine)
{
    QStringList list = sourceLine.split("//");

    assert(!list.isEmpty());

    QString outputLine = list[0] + "\r\n";

    return outputLine;
}

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

void RemoveEmptyStrings::operator()(QTextStream &sourceStream,
                            QTextStream &destinationStream)
{
    QString sourceLine;

    do{
        sourceLine = sourceStream.readLine();
        if(!sourceLine.isEmpty()){
            destinationStream << sourceLine << "\r\n";
        }
    }while(!sourceLine.isNull());
}


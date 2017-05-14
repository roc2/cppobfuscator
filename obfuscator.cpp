#include "obfuscator.h"

#include <QFile>
#include <QTextStream>

#include <QDebug>

#include <assert.h>

Obfuscator::Obfuscator()
{
}

void Obfuscator::operator()(QStringList &sourceList)
{
    foreach (const QString &source, sourceList) {
        removeMultyLineComments(source);
        removeSingleLineComments(source);
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
    qDebug() << source;
    qDebug() << tmpFileName;
    return tmpFileName;
}

void Obfuscator::removeSingleLineComments(const QString &source)
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
    QString sourceLine;

    do{
        sourceLine = sourceStream.readLine();
        if(!sourceLine.isNull()){
            destinationStream << removeSingleLineCommentsFromLine(sourceLine);
        }
    }while(!sourceLine.isNull());

    destinationFile.close();
    sourceFile.close();

    sourceFile.remove();
    destinationFile.rename(source);
}

QString Obfuscator::removeSingleLineCommentsFromLine(const QString &sourceLine)
{
    QStringList list = sourceLine.split("//");

    assert(!list.isEmpty());

    QString outputLine = list[0] + "\r\n";

    return outputLine;
}

void Obfuscator::removeMultyLineComments(const QString &source)
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
    QString sourceLine;

    bool inComment = false;
    do{
        sourceLine = sourceStream.readLine();
        if(!sourceLine.isNull()){
            QString outputLine = sourceLine;
            qDebug() << __LINE__ <<  "s:" << sourceLine;
            while(removeMultyLineCommentsR(outputLine, inComment)){
                ;
            }
            destinationStream << outputLine << "\r\n";
        }
    }while(!sourceLine.isNull());

    destinationFile.close();
    sourceFile.close();

    sourceFile.remove();
    destinationFile.rename(source);
}

bool Obfuscator::removeMultyLineCommentsR(QString &sourceLine, bool &inComment)
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
            qDebug() << __LINE__ << index;
            qDebug() << __LINE__ <<  "s:" << sourceLine;
            outputLine+= sourceLine.left(index);
            qDebug() << __LINE__ <<  "o:" << outputLine;
            QString least = sourceLine.mid(index);
            removeMultyLineCommentsR(least, inComment);
            outputLine+= least;
            qDebug() << __LINE__ <<  "o:" << outputLine;
            sourceLine = outputLine;
            qDebug() << __LINE__ <<  "s:" << sourceLine;
        }else{
            outputLine = sourceLine;
        }
    }else{
        if(sourceLine.contains(commentEnd)){
            found = true;
            inComment = false;
            int index = sourceLine.indexOf(commentEnd);
            qDebug() << __LINE__ << index;
            outputLine+= sourceLine.mid(index + commentEnd.length());
            qDebug() << __LINE__ <<  "o:" << outputLine;
            sourceLine = outputLine;
            qDebug() << __LINE__ <<  "s:" << sourceLine;
        }else{
            sourceLine.clear();
        }
    }
    return found;
}

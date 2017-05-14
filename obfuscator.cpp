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
        removeComments(source);
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

void Obfuscator::removeComments(const QString &source)
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
            QStringList list = sourceLine.split("//");

            assert(!list.isEmpty());

            QString outputLine = list[0] + "\r\n";
            destinationStream << outputLine;

            qDebug() << "source:" << sourceLine;
            qDebug() << "out:" << sourceLine;
        }
    }while(!sourceLine.isNull());

    destinationFile.close();
    sourceFile.close();

    sourceFile.remove();
    destinationFile.rename(source);
}

/** @file
  * @author Yunkin Ilya.
  */
#include "obfuscator.h"

#include <QFile>
#include <QTextStream>

#include <QDebug>

#include <assert.h>

#include "RemoveMultyLineComments.h"
#include "RemoveSingleLineComments.h"
#include "RemoveEmptyStrings.h"

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

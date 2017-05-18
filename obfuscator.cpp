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
#include "RemoveTrailingSpacers.h"
#include "RemoveLeadingSpacers.h"
#include "RemoveInsideSpacers.h"
#include "RemoveLineSpliting.h"
#include "ReplaceByTrigraphs.h"
#include "RemoveLineFeed.h"
#include "ReplaceCharByDigit.h"

Obfuscator::Obfuscator()
{
}

void Obfuscator::operator()(QStringList &sourceList)
{
    foreach (const QString &source, sourceList) {
        qDebug() << source;
        run(source, RemoveTrailingSpacers());
        run(source, RemoveLeadingSpacers());
        run(source, RemoveInsideSpacers());
        run(source, RemoveLineSpliting());
        run(source, RemoveMultyLineComments());
        run(source, RemoveSingleLineComments());
        run(source, RemoveEmptyStrings());
        run(source, ReplaceCharByDigit());
        run(source, ReplaceByTrigraphs());
        run(source, RemoveLineFeed());
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

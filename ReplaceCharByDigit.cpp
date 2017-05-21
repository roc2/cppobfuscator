/** @file
  * @author Yunkin Ilya.
  */
#include "ReplaceCharByDigit.h"

#include <random>
#include <time.h>
#include <assert.h>

#include <QDebug>

#include <StringSplitter.h>
#include <QMap>

class ReplaceCharByDigitPrivate
{
    ReplaceCharByDigitPrivate(ReplaceCharByDigitPrivate &);
public:
    static std::default_random_engine randomEngine;
    QMap<QString, QChar> escMap;
    ReplaceCharByDigitPrivate();
};

std::default_random_engine ReplaceCharByDigitPrivate::randomEngine(time(NULL));

ReplaceCharByDigitPrivate::ReplaceCharByDigitPrivate()
{
    escMap.insert("\\'", '\'');
    escMap.insert("\\", '\"');
    escMap.insert("\\?", '\?');
    escMap.insert("\\\\", '\\');
    escMap.insert("\\0", '\0');
    escMap.insert("\\a", '\a');
    escMap.insert("\\b", '\b');
    escMap.insert("\\f", '\f');
    escMap.insert("\\n", '\n');
    escMap.insert("\\r", '\r');
    escMap.insert("\\t", '\t');
    escMap.insert("\\v", '\v');
}

ReplaceCharByDigit::ReplaceCharByDigit()
{
    privateMembers = new ReplaceCharByDigitPrivate;
}

ReplaceCharByDigit::~ReplaceCharByDigit()
{
    delete privateMembers;
}

void ReplaceCharByDigit::operator()(QTextStream &sourceStream,
                                    QTextStream &destinationStream)
{
    QString sourceLine;

    do{
        sourceLine = sourceStream.readLine();
        qDebug() << __LINE__ << sourceLine;
        if((!sourceLine.isNull()) && (!sourceLine.isEmpty())){
            QString outString = replaceBetween(sourceLine, '\"');
            outString = replaceBetween(outString, '\'');

            destinationStream << outString;
        }else{
            destinationStream << sourceLine;
        }
        destinationStream << "\r\n";
    }while(!sourceLine.isNull());
}

QString ReplaceCharByDigit::getReplacer(const QString &symbol)
{
    QString replacer = symbol;

    if(symbol.length() == 2){
        qDebug() << __LINE__ << replacer;
        QMap<QString, QChar>::iterator it =
                privateMembers->escMap.find(symbol);

        assert(it != privateMembers->escMap.end());

        replacer = getReplacer(*it);
    }else if(symbol.length() == 1){
        qDebug() << __LINE__ << replacer;
        replacer = getReplacer(symbol[0]);
    }else{
    }

    qDebug() << __LINE__ << replacer;
    return replacer;
}

QString ReplaceCharByDigit::getReplacer(QChar symbol)
{
    QString replacer = symbol;

    qDebug() << __LINE__ << replacer;
    bool hexNotOct = privateMembers->randomEngine() % 2 == 0;
    if(hexNotOct){
        replacer = QString("\\x") +
                QString::number(symbol.unicode(), 16);
    }else{
        replacer = QString("\\") +
                QString::number(symbol.unicode(), 8);
    }

    qDebug() << __LINE__ << replacer;
    return replacer;
}


QString ReplaceCharByDigit::replaceBetween(const QString &sourceLine, char quote)
{
    QString outString;
    bool inQuotes = false;
    StringSplitter splitter(sourceLine);

    while (!splitter.isEnd()) {
        QString symbol = splitter.getSymbol();
        QString replacer = symbol;
        qDebug() << __LINE__ << symbol;
        if(inQuotes){
            if(symbol == QString(quote)){
                inQuotes = false;
            }else{
                replacer = getReplacer(symbol);
            }
        }else{
            if(symbol == QString(quote)){
                inQuotes = true;
            }
        }

        outString+= replacer;
    }

    qDebug() << __LINE__ << outString;
    return outString;
}


#include "ReplaceCharByDigit.h"

#include <random>
#include <time.h>

struct ReplaceCharByDigitPrivate
{
    static std::default_random_engine randomEngine;
};

std::default_random_engine ReplaceCharByDigitPrivate::randomEngine(time(NULL));

void ReplaceCharByDigit::operator()(QTextStream &sourceStream,
                                    QTextStream &destinationStream)
{
    QString sourceLine;

    do{
        sourceLine = sourceStream.readLine();
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

QString ReplaceCharByDigit::getReplacer(QChar currentChar, QChar previousChar)
{
    QString replacer = currentChar;
    bool isNotEscape = previousChar != '\\';
    bool isNotSlash = currentChar != '\\';

    if(isNotSlash && isNotEscape){
        if(currentChar == '\"'){
        }else{
            bool hexNotOct = privateMembers->randomEngine() % 2 == 0;
            if(hexNotOct){
                replacer = QString("\\x") +
                        QString::number(int(currentChar.toLatin1()), 16);
            }else{
                replacer = QString("\\") +
                        QString::number(int(currentChar.toLatin1()), 8);
            }
        }
    }else{
    }

    return replacer;
}

QString ReplaceCharByDigit::replaceBetween(const QString &sourceLine, char quote)
{
    QString outString;
    bool inQuotes = false;
    QChar previousChar = ' ';
    foreach (QChar c, sourceLine) {
        QString replacer = c;
        if(inQuotes){
            if(c == quote){
                inQuotes = false;
            }else{
                replacer = getReplacer(c, previousChar);
            }
        }else{
            if(c == quote){
                inQuotes = true;
            }
        }

        outString+= replacer;
        previousChar = c;
    }

    return outString;
}


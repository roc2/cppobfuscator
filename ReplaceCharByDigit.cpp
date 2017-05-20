#include "ReplaceCharByDigit.h"

#include <random>
#include <time.h>

#include <QDebug>

class StringSplitter
{
    StringSplitter();
    StringSplitter(StringSplitter&);
    const QString &line;
    QString::const_iterator it;
public:
    StringSplitter(const QString &line);
    QString getSymbol();
    bool isEnd();
    bool isTwoCharEcsSecond(const QChar &c);
    bool isHexOrUnicodeSecond(const QChar &c);
    bool isHexDigit(const QChar &c);
};

StringSplitter::StringSplitter(const QString &line) :
    line(line),
    it(line.begin())
{
}

QString StringSplitter::getSymbol()
{
    QString output;
    if(it != line.end()){
        QString::const_iterator firstIt = it;
        output += *firstIt;
        ++it;
        if((*firstIt) != '\\'){
        }else{// It is an escape sequence
            bool isHex = false;
            while(it != line.end()){
                const QChar &c = *it;
                bool itIsASecond = output.size() == 1;
                if(itIsASecond){
                    if(c.isDigit()){
                        output+= c;
                        ++it;
                    }else if (isTwoCharEcsSecond(c)){
                        output+= c;
                        ++it;
                        break;
                    }else if(isHexOrUnicodeSecond(c)){
                        isHex = true;
                        output+= c;
                        ++it;
                    }else{
                        break;
                    }
                }else //It should be a hex or oct number
                {
                    if(isHex){
                        if(isHexDigit(c)){
                            output+= c;
                            ++it;
                        }else{
                            break;
                        }
                    }else{
                        if(c.isDigit() && (c <= '7') && (output.length() < 4)){
                            output+= c;
                            ++it;
                        }else{
                            break;
                        }
                    }
                }
            }
        }
    }
    return output;
}

bool StringSplitter::isTwoCharEcsSecond(const QChar &c)
{
    return (c == '\'') ||
            (c == '\"') ||
            (c == '?') ||
            (c == '\\') ||
            (c == 'a') ||
            (c == 'b') ||
            (c == 'f') ||
            (c == 'n') ||
            (c == 'r') ||
            (c == 't') ||
            (c == 'v');
}

bool StringSplitter::isHexOrUnicodeSecond(const QChar &c)
{
    return (c == 'x') ||
            (c == 'u') ||
            (c == 'U');
}

bool StringSplitter::isHexDigit(const QChar &c)
{
    return c.isDigit() ||
            (c.toLower() == 'a') ||
            (c.toLower() == 'b') ||
            (c.toLower() == 'c') ||
            (c.toLower() == 'd') ||
            (c.toLower() == 'e') ||
            (c.toLower() == 'f');
}

bool StringSplitter::isEnd()
{
    return it == line.end();
}

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

QString ReplaceCharByDigit::getReplacer(QString symbol)
{
    QString replacer = symbol;

    if(symbol.length() == 1){
        bool hexNotOct = privateMembers->randomEngine() % 2 == 0;
        if(hexNotOct){
            replacer = QString("\\x") +
                    QString::number(symbol[0].unicode(), 16);
        }else{
            replacer = QString("\\") +
                    QString::number(symbol[0].unicode(), 8);
        }
    }else{
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


/** @file
  * @author Yunkin Ilya.
  */
#include "StringSplitter.h"

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

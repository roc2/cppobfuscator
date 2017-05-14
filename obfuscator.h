#ifndef OBFUSCATOR_H
#define OBFUSCATOR_H

#include <QString>
#include <QStringList>

class Obfuscator
{        
private:
    Obfuscator(Obfuscator&);
    QString getTmpFilename(const QString &source);
    void removeComments(const QString &source);
    QString removeCommentsFromLine(const QString &sourceLine);
public:
    Obfuscator();
    /**
     * @brief Call it to obfuscate your files.
     * @param sourceList - victims list.
     */
    void operator()(QStringList &sourceList);
};

#endif // OBFUSCATOR_H

#ifndef OBFUSCATOR_H
#define OBFUSCATOR_H

#include <QString>
#include <QStringList>

class Obfuscator
{        
private:
    Obfuscator(Obfuscator&);
    QString getTmpFilename(const QString &source);
    void removeSingleLineComments(const QString &source);
    QString removeSingleLineCommentsFromLine(const QString &sourceLine);
    void removeMultyLineComments(const QString &source);
    void removeMultyLineCommentsR(QString &sourceLine, bool &inComment);
public:
    Obfuscator();
    /**
     * @brief Call it to obfuscate your files.
     * @param sourceList - victims list.
     */
    void operator()(QStringList &sourceList);
};

#endif // OBFUSCATOR_H

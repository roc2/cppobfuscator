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
    /**
     * @brief Recursive function. It works with one text line.
     * @param sourceLine - Text to modyfying.
     * @param inComment - true if sourceLine begins in comment.
     * @return true if comment tags found.
     */
    bool removeMultyLineCommentsR(QString &sourceLine, bool &inComment);

    void removeEmptyStrings(const QString &source);
public:
    Obfuscator();
    /**
     * @brief Call it to obfuscate your files.
     * @param sourceList - victims list.
     */
    void operator()(QStringList &sourceList);
};

#endif // OBFUSCATOR_H

#ifndef OBFUSCATOR_H
#define OBFUSCATOR_H

#include <QString>
#include <QStringList>

class Obfuscator
{        
private:
    Obfuscator(Obfuscator&);
    QString getTmpFilename(const QString &source);

    template <class Functor>
    /**
     * @brief Opens text streams, runs functor f, closes streams.
     * @param source - Source file name.
     * @param f - Obfuscation stage's functor.
     */
    void run(const QString &source, Functor f);
public:
    Obfuscator();
    /**
     * @brief Call it to obfuscate your files.
     * @param sourceList - victims list.
     */
    void operator()(QStringList &sourceList);
};

#endif // OBFUSCATOR_H

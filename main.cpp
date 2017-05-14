#include <QCoreApplication>

#include "obfuscator.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Obfuscator obfuscator;

    obfuscator(QStringList() << "/home/user/victim.cpp");
}

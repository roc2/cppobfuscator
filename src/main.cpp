/** @file
  * @author Yunkin Ilya.
  */
#include <QCoreApplication>
#include <QDebug>

#include "obfuscator.h"

int main(int argc, char *argv[])
{
    Obfuscator obfuscator;

    if(argc > 1){
        QStringList list;
        for(int i = 1; i < argc; i++){
            list << QString(argv[i]);
        }
        obfuscator(list);
    }else{
        qDebug() << "File list is empty";
    }
}

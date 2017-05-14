/** @file
  * @author Yunkin Ilya.
  */
#ifndef REMOVEEMPTYSTRINGS_H
#define REMOVEEMPTYSTRINGS_H

#include <QTextStream>

class RemoveEmptyStrings
{
public:
    void operator()(QTextStream &sourceStream,
                    QTextStream &destinationStream);
};

#endif // REMOVEEMPTYSTRINGS_H

/** @file
  * @author Yunkin Ilya.
  */
#ifndef REMOVETRAILINGSPACERS_H
#define REMOVETRAILINGSPACERS_H

#include <QTextStream>

class RemoveTrailingSpacers
{
public:
    void operator()(QTextStream &sourceStream,
                    QTextStream &destinationStream);
};

#endif // REMOVETRAILINGSPACERS_H

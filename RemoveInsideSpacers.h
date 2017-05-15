#ifndef REMOVEINSIDESPACERS_H
#define REMOVEINSIDESPACERS_H

#include <QTextStream>

class RemoveInsideSpacers
{
public:
    void operator()(QTextStream &sourceStream,
                    QTextStream &destinationStream);
};

#endif // REMOVEINSIDESPACERS_H

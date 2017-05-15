#ifndef REMOVELEADINGSPACERS_H
#define REMOVELEADINGSPACERS_H

#include <QTextStream>

class RemoveLeadingSpacers
{
public:
    void operator()(QTextStream &sourceStream,
                    QTextStream &destinationStream);
};

#endif // REMOVELEADINGSPACERS_H

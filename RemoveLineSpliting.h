#ifndef REMOVELINESPLITING_H
#define REMOVELINESPLITING_H

#include <QTextStream>

class RemoveLineSpliting
{
public:
    void operator()(QTextStream &sourceStream,
                    QTextStream &destinationStream);
};

#endif // REMOVELINESPLITING_H

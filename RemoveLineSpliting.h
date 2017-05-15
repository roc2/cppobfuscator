/** @file
  * @author Yunkin Ilya.
  */
#ifndef REMOVELINESPLITING_H
#define REMOVELINESPLITING_H

#include <QTextStream>

class RemoveLineSpliting
{
public:
    /// Trailing spacers should be deleted before calling this operator.
    void operator()(QTextStream &sourceStream,
                    QTextStream &destinationStream);
};

#endif // REMOVELINESPLITING_H

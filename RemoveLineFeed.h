/** @file
  * @author Yunkin Ilya.
  */
#ifndef REMOVELINEFEED_H
#define REMOVELINEFEED_H

#include <QTextStream>

class RemoveLineFeed
{
public:
    /// Trailing spacers and line splits
    /// should be deleted before calling this operator.
    void operator()(QTextStream &sourceStream,
                    QTextStream &destinationStream);
};
#endif // REMOVELINEFEED_H

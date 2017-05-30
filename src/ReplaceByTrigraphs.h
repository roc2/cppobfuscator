/** @file
  * @author Yunkin Ilya.
  */
#ifndef REPLACEBYTRIGRAPHS_H
#define REPLACEBYTRIGRAPHS_H

#include <QTextStream>
#include <QMap>

class ReplaceByTrigraphs
{
    QMap<QChar, QString> trigraphsMap;
public:
    ReplaceByTrigraphs();
    void operator()(QTextStream &sourceStream,
                    QTextStream &destinationStream);
};

#endif // REPLACEBYTRIGRAPHS_H

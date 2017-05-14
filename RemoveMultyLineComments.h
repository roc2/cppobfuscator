/** @file
  * @author Yunkin Ilya.
  */
#ifndef REMOVEMULTYLINECOMMENTS_H
#define REMOVEMULTYLINECOMMENTS_H

#include <QTextStream>

class RemoveMultyLineComments
{
public:
    void operator()(QTextStream &sourceStream,
                    QTextStream &destinationStream);
    /**
     * @brief Recursive function. It works with one text line.
     * @param sourceLine - Text to modyfying.
     * @param inComment - true if sourceLine begins in comment.
     * @return true if comment tags found.
     */
    bool removeMultyLineCommentsR(QString &sourceLine, bool &inComment);

};

#endif // REMOVEMULTYLINECOMMENTS_H

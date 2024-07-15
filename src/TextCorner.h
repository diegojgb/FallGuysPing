#ifndef TEXTCORNER_H
#define TEXTCORNER_H

#include <QObject>

class TextCorner
{
    Q_GADGET

public:
    enum Value {
        TopLeft,
        TopRight,
        BottomLeft,
        BottomRight,
        Custom
    };
    Q_ENUM(Value)
};

#endif // TEXTCORNER_H

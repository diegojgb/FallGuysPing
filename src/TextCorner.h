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

    static QString textCornerToString(const Value value)
    {
        switch(value) {
        case TextCorner::Value::TopLeft:
            return "TopLeft";
        case TextCorner::Value::TopRight:
            return "TopRight";
        case TextCorner::Value::BottomLeft:
            return "BottomLeft";
        case TextCorner::Value::BottomRight:
            return "BottomRight";
        case TextCorner::Value::Custom:
            return "Custom";
        default:
            return "invalid";
        }
    }

    static Value textCornerFromString(const QString& value)
    {
        if (value == "TopLeft")
            return TextCorner::Value::TopLeft;
        if (value == "TopRight")
            return TextCorner::Value::TopRight;
        if (value == "BottomLeft")
            return  TextCorner::Value::BottomLeft;
        if (value == "BottomRight")
            return TextCorner::Value::BottomRight;

        return TextCorner::Value::Custom;
    }
};

#endif // TEXTCORNER_H

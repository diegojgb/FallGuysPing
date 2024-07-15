#ifndef SETTINGS_H
#define SETTINGS_H

#include "TextCorner.h"

#include <QObject>

class Settings : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool startMinimized READ startMinimized WRITE setStartMinimized NOTIFY startMinimizedChanged FINAL)
    Q_PROPERTY(bool draggableText READ draggableText WRITE setDraggableText NOTIFY draggableTextChanged FINAL)
    Q_PROPERTY(TextCorner::Value textCorner READ textCorner WRITE setTextCorner NOTIFY textCornerChanged FINAL)

public:
    explicit Settings(QObject* parent = nullptr);

    bool startMinimized() const;
    void setStartMinimized(bool newStartMinimized);

    bool draggableText() const;
    void setDraggableText(bool newDraggableText);

    TextCorner::Value textCorner() const;
    void setTextCorner(const TextCorner::Value &newTextCorner);

signals:
    void startMinimizedChanged();
    void draggableTextChanged();
    void textCornerChanged();

private:
    bool m_startMinimized = false;
    bool m_draggableText = false;
    TextCorner::Value m_textCorner = TextCorner::Value::TopRight;
};

#endif // SETTINGS_H

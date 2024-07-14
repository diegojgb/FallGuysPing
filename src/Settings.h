#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>

class Settings : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool startMinimized READ startMinimized WRITE setStartMinimized NOTIFY startMinimizedChanged FINAL)
    Q_PROPERTY(bool draggableText READ draggableText WRITE setDraggableText NOTIFY draggableTextChanged FINAL)

public:
    explicit Settings(QObject* parent = nullptr);

    bool startMinimized() const;
    void setStartMinimized(bool newStartMinimized);

    bool draggableText() const;
    void setDraggableText(bool newDraggableText);

signals:
    void startMinimizedChanged();
    void draggableTextChanged();

private:
    bool m_startMinimized = false;
    bool m_draggableText = false;
};

#endif // SETTINGS_H

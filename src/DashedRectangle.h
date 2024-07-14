#ifndef DASHEDRECTANGLE_H
#define DASHEDRECTANGLE_H

#include <QObject>
#include <QQuickPaintedItem>
#include <QPainter>

class DashedRectangle : public QQuickPaintedItem
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(QColor borderColor READ borderColor WRITE setBorderColor NOTIFY borderColorChanged FINAL)

public:
    explicit DashedRectangle(QQuickItem* parent = nullptr);

    virtual void paint(QPainter* painter);

    QColor borderColor() const;
    void setBorderColor(const QColor& newBorderColor);

signals:
    void borderColorChanged();

private:
    QColor m_borderColor;
};

#endif // DASHEDRECTANGLE_H

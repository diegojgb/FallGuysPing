#include "DashedRectangle.h"

DashedRectangle::DashedRectangle(QQuickItem* parent): QQuickPaintedItem(parent)
{}

void DashedRectangle::paint(QPainter *painter)
{
    painter->setPen(QPen(m_borderColor, 1, Qt::DashLine));
    painter->drawRect(0, 0, width() - 1, height() - 1);
}

QColor DashedRectangle::borderColor() const
{
    return m_borderColor;
}

void DashedRectangle::setBorderColor(const QColor &newBorderColor)
{
    if (m_borderColor == newBorderColor)
        return;

    m_borderColor = newBorderColor;

    emit borderColorChanged();
}

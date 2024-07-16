#include "Settings.h"

Settings::Settings(QObject* parent)
    : QObject{parent}
{}

bool Settings::startMinimized() const
{
    return m_startMinimized;
}

void Settings::setStartMinimized(bool newStartMinimized)
{
    if (m_startMinimized == newStartMinimized)
        return;

    m_startMinimized = newStartMinimized;

    emit startMinimizedChanged();
}

bool Settings::draggableText() const
{
    return m_draggableText;
}

void Settings::setDraggableText(bool newDraggableText)
{
    if (m_draggableText == newDraggableText)
        return;

    m_draggableText = newDraggableText;

    emit draggableTextChanged();
}

TextCorner::Value Settings::textCorner() const
{
    return m_textCorner;
}

void Settings::setTextCorner(const TextCorner::Value &newTextCorner)
{
    if (m_textCorner == newTextCorner)
        return;

    m_textCorner = newTextCorner;

    emit textCornerChanged();
}

QColor Settings::textColor() const
{
    return m_textColor;
}

void Settings::setTextColor(const QColor &newTextColor)
{
    if (m_textColor == newTextColor)
        return;

    m_textColor = newTextColor;

    emit textColorChanged();
}

int Settings::textSize() const
{
    return m_textSize;
}

void Settings::setTextSize(int newTextSize)
{
    if (m_textSize == newTextSize)
        return;

    m_textSize = newTextSize;

    emit textSizeChanged();
}

bool Settings::textOutline() const
{
    return m_textOutline;
}

void Settings::setTextOutline(bool newTextOutline)
{
    if (m_textOutline == newTextOutline)
        return;

    m_textOutline = newTextOutline;

    emit textOutlineChanged();
}

bool Settings::boldText() const
{
    return m_boldText;
}

void Settings::setBoldText(bool newBoldText)
{
    if (m_boldText == newBoldText)
        return;

    m_boldText = newBoldText;

    emit boldTextChanged();
}

QString Settings::fontFamily() const
{
    return m_fontFamily;
}

void Settings::setFontFamily(const QString &newFontFamily)
{
    if (m_fontFamily == newFontFamily)
        return;

    m_fontFamily = newFontFamily;

    emit fontFamilyChanged();
}

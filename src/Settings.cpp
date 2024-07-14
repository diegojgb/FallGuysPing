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

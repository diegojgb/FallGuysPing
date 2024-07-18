#include "Settings.h"

Settings::Settings(QObject* parent)
    : QObject{parent},
      m_settingsFile{QApplication::applicationDirPath() + "/config.ini"},
      m_qSettings{QSettings(m_settingsFile, QSettings::IniFormat)}
{
    loadSettings();
}

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

    m_qSettings.setValue("DraggableText", newDraggableText);

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

    m_qSettings.setValue("TextCorner", textCornerToString(newTextCorner));

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

    m_qSettings.setValue("TextColor", newTextColor.name());

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

    m_qSettings.setValue("TextSize", newTextSize);

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

    m_qSettings.setValue("TextOutline", newTextOutline);

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

    m_qSettings.setValue("BoldText", newBoldText);

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

    m_qSettings.setValue("FontFamily", newFontFamily);

    emit fontFamilyChanged();
}

void Settings::loadSettings()
{
    m_draggableText = m_qSettings.value("DraggableText", false).toBool();

    auto str = m_qSettings.value("TextCorner", "TopRight").toString();
    m_textCorner = textCornerFromString(str);

    m_textColor = QColor(m_qSettings.value("TextColor", "#fff").toString());
    m_textSize = m_qSettings.value("TextSize", 14).toInt();
    m_textOutline = m_qSettings.value("TextOutline", false).toBool();
    m_boldText = m_qSettings.value("BoldText", true).toBool();
    m_fontFamily =m_qSettings.value("FontFamily", "Segoe UI").toString();
}

// void Settings::saveSettings()
// {

//     QSettings settings(FileName, QSettings::IniFormat);
// }

QString Settings::textCornerToString(TextCorner::Value value)
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

TextCorner::Value Settings::textCornerFromString(QString &value)
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

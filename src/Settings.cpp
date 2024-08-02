#include "Settings.h"

Settings::Settings(QObject* parent)
    : QObject{parent}
    , m_settingsFile{QApplication::applicationDirPath() + "/config.ini"}
    , m_qSettings{QSettings(m_settingsFile, QSettings::IniFormat)}
    , m_startMinimized{m_qSettings.value("StartMinimized", false).toBool()}
    , m_draggableText{m_qSettings.value("DraggableText", false).toBool()}
    , m_textColor{QColor(m_qSettings.value("TextColor", "#fff").toString())}
    , m_textSize{m_qSettings.value("TextSize", 14).toInt()}
    , m_textOutline{m_qSettings.value("TextOutline", false).toBool()}
    , m_boldText{m_qSettings.value("BoldText", true).toBool()}
    , m_fontFamily{m_qSettings.value("FontFamily", "Segoe UI").toString()}
    , m_alwaysVisible{m_qSettings.value("AlwaysVisible", false).toBool()}
    , m_textCorner{TextCorner::textCornerFromString(m_qSettings.value("TextCorner", "TopRight").toString())}
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

    m_qSettings.setValue("StartMinimized", newStartMinimized);

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

    m_qSettings.setValue("TextCorner", TextCorner::textCornerToString(newTextCorner));

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

// Settings that need to be initialized through the setter.
void Settings::loadSettings()
{
    setPingInterval(m_qSettings.value("PingInterval", 3000).toInt()); // Setter needs to be called for Pinger/PingWorker to update.
    setQuitOnGameExit(m_qSettings.value("QuitOnGameExit", false).toBool()); // Setter needs to be called for FileWatcher to update.
    setLocationToastEnabled(m_qSettings.value("LocationToastEnabled", true).toBool());
}

void Settings::savePosition(QPoint point)
{
    m_qSettings.setValue("CustomX", point.x());
    m_qSettings.setValue("CustomY", point.y());
}

QPoint Settings::getSavedPosition()
{
    int x = m_qSettings.value("CustomX").toInt();
    int y = m_qSettings.value("CustomY").toInt();

    return QPoint(x, y);
}

bool Settings::alwaysVisible() const
{
    return m_alwaysVisible;
}

void Settings::setAlwaysVisible(bool newAlwaysVisible)
{
    if (m_alwaysVisible == newAlwaysVisible)
        return;

    m_alwaysVisible = newAlwaysVisible;

    m_qSettings.setValue("AlwaysVisible", newAlwaysVisible);

    emit alwaysVisibleChanged();
}

int Settings::pingInterval() const
{
    return m_pingInterval;
}

void Settings::setPingInterval(int newPingInterval)
{
    if (m_pingInterval == newPingInterval)
        return;

    m_pingInterval = newPingInterval;

    emit pingIntervalChangedOverload(newPingInterval);
    m_qSettings.setValue("PingInterval", newPingInterval);

    emit pingIntervalChanged();
}

bool Settings::quitOnGameExit() const
{
    return m_quitOnGameExit;
}

void Settings::setQuitOnGameExit(bool newQuitOnGameExit)
{
    if (m_quitOnGameExit == newQuitOnGameExit)
        return;

    m_quitOnGameExit = newQuitOnGameExit;

    emit quitOnGameExitChangedOverload(newQuitOnGameExit);
    m_qSettings.setValue("QuitOnGameExit", newQuitOnGameExit);

    emit quitOnGameExitChanged();
}

bool Settings::locationToastEnabled() const
{
    return m_locationToastEnabled;
}

void Settings::setLocationToastEnabled(bool newLocationToastEnabled)
{
    if (m_locationToastEnabled == newLocationToastEnabled)
        return;

    m_locationToastEnabled = newLocationToastEnabled;

    emit locationToastEnabledChanged();
}

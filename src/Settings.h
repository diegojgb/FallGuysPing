#ifndef SETTINGS_H
#define SETTINGS_H

#include "TextCorner.h"

#include <QApplication>
#include <QColor>
#include <QObject>
#include <QSettings>

class Settings : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool startMinimized READ startMinimized WRITE setStartMinimized NOTIFY startMinimizedChanged FINAL)
    Q_PROPERTY(bool draggableText READ draggableText WRITE setDraggableText NOTIFY draggableTextChanged FINAL)
    Q_PROPERTY(TextCorner::Value textCorner READ textCorner WRITE setTextCorner NOTIFY textCornerChanged FINAL)
    Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor NOTIFY textColorChanged FINAL)
    Q_PROPERTY(int textSize READ textSize WRITE setTextSize NOTIFY textSizeChanged FINAL)
    Q_PROPERTY(bool textOutline READ textOutline WRITE setTextOutline NOTIFY textOutlineChanged FINAL)
    Q_PROPERTY(bool boldText READ boldText WRITE setBoldText NOTIFY boldTextChanged FINAL)
    Q_PROPERTY(QString fontFamily READ fontFamily WRITE setFontFamily NOTIFY fontFamilyChanged FINAL)

public:
    explicit Settings(QObject* parent = nullptr);

    bool startMinimized() const;
    void setStartMinimized(bool newStartMinimized);

    bool draggableText() const;
    void setDraggableText(bool newDraggableText);

    TextCorner::Value textCorner() const;
    void setTextCorner(const TextCorner::Value &newTextCorner);

    QColor textColor() const;
    void setTextColor(const QColor &newTextColor);

    int textSize() const;
    void setTextSize(int newTextSize);

    bool textOutline() const;
    void setTextOutline(bool newTextOutline);

    bool boldText() const;
    void setBoldText(bool newBoldText);

    QString fontFamily() const;
    void setFontFamily(const QString &newFontFamily);

    void loadSettings();
    // void saveSettings();
    QString textCornerToString(TextCorner::Value value);
    TextCorner::Value textCornerFromString(QString& value);

signals:
    void startMinimizedChanged();
    void draggableTextChanged();
    void textCornerChanged();
    void textColorChanged();
    void textSizeChanged();
    void textOutlineChanged();
    void boldTextChanged();
    void fontFamilyChanged();

private:
    bool m_startMinimized = false;
    bool m_draggableText{};
    TextCorner::Value m_textCorner = TextCorner::Value::TopRight;
    QColor m_textColor;
    int m_textSize{};
    bool m_textOutline{};
    bool m_boldText{};
    QString m_fontFamily;
    QString m_settingsFile;
    QSettings m_qSettings;
};

#endif // SETTINGS_H

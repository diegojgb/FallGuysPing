#ifndef TRAYICON_H
#define TRAYICON_H

#include <QObject>
#include <QAction>
#include <QMenu>
#include <QApplication>
#include <QSystemTrayIcon>
#include <QQuickWindow>
#include <Windows.h>


class TrayIcon: public QObject
{
    Q_OBJECT

public:
    explicit TrayIcon(QObject* parent, QObject* root, HWND hwnd);

public slots:
    void trayIconActivated(QSystemTrayIcon::ActivationReason reason);
    void bringToTop();

signals:
    void singleClick();

private:
    QObject* m_root;
    HWND m_hwnd;
    QSystemTrayIcon* m_trayIcon;

    QMenu* createMenu();
};

#endif // TRAYICON_H

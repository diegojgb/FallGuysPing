#include "TrayIcon.h"


TrayIcon::TrayIcon(QObject* parent, QObject* root, HWND hwnd)
    : QObject{parent},
      m_root{root},
      m_hwnd{hwnd},
      m_trayIcon{new QSystemTrayIcon(root)}
{
    QMenu* trayIconMenu = createMenu();

    m_trayIcon->setContextMenu(trayIconMenu);
    m_trayIcon->setIcon(QIcon(":/assets/ping-icon.ico"));
    m_trayIcon->setToolTip("FallGuysPing");
    m_trayIcon->show();

    QQuickWindow* windowRoot = qobject_cast<QQuickWindow*>(m_root);

    connect(m_trayIcon, &QSystemTrayIcon::activated, this, &TrayIcon::trayIconActivated);
    connect(this, &TrayIcon::singleClick, windowRoot, &QQuickWindow::showNormal);
    connect(this, &TrayIcon::singleClick, this, &TrayIcon::bringToTop);
}

void TrayIcon::trayIconActivated(QSystemTrayIcon::ActivationReason reason)
{
    if (reason == QSystemTrayIcon::Trigger)
        emit singleClick();
}

void TrayIcon::bringToTop()
{
    SetForegroundWindow(m_hwnd);
}

QMenu* TrayIcon::createMenu()
{
    QQuickWindow* windowRoot = qobject_cast<QQuickWindow*>(m_root);

    QAction* restoreAction = new QAction(QObject::tr("&Restore"), m_root);
    m_root->connect(restoreAction, &QAction::triggered, windowRoot, &QQuickWindow::showNormal);
    m_root->connect(restoreAction, &QAction::triggered, this, &TrayIcon::bringToTop);

    QAction* quitAction = new QAction(QObject::tr("&Quit"), m_root);
    m_root->connect(quitAction, &QAction::triggered, qApp, &QCoreApplication::quit);

    QMenu* trayIconMenu = new QMenu();
    trayIconMenu->addAction(restoreAction);
    trayIconMenu->addAction(quitAction);
    trayIconMenu->setStyleSheet("QMenu { background-color: white; padding: 2px; }\
                                QMenu::item { color: black; background-color: transparent; padding: 4px 40px 4px 12px; }\
                                QMenu::item:selected { color: white; background-color: #0078d4; border: 0px; }");

    return trayIconMenu;
}

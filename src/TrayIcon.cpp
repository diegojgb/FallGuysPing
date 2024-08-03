#include "TrayIcon.h"


TrayIcon::TrayIcon(QObject* parent,  QQuickWindow *rootWindow)
    : QObject{parent}
    , m_rootWindow{rootWindow}
    , m_hwnd{(HWND)rootWindow->winId()}
    , m_trayIcon{new QSystemTrayIcon(rootWindow)}
{
    QMenu* trayIconMenu = createMenu();

    m_trayIcon->setContextMenu(trayIconMenu);
    m_trayIcon->setIcon(QIcon(":/assets/ping-icon.ico"));
    m_trayIcon->setToolTip("FallGuysPing");
    m_trayIcon->show();

    initWinToast();

    connect(m_trayIcon, &QSystemTrayIcon::activated, this, &TrayIcon::trayIconActivated);
    connect(this, &TrayIcon::singleClicked, this, &TrayIcon::showWindow);
}

void TrayIcon::trayIconActivated(QSystemTrayIcon::ActivationReason reason)
{
    if (reason == QSystemTrayIcon::Trigger)
        emit singleClicked();
}

void TrayIcon::bringToTop()
{
    SetForegroundWindow(m_hwnd);
}

void TrayIcon::showWindow()
{
    m_rootWindow->showNormal();
    bringToTop();
}

QMenu* TrayIcon::createMenu()
{
    QAction* restoreAction = new QAction(QObject::tr("&Restore"), m_rootWindow);
    connect(restoreAction, &QAction::triggered, this, &TrayIcon::showWindow);

    QAction* quitAction = new QAction(QObject::tr("&Quit"), m_rootWindow);
    connect(quitAction, &QAction::triggered, qApp, &QCoreApplication::quit);

    QMenu* trayIconMenu = new QMenu();
    trayIconMenu->addAction(restoreAction);
    trayIconMenu->addAction(quitAction);

    return trayIconMenu;
}

void TrayIcon::initWinToast()
{
    if (!WinToast::isCompatible())
        Utils::errorExit("[WinToast]: Error, your system in not supported!");

    WinToast::instance()->setAppName(L"FallGuysPing");
    const auto aumi = WinToast::configureAUMI(L"diegojgb", L"FallGuysPing", L"ToastNotifications");
    WinToast::instance()->setAppUserModelId(aumi);
    WinToast::instance()->setShortcutPolicy(WinToast::ShortcutPolicy::SHORTCUT_POLICY_IGNORE);

    // Add icon and name to registry, so Windows can display them in toast notifications.
    if (!Registry::createRegistryKey(HKEY_CURRENT_USER, L"Software\\Classes\\AppUserModelId\\diegojgb.FallGuysPing.ToastNotifications"))
    {
        Utils::errorExit("[Registry]: Error opening or creating new Registry key");
    }

    if (!Registry::writeStringInRegistry(
            HKEY_CURRENT_USER,
            L"Software\\Classes\\AppUserModelId\\diegojgb.FallGuysPing.ToastNotifications",
            L"DisplayName",
            L"FallGuysPing"))
    {
        Utils::errorExit("[Registry]: Error saving toast DisplayName Registry value");
    }

    QString defaultIcon = QCoreApplication::applicationDirPath() + "/assets/ping-icon.png";
    defaultIcon.replace("/", "\\");
    if (!Registry::writeStringInRegistry(
            HKEY_CURRENT_USER,
            L"Software\\Classes\\AppUserModelId\\diegojgb.FallGuysPing.ToastNotifications",
            L"IconUri",
            defaultIcon.toStdWString().c_str()))
    {
        Utils::errorExit("[Registry]: Error saving toast IconUri Regitry value");
    }

    if (!WinToast::instance()->initialize())
        Utils::errorExit("[WinToast]: Error, could not initialize WinToast!");
}

void TrayIcon::sendNotification(const WinToastTemplate &templ)
{
    if (WinToast::instance()->showToast(templ, new ToastHandler()) < 0)
    {
        Utils::errorExit("[WinToast]: Could not launch your toast notification!");
    }
}

void TrayIcon::sendNotification(const std::wstring title, const std::wstring subtitle, const std::wstring imagePath)
{
    WinToastTemplate templ = WinToastTemplate(WinToastTemplate::ImageAndText02);
    templ.setTextField(title, WinToastTemplate::FirstLine);
    templ.setTextField(subtitle, WinToastTemplate::SecondLine);
    templ.setImagePath(imagePath);

    sendNotification(templ);
}

#include "Manager.h"


Manager::Manager(QObject *parent)
    : QObject{parent}
{
    connect(&m_fileWatcher, &FileWatcher::ipFound, this, &Manager::onIpFound);
    connect(&m_fileWatcher, &FileWatcher::resetFound, this, &Manager::onResetFound);
}

void Manager::addFile(const QString& filePath)
{
    m_fileWatcher.addFilePath(filePath);
}

void Manager::initTrayIcon(QObject* parent, QObject* root, HWND& hwnd)
{
    if (m_trayIconInitialized)
        Utils::throwError("Tray icon can only be initialized once.");

    m_trayIcon = new TrayIcon(parent, root, hwnd);

    m_trayIconInitialized = true;
}

void Manager::onIpFound(const std::string& ip)
{
    m_pinger.start(ip);
}

void Manager::onResetFound()
{
    m_pinger.stop();
}

Pinger* Manager::pinger()
{
    return &m_pinger;
}

Settings* Manager::settings()
{
    return &m_settings;
}


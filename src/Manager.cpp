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

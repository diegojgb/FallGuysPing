#include "Manager.h"

#include <QDebug>


Manager* g_managerInstance = nullptr;

Manager::Manager(QObject *parent)
    : QObject{parent}, m_isGameForeground{isFallGuysForeground()}
{
    setForegroundWindowChangeHook();

    connect(&m_fileWatcher, &FileWatcher::ipFound, this, &Manager::onIpFound);
    connect(&m_fileWatcher, &FileWatcher::disconnectFound, this, &Manager::onDisconnectFound);
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

bool Manager::isProcessRunning(LPCTSTR& processName)
{
    bool exists = false;
    PROCESSENTRY32 entry;
    entry.dwSize = sizeof(PROCESSENTRY32);

    HANDLE hsnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if (Process32First(hsnap, &entry)) {
        do {
            if (!lstrcmpi(entry.szExeFile, processName)) {
                exists = true;
            }
        } while (Process32Next(hsnap, &entry));
    }

    CloseHandle(hsnap);
    return exists;
}

bool Manager::isFallGuysForeground()
{
    std::wstring title = getForegroundWindowTitle();

    return title == L"FallGuys_client";
}

void Manager::setForegroundWindowChangeHook()
{
    m_hEventHook = SetWinEventHook(EVENT_SYSTEM_FOREGROUND, EVENT_SYSTEM_FOREGROUND, NULL,
                                   WinEventProcCallback, 0, 0, WINEVENT_OUTOFCONTEXT | WINEVENT_SKIPOWNPROCESS);
}

std::wstring Manager::getForegroundWindowTitle()
{
    wchar_t wnd_title[256];

    HWND hwnd = GetForegroundWindow();
    GetWindowText(hwnd, wnd_title, sizeof(wnd_title));

    return wnd_title;
}

VOID CALLBACK Manager::WinEventProcCallback(HWINEVENTHOOK hWinEventHook,
                                   DWORD dwEvent,
                                   HWND hwnd,
                                   LONG idObject,
                                   LONG idChild,
                                   DWORD dwEventThread,
                                   DWORD dwmsEventTime)
{
    if (dwEvent == EVENT_SYSTEM_FOREGROUND) {
        g_managerInstance->setIsGameForeground(isFallGuysForeground());
    }
}

void Manager::onIpFound(const std::string& ip)
{
    m_pinger.start(ip);
}

void Manager::onDisconnectFound()
{
    m_pinger.stop();
}

bool Manager::isFallGuysRunning()
{
    LPCTSTR processName = TEXT("FallGuys_client_game.exe");
    return isProcessRunning(processName);
}

Pinger* Manager::pinger()
{
    return &m_pinger;
}

Settings* Manager::settings()
{
    return &m_settings;
}

bool Manager::isGameForeground() const
{
    return m_isGameForeground;
}

void Manager::setIsGameForeground(bool newIsGameForeground)
{
    if (m_isGameForeground == newIsGameForeground)
        return;

    m_isGameForeground = newIsGameForeground;

    emit isGameForegroundChanged();
}

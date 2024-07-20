#include "Manager.h"

#include <QDebug>

namespace {
    const wchar_t* const GAME_TITLE = L"FallGuys_client";
}

Manager* g_managerInstance = nullptr;

Manager::Manager(QObject *parent, WindowMode windowMode)
    : QObject{parent},
      m_isGameActive{isGameActiveCheck(windowMode)},
      m_windowMode{windowMode}
{
    if (windowMode != WindowMode::Foreground)
        setFocusedWindowChangeHook();

    if (windowMode != WindowMode::Focus)
        setForegroundWindowChangeHook();

    connect(&m_fileWatcher, &FileWatcher::ipFound, this, &Manager::onIpFound);
    connect(&m_fileWatcher, &FileWatcher::disconnectFound, this, &Manager::onDisconnectFound);
    connect(&m_settings, &Settings::pingIntervalChangedOverload, &m_pinger, &Pinger::onPingIntervalChanged);
    connect(&m_settings, &Settings::quitOnGameExitChangedOverload, &m_fileWatcher, &FileWatcher::setQuitOnGameExit);

    m_settings.loadSettings();
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

bool Manager::isGameActiveCheck(WindowMode mode)
{
    wchar_t wnd_title[256];
    bool isForeground = false;
    bool isFocused = false;
    
    if (mode != WindowMode::Foreground) {
        HWND focusHwnd = GetFocus();
        GetWindowText(focusHwnd, wnd_title, sizeof(wnd_title));
        isFocused = wcscmp(wnd_title, GAME_TITLE) == 0;
    }

    if (mode != WindowMode::Focus) {
        HWND foregroundHwnd = GetForegroundWindow();
        GetWindowText(foregroundHwnd, wnd_title, sizeof(wnd_title));
        isForeground = wcscmp(wnd_title, GAME_TITLE) == 0;
    }

    return isFocused || isForeground;
}

void Manager::setFocusedWindowChangeHook()
{
    m_hEventHookFocus = SetWinEventHook(EVENT_OBJECT_FOCUS,
                                   EVENT_OBJECT_FOCUS,
                                   NULL,
                                   WinFocusCallback,
                                   0,
                                   0,
                                   WINEVENT_OUTOFCONTEXT | WINEVENT_SKIPOWNPROCESS);
}

void Manager::setForegroundWindowChangeHook()
{
    m_hEventHookForeground = SetWinEventHook(EVENT_SYSTEM_FOREGROUND,
                                        EVENT_SYSTEM_FOREGROUND,
                                        NULL,
                                        WinForegroundCallback,
                                        0,
                                        0,
                                        WINEVENT_OUTOFCONTEXT | WINEVENT_SKIPOWNPROCESS);
}

VOID CALLBACK Manager::WinFocusCallback(HWINEVENTHOOK hWinEventHook,
                                   DWORD dwEvent,
                                   HWND hwnd,
                                   LONG idObject,
                                   LONG idChild,
                                   DWORD dwEventThread,
                                   DWORD dwmsEventTime)
{
    if (dwEvent == EVENT_OBJECT_FOCUS) {
        wchar_t windowTitle[256];
        GetWindowText(hwnd, windowTitle, sizeof(windowTitle));

        bool isGameFocused = wcscmp(windowTitle, GAME_TITLE) == 0;

        g_managerInstance->setIsGameActive(isGameFocused);
    }
}

void Manager::WinForegroundCallback(HWINEVENTHOOK hWinEventHook,
                                    DWORD dwEvent,
                                    HWND hwnd,
                                    LONG idObject,
                                    LONG idChild,
                                    DWORD dwEventThread,
                                    DWORD dwmsEventTime)
{
    if (dwEvent == EVENT_SYSTEM_FOREGROUND) {
        wchar_t windowTitle[256];
        GetWindowText(hwnd, windowTitle, sizeof(windowTitle));

        bool isGameForeground = wcscmp(windowTitle, GAME_TITLE) == 0;

        g_managerInstance->setIsGameActive(isGameForeground);
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

bool Manager::isGameRunning()
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

bool Manager::isGameActive() const
{
    return m_isGameActive;
}

void Manager::setIsGameActive(bool newIsGameActive)
{
    if (m_isGameActive == newIsGameActive)
        return;

    m_isGameActive = newIsGameActive;

    emit isGameActiveChanged();
}

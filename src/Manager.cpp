#include "Manager.h"


namespace {
    const wchar_t* const GAME_TITLE = L"FallGuys_client";
}

Manager* g_managerInstance = nullptr;

Manager::Manager(QObject *parent, WindowMode windowMode)
    : QObject{parent}
    , m_isGameActive{isGameActiveCheck(windowMode)}
    , m_windowMode{windowMode}
{
    if (windowMode != WindowMode::Foreground)
        setFocusedWindowChangeHook();

    if (windowMode != WindowMode::Focus)
        setForegroundWindowChangeHook();

    connect(&m_fileWatcher, &FileWatcher::ipFound, this, &Manager::onIpFound);
    connect(&m_fileWatcher, &FileWatcher::disconnectFound, this, &Manager::onDisconnectFound);
    connect(&m_settings, &Settings::pingIntervalChangedOverload, &m_pinger, &Pinger::onPingIntervalChanged);
    connect(&m_settings, &Settings::quitOnGameExitChangedOverload, &m_fileWatcher, &FileWatcher::setQuitOnGameExit);
    connect(&m_settings, &Settings::locationToastEnabledChanged, this, &Manager::onLocationToastEnabledChanged);
    connect(&m_settings, &Settings::locationEnabledChanged, this, &Manager::onLocationEnabledChanged);

    m_settings.loadSettings();
}

void Manager::addFile(const QString& filePath)
{
    m_fileWatcher.addFilePath(filePath);
}

void Manager::initTrayIcon(QObject *parent, QQuickWindow *rootWindow)
{
    if (m_trayIcon != nullptr)
        Utils::errorExit("[Manager]: Tray icon can only be initialized once.");

    m_trayIcon = new TrayIcon(parent, rootWindow);
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
    bool isForeground = false;
    bool isFocused = false;
    
    if (mode != WindowMode::Foreground) {
        HWND focusHwnd = GetFocus();
        int length = GetWindowTextLength(focusHwnd) + 1; // +1 for the null character.
        wchar_t* windowTitle = new wchar_t[length];
        GetWindowText(focusHwnd, windowTitle, length);
        isFocused = wcscmp(windowTitle, GAME_TITLE) == 0;
        delete[] windowTitle;
    }

    if (mode != WindowMode::Focus) {
        HWND foregroundHwnd = GetForegroundWindow();
        int length = GetWindowTextLength(foregroundHwnd) + 1; // +1 for the null character.
        wchar_t* windowTitle = new wchar_t[length];
        GetWindowText(foregroundHwnd, windowTitle, length);
        isForeground = wcscmp(windowTitle, GAME_TITLE) == 0;
        delete[] windowTitle;
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
        int length = GetWindowTextLength(hwnd) + 1; // +1 for the null character.
        wchar_t* windowTitle = new wchar_t[length];
        GetWindowText(hwnd, windowTitle, length);

        bool isGameFocused = wcscmp(windowTitle, GAME_TITLE) == 0;

        g_managerInstance->setIsGameActive(isGameFocused);

        delete[] windowTitle;
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
        int length = GetWindowTextLength(hwnd) + 1; // +1 for the null character.
        wchar_t* windowTitle = new wchar_t[length];
        GetWindowText(hwnd, windowTitle, length);

        bool isGameForeground = wcscmp(windowTitle, GAME_TITLE) == 0;

        g_managerInstance->setIsGameActive(isGameForeground);

        delete[] windowTitle;
    }
}

void Manager::onIpFound(const QString& ip)
{
    setIp(ip);
    setConnected(true);
    m_pinger.start(ip);
    m_stopwatch.start();
}

void Manager::onDisconnectFound()
{
    resetIp();
    setConnected(false);
    m_pinger.stop();
    m_stopwatch.stop();
}

void Manager::showLocationToast(const QString& location)
{
    if (m_stopwatch.getElapsedMs() > 5000)
        return;

    TrayIcon::sendNotification(L"Connected to server",
                               location.toStdWString(),
                               QCoreApplication::applicationDirPath().toStdWString() + L"/assets/globe-location.png");
}

void Manager::onLocationToastEnabledChanged()
{
    bool enabled = m_settings.locationToastEnabled();

    if (enabled)
        connect(&m_locator, &IPGeoLocator::locationFound, this, &Manager::showLocationToast);
    else
        disconnect(&m_locator, &IPGeoLocator::locationFound, this, &Manager::showLocationToast);
}

void Manager::onLocationEnabledChanged()
{
    bool enabled = m_settings.locationEnabled();

    if (enabled)
        enableGeo();
    else
        disableGeo();
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

IPGeoLocator* Manager::geoLocator()
{
    return &m_locator;
}

bool Manager::connected() const
{
    return m_connected;
}

void Manager::setConnected(bool newConnected)
{
    if (m_connected == newConnected)
        return;

    m_connected = newConnected;

    emit connectedChanged();
}

void Manager::enableGeo()
{
    if (m_geoEnabled)
        return;

    if (m_connected)
        m_locator.findLocation(m_ip);

    connect(&m_fileWatcher, &FileWatcher::ipFound, &m_locator, &IPGeoLocator::findLocation);
    connect(&m_fileWatcher, &FileWatcher::disconnectFound, &m_locator, &IPGeoLocator::onDisconnectFound);

    m_geoEnabled = true;
}

void Manager::disableGeo()
{
    if (!m_geoEnabled)
        return;

    m_locator.onDisconnectFound(); // Disables it (if enabled).

    disconnect(&m_fileWatcher, &FileWatcher::ipFound, &m_locator, &IPGeoLocator::findLocation);
    disconnect(&m_fileWatcher, &FileWatcher::disconnectFound, &m_locator, &IPGeoLocator::onDisconnectFound);

    m_geoEnabled = false;
}

QString Manager::ip() const
{
    return m_ip;
}

void Manager::setIp(const QString& newIp)
{
    if (m_ip == newIp)
        return;

    m_ip = newIp;

    emit ipChanged();
}

void Manager::resetIp()
{
    setIp("");
}

Stopwatch* Manager::stopwatch()
{
    return &m_stopwatch;
}

#ifndef MANAGER_H
#define MANAGER_H

#include "FileWatcher.h"
#include "Pinger.h"
#include "Settings.h"
#include "TrayIcon.h"
#include "IPGeoLocator.h"
#include "GeoData.h"
#include "Stopwatch.h"

#include <QObject>

#include <tchar.h>
#include <tlhelp32.h>
#include <windows.h>


class Manager : public QObject
{
    Q_OBJECT

    Q_PROPERTY(Pinger* pinger READ pinger CONSTANT)
    Q_PROPERTY(Settings* settings READ settings CONSTANT)
    Q_PROPERTY(IPGeoLocator* geoLocator READ geoLocator CONSTANT)
    Q_PROPERTY(Stopwatch* stopwatch READ stopwatch CONSTANT)
    Q_PROPERTY(bool isGameActive READ isGameActive WRITE setIsGameActive NOTIFY isGameActiveChanged FINAL)
    Q_PROPERTY(bool connected READ connected NOTIFY connectedChanged FINAL)
    Q_PROPERTY(QString ip READ ip WRITE setIp NOTIFY ipChanged FINAL)

public:
    enum WindowMode {
        Focus,
        Foreground,
        Both
    };

    explicit Manager(QObject* parent, WindowMode windowMode);

    void addFile(const QString &filePath);
    void initTrayIcon(QObject* parent, QQuickWindow* rootWindow);

    Pinger* pinger();
    Settings* settings();
    IPGeoLocator* geoLocator();
    Stopwatch* stopwatch();

    bool isGameActive() const;
    void setIsGameActive(bool newIsGameActive);

    bool connected() const;

    QString ip() const;
    void setIp(const QString& newIp);
    void resetIp();

public slots:
    void onIpFound(const QString& ip);
    void onDisconnectFound();
    void showLocationToast(const QString& location);
    void onLocationToastEnabledChanged();
    void onLocationEnabledChanged();

signals:
    void isGameActiveChanged();
    void connectedChanged();
    void ipChanged();

private:
    FileWatcher m_fileWatcher;
    Pinger m_pinger;
    TrayIcon* m_trayIcon{};
    Stopwatch m_stopwatch;
    Settings m_settings;
    IPGeoLocator m_locator;
    HANDLE m_hProcess = NULL;
    HWINEVENTHOOK m_hEventHookFocus{};
    HWINEVENTHOOK m_hEventHookForeground{};
    bool m_isGameActive{};
    WindowMode m_windowMode;
    bool m_connected{};
    bool m_geoEnabled{};
    QString m_ip;

    static VOID CALLBACK WinFocusCallback (HWINEVENTHOOK hWinEventHook, DWORD dwEvent, HWND hwnd, LONG idObject, LONG idChild, DWORD dwEventThread, DWORD dwmsEventTime);
    static VOID CALLBACK WinForegroundCallback (HWINEVENTHOOK hWinEventHook, DWORD dwEvent, HWND hwnd, LONG idObject, LONG idChild, DWORD dwEventThread, DWORD dwmsEventTime);

    bool isGameActiveCheck(WindowMode mode);
    bool isGameRunning();
    bool isProcessRunning(LPCTSTR& processName);
    void setFocusedWindowChangeHook();
    void setForegroundWindowChangeHook();
    void setConnected(bool newConnected);
    void enableGeo();
    void disableGeo();
};

extern Manager* g_managerInstance;

#endif // MANAGER_H

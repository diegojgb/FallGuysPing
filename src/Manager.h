#ifndef MANAGER_H
#define MANAGER_H

#include "FileWatcher.h"
#include "Pinger.h"
#include "Settings.h"
#include "TrayIcon.h"

#include <QObject>

#include <windows.h>
#include <tlhelp32.h>
#include <tchar.h>

class Manager : public QObject
{
    Q_OBJECT

    Q_PROPERTY(Pinger* pinger READ pinger CONSTANT)
    Q_PROPERTY(Settings* settings READ settings CONSTANT)
    Q_PROPERTY(bool isGameActive READ isGameActive WRITE setIsGameActive NOTIFY isGameActiveChanged FINAL)

public:
    enum WindowMode {
        Focus,
        Foreground,
        Both
    };

    explicit Manager(QObject *parent, WindowMode windowMode);

    void addFile(const QString &filePath);
    void initTrayIcon(QObject* parent, QObject* root, HWND& hwnd);

    Pinger* pinger();
    Settings* settings();

    bool isGameActive() const;
    void setIsGameActive(bool newIsGameActive);

public slots:
    void onIpFound(const std::string& ip);
    void onDisconnectFound();

signals:
    void isGameActiveChanged();

private:
    FileWatcher m_fileWatcher;
    Pinger m_pinger;
    TrayIcon* m_trayIcon{};
    Settings m_settings;
    HANDLE m_hProcess = NULL;
    HWINEVENTHOOK m_hEventHookFocus{};
    HWINEVENTHOOK m_hEventHookForeground{};
    bool m_trayIconInitialized = false;
    bool m_isGameActive{};
    WindowMode m_windowMode;

    static VOID CALLBACK WinFocusCallback (HWINEVENTHOOK hWinEventHook, DWORD dwEvent, HWND hwnd, LONG idObject, LONG idChild, DWORD dwEventThread, DWORD dwmsEventTime);
    static VOID CALLBACK WinForegroundCallback (HWINEVENTHOOK hWinEventHook, DWORD dwEvent, HWND hwnd, LONG idObject, LONG idChild, DWORD dwEventThread, DWORD dwmsEventTime);

    bool isGameActiveCheck(WindowMode mode);
    bool isGameRunning();
    bool isProcessRunning(LPCTSTR& processName);
    void setFocusedWindowChangeHook();
    void setForegroundWindowChangeHook();
};

extern Manager* g_managerInstance;

#endif // MANAGER_H

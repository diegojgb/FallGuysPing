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
    Q_PROPERTY(bool isGameForeground READ isGameForeground WRITE setIsGameForeground NOTIFY isGameForegroundChanged FINAL)

public:
    explicit Manager(QObject *parent = nullptr);

    void addFile(const QString &filePath);
    void initTrayIcon(QObject* parent, QObject* root, HWND& hwnd);

    Pinger* pinger();
    Settings* settings();

    bool isGameForeground() const;
    void setIsGameForeground(bool newIsGameForeground);

public slots:
    void onIpFound(const std::string& ip);
    void onDisconnectFound();

signals:
    void isGameForegroundChanged();

private:
    FileWatcher m_fileWatcher;
    Pinger m_pinger;
    TrayIcon* m_trayIcon{};
    Settings m_settings;
    HANDLE m_hProcess = NULL;
    HWINEVENTHOOK m_hEventHook{};
    bool m_trayIconInitialized = false;
    bool m_isGameForeground{};

    static VOID CALLBACK WinEventProcCallback (HWINEVENTHOOK hWinEventHook, DWORD dwEvent, HWND hwnd, LONG idObject, LONG idChild, DWORD dwEventThread, DWORD dwmsEventTime);
    static bool isFallGuysForeground();
    static std::wstring getForegroundWindowTitle();

    bool isFallGuysRunning();
    bool isProcessRunning(LPCTSTR& processName);
    void setForegroundWindowChangeHook();
};

extern Manager* g_managerInstance;

#endif // MANAGER_H

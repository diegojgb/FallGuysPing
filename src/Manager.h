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

public:
    explicit Manager(QObject *parent = nullptr);

    void addFile(const QString &filePath);
    void initTrayIcon(QObject* parent, QObject* root, HWND& hwnd);

    Pinger* pinger();
    Settings* settings();

public slots:
    void onIpFound(const std::string& ip);
    void onDisconnectFound();

private:
    FileWatcher m_fileWatcher;
    Pinger m_pinger;
    TrayIcon* m_trayIcon{};
    Settings m_settings;
    bool m_trayIconInitialized = false;
    HANDLE m_hProcess = NULL;

    bool isFallGuysRunning();
    bool isProcessRunning(LPCTSTR& processName);
};

#endif // MANAGER_H

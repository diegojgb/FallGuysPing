#ifndef MANAGER_H
#define MANAGER_H

#include "FileWatcher.h"
#include "Pinger.h"
#include "TrayIcon.h"

#include <QObject>

class Manager : public QObject
{
    Q_OBJECT

    Q_PROPERTY(Pinger* pinger READ pinger CONSTANT)

public:
    explicit Manager(QObject *parent = nullptr);

    void addFile(const QString &filePath);
    void initTrayIcon(QObject* parent, QObject* root, HWND& hwnd);

    Pinger* pinger();

public slots:
    void onIpFound(const std::string& ip);
    void onResetFound();

private:
    FileWatcher m_fileWatcher;
    Pinger m_pinger;
    TrayIcon* m_trayIcon = nullptr;
    bool m_trayIconInitialized = false;
};

#endif // MANAGER_H

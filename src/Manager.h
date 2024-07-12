#ifndef MANAGER_H
#define MANAGER_H

#include "FileWatcher.h"
#include "Pinger.h"

#include <QObject>

class Manager : public QObject
{
    Q_OBJECT

    Q_PROPERTY(Pinger* pinger READ pinger CONSTANT)

public:
    explicit Manager(QObject *parent = nullptr);

    void addFile(const QString &filePath);

    Pinger* pinger();

public slots:
    void onIpFound(const std::string& ip);
    void onResetFound();

private:
    FileWatcher m_fileWatcher;
    Pinger m_pinger;
};

#endif // MANAGER_H

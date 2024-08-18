#ifndef FILEWATCHER_H
#define FILEWATCHER_H

#define WIN32_LEAN_AND_MEAN

#include "FileChangeWorker.h"
#include "Utils.h"

#include <QObject>
#include <QFileSystemWatcher>
#include <QCoreApplication>
#include <QHash>
#include <QThread>

#include <Windows.h>
#include <mmsystem.h>
#include <regex>


class FileWatcher: public QObject
{
    Q_OBJECT

public:
    explicit FileWatcher(QObject* parent = nullptr);
    ~FileWatcher();

    Q_INVOKABLE void addFilePath(const QString &filePath);
    Q_INVOKABLE void removeFilePath(const QString &filePath);

public slots:
    void onFileChanged(FileData* fileData);
    void changeFilePath(const QString &oldKey, const QString &newKey);
    void setQuitOnGameExit(bool newValue);

signals:
    void ipFound(const QString& ip);
    void disconnectFound();
    void checkFailed(const QString& filePath);

private:
    QThread* m_thread{};
    FileChangeWorker* m_watcher{};
    std::regex m_ipRegex;
    std::regex m_resetRegex;
    std::regex m_exitRegex;
    std::smatch m_match;
    bool m_quitOnGameExit = false;
    bool m_fileInitialized = false;

    bool matchServerInfo(std::string &text);
    bool matchGameExit(std::string &text);
    void initCheck(const QString &filePath);
};

#endif // FILEWATCHER_H

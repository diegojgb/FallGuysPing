#include "FileWatcher.h"


FileWatcher::FileWatcher(QObject* parent)
    : QObject{parent},
      m_ipRegex{std::regex(R"(\[StateConnectToGame\] We're connected to the server! Host = ([0-9.]+))")},
      m_resetRegex{std::regex(R"(\[StateWaitingForRewards\])")}
      m_watcher{new FileChangeWorker()},
      m_thread{new QThread(this)}
{
    m_watcher->moveToThread(m_thread);

    connect(qApp, &QCoreApplication::aboutToQuit, m_watcher, &FileChangeWorker::finish);

    connect(m_thread, &QThread::finished, m_thread, &QThread::deleteLater);
    connect(m_watcher, &FileChangeWorker::finished, m_watcher, &FileChangeWorker::deleteLater);
    connect(m_watcher, &FileChangeWorker::finished, m_thread, &QThread::quit, Qt::DirectConnection);

    connect(m_watcher, &FileChangeWorker::fileChanged, this, &FileWatcher::onFileChanged);
    connect(m_watcher, &FileChangeWorker::checkFailed, this, &FileWatcher::checkFailed);

    m_thread->start();
}

FileWatcher::~FileWatcher()
{
    m_thread->wait();
}

void FileWatcher::changeFilePath(const QString& oldKey, const QString& newKey)
{
    removeFilePath(oldKey);
    addFilePath(newKey);
}

void FileWatcher::addFilePath(const QString &filePath)
{
    QMetaObject::invokeMethod(m_watcher, "addPath", Qt::QueuedConnection,
                              Q_ARG(QString, filePath));
}

void FileWatcher::removeFilePath(const QString &filePath)
{
    QMetaObject::invokeMethod(m_watcher, "removePath", Qt::QueuedConnection,
                              Q_ARG(QString, filePath));
}

void FileWatcher::onFileChanged(FileData* fileData)
{
    // Return if a call for this file change has already executed.
    if (!fileData->saveCurTime())
        return;

    std::string newText = Utils::readToEnd(fileData->file);

    if (newText == "") { // In case modifications were made, and the cursor is broken.
        fileData->startFile();
        return;
    }

    bool ipMatch = std::regex_search(newText, m_match, m_ipRegex);

    if (ipMatch)
        emit ipFound(m_match[1].str());
    else if (std::regex_search(newText, m_resetRegex))
        emit resetFound();
}

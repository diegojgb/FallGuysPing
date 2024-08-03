#include "FileWatcher.h"


FileWatcher::FileWatcher(QObject* parent)
    : QObject{parent},
      m_ipRegex{std::regex(R"(\[StateConnectToGame\] We're connected to the server! Host = ([0-9.]+))")},
      m_resetRegex{std::regex(R"(\[EAC Client\] DisconnectFromGameServer)")},
      m_exitRegex{std::regex(R"(\[GlobalGameStateClient\] OnDestroy called)")},
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

void FileWatcher::setQuitOnGameExit(bool newValue)
{
    if (m_quitOnGameExit == newValue)
        return;

    m_quitOnGameExit = newValue;
}

bool FileWatcher::matchServerInfo(std::string& text)
{
    bool ipMatch = std::regex_search(text, m_match, m_ipRegex);

    if (ipMatch) {
        emit ipFound(QString::fromStdString(m_match[1].str()));
        return true;
    }

    if (std::regex_search(text, m_resetRegex)) {
        emit disconnectFound();
        return true;
    }

    return false;
}

bool FileWatcher::matchGameExit(std::string &text)
{
    if (std::regex_search(text, m_exitRegex)) {
        qApp->exit();
        return true;
    }

    return false;
}

void FileWatcher::initCheck(const QString &filePath)
{
    std::ifstream in(filePath.toStdWString());

    if (!in.is_open())
        return;

    std::vector<std::string> lines;
    std::string line;

    while (std::getline(in, line))
        lines.push_back(line);

    for (auto it = lines.rbegin(); it != lines.rend(); ++it) {
        if(matchServerInfo(*it))
            return;
    }
}

void FileWatcher::addFilePath(const QString &filePath)
{
    initCheck(filePath);

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

    std::string line;

    if (!std::getline(fileData->file, line)) { // In case modifications were made, and the cursor is broken.
        fileData->startFile();
        return;
    }

    do {
        matchServerInfo(line);

        if (m_quitOnGameExit)
            matchGameExit(line);
    }
    while (std::getline(fileData->file, line));

    if (!fileData->file.eof())
        Utils::errorExit("FileWatcher: error reading file");

    fileData->file.clear();
}

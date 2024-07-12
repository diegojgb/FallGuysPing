#include "Pinger.h"

Pinger::Pinger(QObject *parent)
    : QObject{parent},
      m_worker{new PingWorker()},
      m_thread{new QThread(this)}
{
    m_worker->moveToThread(m_thread);

    connect(qApp, &QCoreApplication::aboutToQuit, m_worker, &PingWorker::finish);

    connect(m_thread, &QThread::finished, m_thread, &QThread::deleteLater);
    connect(m_worker, &PingWorker::finished, m_worker, &PingWorker::deleteLater);
    connect(m_worker, &PingWorker::finished, m_thread, &QThread::quit, Qt::DirectConnection);

    connect(m_worker, &PingWorker::pinged, this, &Pinger::onPinged);

    m_thread->start();
}

void Pinger::start(const std::string& ip)
{
    QMetaObject::invokeMethod(m_worker, "start", Qt::QueuedConnection,
                              Q_ARG(std::string, ip));
}

void Pinger::stop()
{
    QMetaObject::invokeMethod(m_worker, "stop", Qt::QueuedConnection);
}

QString Pinger::latestPing() const
{
    return m_latestPing;
}

void Pinger::setLatestPing(const QString& newLatestPing)
{
    if (m_latestPing == newLatestPing)
        return;

    m_latestPing = newLatestPing;

    emit latestPingChanged();
}

void Pinger::onPinged(const QString& latency)
{
    setLatestPing(latency);
}

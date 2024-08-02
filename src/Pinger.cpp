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

void Pinger::start(const QString& ip)
{
    QMetaObject::invokeMethod(m_worker, "startIp", Qt::QueuedConnection,
                              Q_ARG(QString, ip));
}

void Pinger::stop()
{
    QMetaObject::invokeMethod(m_worker, "stopIp", Qt::QueuedConnection);
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

void Pinger::onPingIntervalChanged(int interval)
{
    QMetaObject::invokeMethod(m_worker, "setPingInterval", Qt::QueuedConnection,
                              Q_ARG(int, interval));
}

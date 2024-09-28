#include "Pinger.h"

Pinger::Pinger(QObject *parent)
    : QObject{parent}
    , m_worker{new PingWorker()}
    , m_thread{new QThread(this)}
    , m_latencies{0}
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
    m_active = true;
    QMetaObject::invokeMethod(m_worker, "startIp", Qt::QueuedConnection,
                              Q_ARG(QString, ip));
}

void Pinger::stop()
{
    QMetaObject::invokeMethod(m_worker, "stopIp", Qt::QueuedConnection);
    m_active = false;
    resetValues();
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
    if (!m_active)
        return;

    int ping = latency.toInt();
    m_sum += ping;
    m_count++;

    setLatestPing(latency);
    setAvg10Ping(QString::number(calcAvg10(ping)));
    setAvgPing(QString::number(m_sum / m_count));

    if (ping > m_max || m_max == 0) {
        m_max = ping;
        setMaxPing(latency);
    }

    if (ping < m_min || m_min == 0) {
        m_min = ping;
        setMinPing(latency);
    }
}

void Pinger::onPingIntervalChanged(int interval)
{
    QMetaObject::invokeMethod(m_worker, "setPingInterval", Qt::QueuedConnection,
                              Q_ARG(int, interval));
}

void Pinger::resetValues()
{
    m_sum = 0;
    m_count = 0;
    m_max = 0;
    m_min = 0;

    setLatestPing("0");
    setAvgPing("0");
    setMinPing("0");
    setMaxPing("0");
    setAvg10Ping("0");
}

QString Pinger::avgPing() const
{
    return m_avgPing;
}

void Pinger::setAvgPing(const QString& newAvgPing)
{
    if (m_avgPing == newAvgPing)
        return;

    m_avgPing = newAvgPing;

    emit avgPingChanged();
}

int Pinger::calcAvg10(const int latency)
{
    if (m_count10 == maxSize)
        m_sum10 -= m_latencies[m_currentIndex];
    else
        m_count10++;

    m_sum10 += latency;
    m_latencies[m_currentIndex] = latency;

    // Move to the next index (circularly)
    m_currentIndex = (m_currentIndex + 1) % maxSize;

    int avgLatency = m_sum10 / m_count10;

    return avgLatency;
}

QString Pinger::maxPing() const
{
    return m_maxPing;
}

void Pinger::setMaxPing(const QString& newMaxPing)
{
    if (m_maxPing == newMaxPing)
        return;

    m_maxPing = newMaxPing;

    emit maxPingChanged();
}

QString Pinger::minPing() const
{
    return m_minPing;
}

void Pinger::setMinPing(const QString& newMinPing)
{
    if (m_minPing == newMinPing)
        return;

    m_minPing = newMinPing;

    emit minPingChanged();
}

QString Pinger::avg10Ping() const
{
    return m_avg10Ping;
}

void Pinger::setAvg10Ping(const QString& newAvg10Ping)
{
    if (m_avg10Ping == newAvg10Ping)
        return;

    m_avg10Ping = newAvg10Ping;

    emit avg10PingChanged();
}

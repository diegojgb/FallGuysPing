#include "Stopwatch.h"


Stopwatch::Stopwatch(QObject *parent)
    : QObject(parent)
    , m_elapsedTimer(new QElapsedTimer())
    , m_updateTimer(new QTimer(this))
{
    connect(m_updateTimer, &QTimer::timeout, this, &Stopwatch::updateElapsedTime);
}

QString Stopwatch::elapsedTime() const
{
    return m_elapsedTime;
}

qint64 Stopwatch::getElapsedMs()
{
    if (!m_elapsedTimer->isValid())
        return -1;

    return m_elapsedTimer->elapsed();
}

void Stopwatch::start()
{
    m_elapsedTimer->start();
    m_updateTimer->start(1000);
}

void Stopwatch::stop()
{
    m_updateTimer->stop();
    setElapsedTime("");
}

void Stopwatch::reset()
{
    m_updateTimer->stop();
    m_elapsedTimer->start();
    m_updateTimer->start(1000);
}

void Stopwatch::updateElapsedTime()
{
    if (!m_elapsedTimer->isValid())
        return;

    qint64 elapsedMs = m_elapsedTimer->elapsed();
    QTime elapsedTime = QTime::fromMSecsSinceStartOfDay(elapsedMs);
    m_elapsedTime = elapsedTime.toString("hh:mm:ss");

    emit elapsedTimeChanged();
}

void Stopwatch::setElapsedTime(const QString &newElapsedTime)
{
    if (m_elapsedTime == newElapsedTime)
        return;

    m_elapsedTime = newElapsedTime;

    emit elapsedTimeChanged();
}

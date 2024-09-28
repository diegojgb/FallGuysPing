#ifndef PINGER_H
#define PINGER_H

#include "PingWorker.h"

#include <QObject>
#include <QThread>
#include <QCoreApplication>


class Pinger : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString latestPing READ latestPing NOTIFY latestPingChanged FINAL)
    Q_PROPERTY(QString avgPing READ avgPing NOTIFY avgPingChanged FINAL)
    Q_PROPERTY(QString maxPing READ maxPing NOTIFY maxPingChanged FINAL)
    Q_PROPERTY(QString minPing READ minPing NOTIFY minPingChanged FINAL)
    Q_PROPERTY(QString avg10Ping READ avg10Ping NOTIFY avg10PingChanged FINAL)

public:
    explicit Pinger(QObject *parent = nullptr);

    void start(const QString& ip);
    void stop();

    QString latestPing() const;
    QString avgPing() const;
    QString maxPing() const;
    QString minPing() const;
    QString avg10Ping() const;

public slots:
    void onPinged(const QString& latency);
    void onPingIntervalChanged(int interval);

signals:
    void latestPingChanged();
    void avgPingChanged();
    void maxPingChanged();
    void minPingChanged();
    void avg10PingChanged();

private:
    static const int maxSize = 10;
    int m_latencies[maxSize];
    int m_sum10 = 0;
    int m_count10 = 0;
    int m_currentIndex = 0;

    QThread* m_thread{};
    PingWorker* m_worker{};
    QString m_latestPing = "0";
    QString m_avgPing = "0";
    QString m_avg10Ping = "0";
    QString m_maxPing = "0";
    QString m_minPing = "0";
    int m_sum = 0;
    int m_count = 0;
    int m_max = 0;
    int m_min = 0;
    bool m_active = false;

    void resetValues();
    int calcAvg10(const int latency);

    void setLatestPing(const QString &newLatestPing);
    void setMinPing(const QString& newMinPing);
    void setMaxPing(const QString& newMaxPing);
    void setAvgPing(const QString& newAvgPing);
    void setAvg10Ping(const QString& newAvg10Ping);
};

#endif // PINGER_H

#ifndef PINGER_H
#define PINGER_H

#include "PingWorker.h"

#include <QObject>
#include <QThread>
#include <QCoreApplication>


class Pinger : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString latestPing READ latestPing WRITE setLatestPing NOTIFY latestPingChanged FINAL)

public:
    explicit Pinger(QObject *parent = nullptr);

    QString latestPing() const;
    void setLatestPing(const QString &newLatestPing);

    void start(const QString& ip);
    void stop();

public slots:
    void onPinged(const QString& latency);
    void onPingIntervalChanged(int interval);

signals:
    void latestPingChanged();

private:
    QThread* m_thread{};
    PingWorker* m_worker{};
    QString m_latestPing = "0";
};

#endif // PINGER_H

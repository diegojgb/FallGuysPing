#ifndef PINGWORKER_H
#define PINGWORKER_H

#include <QObject>
#include <QTimerEvent>

#include <WS2tcpip.h>
#include <Windows.h>
#include <iphlpapi.h>
#include <IcmpAPI.h>

#include <iostream>


class PingWorker: public QObject
{
    Q_OBJECT

public:
    explicit PingWorker(QObject* parent = nullptr);
    ~PingWorker();

    Q_INVOKABLE void stop();

public slots:
    void start(const std::string& ip);
    void finish();

signals:
    void pinged(const QString& latency);
    void finished();

private:
    static const WORD m_payloadSize = 1;
    static const DWORD m_replyBufSize = sizeof(ICMP_ECHO_REPLY) + m_payloadSize + 8;
    unsigned char m_payload[m_payloadSize]{};
    unsigned char replyBuf[m_replyBufSize]{}; // Reply buffer for exactly 1 echo reply, payload data, and 8 bytes for ICMP error message.
    IN_ADDR m_ip{};
    HANDLE m_icmpHandle;

    std::string m_ipStr;

    int m_timer{};
    int m_pollingRate = 2000;
    bool m_running = false;

    void timerEvent(QTimerEvent* event) override;

    QString ping();
};

#endif // PINGWORKER_H

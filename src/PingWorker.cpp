#include "PingWorker.h"


PingWorker::PingWorker(QObject *parent)
    : QObject{parent},
      m_icmpHandle{IcmpCreateFile()}
{
    if (m_icmpHandle == INVALID_HANDLE_VALUE) {
        throw;
    }
}

PingWorker::~PingWorker()
{
    IcmpCloseHandle(m_icmpHandle);
}

void PingWorker::start()
{
    if (!m_running) {
        m_timer = startTimer(m_pingInterval);
        m_running = true;
    }
}

void PingWorker::stop()
{
    if (m_running) {
        killTimer(m_timer);
        m_running = false;
    }
}

void PingWorker::restart()
{
    if (m_running) {
        stop();
        start();
    }
}

void PingWorker::startIp(const std::string& ip)
{
    m_ipStr = ip;

    if (InetPtonA(AF_INET, m_ipStr.c_str(), &m_ip) != 1) {
        throw;
    }

    emit pinged(ping());

    start();
}

void PingWorker::stopIp()
{
    stop();

    emit pinged("0");
}

int PingWorker::pingInterval() const
{
    return m_pingInterval;
}

void PingWorker::setPingInterval(int interval)
{
    if (m_pingInterval == interval)
        return;

    m_pingInterval = interval;

    restart();
}

void PingWorker::finish()
{
    stop();
    emit finished();
}

void PingWorker::timerEvent(QTimerEvent *event)
{
    if (event->timerId() == m_timer) {
        emit pinged(ping());
    }
}

QString PingWorker::ping()
{
    DWORD ret = IcmpSendEcho(m_icmpHandle, m_ip.S_un.S_addr,
                                     m_payload, m_payloadSize, NULL, replyBuf, m_replyBufSize, 10000);

    // Return value of 0 indicates failure, try to get error info.
    if (ret == 0) {
        auto e = GetLastError();
        DWORD buf_size = 1000;
        WCHAR buf[1000];

        GetIpErrorString(e, buf, &buf_size);

        std::cerr << "IcmpSendEcho returned error " << e << " (" << buf << ")" << std::endl;
        std::cerr << "Failed to ping: " << m_ipStr << std::endl;
    }

    const ICMP_ECHO_REPLY *r = (const ICMP_ECHO_REPLY*) replyBuf;
    
    auto time = QString::number(r->RoundTripTime);

    return time;
}

#ifndef IPGEOLOCATOR_H
#define IPGEOLOCATOR_H

#include "Utils.h"

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>

#include <iostream>


class IPGeoLocator : public QObject
{
    Q_OBJECT

public:
    static const QString NORDVPN_URL; // "{NORDVPN_URL}{ip}"
    static const QString IP2LOCATION_URL; // "{IP2LOCATION_URL}{ip}" - 500 queries per day
    static const QString IPINFO_URL; // "{IPINFO_URL}{ip}/json" - 1000 queries per day

    explicit IPGeoLocator(QObject* parent = nullptr);

    void findLocation(const QString& ip);

public slots:
    void onReply(QNetworkReply* reply, const QString& serviceUrl);

signals:
    void locationFound(const QString& location);

private:
    QNetworkAccessManager m_manager;
    QString m_currentIp;

    void queryAPI(const QString& ip, const QString& serviceUrl);
};

#endif // IPGEOLOCATOR_H

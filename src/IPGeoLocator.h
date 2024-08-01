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

    explicit IPGeoLocator(QObject* parent = nullptr);

    void findLocation(const QString& ip);

public slots:
    void onNordReply(QNetworkReply* reply);

signals:
    void locationFound(const QString& location);
    void locationError(const QString& error);

private:
    QNetworkAccessManager m_manager;

    void nordGet(const QString& ip);
};

#endif // IPGEOLOCATOR_H

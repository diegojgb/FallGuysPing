#ifndef IPGEOLOCATOR_H
#define IPGEOLOCATOR_H

#include "Utils.h"
#include "GeoData.h"

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>

#include <iostream>


class IPGeoLocator : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString country READ country NOTIFY countryChanged FINAL)
    Q_PROPERTY(QString region READ region NOTIFY regionChanged FINAL)
    Q_PROPERTY(QString serverRegion READ serverRegion NOTIFY serverRegionChanged FINAL)
    Q_PROPERTY(QString city READ city NOTIFY cityChanged FINAL)
    Q_PROPERTY(QString countryCode READ countryCode NOTIFY countryCodeChanged FINAL)
    Q_PROPERTY(bool active READ active NOTIFY activeChanged FINAL)

public:
    static const QString NORDVPN_URL; // "{NORDVPN_URL}{ip}"
    static const QString IP2LOCATION_URL; // "{IP2LOCATION_URL}{ip}" - 500 queries per day
    static const QString IPINFO_URL; // "{IPINFO_URL}{ip}/json" - 1000 queries per day

    explicit IPGeoLocator(QObject* parent = nullptr);

    void findLocation(const QString& ip);

    QString country() const;
    QString region() const;
    QString serverRegion() const;
    QString city() const;
    QString countryCode() const;
    bool active() const;

public slots:
    void onReply(QNetworkReply* reply, const QString& serviceUrl);
    void onDisconnectFound();

signals:
    void countryChanged();
    void regionChanged();
    void serverRegionChanged();
    void cityChanged();
    void countryCodeChanged();
    void activeChanged();

    void locationFound(const QString& location);

private:
    QNetworkAccessManager m_manager;
    QString m_currentIp;
    QString m_countryCode;
    QString m_country;
    QString m_region;
    QString m_city;
    QString m_serverRegion;
    bool m_active = false;

    void queryAPI(const QString& ip, const QString& serviceUrl);
    void updateServerRegion();
    QString getLocationStr();

    void setCountry(const QString& newCountry);
    void setRegion(const QString& newRegion);
    void setServerRegion(const QString& newServerRegion);
    void setCity(const QString& newCity);
    void setCountryCode(const QString& newCountryCode);
    void setActive(bool newActive);
};

#endif // IPGEOLOCATOR_H

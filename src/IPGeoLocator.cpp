#include "IPGeoLocator.h"


const QString IPGeoLocator::NORDVPN_URL = "https://nordvpn.com/wp-admin/admin-ajax.php?action=get_user_info_data&ip=";
const QString IPGeoLocator::IP2LOCATION_URL = "https://api.ip2location.io/?ip=";
const QString IPGeoLocator::IPINFO_URL = "https://ipinfo.io/";


IPGeoLocator::IPGeoLocator(QObject *parent)
    : QObject{parent}, m_manager{QNetworkAccessManager(this)}
{}

void IPGeoLocator::findLocation(const QString& ip)
{
    m_currentIp = ip;
    queryAPI(ip, IP2LOCATION_URL);
}

void IPGeoLocator::queryAPI(const QString& ip, const QString& serviceUrl)
{
    QUrl url = QUrl((serviceUrl == IPINFO_URL) ? serviceUrl + ip + "/json" : serviceUrl + ip);

    QNetworkReply* reply = m_manager.get(QNetworkRequest(url));
    QObject::connect(reply, &QNetworkReply::finished, this, [this, reply, serviceUrl]() {
        this->onReply(reply, serviceUrl);
    });
}

void IPGeoLocator::onReply(QNetworkReply* reply, const QString& serviceUrl)
{
    if (reply->error() != QNetworkReply::NoError) {
        qCritical() << "[IPGeoLocator]: " << reply->errorString();

        if (serviceUrl == IP2LOCATION_URL)
            queryAPI(m_currentIp, IPINFO_URL);

        return;
    }

    QByteArray response_data = reply->readAll();

    QJsonDocument jsonDoc = QJsonDocument::fromJson(response_data);

    if (!jsonDoc.isObject()) {
        qCritical() << "[IPGeoLocator]: Received data is not a valid JSON object.";
        return;
    }

    QJsonObject obj = jsonDoc.object();

    QString countryCodeKey;
    QString regionKey;
    QString cityKey;

    if (serviceUrl == IP2LOCATION_URL || serviceUrl == NORDVPN_URL)
        countryCodeKey = "country_code";
    else if (serviceUrl == IPINFO_URL)
        countryCodeKey = "country";

    if (serviceUrl == IP2LOCATION_URL) {
        regionKey = "region_name";
        cityKey = "city_name";
    } else if (serviceUrl == IPINFO_URL || serviceUrl == NORDVPN_URL) {
        regionKey = "region";
        cityKey = "city";
    }

    if (!obj.contains(countryCodeKey) || !obj[countryCodeKey].isString()) {
        qCritical() << "[IPGeoLocator/IP2location]: Missing/invalid country code.";
        return;
    }
    if (!obj.contains(regionKey) || !obj[regionKey].isString()) {
        qCritical() << "[IPGeoLocator/IP2location]: Missing/invalid country code.";
        return;
    }
    if (!obj.contains(cityKey) || !obj[cityKey].isString()) {
        qCritical() << "[IPGeoLocator/IP2location]: Missing/invalid country code.";
        return;
    }

    QString countryCode = obj[countryCodeKey].toString();
    QString region = obj[regionKey].toString();
    QString city = obj[cityKey].toString();

    QString location = QString("%1, %2, %3").arg(countryCode, region, city);

    emit locationFound(location);

    reply->deleteLater();
}

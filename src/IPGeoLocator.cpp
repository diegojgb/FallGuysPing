#include "IPGeoLocator.h"


const QString IPGeoLocator::NORDVPN_URL = "https://nordvpn.com/wp-admin/admin-ajax.php?action=get_user_info_data&ip=";
const QString IPGeoLocator::IP2LOCATION_URL = "https://api.ip2location.io/?ip=";
const QString IPGeoLocator::IPINFO_URL = "https://ipinfo.io/";


IPGeoLocator::IPGeoLocator(QObject *parent)
    : QObject{parent}
    , m_manager{QNetworkAccessManager(this)}
    , m_country{"D/C"}
    , m_region{"D/C"}
    , m_serverRegion{""}
{}

void IPGeoLocator::findLocation(const QString& ip)
{
    m_currentIp = ip;
    queryAPI(ip, IPINFO_URL);
}

void IPGeoLocator::queryAPI(const QString& ip, const QString& serviceUrl)
{
    QUrl url = QUrl((serviceUrl == IPINFO_URL) ? serviceUrl + ip + "/json" : serviceUrl + ip);

    QNetworkReply* reply = m_manager.get(QNetworkRequest(url));
    QObject::connect(reply, &QNetworkReply::finished, this, [this, reply, serviceUrl]() {
        this->onReply(reply, serviceUrl);
    });
}

void IPGeoLocator::updateServerRegion()
{
    if (m_country == "United States")
        setServerRegion(QString("US (%1)").arg(GeoData::stateToRegionUS(m_region)));
    else
        setServerRegion(GeoData::countryCodeToRegion(m_countryCode));
}

QString IPGeoLocator::getLocationStr()
{
    if (m_serverRegion == "")
        return QString("%1, %2").arg(m_country, m_region);
    else if (m_country == "United States")
        return QString("%1, %2").arg(m_serverRegion, m_region);
    else
        return QString("%1, %2, %3").arg(m_serverRegion, m_country, m_region);
}

void IPGeoLocator::setCountry(const QString& newCountry)
{
    if (m_country == newCountry)
        return;

    m_country = newCountry;

    emit countryChanged();
}

void IPGeoLocator::setRegion(const QString& newRegion)
{
    if (m_region == newRegion)
        return;

    m_region = newRegion;

    emit regionChanged();
}

void IPGeoLocator::setServerRegion(const QString& newServerRegion)
{
    if (m_serverRegion == newServerRegion)
        return;

    m_serverRegion = newServerRegion;

    emit serverRegionChanged();
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
    // QString cityKey;

    if (serviceUrl == IP2LOCATION_URL || serviceUrl == NORDVPN_URL)
        countryCodeKey = "country_code";
    else if (serviceUrl == IPINFO_URL)
        countryCodeKey = "country";

    if (serviceUrl == IP2LOCATION_URL) {
        regionKey = "region_name";
        // cityKey = "city_name";
    } else if (serviceUrl == IPINFO_URL || serviceUrl == NORDVPN_URL) {
        regionKey = "region";
        // cityKey = "city";
    }

    if (!obj.contains(countryCodeKey) || !obj[countryCodeKey].isString()) {
        qCritical() << "[IPGeoLocator/IP2location]: Missing/invalid country code.";
        return;
    }
    if (!obj.contains(regionKey) || !obj[regionKey].isString()) {
        qCritical() << "[IPGeoLocator/IP2location]: Missing/invalid region.";
        return;
    }
    // if (!obj.contains(cityKey) || !obj[cityKey].isString()) {
    //     qCritical() << "[IPGeoLocator/IP2location]: Missing/invalid country code.";
    //     return;
    // }

    m_countryCode = obj[countryCodeKey].toString();

    setRegion(obj[regionKey].toString());
    setCountry(GeoData::countryCodeToName(m_countryCode));
    updateServerRegion();

    emit locationFound(getLocationStr());

    reply->deleteLater();
}

void IPGeoLocator::onDisconnectFound()
{
    setRegion("D/C");
    setCountry("D/C");
    setServerRegion("");
}

QString IPGeoLocator::country() const
{
    return m_country;
}

QString IPGeoLocator::region() const
{
    return m_region;
}

QString IPGeoLocator::serverRegion() const
{
    return m_serverRegion;
}

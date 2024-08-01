#include "IPGeoLocator.h"


const QString IPGeoLocator::NORDVPN_URL = "https://nordvpn.com/wp-admin/admin-ajax.php?action=get_user_info_data&ip=";


IPGeoLocator::IPGeoLocator(QObject *parent)
    : QObject{parent}, m_manager{QNetworkAccessManager(this)}
{}

void IPGeoLocator::findLocation(const QString& ip)
{
    nordGet(ip);
}

void IPGeoLocator::nordGet(const QString& ip)
{
    m_manager.get(QNetworkRequest(QUrl(NORDVPN_URL + ip)));
    QObject::connect(&m_manager, &QNetworkAccessManager::finished, this, &IPGeoLocator::onNordReply);
}

void IPGeoLocator::onNordReply(QNetworkReply* reply)
{
    if (reply->error() != QNetworkReply::NoError)
        emit locationError("[IPGeoLocator/onNordReply] Error: " + reply->errorString());

    QByteArray response_data = reply->readAll();

    QJsonDocument jsonDoc = QJsonDocument::fromJson(response_data);

    if (!jsonDoc.isObject())
        emit locationError("[IPGeoLocator/onNordReply] Received data is not a valid JSON object.");

    QJsonObject obj = jsonDoc.object();

    if (!obj.contains("location") || !obj["location"].isString())
        emit locationError("[IPGeoLocator/onNordReply] Missing/invalid location entry.");

    QString loc = obj["location"].toString();

    emit locationFound(loc);

    reply->deleteLater();
}

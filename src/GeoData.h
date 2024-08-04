#ifndef GEODATA_H
#define GEODATA_H

#include <QObject>
#include <QHash>


class GeoData : public QObject
{
    Q_OBJECT

public:
    static QString countryCodeToName(const QString& code);
    static QString stateToRegionUS(const QString& state);
    static QString countryCodeToRegion(const QString& code);

private:
    static const QHash<QString, QString> codeNameHash;
    static const QHash<QString, QString> stateRegionHash;
    static const QHash<QString, QString> countryRegionHash;
};

#endif // GEODATA_H

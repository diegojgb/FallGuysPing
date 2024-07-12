#include "Utils.h"


void Utils::showCritical(std::string errorStr)
{
    QMessageBox::critical(nullptr, QObject::tr("WatchLog"), QObject::tr(errorStr.c_str()));
}

std::string Utils::readToEnd(std::ifstream &file)
{
    if (!file.is_open())
        throwError("Utils (readToEnd): file's not open");

    std::ostringstream sstr;
    sstr << file.rdbuf();
    return sstr.str();
}

void Utils::throwError(std::string errorStr)
{
    showCritical(errorStr);
    throw std::runtime_error(errorStr);
}

void Utils::showInfo(std::string infoStr)
{
    QMessageBox::information(nullptr, QObject::tr("WatchLog"), QObject::tr(infoStr.c_str()));
}

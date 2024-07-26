#include "Utils.h"


void Utils::showCritical(std::string errorStr)
{
    QMessageBox::critical(nullptr, QObject::tr("WatchLog"), QObject::tr(errorStr.c_str()));
}

void Utils::errorExit(std::string errorStr)
{
    showCritical(errorStr);
    qApp->exit(1);
}

std::string Utils::readToEnd(std::ifstream &file)
{
    if (!file.is_open())
        errorExit("Utils (readToEnd): file's not open");

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

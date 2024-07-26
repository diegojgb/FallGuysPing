#ifndef UTILS_H
#define UTILS_H

#include <QObject>
#include <QMessageBox>
#include <QApplication>

#include <fstream>
#include <sstream>


class Utils
{
public:
    static void throwError(std::string errorStr);
    static void showInfo(std::string infoStr);
    static void showCritical(std::string errorStr);
    static void errorExit(std::string errorStr);
    static std::string readToEnd(std::ifstream& file);
};



#endif // UTILS_H

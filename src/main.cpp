#include "DashedRectangle.h"
#include "Manager.h"

#include <QApplication>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QWindow>
#include <QStyleFactory>
#include <QStandardPaths>

#include <SingleApplication.h>

// #include <Windows.h>


int main(int argc, char *argv[])
{
    QApplication::setStyle(QStyleFactory::create("Fusion"));
    SingleApplication app(argc, argv);

    Manager manager;
    g_managerInstance = &manager;

    QString path = QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation);
    path += "Low/Mediatonic/FallGuys_client/Player.log";

    manager.addFile(path);

    QQmlApplicationEngine engine;

    // Expose objects to QML
    engine.rootContext()->setContextProperty("Manager", &manager);
    qmlRegisterUncreatableType<Settings>("TextCorner", 1, 0, "TextCorner", "Enum is not a type");

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);

    engine.load(QUrl(QStringLiteral("qrc:/qt/qml/FallGuysPing/qml/MainWindow.qml")));
    engine.load(QUrl(QStringLiteral("qrc:/qt/qml/FallGuysPing/qml/PingTextWindow.qml")));

    if (engine.rootObjects().isEmpty())
        return -1;

    QObject* root = engine.rootObjects().at(0);
    QWindow* mainWindow = qobject_cast<QWindow*>(root);
    HWND hwnd = (HWND)mainWindow->winId();

    manager.initTrayIcon(&app, root, hwnd);

    QObject::connect(&app, &SingleApplication::instanceStarted, mainWindow, &QWindow::showNormal);
    QObject::connect(&app, &SingleApplication::instanceStarted, [hwnd]() {
        SetForegroundWindow(hwnd);
    });

    return app.exec();
}

#include "Manager.h"

#include <QApplication>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QWindow>


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Manager manager;

    manager.addFile("C:/Users/diego/AppData/LocalLow/Mediatonic/FallGuys_client/Player.log");

    QQmlApplicationEngine engine;

    // Expose objects to QML
    engine.rootContext()->setContextProperty("Manager", &manager);

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);

    engine.load(QUrl(QStringLiteral("qrc:/qml/MainWindow.qml")));
    engine.load(QUrl(QStringLiteral("qrc:/qml/PingTextWindow.qml")));

    if (engine.rootObjects().isEmpty())
        return -1;

    QObject* root = engine.rootObjects().at(0);
    QWindow* mainWindow = qobject_cast<QWindow*>(root);
    HWND hwnd = (HWND)mainWindow->winId();

    manager.initTrayIcon(&app, root, hwnd);

    return app.exec();
}
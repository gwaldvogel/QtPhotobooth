#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <RaspberryPiConnector.h>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    RaspberryPiConnector rpiConnector;
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("raspberry", &rpiConnector);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}

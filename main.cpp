#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <RaspberryPiConnector.h>
#include <CloudConnector.h>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    RaspberryPiConnector rpiConnector;
    CloudConnector cloudConnector;
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("raspberry", &rpiConnector);
    engine.rootContext()->setContextProperty("cloud", &cloudConnector);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}

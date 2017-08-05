#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <RaspberryPiConnector.h>
#include <CloudConnector.h>

#include <initializer_list>
#include <signal.h>
#include <unistd.h>

void ignoreUnixSignals(std::initializer_list<int> ignoreSignals) {
    // all these signals will be ignored.
    for (int sig : ignoreSignals)
        signal(sig, SIG_IGN);
}

void catchUnixSignals(std::initializer_list<int> quitSignals) {
    auto handler = [](int sig) -> void {
        // blocking and not aysnc-signal-safe func are valid
        printf("\nquit the application by signal(%d).\n", sig);
        QGuiApplication::quit();
    };

    sigset_t blocking_mask;
    sigemptyset(&blocking_mask);
    for (auto sig : quitSignals)
        sigaddset(&blocking_mask, sig);

    struct sigaction sa;
    sa.sa_handler = handler;
    sa.sa_mask    = blocking_mask;
    sa.sa_flags   = 0;

    for (auto sig : quitSignals)
        sigaction(sig, &sa, nullptr);
}

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

    catchUnixSignals({SIGQUIT, SIGINT, SIGTERM, SIGHUP});

    return app.exec();
}

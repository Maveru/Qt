#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QIcon>
#include "randomnumber.h"
#include "counter.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    qmlRegisterType<RandomNumber>("Randomlib",1,0,"RandomNumber");
    qmlRegisterType<Counter>("Counterlib",1,0,"Counter");

    app.setWindowIcon(QIcon("://images/icono.jpg"));

    QQmlApplicationEngine engine;

    //qDebug() << "Offline storage path : " << engine.offlineStoragePath();

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
        &app, [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "appwrapper.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    AppWrapper wrapper;

//    QQmlApplicationEngine engine;

//    engine.rootContext()->setContextProperty("Wrapper",&wrapper);

//    const QUrl url(QStringLiteral("qrc:/main.qml"));
//    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
//        &app, [url](QObject *obj, const QUrl &objUrl) {
//            if (!obj && url == objUrl)
//                QCoreApplication::exit(-1);
//        }, Qt::QueuedConnection);
//    engine.load(url);
    if(!wrapper.initialize())
        return -1;

    return app.exec();
}

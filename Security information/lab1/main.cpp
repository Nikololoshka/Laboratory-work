#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickStyle>

#include "userRepository.h"
#include "user.h"
#include "singletonHelper.h"


int main(int argc, char* argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QQuickStyle::setStyle("Material");
    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));

    qmlRegisterType<UserRepository>("UserRepository", 1, 0, "UserRepository");
    qmlRegisterType<User>("User", 1, 0, "User");

    auto& helper = SingletonHelper::instance();
    engine.rootContext()->setContextProperty("SingletonHelper", &helper);
    engine.addImportPath("qrc:/");

    QObject::connect(
        &engine, &QQmlApplicationEngine::objectCreated,
        &app, [url](QObject* obj, const QUrl& objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);

    engine.load(url);

    return app.exec();
}

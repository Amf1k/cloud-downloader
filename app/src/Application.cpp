#include "Application.hpp"

#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "DownloaderModel.hpp"

Amfik::clouddownloader::Application::Application(int argc, char* argv[])
    : _argc(argc), _argv(argv) {}

std::unique_ptr<Amfik::clouddownloader::Application>
Amfik::clouddownloader::Application::Create(int argc, char* argv[]) {
  return std::make_unique<Application>(argc, argv);
}

int Amfik::clouddownloader::Application::exec() {
  init();

  int result = executeApplication();

  return result;
}

void Amfik::clouddownloader::Application::init() {
  QGuiApplication::setApplicationName("Cloud Downloader");
  QGuiApplication::setOrganizationName("Amf1k");
  DownloaderModel::declareQML();

  //  qInstallMessageHandler([](QtMsgType type, const QMessageLogContext&
  //  context,
  //                            const QString& msg) {
  //    //Тут логика работы с логами.
  //  });
}

int Amfik::clouddownloader::Application::executeApplication() {
  QGuiApplication app(_argc, _argv);

  QQmlApplicationEngine engine;
  const QUrl url(QStringLiteral("qrc:/main.qml"));
  QObject::connect(
      &engine, &QQmlApplicationEngine::objectCreated, &app,
      [url](QObject* obj, const QUrl& objUrl) {
        if (!obj && url == objUrl)
          QCoreApplication::exit(-1);
      },
      Qt::QueuedConnection);
  engine.load(url);

  return app.exec();
}

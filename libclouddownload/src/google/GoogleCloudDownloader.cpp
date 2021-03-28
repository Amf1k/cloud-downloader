#include "GoogleCloudDownloader.hpp"

#include "GoogleUploadHandler.hpp"

Amfik::libclouddownloader::GoogleCloudDownloader::GoogleCloudDownloader(
    Amfik::libclouddownloader::GoogleCloudConfig config,
    QObject* parent)
    : ICloudDownloader(parent),
      _config(std::move(config)),
      _unfinishedUploads{} {}

QSharedPointer<Amfik::libclouddownloader::IUploadHandler>
Amfik::libclouddownloader::GoogleCloudDownloader::upload(
    const Amfik::libclouddownloader::UploadParams& params) {
  auto handler = QSharedPointer<GoogleUploadHandler>::create(
      _config.apiKey(), _config.accessToken(), params.path());
  connect(
      handler.get(), &IUploadHandler::finished, this,
      [this, handler]() {
        emit finished(handler);
        //Неочень приятно, но из-за того что я захватил в лябду умный указатель
        //и в коннкте у нас сендер - это узказатель из умного указателя, есть
        //вероятность того, что будет утечка - коннект ждет когда умрет объект,
        //чтобы разрушить лямбду, а лямбда захватил умный указатель и объект
        //будет жить пока жива лямбда
        disconnect(handler.get());
        std::unique_lock lock(_mutex);
        _unfinishedUploads.removeOne(handler);
      },
      Qt::QueuedConnection);

  std::unique_lock lock(_mutex);
  _unfinishedUploads.append(handler);
  handler->start();
  return handler;
}

QList<QSharedPointer<Amfik::libclouddownloader::IUploadHandler> >
Amfik::libclouddownloader::GoogleCloudDownloader::uploads() const {
  std::shared_lock lock(_mutex);
  return _unfinishedUploads;
}

Amfik::libclouddownloader::CloudType
Amfik::libclouddownloader::GoogleCloudDownloader::type() const {
  return CloudType::Google;
}

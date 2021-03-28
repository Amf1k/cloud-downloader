#ifndef GOOGLEUPLOADHANDLER_HPP
#define GOOGLEUPLOADHANDLER_HPP
#include <QNetworkAccessManager>
#include <QScopedPointer>

#include "IUploadHandler.hpp"
namespace Amfik::libclouddownloader {
/*
 *Немного странноватый класс, в целом думаю идея понятна - инкапсулировать
 *логику по работе с транспортом для конкретного провайдера. В силу упрощений,
 *тут не реализованны проверки на запущен или нет запрос, остановлен или нет
 *запрос и тд. Вообще тут нужна еще одна абстракция над QNetworkAccessManager, в
 *корой могут быть реализованны разные штуки, например, попытки отправитьHTTP
 *запрос и тд и которая поможет протестировать данный класс. Так же немного
 *странная в этом классе работа с загружаемым файлом...
 */
class GoogleUploadHandler : public IUploadHandler {
  Q_OBJECT
  friend class GoogleCloudDownloader;

 public:
  explicit GoogleUploadHandler(const QString& apiKey,
                               const QString& accessToken,
                               const QString& filePath,
                               QObject* parent = nullptr);

  // IUploadHandler interface
 public:
  void stop() override;

 protected:
  void start() override;

 signals:
  void _emitStop();

 private:
  QNetworkRequest makeRequest();

 private:
  QString _apiKey;
  QString _accessToken;
  QString _filePath;
  QScopedPointer<QNetworkAccessManager> _pManager;
};

}  // namespace Amfik::libclouddownloader
#endif  // GOOGLEUPLOADHANDLER_HPP

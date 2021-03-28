#include "GoogleUploadHandler.hpp"

#include <QFile>
#include <QFileInfo>
#include <QMimeDatabase>
#include <QNetworkReply>
#include <QUrl>
#include <QUrlQuery>

const QString GOOGLE_DRIVE_FILE_CREATE_URL{
    "https://www.googleapis.com/drive/v3/files"};

Amfik::libclouddownloader::GoogleUploadHandler::GoogleUploadHandler(
    const QString& apiKey,
    const QString& accessToken,
    const QString& filePath,
    QObject* parent)
    : IUploadHandler(parent),
      _apiKey(apiKey),
      _accessToken(accessToken),
      _filePath(filePath),
      _pManager(new QNetworkAccessManager) {}

void Amfik::libclouddownloader::GoogleUploadHandler::start() {
  emit started();

  QFile* uploadedFile = new QFile(_filePath, this);
  //очевидно тут нужно по лучше ошибку обрабатывать.
  if (!uploadedFile->open(QIODevice::ReadOnly)) {
    emit errorOccurred(UploadError::UnknownError);
    uploadedFile->deleteLater();
    return;
  }

  auto request = makeRequest();
  auto reply = _pManager->post(request, uploadedFile);
  //очевидно и тут нужно по нормальному обрабатывать ошибки.
  connect(reply, &QNetworkReply::errorOccurred, this, [this, reply] {
    qWarning() << "Error request" << reply->errorString();
    emit errorOccurred(UploadError::UnknownError);
  });
  connect(reply, &QNetworkReply::finished, this, [this, reply, uploadedFile] {
    emit finished();
    uploadedFile->deleteLater();
    reply->deleteLater();
  });
  connect(reply, &QNetworkReply::uploadProgress, this,
          &GoogleUploadHandler::uploadProgress);
  connect(this, &GoogleUploadHandler::_emitStop, reply,
          [reply] { reply->abort(); });
}

void Amfik::libclouddownloader::GoogleUploadHandler::stop() {
  emit _emitStop();
}

QNetworkRequest Amfik::libclouddownloader::GoogleUploadHandler::makeRequest() {
  QMimeDatabase db;
  QMimeType type = db.mimeTypeForFile(_filePath);
  QFileInfo fileInfo(_filePath);
  QUrl requestUrl(GOOGLE_DRIVE_FILE_CREATE_URL);
  requestUrl.setQuery(QUrlQuery{{"key", _apiKey}, {"uploadType", "media"}});
  QNetworkRequest request(requestUrl);
  request.setRawHeader("Authorization",
                       QString("Bearer %1").arg(_accessToken).toUtf8());
  request.setHeader(QNetworkRequest::ContentTypeHeader, type.name());
  request.setHeader(QNetworkRequest::ContentLengthHeader, fileInfo.size());
  return request;
}

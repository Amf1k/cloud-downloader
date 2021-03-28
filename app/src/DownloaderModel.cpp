#include "DownloaderModel.hpp"

#include <CloudDownloaderFactory.hpp>
#include <IUploadHandler.hpp>
#include <QDebug>
#include <algorithm>

using namespace Amfik::libclouddownloader;

Amfik::clouddownloader::DownloaderModel::DownloaderModel(QObject* parent)
    : QAbstractListModel(parent),
      _pCloudDownloader(libclouddownloader::Create(
          CloudType::Google,
          GoogleCloudConfig{"apiKey", "accessToken"})),  //Хардкод
      _uploadFiles{} {}

void Amfik::clouddownloader::DownloaderModel::upload(const QUrl& fileuri) {
  if (!fileuri.isLocalFile()) {
    qWarning() << fileuri << "is not local file";
    return;
  }
  auto filePath = fileuri.toLocalFile();
  auto handler = _pCloudDownloader->upload(
      UploadParams{UploadParams::UploadType::Media, filePath});
  //Ну тут тупое дублирование + в целом какая-то куча кода, я все понимаю, но...
  connect(handler.get(), &IUploadHandler::finished, this, [this, filePath] {
    auto it = std::find_if(
        _uploadFiles.begin(), _uploadFiles.end(),
        [filePath](FileInfoUpload info) { return info.name == filePath; });
    if (it == _uploadFiles.end()) {
      qWarning() << "Not found file info for update";
      return;
    }
    (*it).isFinished = true;
    auto a = (*it);
    updateRolesChanging({Roles::IsFinished}, toRow(it));

    qDebug() << "finished upload file:" << filePath;
  });

  connect(
      handler.get(), &IUploadHandler::errorOccurred, this, [this, filePath] {
        auto it = std::find_if(
            _uploadFiles.begin(), _uploadFiles.end(),
            [filePath](FileInfoUpload info) { return info.name == filePath; });
        if (it == _uploadFiles.end()) {
          qWarning() << "Not found file info for update";
          return;
        }
        (*it).isErrored = true;
        updateRolesChanging({Roles::isErrored}, toRow(it));
        qDebug() << "error occurred upload file";
      });

  connect(handler.get(), &IUploadHandler::uploadProgress, this,
          [this, filePath](qint64 bytesSent, qint64 bytesTotal) {
            auto it = std::find_if(_uploadFiles.begin(), _uploadFiles.end(),
                                   [filePath](FileInfoUpload info) {
                                     return info.name == filePath;
                                   });
            if (it == _uploadFiles.end()) {
              qWarning() << "Not found file info for update";
              return;
            }
            int progress = bytesTotal > 0 ? (bytesSent / bytesTotal * 100) : 0;
            (*it).uploadProgress = progress;
            updateRolesChanging({Roles::UploadProgress}, toRow(it));
            qDebug() << "upload progress" << bytesSent << bytesTotal;
          });

  beginInsertRows(QModelIndex(), _uploadFiles.size(), _uploadFiles.size());
  _uploadFiles.append(FileInfoUpload{filePath, 0, false, false});
  endInsertRows();
}

int Amfik::clouddownloader::DownloaderModel::rowCount(
    const QModelIndex& parent) const {
  return _uploadFiles.count();
}

QVariant Amfik::clouddownloader::DownloaderModel::data(const QModelIndex& index,
                                                       int role) const {
  if (!index.isValid())
    return QVariant();
  auto filePath = _uploadFiles.value(index.row());
  switch (role) {
    case Name:
      return filePath.name;
    case UploadProgress:
      return filePath.uploadProgress;
    case IsFinished:
      return filePath.isFinished;
    case isErrored:
      return filePath.isErrored;
  }
  return QVariant{};
}

QHash<int, QByteArray> Amfik::clouddownloader::DownloaderModel::roleNames()
    const {
  static QHash<int, QByteArray> rolesNamesMap{
      {Roles::Name, "name"},
      {Roles::UploadProgress, "uploadProgress"},
      {Roles::IsFinished, "isFinished"},
      {Roles::isErrored, "isErrored"}};
  return rolesNamesMap;
}

void Amfik::clouddownloader::DownloaderModel::updateRolesChanging(
    const QVector<int>& changedRoles,
    int row) {
  auto index = createIndex(row, 0);
  emit dataChanged(index, index, changedRoles);
}

int Amfik::clouddownloader::DownloaderModel::toRow(
    QList<FileInfoUpload>::Iterator it) {
  if (int row = _uploadFiles.indexOf(*it); row != -1) {
    qInfo() << "convert iterator to row" << row;
    return row;
  } else {
    qCritical() << "Failed convert iterator to row, return 0";
    return 0;
  }
}

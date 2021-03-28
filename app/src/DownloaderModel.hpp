#ifndef DOWNLOADERMODEL_HPP
#define DOWNLOADERMODEL_HPP

#include <QAbstractListModel>
#include <QMap>
#include <QSharedPointer>
#include <QtQml>

namespace Amfik::libclouddownloader {
class ICloudDownloader;
class IUploadHandler;
}  // namespace Amfik::libclouddownloader

namespace Amfik::clouddownloader {

struct FileInfoUpload {
  QString name;
  int uploadProgress;
  bool isFinished;
  bool isErrored;

  bool operator==(const FileInfoUpload& other) { return name == other.name; }
};

class DownloaderModel : public QAbstractListModel {
  Q_OBJECT
 public:
  enum Roles { Name = Qt::UserRole + 1, UploadProgress, IsFinished, isErrored };
  explicit DownloaderModel(QObject* parent = nullptr);
  static void declareQML() {
    qmlRegisterType<DownloaderModel>("amf1k.models", 1, 0, "DownloaderModel");
  }

  Q_INVOKABLE void upload(const QUrl& fileuri);

  // QAbstractItemModel interface
 public:
  int rowCount(const QModelIndex& parent) const override;
  QVariant data(const QModelIndex& index, int role) const override;
  QHash<int, QByteArray> roleNames() const override;

 protected:
  void updateRolesChanging(const QVector<int>& changedRoles, int row);
  int toRow(QList<FileInfoUpload>::Iterator it);

 private:
  QSharedPointer<libclouddownloader::ICloudDownloader> _pCloudDownloader;
  QList<FileInfoUpload> _uploadFiles;
};
}  // namespace Amfik::clouddownloader
#endif  // DOWNLOADERMODEL_HPP

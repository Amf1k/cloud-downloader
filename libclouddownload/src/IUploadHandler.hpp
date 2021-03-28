#ifndef IUPLOADHANDLER_HPP
#define IUPLOADHANDLER_HPP
#include <QObject>

namespace Amfik::libclouddownloader {
//Понятно дело что ошибок будет больше, просто не хотелось по кнопкам жать.
enum class UploadError { UnknownError };

class IUploadHandler : public QObject {
  Q_OBJECT
 public:
  virtual ~IUploadHandler() = default;
  virtual void stop() = 0;

 protected:
  virtual void start() = 0;

 signals:
  void started();
  //сигнал о завершении кидается всегда и нужно за этим следить в
  //классах-реализациях. наверно узкое место, но все же...
  void finished();
  void errorOccurred(UploadError error);
  void uploadProgress(qint64 bytesSent, qint64 bytesTotal);

 protected:
  explicit IUploadHandler(QObject* parent = nullptr) : QObject(parent) {}
};
}  // namespace Amfik::libclouddownloader

#endif  // IUPLOADHANDLER_HPP

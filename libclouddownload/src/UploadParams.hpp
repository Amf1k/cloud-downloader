#ifndef UPLOADPARAMS_HPP
#define UPLOADPARAMS_HPP
#include <QObject>
#include <QString>

namespace Amfik::libclouddownloader {
class UploadParams {
 public:
  enum class UploadType { Media, Multipart, Resumable };

 public:
  explicit UploadParams(UploadType type, QString path);
  UploadType type() const;
  const QString& path() const;

 private:
  UploadType _type;
  QString _path;
};

}  // namespace Amfik::libclouddownloader
#endif  // UPLOADPARAMS_HPP

#include "UploadParams.hpp"

Amfik::libclouddownloader::UploadParams::UploadParams(
    Amfik::libclouddownloader::UploadParams::UploadType type,
    QString path)
    : _type(type), _path(std::move(path)) {}

Amfik::libclouddownloader::UploadParams::UploadType
Amfik::libclouddownloader::UploadParams::type() const {
  return _type;
}

const QString& Amfik::libclouddownloader::UploadParams::path() const {
  return _path;
}

#ifndef GOOGLECLOUDDOWNLOADER_HPP
#define GOOGLECLOUDDOWNLOADER_HPP
#include <shared_mutex>

#include "GoogleCloudConfig.hpp"
#include "ICloudDownloader.hpp"

namespace Amfik::libclouddownloader {
class GoogleCloudDownloader : public ICloudDownloader {
  Q_OBJECT
 public:
  explicit GoogleCloudDownloader(GoogleCloudConfig config,
                                 QObject* parent = nullptr);

  // ICloudDownloader interface
 public:
  QSharedPointer<IUploadHandler> upload(const UploadParams& params) override;
  QList<QSharedPointer<IUploadHandler>> uploads() const override;
  CloudType type() const override;

 private:
  GoogleCloudConfig _config;
  mutable std::shared_mutex _mutex;
  QList<QSharedPointer<IUploadHandler>> _unfinishedUploads;
};
}  // namespace Amfik::libclouddownloader

#endif  // GOOGLECLOUDDOWNLOADER_HPP

#ifndef CLOUDDOWNLOADERFACTORY_HPP
#define CLOUDDOWNLOADERFACTORY_HPP
#include "google/GoogleCloudDownloader.hpp"
namespace Amfik::libclouddownloader {
// TODO: вынести в отдельную фабрику.
template <class ConfigType>
static QSharedPointer<ICloudDownloader> Create(CloudType type,
                                               ConfigType config) {
  if (type == CloudType::Google) {
    return QSharedPointer<GoogleCloudDownloader>::create(config);
  }
  throw std::runtime_error("Not implemented cloud.");
}
}  // namespace Amfik::libclouddownloader
#endif  // CLOUDDOWNLOADERFACTORY_HPP

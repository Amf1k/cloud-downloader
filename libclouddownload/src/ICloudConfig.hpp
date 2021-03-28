#ifndef ICLOUDCONFIG_HPP
#define ICLOUDCONFIG_HPP
#include <QString>

namespace Amfik::libclouddownloader {
class ICloudConfig {
 public:
  virtual ~ICloudConfig() = default;
  ICloudConfig(const ICloudConfig&) = default;
  ICloudConfig(ICloudConfig&&) = default;
  ICloudConfig& operator=(const ICloudConfig& x) = default;
  ICloudConfig& operator=(ICloudConfig&& x) = default;

 public:
  virtual const QString& apiKey() const = 0;
  virtual const QString& accessToken() const = 0;

 protected:
  ICloudConfig(){};
};
}  // namespace Amfik::libclouddownloader

#endif  // ICLOUDCONFIG_HPP

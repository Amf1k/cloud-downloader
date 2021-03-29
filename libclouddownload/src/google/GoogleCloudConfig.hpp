#ifndef GOOGLECLOUDCONFIG_HPP
#define GOOGLECLOUDCONFIG_HPP
#include "ICloudConfig.hpp"
namespace Amfik::libclouddownloader {
class GoogleCloudConfig : public ICloudConfig {
 public:
  explicit GoogleCloudConfig(QString apiKey, QString accessToken);

  // ICloudConfig interface
 public:
  const QString& apiKey() const override;
  const QString& accessToken() const override;

 private:
  QString _apiKey;
  QString _accessToken;
};
}  // namespace Amfik::libclouddownloader

#endif  // GOOGLECLOUDCONFIG_HPP

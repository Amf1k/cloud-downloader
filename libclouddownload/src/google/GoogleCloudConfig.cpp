#include "GoogleCloudConfig.hpp"

Amfik::libclouddownloader::GoogleCloudConfig::GoogleCloudConfig(
    QString apiKey,
    QString accessToken)
    : _apiKey(std::move(apiKey)), _accessToken(std::move(accessToken)) {}

const QString& Amfik::libclouddownloader::GoogleCloudConfig::apiKey() const {
  return _apiKey;
}

const QString& Amfik::libclouddownloader::GoogleCloudConfig::accessToken()
    const {
  return _accessToken;
}

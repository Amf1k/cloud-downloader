#ifndef ICLOUDDOWNLOADER_HPP
#define ICLOUDDOWNLOADER_HPP
#include <QList>
#include <QObject>
#include <QSharedPointer>

#include "UploadParams.hpp"

namespace Amfik::libclouddownloader {
class IUploadHandler;

enum class CloudType { Google, Yandex, Mailru, Dropbox, Unknown };

/*
 * Вообще можно не делать QObject этот интерфейс и всех наследников, т.к. вроде
 * как и не особо надо... Но решил оставить, т.к. в перспективе наверно это все
 * понадобится (например, интерфейс должен расшириться и сюда добавится не
 * только загрузка файла, но и получение списка, удаление и тд. Можно будет
 * легко добавить сигнал о том, что список файлов изменился и все в таком духе.
 */
class ICloudDownloader : public QObject {
  Q_OBJECT
 public:
  virtual ~ICloudDownloader() = default;
  /*
   * Будем бросать исключение при ошибке добавления
   */
  virtual QSharedPointer<IUploadHandler> upload(const UploadParams& params) = 0;
  /*
   * Список не законченных загрузок.
   */
  virtual QList<QSharedPointer<IUploadHandler>> uploads() const = 0;
  virtual CloudType type() const = 0;

 signals:
  void finished(QSharedPointer<IUploadHandler> handler);

 protected:
  ICloudDownloader(QObject* parent = nullptr) : QObject(parent) {}
};
}  // namespace Amfik::libclouddownloader

#endif  // ICLOUDDOWNLOADER_HPP

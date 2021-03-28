#ifndef APPLICATION_HPP
#define APPLICATION_HPP
#include <memory>

namespace Amfik::clouddownloader {
class Application {
 public:
  explicit Application(int argc, char* argv[]);
  static std::unique_ptr<Application> Create(int argc, char* argv[]);
  int exec();

 private:
  void init();
  int executeApplication();

 private:
  int _argc;
  char** _argv;
};
}  // namespace Amfik::clouddownloader

#endif  // APPLICATION_HPP

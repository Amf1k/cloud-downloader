#include "Application.hpp"

int main(int argc, char* argv[]) {
  auto app = Amfik::clouddownloader::Application::Create(argc, argv);
  return app ? app->exec() : 1;
}

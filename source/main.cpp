#include "app/application.h"

using namespace deft;

int main(int argc, char const *argv[]) {
  auto app = new Application;

  app->run();

  delete app;

  return 0;
}

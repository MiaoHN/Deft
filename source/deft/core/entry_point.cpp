#include "core/entry_point.h"

int main(int argc, char** argv) {
  auto app = deft::CreateApplication();

  app->initialize();

  app->run();

  delete app;

  return 0;
}

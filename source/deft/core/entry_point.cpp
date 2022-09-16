#include "core/entry_point.h"

int main(int argc, char** argv) {
  auto app = deft::CreateApplication();

  app->run();

  delete app;

  return 0;
}

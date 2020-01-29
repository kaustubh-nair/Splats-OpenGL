#include "../include/controller.h"

int main()
{
  Controller *controller = new Controller();
  controller->mainLoop();
  delete controller;
  return 0;
}

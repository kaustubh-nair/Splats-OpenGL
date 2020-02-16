#include "../include/controller.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../include/definitions.h"


int main()
{
  Controller *controller = new Controller();
  controller->mainLoop();
  delete controller;
  return 0;
}

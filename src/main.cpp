#include <iostream>
#include "SDL_Window.hpp"

int main()
{
  std::cout << "Hello world" << std::endl;

  SDLWindow window("myWindow", 500, 500);
  window.run();
  return EXIT_SUCCESS;
}

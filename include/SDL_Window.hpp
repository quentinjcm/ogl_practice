#ifndef SDLWINDOW_HPP__
#define SDLWINDOW_HPP__

#include <memory>
#include <string>

#include "SDL2/SDL.h"
#include "ngl/Util.h"

class SDLWindow
{
public:
  SDLWindow(std::string _winName, int _width, int _height);
  void run();
private:
  void init();
  GLuint loadShaderSrc(std::string _fileName);
  void keyUp();
  void keyDown();

  SDL_GLContext createGLContext();

  SDL_Window *m_window;
  std::string m_winName;
  int m_winWidth;
  int m_winHeight;
  SDL_Event m_currentEvent;
  bool m_run = true;
};

#endif

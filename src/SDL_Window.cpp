#include <iostream>
#include <vector>
#include <fstream>

#include "ngl/Vec2.h"
#include "ngl/NGLInit.h"

#include "SDL_Window.hpp"

SDLWindow::SDLWindow(std::string _winName, int _width, int _height):
  m_winName(_winName),
  m_winWidth(_width),
  m_winHeight(_height)
{
  init();
}

void SDLWindow::init()
{
  if (SDL_Init( SDL_INIT_VIDEO ) < 0 )
  {
    //failed to init
    std::cerr << "ERROR: SDL Video failed to init in window " << m_winName << std::endl;
    exit(EXIT_FAILURE);
  }
}

void SDLWindow::run()
{
  m_window = SDL_CreateWindow(m_winName.c_str(),
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              m_winWidth,
                              m_winHeight,
                              SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
  if (!m_window)
  {
    std::cerr << "ERROR: unable to create window " << m_winName << std::endl;
    exit(EXIT_FAILURE);
  }

  SDL_GLContext glContext = createGLContext();
  if (!glContext)
  {
    std::cerr << "ERROR: glCOntext creation failed" << std::endl;
    exit(EXIT_FAILURE);
  }

  ngl::NGLInit::instance();
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  SDL_GL_SwapWindow(m_window);


  //vertex data
  std::vector<ngl::Vec2> verts;
  verts.push_back(ngl::Vec2(0, 0.5));
  verts.push_back(ngl::Vec2(0.5, -0.5));
  verts.push_back(ngl::Vec2(-0.5, -0.5));


  GLuint vbo;
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER,
               verts.size() * sizeof(ngl::Vec2),
               &verts[0],
               GL_STATIC_DRAW);

  //shader shit
  std::ifstream vertShaderFile;
  std::ifstream fragShaderFile;
  vertShaderFile.open("shaders/vertexShader.glsl");
  fragShaderFile.open("shaders/fragShader.glsl");

  std::string vertShaderSrc("");
  std::string fragShaderSrc("");

  if(vertShaderFile.is_open())
  {
    std::string line;
    while(std::getline(vertShaderFile, line))
    {
      vertShaderSrc += line;
    }
    vertShaderFile.close();
  }

  if(fragShaderFile.is_open())
  {
    std::string line;
    while(std::getline(fragShaderFile, line))
    {
      fragShaderSrc += line;
    }
    fragShaderFile.close();
  }


  // compiling shaders
  GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertShader, 1, vertShader.c_str, NULL);






  //GLuint fragShader









  while (m_run)
  {
    SDL_PollEvent(&m_currentEvent);
    switch (m_currentEvent.type)
    {
      case SDL_QUIT: m_run = false; break;
    case SDL_KEYUP: keyUp(); break;
    case SDL_KEYDOWN: keyDown(); break;
    }
    SDL_GL_SwapWindow(m_window);
  }


  SDL_GL_DeleteContext(glContext);
  SDL_DestroyWindow(m_window);
  SDL_Quit();
}

SDL_GLContext SDLWindow::createGLContext()
{
  #ifdef __APPLE__
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
  #else
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  #endif
  // set multi sampling else we get really bad graphics that alias
  SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
  SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES,4);
  // Turn on double buffering with a 24bit Z buffer.
  // You may need to change this to 16 or 32 for your system
  // on mac up to 32 will work but under linux centos build only 16
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
  // enable double buffering (should be on by default)
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  return SDL_GL_CreateContext(m_window);
}

void SDLWindow::keyUp()
{
  std::cout << "Key up event" << std::endl;
  SDL_Keycode key = m_currentEvent.key.keysym.sym;
  switch(key)
  {
    case SDLK_ESCAPE: m_run = false;
  }
}

void SDLWindow::keyDown()
{
  std::cout << "Key down event" << std::endl;
}

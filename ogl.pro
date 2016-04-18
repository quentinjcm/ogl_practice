TARGET = ogl

CONFIG += c++11

SOURCES += $$PWD/src/main.cpp \
           $$PWD/src/SDL_Window.cpp

HEADERS += $$PWD/include/SDL_Window.hpp

INCLUDEPATH += ./include

include($(HOME)/NGL/UseNGL.pri)

QMAKE_CXXFLAGS += $$system(sdl2-config --cflags)

LIBS +=$$system(sdl2-config --libs)

OBJECTS_DIR = obj/

OTHER_FILES += $$PWD/shaders/*




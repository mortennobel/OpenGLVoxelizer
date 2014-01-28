#-------------------------------------------------
#
# Project created by QtCreator 2014-01-13T07:06:11
#
#-------------------------------------------------

QT += core gui\
      opengl widgets

CONFIG += c++11

win32{
    INCLUDEPATH +=  "$${PWD}/../glew-1.10.0/include/"
    !contains(QMAKE_TARGET.arch, x86_64) {
        message("x86 build"   )
        LIBS *=  "$${PWD}/../glew-1.10.0/lib/Release/Win32/glew32s.lib"
    } else {
        message("x86_64 build")
        LIBS *=  "$${PWD}/../glew-1.10.0/lib/Release/x64/glew32s.lib"
    }
}

TARGET = OpenGL3x
TEMPLATE = app

SOURCES += main.cpp \
    mywidget.cpp \
    glheader.cpp \
    voxelizer.cpp

HEADERS  += \
    mywidget.h \
    glheader.h \
    voxelizer.h

OTHER_FILES += \
    simple.frag \
    simple.vert

RESOURCES +=  core-profile.qrc


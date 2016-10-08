TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    scene.cpp \
    glslprogram.cpp

HEADERS += \
    scene.h \
    skybox.h \
    camera.h \
    defines.h \
    glinclude.h \
    glslprogram.h \
    vbotorus.h

INCLUDEPATH += /usr/include/GL \
/usr/include/glm \
/usr/include/GL/GLFW \
/usr/include/soil \

LIBS += /usr/lib/x86_64-linux-gnu/libGLEW.so \
/usr/lib/x86_64-linux-gnu/libglfw.so.3 \
/usr/lib/x86_64-linux-gnu/libGL.so \
/usr/lib/x86_64-linux-gnu/libGLU.so \
/usr/lib/x86_64-linux-gnu/libglut.so \
/usr/lib/libSOIL.so

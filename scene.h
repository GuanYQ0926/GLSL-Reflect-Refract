#ifndef SCENE_H
#define SCENE_H

#include "glinclude.h"
#include "glslprogram.h"
#include "skybox.h"
#include "vbotorus.h"

#include <glm/glm.hpp>
using glm::mat4;


class Scene
{
private:
    GLSLProgram prog;

    Skybox* skybox;
    VBOTorus* torusReflect;
    VBOTorus* torusRefract;
    mat4 model;
    mat4 view;
    mat4 projection;

    void setMatrices();
    void compileAndLinkShader();
    GLuint loadCubeMap(const char* filepath);

public:
    Scene();
    GLuint initScene();
    void render(vec3 cameraPos, mat4 cameraView, mat4 cameraProjection);

};

#endif // SCENE_H

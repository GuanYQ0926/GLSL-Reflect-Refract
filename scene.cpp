#include "scene.h"
#include "defines.h"

#include <cstdio>
#include <cstdlib>

#include <iostream>
using std::cout;
using std::endl;

#include <soil/SOIL.h>

using glm::vec3;
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform2.hpp>

Scene::Scene()
{
}

GLuint Scene::initScene()
{
    compileAndLinkShader();
    glEnable(GL_DEPTH_TEST);

    skybox = new Skybox();
    float c = 3.5f;
    torusReflect = new VBOTorus(0.7f*c, 0.3f*c, 50, 50);
    torusRefract = new VBOTorus(0.7f*c, 0.3f*c, 50, 50);

    projection = mat4(1.0f);

    return loadCubeMap("/home/guanyuqing/Documents/cppcode/reflect_refract/reflect_refract/textures");
}

void Scene::render(vec3 cameraPos, mat4 cameraView, mat4 cameraProjection)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //vec3 cameraPos = vec3(1.0f);////////////////////////////////////
    view = cameraView;//glm::lookAt(cameraPos, vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
    projection = cameraProjection;
    prog.setUniform("WorldCameraPosition", cameraPos);

    prog.setUniform("DrawReflect", false);
    prog.setUniform("DrawRefract", false);
    model = mat4(1.0f);
    setMatrices();
    skybox->render();

    prog.setUniform("DrawReflect", true);
    prog.setUniform("Material.MaterialColor", vec4(0.5f, 0.5f, 0.5f, 1.0f));
    prog.setUniform("Material.ReflectionFactor", 0.85f);
    model = mat4(1.0f);
    model *= glm::translate(vec3(5.0f,0.0f,-5.0f));
    //model *= glm::rotate(-90.0f, vec3(1.0f,0.0f,0.0f));
    setMatrices();
    torusReflect->render();
    prog.setUniform("DrawReflect", false);

    prog.setUniform("DrawRefract", true);
    prog.setUniform("Material.Eta", 0.94f);
    prog.setUniform("Material.ReflectionFactor", 0.3f);
    model = mat4(1.0f);
    model *= glm::translate(vec3(-5.0f,0.0f,-5.0f));
    setMatrices();
    torusRefract->render();


}

GLuint Scene::loadCubeMap(const char* filepath)
{
    string imgname[] = {"lostvalley_east.bmp", "lostvalley_west.bmp",
                              "lostvalley_up.bmp", "lostvalley_down.bmp",
                              "lostvalley_south.bmp", "lostvalley_north.bmp"};
    GLuint targets[] = {
        GL_TEXTURE_CUBE_MAP_POSITIVE_X, GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
        GL_TEXTURE_CUBE_MAP_POSITIVE_Y, GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
        GL_TEXTURE_CUBE_MAP_POSITIVE_Z, GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
    };

    unsigned char* image;
    int width, height;

    glActiveTexture(GL_TEXTURE0);
    GLuint texID;
    glGenTextures(1, &texID);

    glBindTexture(GL_TEXTURE_CUBE_MAP, texID);
    for(int i=0;i<6;i++)
    {
        string texName = string(filepath) + "/" + imgname[i];
        image = SOIL_load_image(texName.c_str(), &width, &height,
                                0, SOIL_LOAD_RGB);
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X+i, 0, GL_RGB, width, height,
                     0, GL_RGB, GL_UNSIGNED_BYTE, image);
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
    SOIL_free_image_data(image);
    //prog.setUniform("CubeMapTex", 0);
    return texID;
}

void Scene::setMatrices()
{
    mat4 mv = view * model;
    prog.setUniform("ModelMatrix", model);
    prog.setUniform("MVP", projection * mv);
}

void Scene::compileAndLinkShader()
{
    if(!prog.compileShaderFromFile("/home/guanyuqing/Documents/cppcode/reflect_refract/reflect_refract/shaders/shader.vs",
                                   GLSLShader::VERTEX))
    {
        printf("Vertex shader failed to compile!\n%s",
               prog.log().c_str());
        exit(1);
    }
    if(!prog.compileShaderFromFile("/home/guanyuqing/Documents/cppcode/reflect_refract/reflect_refract/shaders/shader.fs",
                                   GLSLShader::FRAGMENT))
    {
        printf("Fragment shader failed to compile!\n%s",
               prog.log().c_str());
        exit(1);
    }
    if(!prog.link())
    {
        printf("Shader program failed to link!\n%s",
               prog.log().c_str());
        exit(1);
    }
    prog.use();
}




























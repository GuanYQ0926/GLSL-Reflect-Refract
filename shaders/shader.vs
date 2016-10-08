#version 330

layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec3 VertexNormal;
layout (location = 2) in vec2 VertexTexCoord;

out vec3 ReflectDir;
out vec3 RefractDir;

struct MaterialInfo{
    vec4 MaterialColor;
    float Eta;
    float ReflectionFactor;
};
uniform MaterialInfo Material;

uniform bool DrawReflect;
uniform bool DrawRefract;
uniform vec3 WorldCameraPosition;

uniform mat4 ModelViewMatrix;
uniform mat4 ModelMatrix;
uniform mat3 NormalMatrix;
uniform mat4 ProjectionMatrix;
uniform mat4 MVP;

void main()
{
    if(DrawReflect)
    {
        vec3 worldPos = vec3(ModelMatrix * vec4(VertexPosition, 1.0));
        vec3 worldNorm = vec3(ModelMatrix * vec4(VertexNormal, 0.0));
        vec3 worldView = normalize(WorldCameraPosition - worldPos);

        ReflectDir = reflect(-worldView, worldNorm);
    }
    else if(DrawRefract)
    {
        vec3 worldPos = vec3(ModelMatrix * vec4(VertexPosition, 1.0));
        vec3 worldNorm = vec3(ModelMatrix * vec4(VertexNormal, 0.0));
        vec3 worldView = normalize(WorldCameraPosition - worldPos);

        ReflectDir = reflect(-worldView, worldNorm);
        RefractDir = refract(-worldView, worldNorm, Material.Eta);
    }
    else
    {
        ReflectDir = VertexPosition;
    }

    gl_Position = MVP * vec4(VertexPosition, 1.0);
}

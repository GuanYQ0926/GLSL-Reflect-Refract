#version 330

in vec3 ReflectDir;
in vec3 RefractDir;

uniform samplerCube CubeMapTex;

uniform bool DrawReflect;
uniform bool DrawRefract;

struct MaterialInfo{
    vec4 MaterialColor;
    float Eta;
    float ReflectionFactor;
};
uniform MaterialInfo Material;

layout (location = 0) out vec4 FragColor;

void main()
{
    vec4 reflectColor = texture(CubeMapTex, ReflectDir);
    vec4 refractColor = texture(CubeMapTex, RefractDir);

    if(DrawReflect)
    {
        FragColor = mix(Material.MaterialColor, reflectColor, Material.ReflectionFactor);
    }
    else if(DrawRefract)
    {
        FragColor = mix(refractColor, reflectColor, Material.ReflectionFactor);
    }
    else
    {
        FragColor = reflectColor;
    }
}

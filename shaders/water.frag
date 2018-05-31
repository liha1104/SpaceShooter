#version 150
uniform samplerCube skybox;
in mat4 modelView;
in vec4 pos_eye;
in vec3 normal;
out vec4 diffuseColor;
out vec4 refraction;

void main(void)
{
//    gl_FragColor = vec4(0.0, 0.0, 0.8, 0.2);

    float ratio = 1.0/1.3333;
    vec3 eyeCoord = vec3(pos_eye);
    vec3 refracted = refract(normalize(eyeCoord), normalize(normal), ratio);
//    refracted = vec3(inverse(modelView)*vec4(refracted,0.0));

    eyeCoord.x = -eyeCoord.x;

    vec3 reflection = reflect(-normalize(eyeCoord), normal);

    diffuseColor = texture(skybox, reflection);
    diffuseColor.a = 0.6;
}

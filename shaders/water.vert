uniform samplerCube skybox;
varying vec3 normalCoord;
uniform float rand;
varying mat4 modelView;

varying vec4 pos_eye;
varying vec3 normal;
uniform mat4 V;
void main(void)
{
    vec4 pos = gl_Vertex;

    modelView = gl_ModelViewMatrix;

    pos_eye = gl_ModelViewMatrix * gl_Vertex;


//    pos.y = sin(( pos.z + randomBullshit)/(float(64))) + cos(pos.x/(float(64))) * float(5) - float(5);
    pos.y = sin(( pos.z + rand)/(float(200))) + cos(pos.x/(float(200))) - float(35);

    gl_Position = gl_ModelViewProjectionMatrix * pos;

    normalCoord = gl_NormalMatrix * gl_Normal;
    normal = normalCoord;
}

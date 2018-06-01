
varying vec2 texCoord;


void main(void)
{
    vec4 pos = gl_Vertex;
    texCoord = gl_MultiTexCoord0.xy;
    gl_Position = gl_ModelViewProjectionMatrix*pos;
}

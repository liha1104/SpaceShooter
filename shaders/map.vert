uniform sampler2D  height;
varying vec4 texCoord;
varying vec3 normalCoord;

void main()
{
                vec3 normalCoord = gl_NormalMatrix * gl_Normal;
                vec4 pos = gl_Vertex;
                texCoord = gl_MultiTexCoord0;
                vec4 texHeight = texture2D(height, texCoord.xy);
                pos.y = 1.25 * ((texHeight.y * 100.0) - 150.0);
                pos.x = pos.x * 2.0;

    gl_Position = gl_ModelViewProjectionMatrix * pos;
}

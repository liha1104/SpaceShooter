uniform sampler2D  height;
varying vec4 texCoord;

void main()
{
                vec4 pos = gl_Vertex;
                texCoord = gl_MultiTexCoord0;
                vec4 texHeight = texture2D(height, texCoord.xy);
                pos.y = (texHeight.y * 100.0) - 90.0;

    gl_Position = gl_ModelViewProjectionMatrix * pos;
}

uniform sampler2D  color;
varying vec4 texCoord;

void main()
{
        gl_FragColor = texture2D(color, texCoord.xy);
}

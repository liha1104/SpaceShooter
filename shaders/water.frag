uniform sampler2D  tex_colormap;
varying vec4 texCoord;

void main()
{

        gl_FragColor = texture2D(tex_colormap, texCoord.xy);
        gl_FragColor.a = 0.8;
}

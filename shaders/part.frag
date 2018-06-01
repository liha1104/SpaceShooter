
varying vec2 texCoord;
varying vec2 position;
uniform sampler2D color;
uniform float fade;

void main(void)
{
    vec3 diffuseMaterial = texture2D(color, texCoord.xy).rgb;
    vec3 red = vec3(0.0,-0.36,-1.0);
    gl_FragColor = vec4(diffuseMaterial+red, fade);
}

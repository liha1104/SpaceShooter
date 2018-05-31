//#extension GL_EXT_gpu_shader4 : enable

varying vec2 texCoord;
varying vec2 position;
uniform sampler2D color;
uniform float fade;

/*!
  Gets input from vertex shader red.vert.

  We create a checker like pattern with this fragment shader.
  */
void main(void)
{
    //float color = 0.0;
    vec3 diffuseMaterial = texture2D(color, texCoord.xy).rgb;
    vec3 red = vec3(0.0,-0.36,-1.0);
    gl_FragColor = vec4(diffuseMaterial+red, fade);
}

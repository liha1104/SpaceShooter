uniform samplerCube skybox;
varying vec3 texCoord;
void main()
{
      gl_FragColor = textureCube(skybox, texCoord);
}

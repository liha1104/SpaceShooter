uniform float water_data;
varying vec4 texCoord;

void main()
{
                vec4 pos = gl_Vertex;
                texCoord = gl_MultiTexCoord0;
                float xpos = pos.x * 12.0;
                pos.x = xpos;
                pos.z = pos.z * 50.0;
                pos.y = -35.0 + (sin(gl_MultiTexCoord0.x * 20.0 * water_data));
                texCoord.x = texCoord.x + (water_data * 0.05);

                gl_Position = gl_ModelViewProjectionMatrix * pos;
}

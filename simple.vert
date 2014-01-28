#version 150

uniform mat4 mvp;

in vec4 vertex;
in vec4 normal;
out vec4 vNormal;

void main( void )
{
    gl_Position = mvp * vertex;
    vNormal = normal*0.5+vec4(0.5,0.5,0.5,0.5);
}

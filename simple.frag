#version 150

in vec4 vNormal;
out vec4 fragColor;

void main( void )
{
    fragColor = vNormal;
}

#version 410

uniform sampler2D    uTex0;

in vec4        Color;
in vec3        Normal;
in vec2        TexCoord0;
uniform float time;

out vec4     oColor;

void main( void )
{
    vec2 uv = TexCoord0;
    
    vec3 spectrum = vec3(0,0,0);
    vec4 result = vec4(
                       abs(sin(cos(time+3.*uv.y)*2.*uv.x+time)),
                       abs(cos(sin(time+2.*uv.x)*3.*uv.y+time)),
                       spectrum.x * 100.,
                       1.0);
    oColor = result;
}


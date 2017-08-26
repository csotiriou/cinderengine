#version 410

uniform mat4	ciModelViewProjection;
uniform mat3	ciNormalMatrix;
uniform mat4 ciModelView;
uniform float time;

in vec4		ciPosition;
in vec2		ciTexCoord0;
in vec3		ciNormal;
in vec4 ciColor;

out lowp vec4	    vColor;
out highp vec3	Normal;
out highp vec2	TexCoord0;
out vec4    vPosition;


void main( void )
{
	gl_Position	= ciModelViewProjection * ciPosition;
	TexCoord0	= ciTexCoord0;
	Normal		= ciNormalMatrix * ciNormal;
    vPosition  = ciModelView * ciPosition;
    vColor          = ciColor;
}

#version 150

uniform sampler2D	uTex0;

in vec4 vColor;


in vec3		Normal;
in vec2        TexCoord0;

uniform mat4    ciModelViewProjection;
uniform mat3    ciNormalMatrix;
uniform float   time;
uniform mat4    ciModelMatrix;
uniform vec3	lightPosition;

in vec4          vPosition;


out vec4 	oColor;

void main( void )
{
    vec3 worldPosition = ( ciModelMatrix * vPosition).xyz;
    
    vec3 worldNormal = normalize( vec3( ciModelMatrix * vec4( Normal, 0.0 ) ) );
    vec3 lightVector = normalize( lightPosition - worldPosition );
    float brightness = dot( worldNormal, lightVector );


    
   vec3 normal = normalize( -Normal );
   float diffuse = max( dot( normal, vec3( 0, 0, -1 ) ), 0 );
   vec3 textureColor = texture( uTex0, TexCoord0 ).rgb;

    vec3 newColor = vColor.xyz * brightness * textureColor;

    oColor = vec4(newColor, 1.0);
}

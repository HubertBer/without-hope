#version 330

#define FactorA vec2(100.0,100.0)
#define FactorB vec2(1.0,1.0)
#define FactorScale vec2(0.01,0.01)

in vec2 fragTexCoord;
in vec4 fragColor;

uniform sampler2D texture0;
uniform vec4 colDiffuse;
uniform float uTime = 0.0;

out vec4 finalColor;

void main()
{
	vec2 uniA = FactorA;
    vec2 uniB = FactorB;
    vec2 uniScale = FactorScale;

    vec2 dt = vec2(0.0, 0.0);
    dt.x = sin(uTime * uniA.x + uniB.x) * uniScale.x;
    dt.y = cos(uTime * uniA.y + uniB.y) * uniScale.y;

    vec4 texelColor = texture(texture0, fragTexCoord + dt);

    finalColor = texelColor*colDiffuse*fragColor;
}
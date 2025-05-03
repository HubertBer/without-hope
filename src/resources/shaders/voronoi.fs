#version 330

in vec2 fragTexCoord;
in vec4 fragColor;

uniform sampler2D texture0;
uniform vec4 colDiffuse;

uniform float time;         // Time uniform from Raylib
uniform vec2 resolution;    // Resolution of screen

out vec4 finalColor;

vec3 color1 = vec3(67.0 / 255.0, 101.0 / 255.0, 224.0 / 255.0);
vec3 color2 = vec3(15.0 / 255.0, 30.0 / 255.0, 84.0 / 255.0);

vec2 N22(vec2 p) {
    vec3 a = fract(p.xyx*vec3(123.34,234.34,345.65));
    a += dot(a, a+34.45);
    return fract(vec2(a.x*a.y, a.y*a.z));
}

void main()
{
    vec2 uv = fragTexCoord;
    
    float t = 100. + time*.01;
    float minDist = 100.;
    float cellIndex = 0.;
    vec2 cellPoint = vec2(0.);
    
    // Find the minDist and closest point
    for (float i=0.; i<50.; i++) {
        vec2 n = N22(vec2(i));
        vec2 p = sin(n*t)*.5;
        p.x *= resolution.x / resolution.y;
        float d = length(uv - p);
        if (d<minDist) {
            minDist = d;
            cellIndex = i;
            cellPoint = p;
        }
    }
    
    vec3 gradient = mix(color1, color2, minDist*2.);
    vec3 col = mix(gradient, color1, 0.4);
    
    // Determine the edge width between cells
    for (float i=0.; i<50.; i++) {
        if (i == cellIndex) continue;
        vec2 n = N22(vec2(i));
        vec2 p = sin(n*t)*.5;
        p.x *= resolution.x / resolution.y;
        float point_len = length(p-cellPoint);
        float cutoff = 0.2 * point_len*point_len;
        float d = length(uv - p);
        if (d-cutoff<minDist) {
            col = gradient;
        }
    }
    finalColor = vec4(col,1.0);
}
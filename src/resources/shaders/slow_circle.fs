#version 330

// Input vertex attributes (from vertex shader)
in vec2 fragTexCoord;
in vec4 fragColor;

// Input uniform values
uniform sampler2D texture0;
uniform vec4 colDiffuse;
uniform float time;
uniform float ringWidth; // Width of the ring in uv space

// Output fragment color
out vec4 finalColor;

bool isInRing(vec2 uv) {
    float dist = length(uv - vec2(0.5, 0.5));
    return dist >= (0.5 - ringWidth) && dist <= 0.5;
}

void main() {
    if (!isInRing(fragTexCoord)) {
        discard;
    }
    else {
        float edgeFactor = smoothstep(0, 1, (length(fragTexCoord - vec2(0.5, 0.5)) - (0.5 - ringWidth)) / ringWidth);
        vec3 col = vec3(105.0 / 255.0, 1.0 / 255.0, 41.0 / 255.0);
        
        finalColor = vec4(col, edgeFactor);
    }
}
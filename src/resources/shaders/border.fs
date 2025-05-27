#version 330

// Input vertex attributes (from vertex shader)
in vec2 fragTexCoord;
in vec4 fragColor;

// Input uniform values
uniform sampler2D texture0;
uniform vec4 colDiffuse;

// Custom uniforms for player position effect
uniform vec2 playerPosition;
uniform vec4 mapBounds;
uniform vec2 resolution;
const float maxDistance = 300.0;
const float intensity = 0.8;

// Output fragment color
out vec4 finalColor;

bool isInsideBounds(vec2 position) {
    return position.x >= mapBounds.x && position.x <= mapBounds.x + mapBounds.z &&
           position.y >= mapBounds.y && position.y <= mapBounds.y + mapBounds.w;
}

void main()
{
    vec2 screenPos = fragTexCoord * resolution;
    screenPos.y = resolution.y - screenPos.y; // Flip Y coordinate for OpenGL
      
    if (isInsideBounds(screenPos)) {
        finalColor = texture(texture0, fragTexCoord) * colDiffuse * fragColor;
    }
    else {
      // Texel color fetching from texture sampler
      vec4 texelColor = texture(texture0, fragTexCoord);

      // Calculate distance from current fragment to player position
      float distance = length(screenPos - playerPosition);
      
      // Calculate decay factor (1.0 at player position, 0.0 at maxDistance)
      float decayFactor = max(0.0, 1.0 - (distance / maxDistance));
      
      // Create red tint color
      vec4 redTint = vec4(1.0, 0.0, 0.0, 1.0);
      
      // Apply red tint based on distance with smooth falloff
      vec4 tintedColor = mix(texelColor, texelColor + redTint * intensity, decayFactor);
      
      // Final color calculation
      finalColor = tintedColor * colDiffuse * fragColor;
    }
}
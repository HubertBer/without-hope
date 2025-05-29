#include "Entity.h"

#include "../Renderer.h"

void Entity::loadTexture(const std::string& fileName, float scale) {
    texture = Renderer::getTexture(fileName);
    textureScale = scale;
    hitboxRadius = std::max(texture.width * scale, texture.height * scale) / 2.f;
}

void Entity::loadShader(const std::string &name) {
    shader = Renderer::getShader(name);
    useShader = true;
}

void Entity::drawTexture(){
    if (texture.id == 0) return;

    // Source rectangle uses actual texture dimensions
    Rectangle sourceRec = {0, 0, (float)texture.width, (float)texture.height};
    
    // Destination rectangle uses scaled dimensions
    float scaledWidth = texture.width * textureScale;
    float scaledHeight = texture.height * textureScale;
    Rectangle destRec = {posNow.x, posNow.y, scaledWidth, scaledHeight};

    if (useShader) {
        BeginShaderMode(shader);
    }
    DrawTexturePro(texture, sourceRec, destRec, {scaledWidth / 2.f, scaledHeight / 2.f}, rotation, textureTint);
    if (useShader) {
        EndShaderMode();
    }
}

void Entity::onDeath(){
    zombie=true;
}
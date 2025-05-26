#include "Entity.h"

#include "../Renderer.h"

void Entity::gameUpdate(GameData& game, float dt) {
    posNow = game.lerp(prevPos, pos);
}

void Entity::loadTexture(const std::string& fileName, float scale) {
    texture = Renderer::getTexture(fileName);
    texture.width *= scale;
    texture.height *= scale;
    hitboxRadius = std::max(texture.width, texture.height) / 2.f;
}

void Entity::loadShader(const std::string &name) {
    shader = Renderer::getShader(name);
    useShader = true;
}

void Entity::drawTexture(){
    if (texture.id == 0) return;

    Rectangle sourceRec = {0, 0, (float)texture.width, (float)texture.height};
    Rectangle destRec = {posNow.x, posNow.y, (float)texture.width, (float)texture.height};

    if (useShader) {
        BeginShaderMode(shader);
    }
    DrawTexturePro(texture, sourceRec, destRec, {texture.width / 2.f, texture.height / 2.f}, rotation, textureTint);
    if (useShader) {
        EndShaderMode();
    }
}

void Entity::onDeath(){
    zombie=true;
}
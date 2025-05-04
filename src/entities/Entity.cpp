#include "Entity.h"

void Entity::loadTexture(const std::string& path, float scale) {
    texture = LoadTexture(path.c_str());
    if (texture.id == 0) {
        std::cerr << "Failed to load texture\n";
    } else {
        texture.width *= scale;
        texture.height *= scale;
        hitboxRadius = std::max(texture.width, texture.height) / 2.f;
    }
}

void Entity::loadShader(const std::string &path) {
    shader = LoadShader(0, path.c_str());
    if (shader.id == 0) {
        std::cerr << "Failed to load shader\n";
    } else {
        useShader = true;
    }
}

void Entity::drawTexture(){
    if (texture.id == 0) return;

    Rectangle sourceRec = {0, 0, (float)texture.width, (float)texture.height};
    Rectangle destRec = {posNow.x, posNow.y, (float)texture.width, (float)texture.height};

    if (useShader) {
        BeginShaderMode(shader);
    }
    DrawTexturePro(texture, sourceRec, destRec, {texture.width / 2.f, texture.height / 2.f}, rotation, WHITE);
    if (useShader) {
        EndShaderMode();
    }
}
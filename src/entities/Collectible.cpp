#include "Collectible.h"
#include "raylib.h"
#include "raymath.h"
#include "Entity.h"
#include "../GameData.h"
#include "../rand.h"

namespace {
    Vector2 GetRandomInWorldPos(GameData& game) {
        auto mapBounds = game.getMapBoundaries();
        return Vector2{
            GetRandomFloat(mapBounds.x, mapBounds.x + mapBounds.width),
            GetRandomFloat(mapBounds.y, mapBounds.y + mapBounds.height),
        };
    }

    WeaponType RandomWeaponType() {
        return static_cast<WeaponType>(GetRandomValue(0, 2));
    }
}

void Collectible::loadProperTexture() {
    std::string textureName = "star.png"; 
    switch (weapon) {
        case WeaponType::MAIN:
            textureName = "star_1.png";
            break;
        case WeaponType::AUTOMATIC:
            textureName = "star_2.png";
            break;
        case WeaponType::SPECIAL:
            textureName = "star_3.png";
            break;
    }
    loadTexture(textureName, 0.8f);
}

Collectible::Collectible(Vector2 pos) : 
    Entity(pos, pos, Vector2{0,0}, BASE_RADIUS, 0, DrawingLayer::BLOOM),
    life_timer(LIFETIME),
    change_timer(CHANGE_COOLDOWN),
    weapon(RandomWeaponType())
{
    loadProperTexture();
    collider = MakeCircleCollider(pos, BASE_RADIUS);
}


void Collectible::physicsUpdate(GameData& game) {
    prevPos = pos;
    Vector2 dir = target - pos;
    
    if (Vector2Length(dir) <= MAX_SPEED * GameData::physicsDt) {
        pos = target;
        target = GetRandomInWorldPos(game);
    }
    pos += Vector2Normalize(dir) * MAX_SPEED * GameData::physicsDt;

    life_timer -= GameData::physicsDt;
    if (life_timer < 0) {
        onDeath();
        return;
    }

    change_timer -= GameData::physicsDt;
    if (change_timer < 0) {
        weapon = RandomWeaponType();
        loadProperTexture();
        change_timer += CHANGE_COOLDOWN;
    }

    collider.p0 = pos; 
}

void Collectible::collide(std::shared_ptr<Entity> other, GameData& game) {
    if(game.isPlayer(other)) {
        onDeath();
    }
}

void Collectible::draw() {
    drawTexture();
}

void Collectible::start(GameData& game) {
    target = GetRandomInWorldPos(game);   
}

EntityType Collectible::type() {
    return COLLECTIBLE;
}
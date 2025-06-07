#include "SimpleBullet.h"


#include <raymath.h>

#include "../GameData.h"

SimpleBullet::SimpleBullet(Vector2 prevPos, Vector2 pos, Vector2 velocity, float rotation, EntityType parent_type, Color color)
    : Entity(prevPos, pos, velocity,  BASE_RADIUS, rotation, DrawingLayer::BLOOM), parent_type{parent_type}{
    loadTexture("bullet.png", 0.2f);
    collider = MakeCircleCollider(pos, hitboxRadius);
    textureTint = color;
    if(parent_type==PLAYER){
        PlaySound(SoundLoader::audio["playerBullet"]);
    }
}

void SimpleBullet::gameUpdate(GameData& game, float dt) {
    posNow = game.lerp(prevPos, pos);
    lifetime -= dt;
    if(lifetime < 0) {
        onDeath();
    }
    velocityModifierDuration -= dt;
    if(velocityModifierDuration<0.f){
        velocityModifier=DEFAULT_VELOCITY_MODIFIER;
    }
}

void SimpleBullet::physicsUpdate(GameData& game) {
    prevPos = pos;
    pos += velocity * GameData::physicsDt * velocityModifier ;
    collider.p0 = pos;

    Rectangle mapBoundaries = game.getMapBoundaries();
    if (parent_type == PLAYER && (
            pos.x < 0.0f || pos.x > mapBoundaries.width ||
            pos.y < 0.0f || pos.y > mapBoundaries.height
        )) {
        onDeath();
    }
}

void SimpleBullet::collide(std::shared_ptr<Entity> entity, GameData& gameData) {
    if(parent_type!= PLAYER && entity->type()==EntityType::PLAYER_SLOWER){
        //make the slower responsible for the constants?
        velocityModifier=0.25f;
        velocityModifierDuration=2.0f;
        return;
    }
    if(parent_type== PLAYER && entity->type()==EntityType::PLAYER_SLOWER){
        //make the slower responsible for the constants?
        return;
    }
    if(entity->type() != parent_type && entity->type() != NEUTRAL){
        onDeath();
    };
    
}

void SimpleBullet::draw() {
    drawTexture();
}

EntityType SimpleBullet::type() {
    return parent_type;
}
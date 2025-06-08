#include "ShootingEnemy.h"
#include "raylib.h"
#include "raymath.h"
#include "SimpleBullet.h"

ShootingEnemy::ShootingEnemy(Vector2 pos) 
    : Entity(pos, pos, Vector2Zero(), BASE_RADIUS, 0, DrawingLayer::BLOOM),
    burst_timer(0), reload_timer(0), bullets_to_fire(BURST_SIZE){
    loadTexture("circle.png", 0.5f);
    textureTint = DARKPURPLE;
    collider = MakeCircleCollider(pos, hitboxRadius);
}

void ShootingEnemy::gameUpdate(GameData& game, float dt) {
    posNow = game.lerp(prevPos, pos);
    // SHOOTING
    reload_timer -= dt;
    if (reload_timer < 0) {
        burst_timer -= dt;
        if (burst_timer < 0) {
            burst_timer += BURST_DELAY;
            Vector2 bullet_vel = game.playerPos() -  pos;
            if(Vector2LengthSqr(bullet_vel) < EPSILON){
                bullet_vel = {1.0, 0.0f}; 
            }
            bullet_vel = Vector2Normalize(bullet_vel) * SimpleBullet::maxSpeed;
            float rotation = Vector2Angle(Vector2{1, 0}, bullet_vel) * RAD2DEG;
            auto bullet = std::make_shared<SimpleBullet>(pos, pos, bullet_vel, rotation, ENEMY, BULLET_COLOR);
            game.registerEntity(bullet);
            bullets_to_fire -= 1;
        }

        if (bullets_to_fire <= 0) {
            bullets_to_fire = BURST_SIZE;
            burst_timer = 0;
            reload_timer = REALOAD_TIME;
        }
    }

    // MOVEMENT

    velocityModifierDuration -= dt;
    if(velocityModifierDuration<0.f){
        velocityModifier=DEFAULT_VELOCITY_MODIFIER;
    }

    const float player_dist = Vector2Distance(pos, game.playerPos());
    acceleration = game.playerPos() - pos;
    if (player_dist < TARGET_DISTANCE) {
        acceleration *= -1;
    }
    
    Rectangle map = game.getMapBoundaries();
    if (pos.x < map.x) acceleration.x = MAX_ACCELERATION;
    if (pos.x > map.x + map.width) acceleration.x = -MAX_ACCELERATION;
    if (pos.y < map.y) acceleration.y = MAX_ACCELERATION;
    if (pos.y > map.y + map.height) acceleration.x = -MAX_ACCELERATION;

    if (Vector2Length(acceleration) > EPSILON) {
        acceleration = Vector2Normalize(acceleration) * MAX_ACCELERATION;
    } else {
        acceleration = Vector2Zero();
    }
}

void ShootingEnemy::physicsUpdate(GameData& game) {
    prevPos = pos;
    velocity += acceleration * GameData::physicsDt;
    if(Vector2Length(velocity) > maxSpeed){
        velocity = Vector2Normalize(velocity) * maxSpeed;
    }
    pos += velocity * GameData::physicsDt * velocityModifier ;
    collider.p0 = pos;
}

void ShootingEnemy::collide(std::shared_ptr<Entity> other, GameData& gameData) {
    if(other->type() == EntityType::PLAYER){
        onDeath();
    };
    if(other->type()==EntityType::PLAYER_SLOWER){
        //make the slower responsible for the constants?
        velocityModifier=0.25f;
        velocityModifierDuration=2.0f;
    }
}

void ShootingEnemy::draw() {
    drawTexture();
}

EntityType ShootingEnemy::type() {
    return ENEMY;
}
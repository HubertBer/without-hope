#include "BasicParticleEffect.h"
#include <algorithm>
#include "../GameData.h"
#include "raymath.h"
#include "../rand.h"

namespace{
    float invExpDecay(float c, float t, float x, float k = 3){
        return c * (1 - powf(t/x, k));
    }
}

BasicParticleEffect::BasicParticleEffect(Vector2 pos, float rotation, float spread, Vector2 radius, Vector2 speed, Vector2 lifetime, Vector2 spawnCooldown, Vector2 burstCount, Color color)
    : Entity(pos, pos, Vector2{0, 0}, 0, rotation, DrawingLayer::BLOOM), spread(spread), radius(radius), speed(speed), lifetime(lifetime), spawnCooldown(spawnCooldown), burstCount(burstCount), color(color){}

void BasicParticleEffect::physicsUpdate(GameData&){
    for(auto& p : particles){
        p.lifetime -= GameData::physicsDt;
    }
    
    std::erase_if(particles, [](const Particle& p){
        return p.lifetime < 0;
    });

    for(auto& p : particles){
        p.prevPos = p.pos;
        p.pos += p.velocity * GameData::physicsDt;
    }
}
void BasicParticleEffect::stopSpawning(){
    spawning = false;
}

void BasicParticleEffect::resumeSpawning(){
    spawning = true;
}

void BasicParticleEffect::gameUpdate(GameData& game, float dt){
    for(auto& p : particles){
        p.posNow = game.lerp(p.prevPos, p.pos);
    }

    timer -= dt;
    if(timer < 0.f){
        timer += GetRandomFloat(spawnCooldown);

        if(!spawning){
            return;
        }
        int count = ceil(GetRandomFloat(burstCount));
        for(int i = 0; i < count; ++i){
            Vector2 vel = Vector2Rotate(direction, (rotation + GetRandomFloat(-spread, spread)) * DEG2RAD);
            vel *= GetRandomFloat(speed);
            float lt = GetRandomFloat(lifetime);

            particles.push_back(Particle{
                pos,
                pos,
                pos,
                vel,
                GetRandomFloat(radius),
                lt,
                lt,
                true
            });
        }
    }
}

void BasicParticleEffect::collide(std::shared_ptr<Entity> entity,GameData& gameData){}

void BasicParticleEffect::draw(){
    for(const auto& p : particles){
        float r = p.radius;
        if(p.downscale){
            r = invExpDecay(r, p.baseLifetime - p.lifetime, p.baseLifetime);
        }
        DrawCircle(p.posNow.x, p.posNow.y, r, color);
    }
}
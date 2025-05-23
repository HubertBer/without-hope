#pragma once

#include "raylib.h"
#include "Entity.h"
#include <memory>

class TargetableCamera : public Entity{
public:
    TargetableCamera(std::shared_ptr<Entity> target);
    void gameUpdate(GameData& game, float dt) override;

private:
    std::shared_ptr<Entity> target;
};
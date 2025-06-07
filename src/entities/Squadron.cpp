#include "Squadron.h"
#include "Entity.h"
#include "raylib.h"
#include "raymath.h"
#include "../GameData.h"
#include "Trail.h"

Squadron::Squadron(Vector2 pos, float rotation, bool hasSplit, Vector2 shipsOffset, const std::vector<std::weak_ptr<SquadronShip>>& ships) 
    : Entity(pos, pos, Vector2{0, 0}, 0, rotation), hasSplit(hasSplit), shipsOffset(shipsOffset), ships(ships){
    
    int w = 1;
    int w_min = 0;
    int w_max = 0;
    int layer = 0;
    
    for(int i = 0; i < SQUADRON_SIZE; ++i){
        int j = i - w_min;
        Vector2 base = Vector2{w % 2 == 0 ? 0.f : -0.5f * X_OFFSET, -Y_OFFSET * layer};

        if(j % 2 == 0){
            offset[i] = base + Vector2{ (j / 2) * X_OFFSET, 0.f};
        }else{
            offset[i] = base + Vector2{ -(j / 2 + 1) * X_OFFSET, 0.f};
        }
        
        if(i == w_max){
            layer += 1;
            w += 1;
            w_min = w_max + 1;
            w_max += w;
        }
    }
};

void Squadron::start(GameData& game){
    if(hasSplit){
        return;
    }
    for(int i = 0; i < SQUADRON_SIZE; ++i){
        std::shared_ptr<SquadronShip> ship = std::make_shared<SquadronShip>(pos + offset[i], rotation);
        game.registerEntity(ship);
        ships.push_back(ship);

        auto shipTrail = std::make_shared<Trail>(ship);
        game.registerEntity(shipTrail);
    }
}

void Squadron::gameUpdate(GameData& game, float dt){
    velocityModifierDuration -= dt;
    if(velocityModifierDuration<0.f){
        velocityModifier=DEFAULT_VELOCITY_MODIFIER;
    }
}

void Squadron::split(GameData& game){
    PlaySound(SoundLoader::audio["squadron"]);
    std::vector<std::weak_ptr<SquadronShip>> leftShips;
    std::vector<std::weak_ptr<SquadronShip>> rightShips;
    repositionShips();

    int w = 1;
    int w_min = 0;
    int w_max = 0;
    int layer = 0;
    for(int i = 0; i < ships.size(); ++i){
        int j = i - w_min;
        if(j % 2 == 0){
            leftShips.push_back(ships[i]);
        }else{
            rightShips.push_back(ships[i]);
        }

        if(i == w_max){
            layer += 1;
            w += 1;
            w_min = w_max + 1;
            w_max += w;
        }
    }

    game.registerEntity(std::make_shared<Squadron>(
        pos,
        rotation,
        true,
        Vector2{100.f, 70.f},
        rightShips
    ));
    game.registerEntity(std::make_shared<Squadron>(
        pos,
        rotation,
        true,
        Vector2{-100.f, 70.f},
        leftShips
    ));

    ships.clear();
    zombie = true;
}

void Squadron::physicsUpdate(GameData& game){
    prevPos = pos;

    Vector2 dir = game.playerPos() - pos;
    
    if(!hasSplit && Vector2Length(dir) < SPLIT_DISTANCE){
        split(game);
        return;
    }
    
    if(Vector2Length(dir) < MAX_SPEED * GameData::physicsDt){
        pos = game.playerPos();
        velocity = Vector2Zero();
    }else{
        rotation = Vector2Angle(Vector2{1, 0}, dir) * RAD2DEG;
    }

    velocity = Vector2Normalize(dir) * MAX_SPEED;
    pos += velocity * GameData::physicsDt * velocityModifier ;

    repositionShips();
    if(zombie){
        return;
    }

    // TODO_IDEA:
    // Need to add acceleration and modify it directly instead of velocity
    // as now the rotation is not continous and ships follow shitty path.
    int i = 0;
    for(auto ship : ships){
        Vector2 target = Vector2Rotate(shipsOffset + offset[i], (rotation - 90) * DEG2RAD);
        ship.lock()->setTarget(pos + target);
        i += 1;
    }
}

void Squadron::collide(std::shared_ptr<Entity> other, GameData& gameData){
    if(other->type()==EntityType::PLAYER_SLOWER){
        //make the slower responsible for the constants?
        velocityModifier=0.25f;
        velocityModifierDuration=2.0f;
    }
}

void Squadron::draw(){}

void Squadron::repositionShips(){
    if(ships.size() == 0){
        return;
    }

    // TODO_IDEA:
    // For now reordering happens randomly, based on how erase_if orders the data
    // It would be nice if the formation reordering was smooth, and the closest
    // ship would take the place of dead one. 
    std::erase_if(ships, [](std::weak_ptr<Entity> s){return s.expired();});
    if(ships.size() == 0){
        zombie = true;
    }
}
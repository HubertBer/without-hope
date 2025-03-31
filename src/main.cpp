#include "raylib.h"
#include "raymath.h"
#include <vector>

const int screenWidth = 1280;
const int screenHeight = 720;
const float physicsDt = 1.0f/60.0f;

struct SimpleEnemy;
struct SimpleBullet;
struct Player;

struct GameData{
    std::vector<SimpleEnemy> enemies;
    std::vector<SimpleBullet> bullets;
    Player* player;

    const float player_speed = 500.0f;

    void Frame(float dt);
    void PhysicsFrame();
    void Draw(float lerp_value);
};

enum EntityType{
    NONE,
    PLAYER,
    SIMPLE_ENEMY,
    SIMPLE_BULLET,
};

struct Entity{
    virtual void Frame(GameData& game, float dt){}
    virtual void PhysicsFrame(GameData&){}
    virtual void Render(float lerp_value){}
    virtual EntityType type(){return NONE;}
};

struct SimpleBullet : public Entity{
    Vector2 prevPos;
    Vector2 pos;
    Vector2 velocity;
    constexpr static float maxSpeed = 800.f;

    SimpleBullet(Vector2 prevPos, Vector2 pos, Vector2 velocity)
        : prevPos(prevPos), pos(pos), velocity(velocity){}

    void Frame(GameData& game, float dt)override{}

    void PhysicsFrame(GameData& game) override{
        prevPos = pos;
        pos += velocity * physicsDt;
    }

    void Render(float lerpValue) override{
        Vector2 bulletPosNow = Vector2Lerp(prevPos, pos, lerpValue);        
        DrawRectangle(static_cast<int>(bulletPosNow.x), static_cast<int>(bulletPosNow.y), 5, 20, YELLOW);
    }

    EntityType type() override{
        return SIMPLE_BULLET;
    }    
};

struct Player : public Entity{
    Vector2 pos;
    Vector2 prevPos;
    Vector2 velocity;
    static constexpr float maxSpeed = 500.0f;

    Player(Vector2 prevPos, Vector2 pos, Vector2 velocity)
        : prevPos(prevPos), pos(pos), velocity(velocity){}

    void PhysicsFrame(GameData& game) override{
        prevPos = pos;
        pos += velocity * physicsDt;
    }

    void Frame(GameData& game, float dt) override{
        velocity = {0, 0};
        if (IsKeyDown(KEY_D)) velocity.x += 1;
        if (IsKeyDown(KEY_A)) velocity.x -= 1;
        if (IsKeyDown(KEY_W)) velocity.y -= 1;
        if (IsKeyDown(KEY_S)) velocity.y += 1;
        if(Vector2LengthSqr(velocity) > EPSILON){
            velocity = Vector2Normalize(velocity);
            velocity *= maxSpeed;
        }

        if(IsKeyPressed(KEY_SPACE)){
            Vector2 bullet_vel = (pos - prevPos); //Later probably just based on rotation
            if(Vector2LengthSqr(bullet_vel) < EPSILON){
                bullet_vel = {1.0, 0.0f}; 
            }
            bullet_vel = Vector2Normalize(bullet_vel) * SimpleBullet::maxSpeed;

            game.bullets.push_back(SimpleBullet{
                pos,
                pos,
                bullet_vel,
            });
        }
    }

    void Render(float lerpValue) override{
        Vector2 playerPosNow = Vector2Lerp(prevPos, pos, lerpValue);        
        DrawCircle(static_cast<int>(playerPosNow.x), static_cast<int>(playerPosNow.y), 30, RED);    
    }

    EntityType type() override{
        return PLAYER;
    }
};

struct SimpleEnemy : public Entity{
    Vector2 prevPos;
    Vector2 pos;
    Vector2 velocity;
    static constexpr float maxSpeed = 300.f;

    SimpleEnemy(Vector2 prevPos, Vector2 pos, Vector2 velocity)
        : prevPos(prevPos), pos(pos), velocity(velocity){}

    void Frame(GameData& game, float dt)override{}
    
    void PhysicsFrame(GameData& game) override{
        prevPos = pos;
        velocity = Vector2Normalize(game.player->pos - pos) * SimpleBullet::maxSpeed;
        pos += velocity * physicsDt;
    }

    void Render(float lerpValue) override{
        Vector2 enemyPosNow = Vector2Lerp(prevPos, pos, lerpValue);        
        DrawRectangle(static_cast<int>(enemyPosNow.x), static_cast<int>(enemyPosNow.y), 20, 40, GREEN);
    }

    EntityType type() override{
        return SIMPLE_ENEMY;
    }
};


void GameData::Frame(float dt){
    for(auto enemy : enemies){
        enemy.Frame(*this, dt);
    }

    for(auto bullet : bullets){
        bullet.Frame(*this, dt);
    }

    player->Frame(*this, dt);
}

void GameData::PhysicsFrame(){
    for(auto enemy : enemies){
        enemy.PhysicsFrame(*this);
    }

    for(auto bullet : bullets){
        bullet.PhysicsFrame(*this);
    }

    player->PhysicsFrame(*this);
}

void GameData::Draw(float lerp_value){
    for(auto enemy : enemies){
        enemy.Render(lerp_value);
    }

    for(auto bullet : bullets){
        bullet.Render(lerp_value);
    }

    player->Render(lerp_value);
}

int main() {
    InitWindow(screenWidth, screenHeight, "geometry-game");
    SetTargetFPS(300);

    GameData game;
    game.player = new Player({100.0, 100.0f}, {100.0, 100.0f}, {0.0f, 0.0f});
    SetRandomSeed(0);
    for(int i = 0; i < 10; ++i){
        Vector2 pos = {(float)GetRandomValue(100, 1000), (float)GetRandomValue(100, 1000)};
        game.enemies.push_back({
            pos,
            pos,
            {0, 0},
        });
    }

    float gameTime = 0;
    float physicsTime = 0;

    while (!WindowShouldClose()) {
        // PHYSICS SIMULATION - CONSTANT FRAME TIME SIMULATION
        float dt = GetFrameTime();
        gameTime += dt;
        if(dt > 0.25f){
            dt = 0.25f; // If the program lags, just slow it down
        }
        while(physicsTime < gameTime){
            physicsTime += physicsDt;
            game.PhysicsFrame();
        }
        game.Frame(dt);

        // DRAWING 
        BeginDrawing();
        ClearBackground(BLUE);
        game.Draw(1 - (physicsTime - gameTime)/physicsDt);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}

#include "raylib.h"
#include "raymath.h"
#include <vector>

const int screenWidth = 1280;
const int screenHeight = 720;
const float physics_dt = 1.0f/60.0f;

const Vector2 dir[4] = {{1, 0}, {0, 1}, {-1,0}, {0, -1}};

Vector2 GetRandomVector2(){
    return Vector2Normalize({(float)GetRandomValue(-500, 500), (float)GetRandomValue(-500, 500)});
}

struct enemy{
    Vector2 prev_pos;
    Vector2 pos;
    Vector2 velocity;
    constexpr static float max_speed = 300.f;
};

struct game_data{
    Vector2 player_pos = {100.0f, 100.0f};
    Vector2 prev_player_pos = {100.0f, 100.0f};
    Vector2 player_velocity = {0, 0};
    std::vector<enemy> enemies {};

    const float player_speed = 500.0f;
};

void physics_tick(game_data& game){
    // Player
    game.prev_player_pos = game.player_pos; 
    game.player_pos += game.player_velocity * physics_dt;

    // Enemies
    
    
    for(enemy& enem : game.enemies){
        enem.prev_pos = enem.pos;
        if(GetRandomValue(0, 99) == 0){
            enem.velocity = GetRandomVector2() * enemy::max_speed;
        }
        enem.pos += enem.velocity * physics_dt;
    }
}

int main() {
    InitWindow(screenWidth, screenHeight, "geometry-game");
    SetTargetFPS(300);

    game_data game;
    SetRandomSeed(0);
    for(int i = 0; i < 10; ++i){
        Vector2 pos = {(float)GetRandomValue(100, 1000), (float)GetRandomValue(100, 1000)};
        Vector2 vel = GetRandomVector2() * enemy::max_speed;
        game.enemies.push_back({
            pos,
            pos,
            vel,
        });
    }

    float game_time = 0;
    float physics_time = 0;

    while (!WindowShouldClose()) {
        // INPUT PROCESSING
        game.player_velocity = {0, 0};
        if (IsKeyDown(KEY_D)) game.player_velocity.x += 1;
        if (IsKeyDown(KEY_A)) game.player_velocity.x -= 1;
        if (IsKeyDown(KEY_W)) game.player_velocity.y -= 1;
        if (IsKeyDown(KEY_S)) game.player_velocity.y += 1;
        if(Vector2LengthSqr(game.player_velocity) > EPSILON){
            game.player_velocity = Vector2Normalize(game.player_velocity);
            game.player_velocity *= game.player_speed;
        }

        // PHYSICS SIMULATION - CONSTANT FRAME TIME SIMULATION
        float dt = GetFrameTime();
        game_time += dt;
        if(dt > 0.25f){
            dt = 0.25f; // If the program lags, just slow it down
        }
        while(physics_time < game_time){
            physics_time += physics_dt;
            physics_tick(game);
        }

        // DRAWING 
        BeginDrawing();
        ClearBackground(BLUE);
        
        // Rember that positions are in the physics simulation which is slightly ahead, we need to interpolate between current position and the previous position 
        Vector2 player_pos_now = Vector2Lerp(game.prev_player_pos, game.player_pos, (physics_time - game_time)/physics_dt);
        DrawCircle(static_cast<int>(player_pos_now.x), static_cast<int>(player_pos_now.y), 30, RED);

        for(enemy enem : game.enemies){
            Vector2 enem_pos_now = Vector2Lerp(enem.prev_pos, enem.pos, (physics_time - game_time)/physics_dt);        
            DrawRectangle(static_cast<int>(enem_pos_now.x), static_cast<int>(enem_pos_now.y), 20, 40, GREEN);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}

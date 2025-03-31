#include "raylib.h"
#include "raymath.h"
#include <vector>

#include "Projection.h"

const int screenWidth = 1280;
const int screenHeight = 720;
const float physics_dt = 1.0f/60.0f;

const Vector2 dir[4] = {{1, 0}, {0, 1}, {-1,0}, {0, -1}};

Vector2 GetRandomVector2(){
    return Vector2Normalize({(float)GetRandomValue(-500, 500), (float)GetRandomValue(-500, 500)});
}

struct bullet{
    Vector2 prev_pos;
    Vector2 pos;
    Vector2 velocity;
    constexpr static float max_speed = 800.f;
};

struct enemy{
    Vector2 prev_pos;
    Vector2 pos;
    Vector2 velocity;
    constexpr static float max_speed = 300.f;
};

struct game_data{
    Vector2 player_pos = {0.f, 0.f};
    Vector2 prev_player_pos = player_pos;
    Vector2 player_velocity = {0, 0};
    float rotation; // 0 is in the direction of the pole (0, 0, 1), going clockwise, in radians
    std::vector<enemy> enemies {};
    std::vector<bullet> bullets {};
    
    const float player_speed = 2.f;
};

void physics_tick(game_data& game){
    // Player
    game.prev_player_pos = game.player_pos; 
    game.player_pos = movePlayer(game.player_pos, game.player_velocity * physics_dt);

    // Enemies
    for(enemy& enem : game.enemies){
        enem.prev_pos = enem.pos;
        enem.velocity = Vector2Normalize(game.player_pos - enem.pos) * enemy::max_speed;
        // if(GetRandomValue(0, 99) == 0){
        //     enem.velocity = GetRandomVector2() * enemy::max_speed;
        // }
        //enem.pos += enem.velocity * physics_dt;
    }

    // Bullets
    for(bullet& b : game.bullets){
        b.prev_pos = b.pos;
        b.pos += b.velocity * physics_dt;
    }
}

// move the origin (0, 0) to the center of the screen
Vector2 centerOnScreen(Vector2 a) {
    return {a.x + screenWidth / 2, a.y + screenHeight / 2};
}

int main() {
    InitWindow(screenWidth, screenHeight, "geometry-game");
    SetTargetFPS(300);

    Image image = LoadImage("resources/grid.jpg");
    ImageResize(&image, 512, 512);

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

    // Enemies at the poles
    game.enemies.push_back({
        {0, 0},
        {0, 0},
        {0, 0},
    });
    game.enemies.push_back({
        {0, PI},
        {0, PI},
        {0, 0},
    });

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

        if(IsKeyPressed(KEY_SPACE)){
            Vector2 bullet_vel = (game.player_pos - game.prev_player_pos); //Later probably just based on rotation
            if(Vector2LengthSqr(bullet_vel) < EPSILON){
                bullet_vel = {1.0, 0.0f}; 
            }
            bullet_vel = Vector2Normalize(bullet_vel) * bullet::max_speed;

            game.bullets.push_back({
                game.player_pos,
                game.player_pos,
                bullet_vel,
            });
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

        Vector2 player_pos_now = Vector2Lerp(game.prev_player_pos, game.player_pos, 1 - (physics_time - game_time)/physics_dt);
        
        // Draw projected grid
        for (float theta = 0; theta < PI * 2; theta += (PI * 2)/ 300) {
            for (float phi = 0; phi < PI; phi += PI / 300) {
                Vector2 coords = centerOnScreen(stereographicProjection({ theta, phi }, player_pos_now));
                if (coords.x < 0 || coords.x > screenWidth || coords.y < 0 || coords.y > screenHeight) continue;

                // Sample color from texture
                Color texColor = GetImageColor(image, 
                               (theta/(2 * PI)) * image.width, 
                               (phi/PI) * image.height);

                DrawPixel(static_cast<int>(coords.x), static_cast<int>(coords.y), texColor);
            }
        }
        
        // Rember that positions are in the physics simulation which is slightly ahead, we need to interpolate between current position and the previous position 
        Vector2 centered_player = centerOnScreen({0, 0});
        DrawCircle(static_cast<int>(centered_player.x), static_cast<int>(centered_player.y), 30, RED);

        for(enemy enem : game.enemies){
            Vector2 enem_pos_now = Vector2Lerp(enem.prev_pos, enem.pos, 1 - (physics_time - game_time)/physics_dt);
            Vector2 translated = centerOnScreen(stereographicProjection(enem_pos_now, player_pos_now));     
            DrawRectangle(static_cast<int>(translated.x), static_cast<int>(translated.y), 20, 40, GREEN);
        }
        
        for(bullet b : game.bullets){
            Vector2 bullet_pos_now = Vector2Lerp(b.prev_pos, b.pos, 1 - (physics_time - game_time)/physics_dt);
            Vector2 translated = centerOnScreen(stereographicProjection(bullet_pos_now, player_pos_now));
            DrawRectangle(static_cast<int>(translated.x), static_cast<int>(translated.y), 5, 20, YELLOW);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}

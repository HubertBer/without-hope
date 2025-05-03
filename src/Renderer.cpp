#include "Renderer.h"

#include <stdexcept>

#include <rlgl.h>

#include "Config.h"
#include "UI/Scaler.h"

Renderer::Renderer(int width, int height) {
    shakeShader = LoadShader(0, "src/resources/shaders/shake.fs");
    baseShader = LoadShader(0, "src/resources/shaders/base.fs");
    backgroundShader = LoadShader(0, "src/resources/shaders/background.fs");
    if (shakeShader.id == 0 || baseShader.id == 0 || backgroundShader.id == 0) {
        throw std::runtime_error("Failed to load shader");
    }

    // Setup needed because: https://github.com/raysan5/raylib/issues/1730
    Texture2D texture{ rlGetTextureIdDefault(), 1, 1, 1, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8 };
    SetShapesTexture(texture, Rectangle{ 0.0f, 0.0f, 1.0f, 1.0f });
}

Renderer::~Renderer() {
    UnloadShader(shakeShader);
    UnloadShader(baseShader);
    UnloadShader(backgroundShader);
}

void Renderer::draw(GameData &game, RenderTexture2D &target) {
    float resolution[2] = {(float)target.texture.width, (float)target.texture.height};
    SetShaderValue(backgroundShader, GetShaderLocation(backgroundShader, "resolution"), resolution, SHADER_UNIFORM_VEC2);

    float time = GetTime();
    SetShaderValue(shakeShader, GetShaderLocation(shakeShader, "uTime"), &time, SHADER_UNIFORM_FLOAT);
    SetShaderValue(backgroundShader, GetShaderLocation(backgroundShader, "time"), &time, SHADER_UNIFORM_FLOAT);

    BeginTextureMode(target);
        ClearBackground(BLACK);

        BeginShaderMode(backgroundShader);
            DrawRectangle(0, 0, Config::screenWidth, Config::screenHeight, WHITE);
        EndShaderMode();

        BeginMode2D(game.getMainCamera());
        game.draw();
        EndMode2D();
    EndTextureMode();

    BeginDrawing();
        ClearBackground(RAYWHITE);

        BeginShaderMode(time - game.getTimeSinceKill() > 0.1f ? baseShader : shakeShader);
            drawTextureStretched(target);
        EndShaderMode();
    EndDrawing();
}


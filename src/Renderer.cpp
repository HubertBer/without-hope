#include "Renderer.h"

#include <stdexcept>

#include <rlgl.h>

#include "Config.h"
#include "UI/Scaler.h"
#include "screens/Screen.h"
#include "screens/GameScreen.h"

void Renderer::init(int width, int height)
{
    target = LoadRenderTexture(width, height);
    targetBloom = LoadRenderTexture(width, height);
    if (target.texture.id == 0 || targetBloom.texture.id == 0) {
        throw std::runtime_error("Failed to load render texture");
    }

    // Setup needed because: https://github.com/raysan5/raylib/issues/1730
    Texture2D texture{ rlGetTextureIdDefault(), 1, 1, 1, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8 };
    SetShapesTexture(texture, Rectangle{ 0.0f, 0.0f, 1.0f, 1.0f });
}

void Renderer::draw(std::shared_ptr<Screen> screen, ScreenType type)
{
    if (type == ScreenType::SCREEN_GAME)
    {
        Shader& voronoiShader = getShader("voronoi");
        Shader& shakeShader = getShader("shake");
        Shader& baseShader = getShader("base");
        Shader& bloomShader = getShader("bloom");

        float resolution[2] = {(float)target.texture.width, (float)target.texture.height};
        SetShaderValue(voronoiShader, GetShaderLocation(voronoiShader, "resolution"), resolution, SHADER_UNIFORM_VEC2);
        SetShaderValue(bloomShader, GetShaderLocation(bloomShader, "resolution"), resolution, SHADER_UNIFORM_VEC2);

        float time = GetTime();
        SetShaderValue(shakeShader, GetShaderLocation(shakeShader, "uTime"), &time, SHADER_UNIFORM_FLOAT);
        SetShaderValue(voronoiShader, GetShaderLocation(voronoiShader, "time"), &time, SHADER_UNIFORM_FLOAT);

        auto gameScreen = std::dynamic_pointer_cast<GameScreen>(screen);
        auto drawLayers = gameScreen->game.prepareDraw();

        // Prerender to a texture all layers except bloom
        BeginTextureMode(target);
        ClearBackground(BLACK);

        BeginShaderMode(voronoiShader);
        DrawRectangle(0, 0, Config::screenWidth, Config::screenHeight, WHITE);
        EndShaderMode();

        BeginMode2D(gameScreen->game.getMainCamera());
        for (const auto &[layer, entities] : drawLayers) {
            if (layer != DrawingLayer::BLOOM) {
                for (const auto &entity : entities) {
                    entity->draw();
                }
            }
        }
        Rectangle mapBounds = gameScreen->game.getMapBoundaries();
        float desiredPx   = 8.0f;
        float thicknessWS = desiredPx / gameScreen->game.getMainCamera().zoom;
        DrawRectangleLinesEx(mapBounds, thicknessWS, BLACK);
        EndMode2D();
        EndTextureMode();

        // Render bloom layer to a separate texture
        BeginTextureMode(targetBloom);
        ClearBackground(BLANK);
        BeginMode2D(gameScreen->game.getMainCamera());
        const auto &entities = drawLayers[DrawingLayer::BLOOM];
        for (const auto &entity : entities) {
            entity->draw();
        }
        EndMode2D();
        EndTextureMode();

        // Draw all the layers to the screen
        BeginDrawing();
        ClearBackground(BLACK);

        BeginShaderMode(time - dynamic_cast<GameScreen &>(*screen).game.getLastDamageTime() > 0.1f ? baseShader : shakeShader);
        
        BeginBlendMode(BLEND_ADDITIVE);
        drawTextureStretched(target);
        BeginShaderMode(bloomShader);
        drawTextureStretched(targetBloom);
        EndShaderMode();
        EndBlendMode();

        gameScreen->drawScore();
        EndShaderMode();
        EndDrawing();
    }
    else
    {
        BeginDrawing();
        screen->draw();
        EndDrawing();
    }
}

Shader& Renderer::getShader(const std::string &name)
{
    auto it = shaderCache.find(name);
    if (it != shaderCache.end()) {
        return it->second;
    }
    else {
        Shader shader = LoadShader(0, ("src/resources/shaders/" + name + ".fs").c_str());
        if (shader.id == 0) {
            throw std::runtime_error("Failed to load shader: " + name);
        }
        shaderCache[name] = shader;
        return shaderCache[name];
    }
}

Texture2D Renderer::getTexture(const std::string &name)
{
    auto it = textureCache.find(name);
    if (it != textureCache.end()) {
        return it->second;
    }
    else {
        Texture2D texture = LoadTexture(("src/resources/sprites/" + name).c_str());
        if (texture.id == 0) {
            throw std::runtime_error("Failed to load texture: " + name);
        }
        textureCache[name] = texture;
        return textureCache[name];
    }
}

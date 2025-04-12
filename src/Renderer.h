#pragma once

#include <raylib.h>

#include "GameData.h"

class Renderer {
public:
    Renderer(int width, int height);
    ~Renderer();

    void draw(GameData& game);
private:
    RenderTexture2D target;
    Shader shakeShader;
    Shader baseShader;
    Shader backgroundShader;
};
#pragma once

#include <raylib.h>

#include "GameData.h"

class Renderer {
public:
    Renderer(int width, int height);
    ~Renderer();

    void draw(GameData& game);
private:
    Shader shakeShader;
    Shader baseShader;
    Shader backgroundShader;
    RenderTexture2D target;
};
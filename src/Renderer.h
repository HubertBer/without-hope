#pragma once

#include <raylib.h>

#include "screens/Screen.h"

class Renderer {
public:
    Renderer(int width, int height);
    ~Renderer();

    void draw(std::shared_ptr<Screen> screen, ScreenType type);
private:
    Shader shakeShader;
    Shader baseShader;
    Shader backgroundShader;
    RenderTexture2D target;
};
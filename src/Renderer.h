#pragma once

#include <unordered_map>

#include <raylib.h>

#include "screens/Screen.h"

class Renderer {
public:
    Renderer() = delete;
    static void init(int width, int height);
    static void draw(std::shared_ptr<Screen> screen, ScreenType type);
    static Shader& getShader(const std::string& name);
    // We don't return a reference to the texture, so that the 
    // end user can modify the dimensions for a particular instance
    static Texture2D getTexture(const std::string& name);
private:
    inline static std::unordered_map<std::string, Shader> shaderCache;
    inline static std::unordered_map<std::string, Texture2D> textureCache;
    inline static RenderTexture2D target;
    inline static RenderTexture2D targetBloom;
};
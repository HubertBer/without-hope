#include "GridBackground.h"
#include "raylib.h"
#include "../GameData.h"

GridBackground::GridBackground()
: Entity(Vector2{0, 0}, Vector2{0, 0}, Vector2{0, 0}, 0.f, 0.f, DrawingLayer::BACKGROUND){}

void GridBackground::gameUpdate(GameData& game, float dt){
    cameraBoundaries = GameData::getCameraVisionBoundaries(game.getMainCamera());
}

void GridBackground::physicsUpdate(GameData& game){}

void GridBackground::draw(){
    float x0 = (cameraBoundaries.x); 
    float x1 = (cameraBoundaries.x + cameraBoundaries.width); 
    float y0 = (cameraBoundaries.y); 
    float y1 = (cameraBoundaries.y + cameraBoundaries.height); 
    
    x0 = static_cast<int>(x0 / lineSpacing) * lineSpacing; 
    x1 = static_cast<int>(x1 / lineSpacing) * lineSpacing; 
    y0 = static_cast<int>(y0 / lineSpacing) * lineSpacing; 
    y1 = static_cast<int>(y1 / lineSpacing) * lineSpacing; 

    // Vertical lines
    for(float x = x0; x < x1 + 100; x += lineSpacing){
        int xi = static_cast<int>(x); 
        int y0i = static_cast<int>(y0) - 100; 
        int y1i = static_cast<int>(y1) + 100; 
        
        DrawLine(xi, y0i, xi, y1i, color);
    }

    // Horizontal lines
    for(float y = y0; y < y1 + 100; y += lineSpacing){
        int yi = static_cast<int>(y); 
        int x0i = static_cast<int>(x0) - 100; 
        int x1i = static_cast<int>(x1) + 100; 
        
        DrawLine(x0i, yi, x1i, yi, color);
    }
}

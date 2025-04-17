#include "rand.h"
#include "raylib.h"

namespace{
    const int BIG_NUM = 1048576;
}

float GetRandomFloat(float min, float max){
    return min + (max - min) * (GetRandomValue(0, BIG_NUM) / (float) BIG_NUM);
}
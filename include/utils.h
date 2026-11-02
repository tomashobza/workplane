#pragma once

#include "raylib.h"
#include "globals.h"

float max(float a, float b);
Vector2 inv(Vector2 v);
Vector2 trans(Vector2 v1, Vector2 v2);
Vector2 scale(Vector2 v, float scaleCoef);
Vector2 world2scene_vec2(Vector2 v);
Rectangle world2scene_rect(Rectangle r);
float world2scene_scale(float v);
Vector2 scene2world(Vector2 v);
bool isInside(Vector2 pointer, Rectangle bb);

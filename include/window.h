#pragma once

#include "raylib.h"

typedef struct {
    char* name;
    unsigned int index;
    Rectangle shape;
} Window;

void DrawWindow(Window w);

Rectangle getWindowBoundingBox(Window w);

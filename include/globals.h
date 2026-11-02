#pragma once

#include "raylib.h"

typedef struct {
    Vector2 position;
    float scale;
} WorldView;

extern WorldView wv;

extern const int WINDOW_W;
extern const int WINDOW_H;
extern const float CENTER_X;
extern const float CENTER_Y;
extern const Vector2 CENTER;

extern int selectedWindow;

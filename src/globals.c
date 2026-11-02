#include "globals.h"

Vector2 position = {0, 0};
float scaleCoef = 1.0;

WorldView wv = {{0,0}, 1.0};

const int WINDOW_W = 800;
const int WINDOW_H = 450;
const float CENTER_X = WINDOW_W / 2.0;
const float CENTER_Y = WINDOW_H / 2.0;
const Vector2 CENTER = {CENTER_X, CENTER_Y};

int selectedWindow = -1;

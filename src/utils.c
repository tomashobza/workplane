#include "utils.h"
#include "raylib.h"


float max(float a, float b) {
    return a > b ? a : b;
}

Vector2 inv(Vector2 v) {
    return (Vector2){
        -v.x,
        -v.y
    };
}

Vector2 trans(Vector2 v1, Vector2 v2) {
    return (Vector2){
        v1.x+v2.x,
        v1.y+v2.y
    };
}

Vector2 scale(Vector2 v, float scaleCoef) {
    return (Vector2){
        v.x*scaleCoef,
        v.y*scaleCoef
    };
}

Vector2 world2scene_vec2(Vector2 v) {
    return trans(scale(trans(v, inv(wv.position)), wv.scale), CENTER);
}

Rectangle world2scene_rect(Rectangle r) {
    Vector2 position = world2scene_vec2((Vector2){ r.x, r.y });
    float width = world2scene_scale(r.width);
    float height = world2scene_scale(r.height);

    return (Rectangle){ position.x, position.y, width, height };
}

float world2scene_scale(float v) {
    return v * wv.scale;
}

Vector2 scene2world(Vector2 v) {
    return trans(scale(trans(v, inv(CENTER)), 1.0 / wv.scale), wv.position);
}

bool isInside(Vector2 pointer, Rectangle bb) {
    bool isInX = pointer.x >= bb.x && pointer.x <= bb.x + bb.width;
    bool isInY = pointer.y >= bb.y && pointer.y <= bb.y + bb.height;
    return isInX && isInY;
}

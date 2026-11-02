#include "window.h"
#include "globals.h"
#include "utils.h"

const int HEADER_HEIGHT = 20.0;
const int BORDER_W = 2.0;

void DrawWindow(Window w) {
    Rectangle header = w.shape;
    header.height = HEADER_HEIGHT;
    Rectangle body = w.shape;
    body.y += HEADER_HEIGHT - BORDER_W;

    Rectangle sceneHeader = world2scene_rect(header);
    Rectangle sceneBody = world2scene_rect(body);

    Color c = GRAY;
    if (selectedWindow == w.index) {
        c = BLUE;
    }

    DrawRectangleRec(sceneHeader, c);
    DrawRectangleLinesEx(sceneBody, world2scene_scale(BORDER_W), c);
    Vector2 titlePosition = world2scene_vec2((Vector2){ header.x + BORDER_W, header.y + BORDER_W });
    DrawText(w.name, titlePosition.x, titlePosition.y, world2scene_scale(HEADER_HEIGHT - (2*BORDER_W)), WHITE);
}

Rectangle getWindowBoundingBox(Window w) {
    Rectangle fullWindow = w.shape;
    fullWindow.height += HEADER_HEIGHT;
    Rectangle bb = world2scene_rect(fullWindow);
    return bb;
}

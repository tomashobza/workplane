#include "raylib.h"

const int WINDOW_W = 800;
const int WINDOW_H = 450;

Vector2 position = {0, 0};
Vector2 lastPos = {0, 0};
Vector2 downPos = {0, 0};

float scale = 1.0;

float max(float a, float b) {
    return a > b ? a : b;
}

float coordX(float pos, Vector2 worldPos) {
    int newPos = (pos + worldPos.x)*scale;
    newPos += WINDOW_W / 2.0;
    return newPos;
}

float coordY(float pos, Vector2 worldPos) {
    int newPos = (pos + worldPos.y)*scale;
    newPos += WINDOW_H / 2.0;
    return newPos;
}

Vector2 coords(Vector2 pos, Vector2 worldPos) {
    Vector2 newPos;
    newPos.x = coordX(pos.x, worldPos);
    newPos.y = coordY(pos.y, worldPos);
    return newPos;
}

int main(void) {
    // Initialize the window size and title
    InitWindow(WINDOW_W, WINDOW_H, "workplane");

    // Target 60 frames per second
    SetTargetFPS(60);

    // Main game loop
    while (!WindowShouldClose()) { // Detect window close button or ESC key
        // Update variables here
        Vector2 mousePos = GetMousePosition();
        bool justMouseDown = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
        bool mouseDown = IsMouseButtonDown(MOUSE_BUTTON_LEFT);

        float scroll = GetMouseWheelMove();
        scale = max(scale + scroll / 10.0, 0.1);

        if (justMouseDown) {
            downPos.x = mousePos.x;
            downPos.y = mousePos.y;

            // save pos
            lastPos = position;
        }

        float xDelta = 0;
        float yDelta = 0;

        if (mouseDown) {
            xDelta = (mousePos.x - downPos.x) / scale;
            yDelta = (mousePos.y - downPos.y) / scale;
            position.x = lastPos.x + xDelta;
            position.y = lastPos.y + yDelta;
        }

        // Draw
        BeginDrawing();

            ClearBackground(RAYWHITE);
            int rectsize = 50 * scale;
            DrawRectangle((coordX(0, position)), (coordY(0, position)), rectsize, rectsize, PINK);
            DrawRectangle((coordX(-50, position)), (coordY(-50, position)), rectsize, rectsize, PINK);
            DrawRectangle((coordX(50, position)), (coordY(50, position)), rectsize, rectsize, PINK);
            // DrawText(TextFormat("Vector2 Pos: (%0.1f, %0.1f)", mousePos.x, mousePos.y), WINDOW_W - 280, WINDOW_H - 30, 20, DARKGRAY);
            DrawText(TextFormat("Scale: (%0.1f)", scale), WINDOW_W - 280, WINDOW_H - 30, 20, DARKGRAY);
            // if (mouseDown) {
                // DrawText(TextFormat("Vector2 Pos: (%0.1f, %0.1f)", position.x, position.y), WINDOW_W - 280, WINDOW_H - 30, 20, DARKGRAY);
            // }
            // DrawText("Congrats! You created your first raylib window!", 200, 200, 20, LIGHTGRAY);

            DrawFPS(10, 10);

        EndDrawing();
    }

    // Close window and OpenGL context
    CloseWindow();

    return 0;
}

#include "raylib.h"

const int WINDOW_W = 800;
const int WINDOW_H = 450;

Vector2 position = {0, 0};
Vector2 lastPos = {0, 0};
Vector2 downPos = {0, 0};

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

        if (justMouseDown) {
            downPos.x = mousePos.x;
            downPos.y = mousePos.y;

            // save pos
            lastPos = position;
        }

        float xDelta = 0;
        float yDelta = 0;

        if (mouseDown) {
            xDelta = mousePos.x - downPos.x;
            yDelta = mousePos.y - downPos.y;
            position.x = lastPos.x + xDelta;
            position.y = lastPos.y + yDelta;
        }

        // Draw
        BeginDrawing();

            ClearBackground(RAYWHITE);
            DrawRectangle(10 + position.x, 10 + position.y, 50, 50, PINK);
            DrawRectangle(80 + position.x, 100 + position.y, 50, 50, PINK);
            DrawRectangle(10 + position.x, 150 + position.y, 50, 50, PINK);
            // DrawText(TextFormat("Vector2 Pos: (%0.1f, %0.1f)", mousePos.x, mousePos.y), WINDOW_W - 280, WINDOW_H - 30, 20, DARKGRAY);
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

#include "raylib.h"

int main(void) {
    // Initialize the window size and title
    InitWindow(800, 450, "raylib [core] example - basic window");

    // Target 60 frames per second
    SetTargetFPS(60);

    // Main game loop
    while (!WindowShouldClose()) { // Detect window close button or ESC key
        // Update variables here
        
        // Draw
        BeginDrawing();

            ClearBackground(RAYWHITE);
            DrawText("Congrats! You created your first raylib window!", 190, 200, 20, LIGHTGRAY);

        EndDrawing();
    }

    // Close window and OpenGL context
    CloseWindow();

    return 0;
}


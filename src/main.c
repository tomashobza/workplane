#include "raylib.h"
#include "globals.h"
#include "utils.h"
#include "window.h"

int main(void) {
    // Initialize the window size and title
    InitWindow(WINDOW_W, WINDOW_H, "workplane");

    // Target 60 frames per second
    SetTargetFPS(60);

    Vector2 lastPos = {0, 0};
    Vector2 downPos = {0, 0};

    // Main game loop
    while (!WindowShouldClose()) { // Detect window close button or ESC key
        // Update variables here
        Vector2 mousePos = GetMousePosition();
        bool justMouseDown = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
        bool mouseDown = IsMouseButtonDown(MOUSE_BUTTON_LEFT);

        float scroll = GetMouseWheelMove();

        // TODO: figure out how tf we can zoom to the mouse
        if (scroll != 0) {
            Vector2 beforeMouseWrld = scene2world(mousePos);

            wv.scale = max(wv.scale + scroll / 10.0, 0.1);

            Vector2 afterMouseWrld = scene2world(mousePos);

            wv.position = trans(trans(beforeMouseWrld, inv(afterMouseWrld)), wv.position);
        }

        Window w;
        w.index = 0;
        w.name = "Pokus okno";
        w.shape = (Rectangle){ 30, 20, 100, 100 };
        Rectangle bb = getWindowBoundingBox(w);

        if (justMouseDown) {
            if (isInside(mousePos, bb)) {
                selectedWindow = w.index;
            } else {
                selectedWindow = -1;
            }

            downPos.x = mousePos.x;
            downPos.y = mousePos.y;

            // save pos
            lastPos = wv.position;
        }

        float xDelta = 0;
        float yDelta = 0;

        if (mouseDown) {
            xDelta = (mousePos.x - downPos.x) / wv.scale;
            yDelta = (mousePos.y - downPos.y) / wv.scale;
            wv.position.x = lastPos.x - xDelta;
            wv.position.y = lastPos.y - yDelta;
        }

        // Draw
        BeginDrawing();

            ClearBackground(RAYWHITE);

            int rectsize = 50;
            // DrawRectangle((coordX(0, position)), (coordY(0, position)), rectsize, rectsize, PINK);
            // DrawRectangle((coordX(-50, position)), (coordY(-50, position)), rectsize, rectsize, PINK);
            // DrawRectangle((coordX(50, position)), (coordY(50, position)), rectsize, rectsize, PINK);
            // Vector2 rectPos = world2scene_vec2((Vector2){ 0, 0 });
            // Vector2 rectPos2 = world2scene_vec2((Vector2){ 50, 50 });
            // Vector2 rectPos3 = world2scene_vec2((Vector2){ -50, -50 });
            // DrawRectangle(rectPos.x, rectPos.y, world2scene_scale(rectsize), world2scene_scale(rectsize), PINK);
            // DrawRectangle(rectPos2.x, rectPos2.y, world2scene_scale(rectsize), world2scene_scale(rectsize), PINK);
            // DrawRectangle(rectPos3.x, rectPos3.y, world2scene_scale(rectsize), world2scene_scale(rectsize), PINK);
            DrawWindow(w);
            // DrawRectangleLinesEx((Rectangle){ rectPos.x, rectPos.y, world2scene_scale(rectsize), world2scene_scale(rectsize) }, world2scene_scale(2.0), BLUE);
            // DrawText(TextFormat("Vector2 Pos: (%0.1f, %0.1f)", mousePos.x, mousePos.y), WINDOW_W - 280, WINDOW_H - 30, 20, DARKGRAY);
            DrawText(TextFormat("Scale: (%0.1f)", wv.scale), WINDOW_W - 280, WINDOW_H - 30, 20, DARKGRAY);
            // if (mouseDown) {
                // DrawText(TextFormat("Vector2 Pos: (%0.1f, %0.1f)", invCoordX(mousePos.x, position), invCoordY(mousePos.y, position)), WINDOW_W - 280, WINDOW_H - 30, 20, DARKGRAY);
                // DrawText(TextFormat("Vector2 Pos: (%0.1f, %0.1f)", position.x, position.y), WINDOW_W - 280, WINDOW_H - 30, 20, DARKGRAY);
            // }
            // DrawText("Congrats! You created your first raylib window!", 200, 200, 20, LIGHTGRAY);

            // if (wv.scale > 2) {
            //     for (int i=0; i<=100; i++) {
            //         for (int j=0; j<=100; j++) {
            //             Vector2 pos = world2scene_vec2((Vector2){ i*10, j*10 });
            //             Vector2 pos2 = world2scene_vec2((Vector2){ i*10 + 10, j*10 + 10 });
            //             DrawLine(pos.x, pos.y, pos.x, pos2.y, RED);
            //             DrawLine(pos.x, pos.y, pos2.x, pos.y, RED);
            //         }
            //     }
            // }

            Vector2 zero = world2scene_vec2((Vector2){ 0, 0 });
            DrawLine(zero.x, 0, zero.x, WINDOW_H, RED);
            DrawLine(0, zero.y, WINDOW_W, zero.y, RED);
            DrawText(TextFormat("%0.1f, %0.1f", wv.position.x, wv.position.y), zero.x + 5, zero.y + 5, 12, RED);

            Vector2 pointerWrld = scene2world(mousePos);
            DrawLine(mousePos.x, 0, mousePos.x, WINDOW_H, BLUE);
            DrawLine(0, mousePos.y, WINDOW_W, mousePos.y, BLUE);
            DrawText(TextFormat("%0.1f, %0.1f", pointerWrld.x, pointerWrld.y), mousePos.x + 5, mousePos.y + 5, 12, BLUE);

            DrawFPS(10, 10);

        EndDrawing();
    }

    // Close window and OpenGL context
    CloseWindow();

    return 0;
}

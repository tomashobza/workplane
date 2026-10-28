#include "raylib.h"

const int WINDOW_W = 800;
const int WINDOW_H = 450;
const float CENTER_X = WINDOW_W / 2.0;
const float CENTER_Y = WINDOW_H / 2.0;
const Vector2 CENTER = {CENTER_X, CENTER_Y};

Vector2 position = {0, 0};
Vector2 lastPos = {0, 0};
Vector2 downPos = {0, 0};

float scaleCoef = 1.0;

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

Vector2 world2scene(Vector2 v) {
    return trans(scale(trans(v, inv(position)), scaleCoef), CENTER);
}

Vector2 scene2world(Vector2 v) {
    return trans(scale(trans(v, inv(CENTER)), 1.0 / scaleCoef), position);
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

        // TODO: figure out how tf we can zoom to the mouse
        if (scroll != 0) {
            Vector2 beforeMouseWrld = scene2world(mousePos);

            scaleCoef = max(scaleCoef + scroll / 10.0, 0.1);

            Vector2 afterMouseWrld = scene2world(mousePos);

            position = trans(trans(beforeMouseWrld, inv(afterMouseWrld)), position);
        }

        if (justMouseDown) {
            downPos.x = mousePos.x;
            downPos.y = mousePos.y;

            // save pos
            lastPos = position;
        }

        float xDelta = 0;
        float yDelta = 0;

        if (mouseDown) {
            xDelta = (mousePos.x - downPos.x) / scaleCoef;
            yDelta = (mousePos.y - downPos.y) / scaleCoef;
            position.x = lastPos.x - xDelta;
            position.y = lastPos.y - yDelta;
        }

        // Draw
        BeginDrawing();

            ClearBackground(RAYWHITE);

            int rectsize = 50 * scaleCoef;
            // DrawRectangle((coordX(0, position)), (coordY(0, position)), rectsize, rectsize, PINK);
            // DrawRectangle((coordX(-50, position)), (coordY(-50, position)), rectsize, rectsize, PINK);
            // DrawRectangle((coordX(50, position)), (coordY(50, position)), rectsize, rectsize, PINK);
            Vector2 rectPos = world2scene((Vector2){ 0, 0 });
            Vector2 rectPos2 = world2scene((Vector2){ 50, 50 });
            Vector2 rectPos3 = world2scene((Vector2){ -50, -50 });
            DrawRectangle(rectPos.x, rectPos.y, rectsize, rectsize, PINK);
            DrawRectangle(rectPos2.x, rectPos2.y, rectsize, rectsize, PINK);
            DrawRectangle(rectPos3.x, rectPos3.y, rectsize, rectsize, PINK);
            // DrawText(TextFormat("Vector2 Pos: (%0.1f, %0.1f)", mousePos.x, mousePos.y), WINDOW_W - 280, WINDOW_H - 30, 20, DARKGRAY);
            DrawText(TextFormat("Scale: (%0.1f)", scaleCoef), WINDOW_W - 280, WINDOW_H - 30, 20, DARKGRAY);
            // if (mouseDown) {
                // DrawText(TextFormat("Vector2 Pos: (%0.1f, %0.1f)", invCoordX(mousePos.x, position), invCoordY(mousePos.y, position)), WINDOW_W - 280, WINDOW_H - 30, 20, DARKGRAY);
                // DrawText(TextFormat("Vector2 Pos: (%0.1f, %0.1f)", position.x, position.y), WINDOW_W - 280, WINDOW_H - 30, 20, DARKGRAY);
            // }
            // DrawText("Congrats! You created your first raylib window!", 200, 200, 20, LIGHTGRAY);

            if (scaleCoef > 2) {
                for (int i=0; i<=100; i++) {
                    for (int j=0; j<=100; j++) {
                        Vector2 pos = world2scene((Vector2){ i*10, j*10 });
                        Vector2 pos2 = world2scene((Vector2){ i*10 + 10, j*10 + 10 });
                        DrawLine(pos.x, pos.y, pos.x, pos2.y, RED);
                        DrawLine(pos.x, pos.y, pos2.x, pos.y, RED);
                    }
                }
            }

            Vector2 zero = world2scene((Vector2){ 0, 0 });
            DrawLine(zero.x, 0, zero.x, WINDOW_H, RED);
            DrawLine(0, zero.y, WINDOW_W, zero.y, RED);
            DrawText(TextFormat("%0.1f, %0.1f", position.x, position.y), zero.x + 5, zero.y + 5, 12, RED);

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

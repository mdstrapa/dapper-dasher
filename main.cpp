#include "raylib.h"

int main(){

    const int windowWidth{512};
    const int windowHeight{380};

    InitWindow(windowWidth,windowHeight,"Dapper Dasher Game");

    const int gravity{1};

    // rectangle dimensions
    const int width{50};
    const int height{80};

    int posY{windowHeight - height};
    int velocity{0};


    SetTargetFPS(60);
    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(WHITE);

        // perform a ground check
        if(posY >= windowHeight - height){
            // rectangle is on the ground
            velocity = 0;
        }else{
            // rectangle is on the air
            velocity += gravity;
        }

        if(IsKeyPressed(KEY_SPACE)){
            velocity = -10;
        }

        // update position
        posY += velocity;

        DrawRectangle(windowWidth/2, posY, width, height, BLUE);

        EndDrawing();
    }
    CloseWindow();
}
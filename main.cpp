#include "raylib.h"

int main(){

    const int windowWidth{512};
    const int windowHeight{380};

    InitWindow(windowWidth,windowHeight,"Dapper Dasher Game");

    const int gravity{1'000};

    // nebula variables
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");
    Rectangle nebRec;
    nebRec.x = 0;
    nebRec.y = 0;
    nebRec.width = nebula.width/8;
    nebRec.height = nebula.height/8;
    Vector2 nebPos{windowWidth,windowHeight-nebRec.height};

    // nebula X velocity (pixels/second)
    int nebVel{-600};

    // scarfy variables
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    Rectangle scarfyRec;
    scarfyRec.width = scarfy.width / 6;
    scarfyRec.height = scarfy.height;
    scarfyRec.x = 0;
    scarfyRec.y = 0;
    Vector2 scarfyPos;
    scarfyPos.x = windowWidth / 2 - scarfyRec.width / 2;
    scarfyPos.y = windowHeight - scarfyRec.height;

    int frame{0};
    // amount of time before we update the animation frame
    const float updateTime{1.0/12};
    float runningTime{};

    int velocity{0};

    bool isInAir{false};

    // pixels per second
    const int jumpVel{-600};

    SetTargetFPS(60);
    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(WHITE);
        float dt{GetFrameTime()};

        // perform a ground check
        if(scarfyPos.y >= windowHeight - scarfyRec.height){
            // rectangle is on the ground
            velocity = 0;
            isInAir = false;
        }else{
            // rectangle is on the air
            velocity += gravity * dt;
            isInAir = true;
        }


        // jump check
        if(IsKeyPressed(KEY_SPACE) && !isInAir){
            velocity += jumpVel;
        }

        // update nebula posistion
        nebPos.x += nebVel * dt;

        // update scarfy position
        scarfyPos.y += velocity * dt;
        

        if(!isInAir){
            // update animantion frame
            runningTime += dt;
            if(runningTime>=updateTime){
                runningTime = 0;
                scarfyRec.x = frame * scarfyRec.width;
                frame++;
                if(frame > 5) {
                    frame = 0;
                }
            }
        }

        
        // draw nebula
        DrawTextureRec(nebula,nebRec,nebPos,WHITE);

        // draw scarfy
        DrawTextureRec(scarfy,scarfyRec,scarfyPos,WHITE);

        EndDrawing();
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();
}
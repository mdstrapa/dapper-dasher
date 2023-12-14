#include "raylib.h"

struct AnimData{
    Rectangle rec;
    Vector2 pos;
    int frame;
    float updateTime;
    float runningTime;
};


int main(){

    const int windowWidth{512};
    const int windowHeight{380};

    InitWindow(windowWidth,windowHeight,"Dapper Dasher Game");

    const int gravity{1'000};

    // nebula variables
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");

    // AnimData for nebula
    AnimData nebData;
    nebData.rec.height = nebula.height/8;
    nebData.rec.width = nebula.width/8;
    nebData.rec.x = 0.0;
    nebData.rec.y = 0.0;
    nebData.pos.x = windowWidth;
    nebData.pos.y = windowHeight - nebula.height/8;
    nebData.frame = 0;
    nebData.updateTime =  1.0/12.0;
    nebData.runningTime = 0.0;

    AnimData neb2Data;
    neb2Data.rec.height = nebula.height/8;
    neb2Data.rec.width = nebula.width/8;
    neb2Data.rec.x = 0.0;
    neb2Data.rec.y = 0.0;
    neb2Data.pos.x = windowWidth + 300;
    neb2Data.pos.y = windowHeight - nebula.height/8;
    neb2Data.frame = 0;
    neb2Data.updateTime =  1.0/16.0;
    neb2Data.runningTime = 0.0;


    // nebula X velocity (pixels/second)
    int nebVel{-200};

    // scarfy variables
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    AnimData scarfyData;
    scarfyData.rec.width = scarfy.width / 6;
    scarfyData.rec.height = scarfy.height;
    scarfyData.rec.x = 0;
    scarfyData.rec.y = 0;
    scarfyData.pos.x = windowWidth / 2 - scarfyData.rec.width / 2;
    scarfyData.pos.y = windowHeight - scarfyData.rec.height;
    scarfyData.frame = 0;
    scarfyData.updateTime = 1.0/12.0;
    scarfyData.runningTime = 0.0;


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
        if(scarfyData.pos.y >= windowHeight - scarfyData.rec.height){
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
        nebData.pos.x += nebVel * dt;
        // update second neb position
        neb2Data.pos.x += nebVel * dt;



        // update scarfy position
        scarfyData.pos.y += velocity * dt;
        
        // update scarfy animation frame
        if(!isInAir){
            // update animantion frame
            scarfyData.runningTime += dt;
            if(scarfyData.runningTime>=scarfyData.updateTime){
                scarfyData.runningTime = 0;
                scarfyData.rec.x = scarfyData.frame * scarfyData.rec.width;
                scarfyData.frame++;
                if(scarfyData.frame > 5) {
                    scarfyData.frame = 0;
                }
            }
        }

        // update nebula animantion frame
        nebData.runningTime += dt;
        if(nebData.runningTime>=nebData.updateTime){
            nebData.runningTime = 0;
            nebData.rec.x = nebData.frame * nebData.rec.width;
            nebData.frame++;
            if(nebData.frame > 7) {
                nebData.frame = 0;
            }
        }

        neb2Data.runningTime += dt;
        if(neb2Data.runningTime>=neb2Data.updateTime){
            neb2Data.runningTime = 0;
            neb2Data.rec.x = neb2Data.frame * neb2Data.rec.width;
            neb2Data.frame++;
            if(neb2Data.frame > 7) {
                neb2Data.frame = 0;
            }
        }


        
        // draw nebula
        DrawTextureRec(nebula,nebData.rec,nebData.pos,WHITE);
        // draw the second nebula
        DrawTextureRec(nebula,neb2Data.rec,neb2Data.pos,RED);

        // draw scarfy
        DrawTextureRec(scarfy,scarfyData.rec,scarfyData.pos,WHITE);

        EndDrawing();
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();
}
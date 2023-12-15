#include "raylib.h"

struct AnimData{
    Rectangle rec;
    Vector2 pos;
    int frame;
    float updateTime;
    float runningTime;
};


int main(){

    int windowDimensions[2];
    windowDimensions[0] = 512;
    windowDimensions[1] = 380;

    InitWindow(windowDimensions[0],windowDimensions[1],"Dapper Dasher Game");

    const int gravity{1'000};

    // nebula variables
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");

    // AnimData for nebula
    const int sizeOfNebule{6};
    AnimData nebulae[sizeOfNebule]{};

    for(int i = 0; i < sizeOfNebule; i++){
        nebulae[i].rec.x = 0.0;
        nebulae[i].rec.y = 0.0;
        nebulae[i].rec.width = nebula.width/8;
        nebulae[i].rec.height = nebula.height/8;
        nebulae[i].pos.x = windowDimensions[0] + (i * 300);
        nebulae[i].pos.y = windowDimensions[1] - nebula.height/8;
        nebulae[i].frame = 0;
        nebulae[i].runningTime = 0.0;
        nebulae[i].updateTime = 1.0/16.0;
    }

    // nebula X velocity (pixels/second)
    int nebVel{-200};

    // scarfy variables
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    AnimData scarfyData;
    scarfyData.rec.width = scarfy.width / 6;
    scarfyData.rec.height = scarfy.height;
    scarfyData.rec.x = 0;
    scarfyData.rec.y = 0;
    scarfyData.pos.x = windowDimensions[0] / 2 - scarfyData.rec.width / 2;
    scarfyData.pos.y = windowDimensions[1] - scarfyData.rec.height;
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
        if(scarfyData.pos.y >= windowDimensions[1] - scarfyData.rec.height){
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
        for(int i = 0; i < sizeOfNebule; i++){
            nebulae[i].pos.x += nebVel * dt;
        }

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
        for(int i = 0; i < sizeOfNebule; i++){
            nebulae[i].runningTime += dt;
            if(nebulae[i].runningTime>=nebulae[i].updateTime){
                nebulae[i].runningTime = 0;
                nebulae[i].rec.x = nebulae[i].frame * nebulae[i].rec.width;
                nebulae[i].frame++;
                if(nebulae[i].frame > 7) {
                    nebulae[i].frame = 0;
                }
            }
        }

        // draw nebula
        for(int i = 0; i < sizeOfNebule; i++){
            DrawTextureRec(nebula,nebulae[i].rec,nebulae[i].pos,WHITE);
        }

        // draw scarfy
        DrawTextureRec(scarfy,scarfyData.rec,scarfyData.pos,WHITE);

        EndDrawing();
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();
}
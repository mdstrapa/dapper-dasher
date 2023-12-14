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

    Rectangle neb2Rec;
    neb2Rec.x = 0;
    neb2Rec.y = 0;
    neb2Rec.width = nebula.width/8;
    neb2Rec.height = nebula.height/8;
    Vector2 neb2Pos{windowWidth + 300,windowHeight-nebRec.height};


    // nebula X velocity (pixels/second)
    int nebVel{-200};

    // nebula animation variables
    int nebFrame{0};
    const float nebUpdateTime{1.0/12.0};
    float nebRunningTime{};

    int neb2Frame{0};
    const float neb2UpdateTime{1.0/16.0};
    float neb2RunningTime{};


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
        // update second neb position
        neb2Pos.x += nebVel * dt;



        // update scarfy position
        scarfyPos.y += velocity * dt;
        
        // update scarfy animation frame
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

        // update nebula animantion frame
        nebRunningTime += dt;
        if(nebRunningTime>=nebUpdateTime){
            nebRunningTime = 0;
            nebRec.x = nebFrame * nebRec.width;
            nebFrame++;
            if(nebFrame > 7) {
                nebFrame = 0;
            }
        }

        neb2RunningTime += dt;
        if(neb2RunningTime>=neb2UpdateTime){
            neb2RunningTime = 0;
            neb2Rec.x = neb2Frame * neb2Rec.width;
            neb2Frame++;
            if(neb2Frame > 7) {
                neb2Frame = 0;
            }
        }


        
        // draw nebula
        DrawTextureRec(nebula,nebRec,nebPos,WHITE);
        // draw the second nebula
        DrawTextureRec(nebula,neb2Rec,neb2Pos,RED);

        // draw scarfy
        DrawTextureRec(scarfy,scarfyRec,scarfyPos,WHITE);

        EndDrawing();
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();
}
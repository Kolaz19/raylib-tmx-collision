#include "../include/raylib.h"

#define RAYLIB_TMX_IMPLEMENTATION
#include "../include/raylib-tmx.h"
#include "../MapCollision.h"
#include <stdbool.h>

    
    const int originalScreenWidth = 1920*0.95f;
    const int originalScreenHeight = 1080*0.95f;
    static int currentScreenWidth = originalScreenWidth;
    static int currentScreenHeight = originalScreenHeight;
    const int scaleMultiplier = 7;

void config();
void updatePlayerPosition(Rectangle *rect);
void resizePlayerWithMousewheel(Rectangle *player);

int main(void) {
    config();
    RenderTexture2D backgroundTexture = LoadRenderTexture(256,128);
    RenderTexture2D renderAll = LoadRenderTexture(256*scaleMultiplier,128*scaleMultiplier);

    tmx_map* room = LoadTMX("simpleMap.tmx");
    Rectangle player = {140,140, 18*scaleMultiplier,18*scaleMultiplier};
    Rectangle playerPrevious = player;


    //Prepare map texture and scale it up
    BeginTextureMode(backgroundTexture);
    DrawTMX(room,0,0,WHITE);
    EndTextureMode();



    //Map Collision


   // MapLayout *map = initMapLayout(0,0,16*scaleMultiplier,16*scaleMultiplier,16,8,&collisionMapping[0][0]);
    tmx_resource_manager* rm = tmx_make_resource_manager();
    CollisionBoxes *boxes = initCollisionBoxes("simpleMap.tmx",(Vector2){0.0f,0.0f},7.0f,rm, 1);


    while (!WindowShouldClose())
    {

        resizePlayerWithMousewheel(&player);
        updatePlayerPosition(&player);
        
        //To use this method, we have to keep the previous frame position/information
        //keepOutsideMapCollision(&player, playerPrevious, map);
        playerPrevious = player;
/*----------------------------------------------------------
*   Draw all entities to one texture with proper scaling
----------------------------------------------------------*/
        BeginTextureMode(renderAll);
        DrawTexturePro(backgroundTexture.texture,
                        (Rectangle){ 0.0f, 0.0f, (float)backgroundTexture.texture.width, (float)-backgroundTexture.texture.height },
                        (Rectangle){ (0.0f), (0.0f),backgroundTexture.texture.width * scaleMultiplier, backgroundTexture.texture.height * scaleMultiplier},
                        (Vector2){ 0, 0 },
                        0.0f,
                        WHITE);
                DrawRectanglePro(player,(Vector2){0,0},0.0f,GREEN);                    


        EndTextureMode();

/*----------------------------------------------------------
*   Draw Calls
----------------------------------------------------------*/
        BeginDrawing();

            ClearBackground(RAYWHITE);
                DrawTexturePro(renderAll.texture,
                        (Rectangle){ 0.0f, 0.0f, (float)renderAll.texture.width, (float)-renderAll.texture.height },
                        (Rectangle){ (0.0f), (0.0f),renderAll.texture.width, renderAll.texture.height},
                        (Vector2){ 0, 0 },
                        0.0f,
                        WHITE);
                for (int i = 0; i < boxes->amountCollisionBoxes; i++) {
                    Rectangle *currentRectangle = boxes->scaledCollision+i;
                    DrawRectangle(currentRectangle->x, currentRectangle->y, currentRectangle->width, currentRectangle->height, PINK);
                }

        EndDrawing();


    }

    UnloadTMX(room);
    unloadMapCollision(boxes);
    tmx_free_resource_manager(rm);
    //unloadMapLayout(map);
    CloseWindow();        // Close window and OpenGL context
    return 0;
}

void config() {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    SetConfigFlags(FLAG_VSYNC_HINT);
    InitWindow(currentScreenWidth, currentScreenHeight, "Move Rectangle");
    SetTargetFPS(60);              

}


void updatePlayerPosition(Rectangle *rect) {
    float speed = 10.0f;
    //Sideways movement
    if ((IsKeyDown(KEY_A) && IsKeyDown(KEY_W)) || 
    (IsKeyDown(KEY_W) && IsKeyDown(KEY_D)) ||
    (IsKeyDown(KEY_D) && IsKeyDown(KEY_S)) ||
    (IsKeyDown(KEY_S) && IsKeyDown(KEY_A))) {
        // speed *= 0.7f;
        speed = 7.0f;
    }

    if(IsKeyDown(KEY_A)) {
        rect->x -= speed;
    } 
    if(IsKeyDown(KEY_D)) {
        rect->x += speed;
    }
    if(IsKeyDown(KEY_W)) {
        rect->y -= speed;
    }
    if(IsKeyDown(KEY_S)) {
        rect->y += speed;
    }
}

void resizePlayerWithMousewheel(Rectangle *player) {
    float mouseWheelMovement = GetMouseWheelMove();
    if (mouseWheelMovement > 0 && player->height < (25*scaleMultiplier)) {
        player->height = player->height + 3;
        player->width = player->width + 3;
        player->x = 140;
        player->y = 140;
    } else if(mouseWheelMovement < 0 && player->height > 20) {
        player->height = player->height - 3;
        player->width = player->width - 3;    
        player->x = 140;
        player->y = 140;
    }
}



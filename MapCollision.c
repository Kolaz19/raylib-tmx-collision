#include "MapCollision.h"
#include <stdlib.h>
//#define NDEBUG
#include <assert.h>



void initCollisionRectangles(MapLayout *map, int *collision);

/// @param xStart At which x coordinate does map render
/// @param yStart At which y coordinate does map render
/// @param amountTileX The amount of tiles on the x-axis
/// @param amountTileY The amount of tiles on the y-asix
/// @param collision 2D array with collision mapping
MapLayout* initMapLayout(int xStart, int yStart, int tileHeight, int tileWidth, int amountTileX, int amountTileY, int *collision) {
    MapLayout *layout = malloc(sizeof(MapLayout));
    layout->xStart = xStart;
    layout->yStart = yStart;
    layout->tileHeight = tileHeight;
    layout->tileWidth = tileWidth;
    layout->amountTileX = amountTileX;
    layout->amountTileY = amountTileY;

    initCollisionRectangles(layout, collision);

    return layout;
}

/// @brief Creates a rectangle for every collision box
/// @param map 2D array with collision mapping
void initCollisionRectangles(MapLayout *map, int *collision) {
    int currentRectangle = 0;
    map->amountCollisionBoxes = 0;

    //Determine size of rectangle array
    for(int i = 0; i < map->amountTileY; i++) {
        for (int k = 0; k < map->amountTileX; k++) {
            if(*(collision+(map->amountTileX*i+k)) == 1) {
                map->amountCollisionBoxes++;
            }
        }
    }

    map->collision = malloc(sizeof(Rectangle) * map->amountCollisionBoxes);

    for(int i = 0; i < map->amountTileY; i++) {
        for (int k = 0; k < map->amountTileX; k++) {
            if(*(collision+(map->amountTileX*i+k)) == 1) {
                map->collision[currentRectangle].height = map->tileHeight;
                map->collision[currentRectangle].width = map->tileWidth;
                map->collision[currentRectangle].x = map->xStart + (k * map->tileWidth);
                map->collision[currentRectangle].y = map->yStart + (i * map->tileHeight);
                currentRectangle++;
            }
        }
    }

    assert(currentRectangle == map->amountCollisionBoxes);
}

bool isColliding(const Rectangle *rect, MapLayout *map ) {
    for (int i = 0; i < map->amountCollisionBoxes; i++) {
        if (CheckCollisionRecs(*rect, map->collision[i])) {
            return true;
        }
    }
    return false;
}

void keepOutsideMapCollision (Rectangle *rect, Rectangle rectPreviousFrame, MapLayout *map) {
    int originalX = rect->x;

    //First take X placement out of the equation
    //X position to last frame where no collision was detected
    rect->x = rectPreviousFrame.x;
    //Correct y placement until no collision is detected
    for (int i = 0; i < map->amountCollisionBoxes; i++) {         

        while(CheckCollisionRecs(*rect,map->collision[i])) {
            if(rect->y > rectPreviousFrame.y) {
                rect->y -= 1;
            } else if(rect->y < rectPreviousFrame.y) {
                rect->y += 1;
            }   
        }

    }

    //Correct x placement until no collision is detected
    rect->x = originalX;
    for (int i = 0; i < map->amountCollisionBoxes; i++) {

        while(CheckCollisionRecs(*rect,map->collision[i])) {
            if(rect->x > rectPreviousFrame.x) {
                rect->x -= 1;
            } else if(rect->x < rectPreviousFrame.x) {
                rect->x += 1;
            }
        }

    }

}




void unloadMapLayout(MapLayout *map) {
    free(map->collision);
    free(map);
}


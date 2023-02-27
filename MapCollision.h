#ifndef MAP_COLLISION_H
#define MAP_COLLISION_H
#include <stdbool.h>
#include "./include/raylib.h"


typedef struct MapLayout {
    int xStart;
    int yStart;
    int tileHeight;
    int tileWidth;
    int amountTileX;
    int amountTileY;
    int amountCollisionBoxes;
    Rectangle *collision;
} MapLayout;

MapLayout* initMapLayout(int xStart, int yStart, int tileHeight, int tileWidth, int amountTileX, int amountTileY, int *collision);
void unloadMapLayout(MapLayout *map);
bool isColliding(const Rectangle *rect, MapLayout *map );
void keepOutsideMapCollision (Rectangle *rect, Rectangle rectPreviousFrame, MapLayout *map);


#endif
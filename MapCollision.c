#include "MapCollision.h"
#include "TmxCollisionMapper.h"
#include <stdlib.h>
#include <stdio.h>
//#define NDEBUG
#include <assert.h>




CollisionBoxes* initCollisionBoxes(const char* tmxFileName, Vector2 origin, float scale, tmx_resource_manager* resource_manager) {


    MapCollisionData* mapData = getRawMapData(resource_manager,"simpleMap.tmx",1);

    for (int i = 0; i < mapData->collisionTilesCount; i++) {
        TileWithCollisionData* colData = mapData->collisionTiles+i;
        printf("x:%d\ty:%d\n",(mapData->collisionTiles+i)->xPos,(mapData->collisionTiles+i)->yPos);
    }

    CollisionBoxes *collisionBoxes = malloc(sizeof(CollisionBoxes));
    collisionBoxes->amountCollisionBoxes = 0;

    tmx_object* collision = NULL;
    for (int i = 0; i < mapData->collisionTilesCount; i++) {
        collision = mapData->collisionTiles[i].collisionData;
        while (collision != NULL) {
            collisionBoxes->amountCollisionBoxes++;
            collision = collision->next;
        }
    }

    collisionBoxes->scaledCollision = malloc(sizeof(Rectangle) * collisionBoxes->amountCollisionBoxes);
    collisionBoxes->scale = scale;
    Rectangle* currentRect = NULL;
    TileWithCollisionData* currentCollision = NULL;
    tmx_object* currentCollisionData = NULL;

    int currentIndex = 0;
    for (int i = 0; i < mapData->collisionTilesCount; i++) {
        currentCollision = mapData->collisionTiles+i;

        currentCollisionData = currentCollision->collisionData;

        while (currentCollisionData != NULL) {
            currentRect = collisionBoxes->scaledCollision+currentIndex;
            currentRect->x = origin.x + ((( origin.x + currentCollision->xPos * *mapData->tileWidth + currentCollisionData->x ) - origin.x ) * scale );
            currentRect->y = origin.y + ((( origin.y + currentCollision->yPos * *mapData->tileHeight + currentCollisionData->y ) - origin.y ) * scale );
            currentRect->width = currentCollisionData->width * scale;
            currentRect->height = currentCollisionData->height * scale;
            currentCollisionData = currentCollisionData->next;
            currentIndex++;
        }
    }

    return collisionBoxes;




//TODO unload Resources
}




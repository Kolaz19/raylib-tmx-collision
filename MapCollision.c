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
    collisionBoxes->scaledCollision = malloc(sizeof(Rectangle)*mapData->collisionTilesCount);
    Rectangle* currentRect = NULL;
    TileWithCollisionData* currentCollision = NULL;

    for (int i = 0; i < mapData->collisionTilesCount; i++) {
        currentRect = collisionBoxes->scaledCollision+i;
        currentCollision = mapData->collisionTiles+i;
    }






//TODO unload Resources
}




#include "TmxCollisionMapper.h"
#include <stdbool.h>
#include <stdlib.h>


typedef struct CollisionTile{
    int tileid;
    tmx_object* collisionData;
} CollisionTile;


//TODO resource manager NULL
MapCollisionData* getRawMapData(tmx_resource_manager* rm, const char *tmxFileName, int layerid) {
    int collisionCount = 0;
    tmx_map* map = tmx_rcmgr_load(rm,tmxFileName);

    for (int i = 0; i < map->ts_head->tileset->tilecount; i++) {
        if ((map->ts_head->tileset->tiles+i)->collision != NULL) {
            collisionCount++;
        }
    }

    MapCollisionData* collisionData = malloc(sizeof(MapCollisionData));
    collisionData->collisionTilesCount = 0;
    collisionData->map = map;
    CollisionTile* collisionTiles = malloc(collisionCount*sizeof(CollisionTile));
    collisionData->tileHeight = &map->ts_head->tileset->tile_height;
    collisionData->tileWidth = &map->ts_head->tileset->tile_width;
    //TODO Tile Offset

    collisionCount = 0;
    for (int i = 0; i < map->ts_head->tileset->tilecount; i++) {
        if ((map->ts_head->tileset->tiles+i)->collision != NULL) {
            (collisionTiles+collisionCount)->collisionData = (map->ts_head->tileset->tiles+i)->collision;
            (collisionTiles+collisionCount)->tileid = (map->ts_head->tileset->tiles+i)->id;
            collisionCount++;
        }
    }



    for (int out = 0; out < map->height; out++) {
        for (int in = 0; in < map->width; in++) {
            for (int collisionCounter = 0; collisionCounter < collisionCount; collisionCounter++) {
                if (*(map->ly_head->content.gids+(out*map->width+in)) == (collisionTiles+collisionCounter)->tileid+1 ){ //TODO check if +1 necessary
                    collisionData->collisionTilesCount++;                               
                }           
            }
        }  
    }

    collisionData->collisionTiles = malloc(collisionData->collisionTilesCount*sizeof(TileWithCollisionData));

    tmx_layer* currentLayer = map->ly_head;
    while (currentLayer->id != layerid ) {
        currentLayer = currentLayer->next;
    }

    int collisionTilesCounter = 0;
    for (int out = 0; out < map->height; out++) {
        for (int in = 0; in < map->width; in++) {
            for (int collisionCounter = 0; collisionCounter < collisionCount; collisionCounter++) {
                //TODO Choose layer
                if (*(map->ly_head->content.gids+(out*map->width+in)) == (collisionTiles+collisionCounter)->tileid+1 ){ //TODO check if +1 necessary
                    (collisionData->collisionTiles+collisionTilesCounter)->collisionData = (collisionTiles+collisionCounter)->collisionData;   
                    (collisionData->collisionTiles+collisionTilesCounter)->xPos = in;
                    (collisionData->collisionTiles+collisionTilesCounter)->yPos = out;                    
                    collisionTilesCounter++;
                }           
            }
        }  
    }




    free(collisionTiles);
    return collisionData;
}


void unloadRawMapData(MapCollisionData* mapData) {
    free(mapData->collisionTiles);
    tmx_map_free(mapData->map);
    free(mapData);
}
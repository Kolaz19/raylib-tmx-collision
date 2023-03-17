#include "TmxCollisionMapper.h"
#include <stdbool.h>
#include <stdlib.h>


typedef struct CollisionTile{
    int tileid;
    tmx_object* collisionData;
} CollisionTile;


//TODO resource manager NULL
MapCollisionData* getRawMapData(tmx_resource_manager* rm, const char *tmxFileName) {
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




free(collisionTiles);
return collisionData;
}

//TODO free resources
void unloadRawMapData(MapCollisionData* mapData) {
    tmx_map_free(mapData->map);
    free(mapData);
}
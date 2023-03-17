#include "TmxCollisionMapper.h"
#include <stdbool.h>
#include <stdlib.h>




MapDataRaw* getRawMapData(tmx_resource_manager* rm, const char *tmxFileName) {
int collisionCount = 0;
tmx_map* map = tmx_rcmgr_load(rm,tmxFileName);

for (int i = 0; i < map->ts_head->tileset->tilecount; i++) {
    if ((map->ts_head->tileset->tiles+i)->collision != NULL) collisionCount++;
}

MapDataRaw* mapDataRaw = malloc(sizeof(MapDataRaw));
mapDataRaw->map = map;
mapDataRaw->collisionCount = collisionCount;
mapDataRaw->collisionData = malloc(collisionCount*sizeof(tmx_object*));

tmx_object* colObjects[collisionCount];
collisionCount = 0;
for (int i = 0; i < map->ts_head->tileset->tilecount; i++) {
    if ((map->ts_head->tileset->tiles+i)->collision != NULL) {
        *(mapDataRaw->collisionData+collisionCount) = (map->ts_head->tileset->tiles+i)->collision;
        collisionCount++;
    }
}


return mapDataRaw;
}


void unloadRawMapData(MapDataRaw* mapData) {
    free(mapData->collisionData);
    tmx_map_free(mapData->map);
    free(mapData);
}
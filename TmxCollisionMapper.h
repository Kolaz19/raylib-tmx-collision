#ifndef TMX_COLLISION_MAPPER_H
#define TMX_COLLISION_MAPPER_H
#include "include/tmx.h"

typedef struct MapDataRaw{
    tmx_map* map;
    tmx_object** collisionData;
    int collisionCount;
} MapDataRaw;

MapDataRaw* getRawMapData(tmx_resource_manager* rm, const char *tmxFileName);
void unloadRawMapData(MapDataRaw* mapData);


#endif
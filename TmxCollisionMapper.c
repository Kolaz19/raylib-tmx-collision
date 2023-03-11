#include "TmxCollisionMapper.h"
#include "include/tmx.h"
#include <stdbool.h>



void testMethodTmx(void) {
int collisionCount = 0;
tmx_resource_manager* rm = tmx_make_resource_manager();
tmx_map* map = tmx_rcmgr_load(rm, "simpleMap.tmx");

for (int i = 0; i < map->ts_head->tileset->tilecount; i++) {
    if ((map->ts_head->tileset->tiles+i)->collision != NULL) collisionCount++;
}


tmx_object* colObjects[collisionCount];
collisionCount = 0;
for (int i = 0; i < map->tilecount; i++) {
    if ((map->ts_head->tileset->tiles+i)->collision != NULL) {
        colObjects[collisionCount] = (map->ts_head->tileset->tiles+i)->collision;
        collisionCount++;
    }
}


tmx_map_free(map);
tmx_free_resource_manager(rm);
}
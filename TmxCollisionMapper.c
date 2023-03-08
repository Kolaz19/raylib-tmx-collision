#include "TmxCollisionMapper.h"
#include "include/tmx.h"

void testMethodTmx(void) {
tmx_resource_manager* rm = tmx_make_resource_manager();
tmx_map* map = tmx_rcmgr_load(rm, "simpleMap.tmx");

tmx_object* col1 = map->ts_head->tileset->tiles->collision;
tmx_object* col2 = (map->ts_head->tileset->tiles+1)->collision;


tmx_map_free(map);
tmx_free_resource_manager(rm);
int hey = 7;
}
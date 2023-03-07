#include "TmxReader.h"
#include "include/tmx.h"

void testMethodTmx(void) {
tmx_map* map = tmx_load("simpleMap.tmx");
tmx_tile* tile = *(map->tiles);

int hey = 7;
}
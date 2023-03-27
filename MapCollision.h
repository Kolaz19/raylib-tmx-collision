#ifndef MAP_COLLISION_H
#define MAP_COLLISION_H
#include <stdbool.h>
#include "./include/raylib.h"
#include "include/tmx.h"


typedef struct CollisionBoxes {
    int amountCollisionBoxes;
    Rectangle *scaledCollision;
    float scale;
} CollisionBoxes;

CollisionBoxes* initCollisionBoxes(const char* tmxFileName, Vector2 origin, float scale, tmx_resource_manager* resource_manager);



#endif
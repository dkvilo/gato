#if !defined(DK_RAYCAST_H)
#define DK_RAYCAST_H

#include "dk_collision.h"

typedef struct {
  float x;
  float y;
} dk_vec2;

typedef struct {
  dk_vec2 origin;
  dk_vec2 direction;
} dk_ray;

typedef struct {
  dk_vec2 position;
  dk_vec2 normal;
  float distance;
} dk_hit;

typedef struct {
  dk_ray ray;
  dk_hit hit;
} dk_raycast_result;

dk_raycast_result dk_raycast(dk_ray ray, BoundingBox box);

#endif // DK_RAYCAST_H
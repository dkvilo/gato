#include "dk_raycast.h"

dk_raycast_result dk_raycast(dk_ray ray, BoundingBox box) {
  dk_raycast_result result = {0};
  
  dk_vec2 inv_direction = {0};
  inv_direction.x = 1.0f / ray.direction.x;
  inv_direction.y = 1.0f / ray.direction.y;
  
  int sign[2] = {0};
  sign[0] = (inv_direction.x < 0);
  sign[1] = (inv_direction.y < 0);

  float tmin, tmax, tymin, tymax;
  
  tmin = (box.x - ray.origin.x) * inv_direction.x;
  tmax = (box.x + box.width - ray.origin.x) * inv_direction.x;

  tymin = (box.y - ray.origin.y) * inv_direction.y;
  tymax = (box.y + box.height - ray.origin.y) * inv_direction.y;

  if ((tmin > tymax) || (tymin > tmax)) {
    return result;
  }

  if (tymin > tmin) {
    tmin = tymin;
  }

  if (tymax < tmax) {
    tmax = tymax;
  }

  result.hit.position.x = ray.origin.x + ray.direction.x * tmin;
  result.hit.position.y = ray.origin.y + ray.direction.y * tmin;

  result.hit.normal.x = sign[0] ? -1.0f : 1.0f;
  result.hit.normal.y = sign[1] ? -1.0f : 1.0f;

  result.hit.distance = tmin;

  return result;
}
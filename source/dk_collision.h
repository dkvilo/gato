#if !defined(__DK_COLLISION_H__)
#define __DK_COLLISION_H__

#include <stdint.h>
#include <stdbool.h>
#include <math.h>

typedef struct BoundingBox {
  float x, y;
  float width, height;
} BoundingBox;

typedef struct BoundingCircle {
  float x;
  float y;
  float radius;
} BoundingCircle;

BoundingBox Box(float x, float y, float width, float height);

BoundingCircle Circle(float x, float y, float radius);

bool DKCollision_BoundingBoxesAreColliding(BoundingBox *a, BoundingBox *b);

bool DKCollision_BoundingBoxAndCircleAreColliding(BoundingBox *box, BoundingCircle *circle);

bool DKCollision_BoundingCirclesAreColliding(BoundingCircle *a, BoundingCircle *b);

#endif // __DK_COLLISION_H__
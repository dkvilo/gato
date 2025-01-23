#include "dk_collision.h"

/**
 * @todo move this to a math library
 */
static float distanceSq(float x1, float y1, float x2, float y2) {
  float dx = x2 - x1;
  float dy = y2 - y1;
  return dx * dx + dy * dy;
}

BoundingBox Box(float x, float y, float width, float height) {
  BoundingBox box;
  box.x = x;
  box.y = y;
  box.width = width;
  box.height = height;
  return box;
}

BoundingCircle Circle(float x, float y, float radius) {
  BoundingCircle circle;
  circle.x = x;
  circle.y = y;
  circle.radius = radius;
  return circle;
}

bool DKCollision_BoundingBoxesAreColliding(BoundingBox *a, BoundingBox *b) {
  return (
    a->x < b->x + b->width &&
    a->x + a->width > b->x &&
    a->y < b->y + b->height &&
    a->y + a->height > b->y
  );
}

bool DKCollision_BoundingBoxAndCircleAreColliding(BoundingBox *box, BoundingCircle *circle) {
  float x = fmax(box->x, fmin(circle->x, box->x + box->width));
  float y = fmax(box->y, fmin(circle->y, box->y + box->height));
  return distanceSq(x, y, circle->x, circle->y) < (circle->radius * circle->radius);
}

bool DKCollision_BoundingCirclesAreColliding(BoundingCircle *a, BoundingCircle *b) {
  float distanceSqBetweenCenters = distanceSq(a->x, a->y, b->x, b->y);
  float sumOfRadiiSq = (a->radius + b->radius) * (a->radius + b->radius);
  return distanceSqBetweenCenters <= sumOfRadiiSq;
}


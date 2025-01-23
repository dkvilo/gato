#if !defined(DK_TWEEN_H)
#define DK_TWEEN_H

float static dk_tween_linear(float t, float b, float c, float d);

float static dk_tween_easeInQuad(float t, float b, float c, float d);
float static dk_tween_easeOutQuad(float t, float b, float c, float d);
float static dk_tween_easeInOutQuad(float t, float b, float c, float d);

float static dk_tween_easeInCubic(float t, float b, float c, float d);
float static dk_tween_easeOutCubic(float t, float b, float c, float d);
float static dk_tween_easeInOutCubic(float t, float b, float c, float d);

float static dk_tween_easeInQuart(float t, float b, float c, float d);
float static dk_tween_easeOutQuart(float t, float b, float c, float d);
float static dk_tween_easeInOutQuart(float t, float b, float c, float d);

#  if defined(DK_TWEEN_IMPL)
float static dk_tween_linear(float t, float b, float c, float d)
{
  t /= d;
  return c * t + b;
}

float static dk_tween_easeInQuad(float t, float b, float c, float d)
{
  t /= d;
  return c * t * t + b;
}

float static dk_tween_easeOutQuad(float t, float b, float c, float d)
{
  t /= d;
  float temp = t - 2;
  return -c * t * temp + b;
}

float static dk_tween_easeInOutQuad(float t, float b, float c, float d)
{
  t /= d;
  float temp = --t;
  return (t < 1) ? c / 2 * t * t + b : -c / 2 * (temp * (t - 2) - 1) + b;
}

float static dk_tween_easeInCubic(float t, float b, float c, float d)
{
  t /= d;
  return c * t * t * t + b;
}

float static dk_tween_easeOutCubic(float t, float b, float c, float d)
{
  t = t / d - 1;
  return c * (t * t * t + 1) + b;
}

float static dk_tween_easeInOutCubic(float t, float b, float c, float d)
{
  t /= d;
  float temp = t - 2;
  return (t < 1) ? c / 2 * t * t * t + b : c / 2 * (temp * t * t + 2) + b;
}

float static dk_tween_easeInQuart(float t, float b, float c, float d)
{
  t /= d;
  return c * t * t * t * t + b;
}

float static dk_tween_easeOutQuart(float t, float b, float c, float d)
{
  t = t / d - 1;
  return -c * (t * t * t * t - 1) + b;
}

float static dk_tween_easeInOutQuart(float t, float b, float c, float d)
{
  t /= d;
  float temp = t - 2;
  return (t < 1) ? c / 2 * t * t * t * t + b
                 : -c / 2 * (temp * t * t * t - 2) + b;
}
#endif // DK_TWEEN_IMPL

#endif // DK_TWEEN_H
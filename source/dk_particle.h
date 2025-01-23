#if !defined(__DK_PARTICLE_H__)
#define __DK_PARTICLE_H__

#define DK_GFX_IMPL
#include "dk_gfx.h"

#include "dk_component.h"
#include "dk_collision.h"

#if !defined(MAX_PARTICLES)
#define MAX_PARTICLES 1000
#endif // MAX_PARTICLES

typedef struct {
  Velocity velocity;
  Position position;
  Acceleration acceleration;
  Size start_size;

  float gravity;
  int32_t lifetime;
  int32_t max_lifetime;

  DK_GFX_Color color;
  DK_GFX_Color color_end;

} Particle;

typedef struct {
  Particle particles[MAX_PARTICLES];
  int32_t num_particles;

  BoundingBox area;
  bool is_running;
} ParticleSystem;

void ParticleUpdate(Particle *particle, float dt); 

void ParticleRender(DK_GFX_Context *gfx_context, Particle *particle);

void ParticleSystemInit(ParticleSystem *system);

void ParticleSystemUpdate(ParticleSystem *system, float dt);

void ParticleSystemRender(DK_GFX_Context *gfx_context, ParticleSystem *system);

#endif // __DK_PARTICLE_H__
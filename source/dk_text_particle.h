#if !defined(__DK_TEXT_PARTICLE_H__)
#define __DK_TEXT_PARTICLE_H__

#define DK_GFX_IMPL
#include "dk_gfx.h"

#include "dk_component.h"

#if !defined(MAX_TEXT_PARTICLES)
#define MAX_TEXT_PARTICLES 1000
#endif // MAX_TEXT_PARTICLES

typedef struct {
  Velocity velocity;
  Position position;
  Acceleration acceleration;

  float gravity;

  int32_t lifetime;
  int32_t max_lifetime;

  char *text;
  DK_GFX_Color color;
  DK_GFX_Color color_end;
} TextParticle;

typedef struct {
  TextParticle particles[MAX_TEXT_PARTICLES];
  int32_t num_particles;
  bool is_running;
} TextParticleSystem;

void TextParticleUpdate(TextParticle *particle, float dt); 

void TextParticleRender(DK_GFX_Context *gfx_context, TextParticle *particle);

void TextParticleSystemInit(TextParticleSystem *system);

void TextParticleSystemUpdate(TextParticleSystem *system, float dt);

void TextParticleSystemRender(DK_GFX_Context *gfx_context, TextParticleSystem *system);

#endif // __DK_TEXT_PARTICLE_H__
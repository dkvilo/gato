#include "dk_particle.h"

#include <stdint.h>
#include <string.h>

void ParticleUpdate(Particle *particle, float dt) {
  float speed = 10.0f * dt;

  particle->velocity.y += particle->gravity * dt;
  particle->position.x += particle->velocity.x * speed;
  particle->position.y += particle->velocity.y * speed;
  particle->lifetime -= 2.0f * dt;

  float percent = (particle->lifetime / (float)particle->max_lifetime);
  particle->color.a = (uint8_t)(particle->color_end.a * percent);

  particle->start_size.w -= dt;
  particle->start_size.h -= dt;
}

void ParticleRender(DK_GFX_Context *gfx_context, Particle *particle) {
  DK_GFX_DrawDebugRectFilled(gfx_context, &(DK_GFX_Debug_Rect_Desc_t) {
    .rect = (DK_GFX_Rect) {
      .x = particle->position.x, .y = particle->position.y,
      .w = particle->start_size.w, .h = particle->start_size.h
    },
    .color = particle->color
  });
}

void ParticleSystemInit(ParticleSystem *system) {
  memset(system, 0, sizeof(ParticleSystem));
}

void ParticleSystemUpdate(ParticleSystem *system, float dt) {
  for (int i = 0; i < system->num_particles; i++) {
    ParticleUpdate(&system->particles[i], dt);

    // we are removing the particles that have expired
    if (system->particles[i].lifetime <= 0) {
      system->particles[i] = system->particles[system->num_particles - 1];
      system->num_particles--;
    }
  }
}

void ParticleSystemRender(DK_GFX_Context *gfx_context, ParticleSystem *system) {
  for (int i = 0; i < system->num_particles; i++) {
    ParticleRender(gfx_context, &system->particles[i]);
  }
}

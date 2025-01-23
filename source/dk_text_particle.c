#include "dk_text_particle.h"

#include <stdint.h>
#include <string.h>

void TextParticleUpdate(TextParticle *particle, float dt) {
  float speed = (dt / 100.0f);
  particle->velocity.y += particle->gravity * speed;
  particle->position.x += particle->velocity.x * speed;
  particle->position.y += particle->velocity.y * speed;
  particle->lifetime -= speed;

  float percent = particle->lifetime / (float)particle->max_lifetime;
  particle->color.a = (uint8_t)(particle->color_end.a * percent);
}

void TextParticleRender(DK_GFX_Context *gfx_context, TextParticle *particle) {
  DK_GFX_DrawText(gfx_context, &(DK_GFX_Text_Desc_t){
    .text = particle->text,
    .pos = { .x = particle->position.x, .y = particle->position.y },
    .color = particle->color,
  });
}

void TextParticleSystemInit(TextParticleSystem *system) {
  memset(system, 0, sizeof(TextParticleSystem));
}

void TextParticleSystemUpdate(TextParticleSystem *system, float dt) {
  for (int i = 0; i < system->num_particles; i++) {
    TextParticleUpdate(&system->particles[i], dt);

    // we are removing the particles that have expired
    if (system->particles[i].lifetime <= 0) {
      system->particles[i] = system->particles[system->num_particles - 1];
      system->num_particles--;
    }
  }
}

void TextParticleSystemRender(DK_GFX_Context *gfx_context, TextParticleSystem *system) {
  for (int i = 0; i < system->num_particles; i++) {
    TextParticleRender(gfx_context, &system->particles[i]);
  }
}

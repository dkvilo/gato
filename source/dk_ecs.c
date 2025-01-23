#include <stdio.h>
#include <SDL2/SDL.h>

#include "dk_ecs.h"

ECS* ECS_Init() {
  ECS* ecs = (ECS*)malloc(sizeof(ECS));
  memset(ecs->entities, 0, sizeof(ecs->entities));
  ecs->numEntities = 0;
  return ecs;
}

Entity* ECS_CreateEntity(ECS* ecs, ENTITY_ID id) {
  if (ecs->numEntities >= MAX_ENTITIES) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Maximum number of components reached on Entity(%s).\n", ENTITY_ID_TO_STR(id));
    return NULL;
  }

  Entity* entity = (Entity*)malloc(sizeof(Entity));
  entity->id = id;
  ecs->entities[ecs->numEntities++] = entity;
  return entity;
}

Entity* ECS_GetEntity(ECS* ecs, ENTITY_ID id) {
  Entity *ent = ecs->entities[id];
  if (ent != NULL) {
    return ent;
  }
  SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Entity(%s) does not exist.\n", ENTITY_ID_TO_STR(id));
  return NULL;
}

void ECS_AddComponent(Entity* entity, void *component, COMPONENT_ID id, size_t size) {
  if (id >= MAX_COMPONENTS) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Maximum number of components reached on Entity(%s).\n", ENTITY_ID_TO_STR(entity->id));
    exit(1);
  }

  #if !defined(PLATFORM_WEB) && 0
    if (entity->components[id] != NULL) {
      SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Component(%s) already exists on Entity(%s).\n", COMPONENT_ID_TO_STR(id), ENTITY_ID_TO_STR(entity->id));
      exit(1);
    }
  #endif

  entity->components[id] = malloc(size);
  memset(entity->components[id], 0, size);

  memcpy(entity->components[id], component, size);
}

void *ECS_GetComponent(Entity* entity, COMPONENT_ID id) {
  if (id >= MAX_COMPONENTS) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Maximum number of components reached on Entity(%s).\n", ENTITY_ID_TO_STR(entity->id));
    return NULL;
  }

  return entity->components[id];
}
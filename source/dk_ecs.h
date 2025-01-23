#if !defined (DK_ECS_H)
#define DK_ECS_H

#include <stdint.h>
#include <stdlib.h>

#define MAX_ENTITIES 100
#define MAX_COMPONENTS 32

#include "dk_ecs_id.h"
#include "dk_component.h"

typedef COMPONENT_ID dkComponent;

typedef struct {
  ENTITY_ID id;
  dkComponent *components[MAX_COMPONENTS];
} Entity;

typedef struct {
  Entity *entities[MAX_ENTITIES];
  int32_t numEntities;
} ECS;

ECS* ECS_Init();

Entity* ECS_CreateEntity(ECS* ecs, ENTITY_ID id);

Entity* ECS_GetEntity(ECS* ecs, ENTITY_ID id);

void ECS_AddComponent(Entity* entity, void *component, COMPONENT_ID id, size_t size);

void *ECS_GetComponent(Entity* entity, COMPONENT_ID id);


#endif // DK_ECS_H
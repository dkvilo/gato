/**
 * @file dk_game.h
 * @brief Game header file that contains all the game related stuff, like game
 * loop, game state, etc.
 * @version 0.1
 * @date 2023-09-06
 *
 * @author David Kviloria,
 *         SKYSTAR GAMES Interactive.
 */
#if !defined(__DK_GAME_H__)
#define __DK_GAME_H__

#include <stdbool.h>
#include <stdint.h>

#include "dk_collision.h"
#include "dk_component.h"
#include "dk_ui.h"
#include "dk_text_particle.h"
#include "dk_particle.h"

typedef enum PLAYER_ID {
  PLAYER_ID_ONE = 0,
  PLAYER_ID_TWO = 1,
  PLAYER_ID_COUNT
} PLAYER_ID;

#define MAX_POINTS 100
#define MAX_PROJECTILES 100

typedef enum GAME_SCREEN {
  GAME_SCREEN_TITLE,
  GAME_SCREEN_GAMEPLAY,
  GAME_SCREEN_SETTINGS,
  GAME_SCREEN_CONFIGURATION,
  GAME_SCREEN_COUNT
} GAME_SCREEN;

typedef enum GAME_MODE {
  GAME_MODE_CAPTURE_FLAG,
  GAME_MODE_BUILD_WORD,
  GAME_MODE_COUNT
} GAME_MODE;

typedef struct Game {
  ImUI _dev_ui;
  GAME_SCREEN screen;
  GAME_MODE mode;
  int32_t score[PLAYER_ID_COUNT];
  float music_volume;
  float sound_effect_volume;

  int32_t seconds;
  int32_t minutes;
} Game;

void GameInit(DK_GFX_Context *gfx_context);
void GameUpdate(DK_GFX_Context *gfx_context);
void GameRender(DK_GFX_Context *gfx_context);
void GameDestroy();

typedef enum PLATFORM_TYPE {
  PLATFORM_TYPE_NONE = 0,
  PLATFORM_TYPE_TRANSPARENT = 1,
  PLATFORM_TYPE_CLOUD = 2,
  PLATFORM_TYPE_GRASS = 3,
  PLATFORM_TYPE_BRICK = 4,
  PLATFORM_TYPE_PIPE = 5,
  PLATFORM_TYPE_COUNT
} PLATFORM_TYPE;

typedef struct {
  DK_GFX_Rect rect;
  BoundingBox bb;
  PLATFORM_TYPE type;
} Platform;

#  define MAX_PLATFORMS 8

typedef struct PlatformManager {
  Platform platforms[MAX_PLATFORMS];
  int32_t count;
} PlatformManager;

typedef enum ANIMATION_STATE {
  ANIMATION_STATE_IDLE = 0,
  ANIMATION_STATE_WALK = 1,
  ANIMATION_STATE_JUMP = 2,
  ANIMATION_STATE_COUNT
} ANIMATION_STATE;

typedef struct GameEntity {  
  PLAYER_ID id;

  DK_GFX_FPoint position;
  DK_GFX_FPoint velocity;
  DK_GFX_Point size;

  ANIMATION_STATE anim_state;
  BoundingBox bb;

  bool is_jumping;
  bool is_on_ground;

  float WALK_SPEED;
  float JUMP_HEIGHT;

  DK_GFX_RendererFlip Flip;

  int32_t OFFSET_FROM_GROUND;
  int32_t OFFSET_FROM_PLATFORM;

  union {
    int32_t platform_id;
  } userdata;

} GameEntity;

void player_update(GameEntity *player, PlatformManager *platform_manager, DK_GFX_Context *gfx_context, float dt);

void player_render(GameEntity *e, DK_GFX_Context *gfx_context);

void add_platform(PlatformManager *manager, DK_GFX_Rect rect, PLATFORM_TYPE type);

void platform_manager_render(PlatformManager *platform_manager, DK_GFX_Context *gfx_context);

void place_platforms(DK_GFX_Context *gfx_context, PlatformManager *platform_manager);

void parallax_layer_setup(DK_GFX_Context *gfx_context, DK_GFX_ParallaxLayer *layer, GAME_SCREEN screen);

void load_textures(DK_GFX_Context *gfx_context);

int32_t cmp_func(const void *a, const void *b);

DK_GFX_Point get_platform_surface_position(Platform *platform, int32_t size, int32_t offset);

#define MAX_FLAGS 10
typedef struct FlagManager {
  GameEntity item[MAX_FLAGS];
  int32_t count;
} FlagManager;

void spawn_flag_on_platform(FlagManager *flag_manager, Platform *p, int32_t id);

void flag_manager_render(FlagManager *flag_manager, DK_GFX_Context *gfx_context);

void capture_flag(DK_GFX_Context *gfx_context, GameEntity *player, PlatformManager *platform_manager);

void game_screen_gameplay_render(DK_GFX_Context *gfx_context);
void game_screen_gameplay_update(DK_GFX_Context *gfx_context, float dt);

void game_screen_title_screen_render(DK_GFX_Context *gfx_context);
void game_screen_title_screen_update(DK_GFX_Context *gfx_context, float dt);

void game_screen_settings_render(DK_GFX_Context *gfx_context);
void game_screen_settings_update(DK_GFX_Context *gfx_context, float dt);

void game_screen_configuration_render(DK_GFX_Context *gfx_context);
void game_screen_configuration_update(DK_GFX_Context *gfx_context, float dt);

void game_on_screen_resize(DK_GFX_Context *gfx_context);

#endif // __DK_GAME_H__

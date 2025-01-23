#include <stdio.h>
#include <stdlib.h>

#include "dk_game.h"

#define DK_UI_IMPLEMENTATION
#include "dk_ui.h"

float   GRAVITY = 75.0f;
int32_t GROUND_OFFSET = 70;
int32_t GROUND_TILE_SIZE = 200;
float   SCREEN_TRANSITION_SPEED = 2.5f;

bool DEBUG_DRAW = !false;

#define PARALLAX_LAYER_COUNT 5
#define PARALLAX_SCALE_UNIT 5
#define PARALLAX_SCALE                                                         \
  {                                                                            \
    .x = PARALLAX_SCALE_UNIT, .y = PARALLAX_SCALE_UNIT                         \
  }
#define PARALLAX_TEXTURE_WIDTH 320
#define PARALLAX_TEXTURE_HEIGHT 180

DK_GFX_ParallaxLayer game_parallax_layers[PARALLAX_LAYER_COUNT] = {
  {
    .texture = NULL,
    .pos = {.x = 0, .y = 0},
    .pos2 = {.x = PARALLAX_TEXTURE_WIDTH * PARALLAX_SCALE_UNIT, .y = 0},
    .scale = PARALLAX_SCALE,
    .speed = 0.0f,
    .texture_width = PARALLAX_TEXTURE_WIDTH,
    .texture_height = PARALLAX_TEXTURE_HEIGHT
  },
  {
    .texture = NULL,
    .pos = {.x = 0, .y = 0},
    .pos2 = {.x = PARALLAX_TEXTURE_WIDTH * PARALLAX_SCALE_UNIT, .y = 0},
    .scale = PARALLAX_SCALE,
    .speed = 0.0f,
    .texture_width = PARALLAX_TEXTURE_WIDTH,
    .texture_height = PARALLAX_TEXTURE_HEIGHT
  },
  {
    .texture = NULL,
    .pos = {.x = 0, .y = 0},
    .pos2 = {.x = PARALLAX_TEXTURE_WIDTH * PARALLAX_SCALE_UNIT, .y = 0},
    .scale = PARALLAX_SCALE,
    .speed = 0.0f,
    .texture_width = PARALLAX_TEXTURE_WIDTH,
    .texture_height = PARALLAX_TEXTURE_HEIGHT
  },
  {
    .texture = NULL,
    .pos = {.x = 0, .y = 0},
    .pos2 = {.x = PARALLAX_TEXTURE_WIDTH * PARALLAX_SCALE_UNIT, .y = 0},
    .scale = PARALLAX_SCALE,
    .speed = 0.0f,
    .texture_width = PARALLAX_TEXTURE_WIDTH,
    .texture_height = PARALLAX_TEXTURE_HEIGHT
  },
  {
    .texture = NULL,
    .pos = {.x = 0, .y = 0},
    .pos2 = {.x = PARALLAX_TEXTURE_WIDTH * PARALLAX_SCALE_UNIT, .y = 0},
    .scale = PARALLAX_SCALE,
    .speed = 0.5,
    .texture_width = PARALLAX_TEXTURE_WIDTH,
    .texture_height = PARALLAX_TEXTURE_HEIGHT
  },
};
DK_GFX_ParallaxLayer menu_parallax_layers[PARALLAX_LAYER_COUNT] = {
  {
    .texture = NULL,
    .pos = {.x = 0, .y = 0},
    .pos2 = {.x = PARALLAX_TEXTURE_WIDTH * PARALLAX_SCALE_UNIT, .y = 0},
    .scale = PARALLAX_SCALE,
    .speed = 0.0f,
    .texture_width = PARALLAX_TEXTURE_WIDTH,
    .texture_height = PARALLAX_TEXTURE_HEIGHT
  },
  {
    .texture = NULL,
    .pos = {.x = 0, .y = 0},
    .pos2 = {.x = PARALLAX_TEXTURE_WIDTH * PARALLAX_SCALE_UNIT, .y = 0},
    .scale = PARALLAX_SCALE,
    .speed = 0.0f,
    .texture_width = PARALLAX_TEXTURE_WIDTH,
    .texture_height = PARALLAX_TEXTURE_HEIGHT
  },
  {
    .texture = NULL,
    .pos = {.x = 0, .y = 0},
    .pos2 = {.x = PARALLAX_TEXTURE_WIDTH * PARALLAX_SCALE_UNIT, .y = 0},
    .scale = PARALLAX_SCALE,
    .speed = 0.0f,
    .texture_width = PARALLAX_TEXTURE_WIDTH,
    .texture_height = PARALLAX_TEXTURE_HEIGHT
  },
  {
    .texture = NULL,
    .pos = {.x = 0, .y = 0},
    .pos2 = {.x = PARALLAX_TEXTURE_WIDTH * PARALLAX_SCALE_UNIT, .y = 0},
    .scale = PARALLAX_SCALE,
    .speed = 0.0f,
    .texture_width = PARALLAX_TEXTURE_WIDTH,
    .texture_height = PARALLAX_TEXTURE_HEIGHT
  },
  {
    .texture = NULL,
    .pos = {.x = 0, .y = 0},
    .pos2 = {.x = PARALLAX_TEXTURE_WIDTH * PARALLAX_SCALE_UNIT, .y = 0},
    .scale = PARALLAX_SCALE,
    .speed = 0.5,
    .texture_width = PARALLAX_TEXTURE_WIDTH,
    .texture_height = PARALLAX_TEXTURE_HEIGHT
  },
};

Game game = {0};

PlatformManager platform_manager = {0};

#define PLAYER_COUNT 2

GameEntity player[PLAYER_COUNT] = {
  [PLAYER_ID_ONE] = {
    .id = PLAYER_ID_ONE,
    .anim_state = ANIMATION_STATE_IDLE,
    .JUMP_HEIGHT = 20.0f,
    .WALK_SPEED = 5.0f,
    .is_jumping = false,
    .is_on_ground = false,
    .Flip = DK_GFX_FLIP_NONE,
    .size = {35.0f, 20.0f},
    .position = {100.0f, 100.0f},
    .velocity = {0.0f, 0.0f},
    .OFFSET_FROM_GROUND = 5,
    .OFFSET_FROM_PLATFORM = 15
  },
  [PLAYER_ID_TWO] = {
    .id = PLAYER_ID_TWO,
    .anim_state = ANIMATION_STATE_IDLE,
    .JUMP_HEIGHT = 20.0f,
    .WALK_SPEED = 5.0f,
    .is_jumping = false,
    .is_on_ground = false,
    .Flip = DK_GFX_FLIP_NONE,
    .size = {35.0f, 20.0f},
    .position = {100, 100.0f},
    .velocity = {0.0f, 0.0f},
    .OFFSET_FROM_GROUND = 5,
    .OFFSET_FROM_PLATFORM = 15
  }
};

FlagManager flag_manager = {0};

TextParticleSystem text_particle_system = {};
ParticleSystem particle_system = {};

void GameInit(DK_GFX_Context *gfx_context)
{
  player[PLAYER_ID_TWO].position.x = gfx_context->width - 100.0f;
  player[PLAYER_ID_TWO].Flip = DK_GFX_FLIP_HORIZONTAL;

  game._dev_ui.gfx_context = gfx_context;
  game._dev_ui.context = (ImUIContext){0};

  game._dev_ui.theme = IMUI_LIGHT;
  game._dev_ui.theme.font = DK_GFX_LoadFont("assets/PixelOperator8-Bold.ttf", 40);

  game.music_volume = 70.0f;
  game.sound_effect_volume = 10.0f;

  DK_GFX_SetFont(gfx_context, game._dev_ui.theme.font);

  load_textures(gfx_context);

  place_platforms(gfx_context, &platform_manager);

  DK_GFX_ScreenTransitionInit(gfx_context, GAME_SCREEN_TITLE, SCREEN_TRANSITION_SPEED);

  switch (game.mode)
  {
  case GAME_MODE_CAPTURE_FLAG: {
    int32_t rr = rand() % platform_manager.count;
    spawn_flag_on_platform(&flag_manager, &platform_manager.platforms[rr], rr);
  }
   break;
  case GAME_MODE_BUILD_WORD:
   break;
   default:
   break;
  }

  DK_GFX_LoadAudioFx(gfx_context, DK_GFX_AUDIO_FX_0, "assets/sample.wav");
  DK_GFX_LoadAudioFx(gfx_context, DK_GFX_AUDIO_FX_1, "assets/open.wav");
  DK_GFX_LoadAudioFx(gfx_context, DK_GFX_AUDIO_FX_2, "assets/close.wav");
  DK_GFX_LoadAudioFx(gfx_context, DK_GFX_AUDIO_FX_3, "assets/pick-up.wav");

  DK_GFX_SetAudioFxMasterVolume(gfx_context, game.sound_effect_volume / 100.0f);
}

void GameRender(DK_GFX_Context *gfx_context)
{
  DK_GFX_RenderClear(gfx_context->renderer);
  DK_GFX_SetBlendMode(gfx_context, DK_GFX_BLEND_ALPHA);
  
  switch (game.screen)
  {
  case GAME_SCREEN_TITLE: {
    game_screen_title_screen_render(gfx_context);
  } break;

  case GAME_SCREEN_CONFIGURATION: {
    game_screen_configuration_render(gfx_context);

  } break;

  case GAME_SCREEN_GAMEPLAY:
    game_screen_gameplay_render(gfx_context);
  break;
  
  case GAME_SCREEN_SETTINGS: {
    game_screen_settings_render(gfx_context);
  } break;

  default:
    break;
  }

  DK_GFX_ScreenTransitionRender(gfx_context);
}

bool saveScreenshot(const char *file, SDL_Renderer *renderer, SDL_Rect _viewport, int32_t borderSize) {
  SDL_Surface *_surface = SDL_CreateRGBSurface(0, _viewport.w, _viewport.h, 32, 0, 0, 0, 0);
  if (_surface == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Cannot create SDL_Surface %s.\n", SDL_GetError());
    return false;
  }
  
  if (SDL_RenderReadPixels(renderer, &_viewport, _surface->format->format, _surface->pixels, _surface->pitch) != 0) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Cannot read data from SDL_Renderer %s.\n", SDL_GetError());
    SDL_FreeSurface(_surface);
    return false;
  }

  SDL_Surface *borderedSurface = SDL_CreateRGBSurface(0, _viewport.w + 2 * borderSize, _viewport.h + 2 * borderSize, 32, 0, 0, 0, 0); 
  if (borderedSurface == NULL) {
    SDL_FreeSurface(_surface);
    return false;
  }

  SDL_FillRect(borderedSurface, NULL, SDL_MapRGBA(borderedSurface->format, 255, 255, 255, 255));
  
  SDL_Rect destRect;
  destRect.x = borderSize;
  destRect.y = borderSize;
  destRect.w = _viewport.w;
  destRect.h = _viewport.h;
  
  SDL_BlitSurface(_surface, NULL, borderedSurface, &destRect);
  if (IMG_SavePNG(borderedSurface, file) != 0) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Cannot save PNG file %s.\n", SDL_GetError());
    SDL_FreeSurface(_surface);
    SDL_FreeSurface(borderedSurface);
    return false;
  }
  
  SDL_FreeSurface(_surface);
  SDL_FreeSurface(borderedSurface);
  return true;
}

void GameUpdate(DK_GFX_Context *gfx_context)
{
  float dt = gfx_context->dt;

  switch (game.screen)
  {
  case GAME_SCREEN_TITLE:
    game_screen_title_screen_update(gfx_context, dt);
  break;

  case GAME_SCREEN_CONFIGURATION:
    game_screen_configuration_update(gfx_context, dt);
  break; 
  
  case GAME_SCREEN_GAMEPLAY:
    game_screen_gameplay_update(gfx_context, dt);
  break;
  
  case GAME_SCREEN_SETTINGS:
    game_screen_settings_update(gfx_context, dt); 
  break;

  default:
    break;
  }
}

void GameDestroy() {}

// Game systems implementation
// _____________________________________________________

void game_screen_configuration_update(DK_GFX_Context *gfx_context, float dt)
{
  for (int32_t i = 0; i < PARALLAX_LAYER_COUNT; i++) {
    DK_GFX_UpdateParallaxLayer(gfx_context, &menu_parallax_layers[i], gfx_context->dt);
  }

  if (DK_GFX_IsKeyPressed(gfx_context, KEY_ESCAPE) 
    || DK_GFX_IsGamepadButtonPressed(gfx_context, DK_GFX_INPUT_SENDER_ID_ONE, GAMEPAD_BUTTON_MIDDLE_RIGHT)) {
    DK_GFX_TransitionScreen(gfx_context, (int32_t *)&game.screen, GAME_SCREEN_TITLE);
  }

  if (DK_GFX_IsKeyPressed(gfx_context, KEY_ENTER)) {
    DK_GFX_TransitionScreen(gfx_context, (int32_t *)&game.screen, GAME_SCREEN_GAMEPLAY);
  }
}

void game_screen_configuration_render(DK_GFX_Context *gfx_context) 
{
  DK_GFX_SetFont(gfx_context, game._dev_ui.theme.font);

  for (int32_t i = 0; i < PARALLAX_LAYER_COUNT; i++) {
    DK_GFX_DrawParallaxLayer(gfx_context, &menu_parallax_layers[i]);
  }
  
  int32_t original_width = 54;
  int32_t original_height = 36;

  int32_t desired_scale = 15;

  int32_t on_screen_width = original_width * desired_scale;
  int32_t on_screen_height = original_height * desired_scale; 

  int32_t sprite_origin_x = (gfx_context->width / 2) - (on_screen_width / 2);
  int32_t sprite_origin_y = (gfx_context->height / 2) - (on_screen_height / 2);

  float alpha = 0.5;
  DK_GFX_DrawFullScreenRect(gfx_context, alpha);

  DK_GFX_DrawSprite(gfx_context, (DK_GFX_SpriteDesc){
    .slot = DK_GFX_TEXTURE_3,
    .pos = (DK_GFX_Point){
      .x = sprite_origin_x,
      .y = sprite_origin_y
    },

    .scale = {
      desired_scale,
      desired_scale
    },

    .col = 0,
    .row = 6,

    .width = original_width,
    .height = original_height,
  });

  const int32_t MAX_LABELS = 3;
  const char *labels[MAX_LABELS] = {
    "Single Player",
    "Catch the Flag",
    "00:02:00"
  };

  int32_t panel_content_padding = 40;

  int32_t BUTTON_MARGIN = 55;
  int32_t BUTTON_HEIGHT = 100;

  int32_t BUTTON_WIDTH = on_screen_width + (panel_content_padding / 2);

  for (int32_t i = 0; i < MAX_LABELS; ++i) {

    DK_GFX_DrawText(gfx_context, &(DK_GFX_Text_Desc_t) {
      .text = labels[i],
      .color = DK_GFX_WHITE,
      .pos = {
        .x = (sprite_origin_x + (BUTTON_WIDTH/2)) - DK_GFX_GetTextWidth(gfx_context, labels[i])/2,
        .y = sprite_origin_y + panel_content_padding + BUTTON_MARGIN + (i*(BUTTON_HEIGHT + BUTTON_MARGIN))
      }
    });
  }
}

void player_update(GameEntity *player, PlatformManager *platform_manager, DK_GFX_Context *gfx_context, float dt)
{

  if (player->id == PLAYER_ID_ONE) {
    if ((DK_GFX_IsKeyDown(gfx_context, KEY_A) 
      || DK_GFX_IsGamepadButtonDown(gfx_context, DK_GFX_INPUT_SENDER_ID_ONE, GAMEPAD_BUTTON_LEFT_FACE_LEFT))) {
      player->Flip = DK_GFX_FLIP_HORIZONTAL;
      player->velocity.x = -player->WALK_SPEED;
      player->anim_state = ANIMATION_STATE_WALK;
    } else if ((DK_GFX_IsKeyDown(gfx_context, KEY_D) 
      || DK_GFX_IsGamepadButtonDown(gfx_context, DK_GFX_INPUT_SENDER_ID_ONE, GAMEPAD_BUTTON_LEFT_FACE_RIGHT))) {
      player->Flip = DK_GFX_FLIP_NONE;
      player->velocity.x = player->WALK_SPEED;
      player->anim_state = ANIMATION_STATE_WALK;
    } else {
      player->velocity.x = 0;
      player->anim_state = ANIMATION_STATE_IDLE;
    }
  }

  if (player->id == PLAYER_ID_TWO) {
    if ((DK_GFX_IsKeyDown(gfx_context, KEY_LEFT) 
        || DK_GFX_IsGamepadButtonDown(gfx_context, DK_GFX_INPUT_SENDER_ID_TWO, GAMEPAD_BUTTON_LEFT_FACE_LEFT))) {
      player->Flip = DK_GFX_FLIP_HORIZONTAL;
      player->velocity.x = -player->WALK_SPEED;
      player->anim_state = ANIMATION_STATE_WALK;
    } else if ((DK_GFX_IsKeyDown(gfx_context, KEY_RIGHT) 
      || DK_GFX_IsGamepadButtonDown(gfx_context, DK_GFX_INPUT_SENDER_ID_TWO, GAMEPAD_BUTTON_LEFT_FACE_RIGHT))) {
      player->Flip = DK_GFX_FLIP_NONE;
      player->velocity.x = player->WALK_SPEED;
      player->anim_state = ANIMATION_STATE_WALK;
    } else {
      player->velocity.x = 0;
      player->anim_state = ANIMATION_STATE_IDLE;
    }
  }

  player->position.x += player->velocity.x;
  player->position.y += player->velocity.y;

  player->bb = (BoundingBox){
    .x = player->position.x - player->size.x / 2,
    .y = player->position.y + player->size.y,
    .width = player->size.x,
    .height = player->size.y
  };

  /* @collision @player and @floor */
  if (player->position.y >= (gfx_context->height - GROUND_OFFSET) - player->size.y - player->OFFSET_FROM_GROUND) {
    player->position.y = (gfx_context->height - GROUND_OFFSET) - player->size.y - player->OFFSET_FROM_GROUND;
    player->velocity.y = 0;
    player->is_on_ground = true;
  } else {
    player->is_on_ground = false;
  }

  if (!player->is_on_ground) {
    player->velocity.y += GRAVITY * dt;
  }

  // @collision @player and @platforms
  for (int i = 0; i < platform_manager->count; ++i) {
    Platform *platform = &platform_manager->platforms[i];
    platform->bb = (BoundingBox){.x = platform->rect.x, .y = platform->rect.y, .width = platform->rect.w, .height = platform->rect.h};

    if (DKCollision_BoundingBoxesAreColliding(&platform->bb, &player->bb)) {
      if (player->velocity.y > 0 && player->position.y + player->size.y <= platform->rect.y + player->velocity.y) {
        player->position.y = platform->rect.y - player->size.y - player->OFFSET_FROM_PLATFORM;
        player->velocity.y = 0;
        player->is_on_ground = true;
        // if (player->is_on_ground) {
        //   player->velocity.y = -player->JUMP_HEIGHT;
        //   player->is_on_ground = false;
        //   player->is_jumping = true;
        // }
      }
    }
  }

  if (player->position.x < (player->bb.width/2))
  {
    player->position.x = gfx_context->width - (player->bb.width/2);
  }

  else if (player->position.x > (gfx_context->width - (player->bb.width/2)))
  {
    player->position.x = (player->bb.width/2);
  }

  if (player->id == PLAYER_ID_ONE) {

    bool jump_pressed = (DK_GFX_IsKeyPressed(gfx_context, KEY_W) 
      || DK_GFX_IsGamepadButtonPressed(gfx_context, DK_GFX_INPUT_SENDER_ID_ONE, GAMEPAD_BUTTON_LEFT_FACE_UP)
      || DK_GFX_IsGamepadButtonPressed(gfx_context, DK_GFX_INPUT_SENDER_ID_ONE, GAMEPAD_BUTTON_RIGHT_FACE_DOWN)
      );
      
    if (jump_pressed && player->is_on_ground) {
      player->velocity.y = -player->JUMP_HEIGHT;
      player->is_on_ground = false;
      player->is_jumping = true;
    }
  }

  if (player->id == PLAYER_ID_TWO) {
      bool jump_pressed = (
        DK_GFX_IsKeyPressed(gfx_context, KEY_UP) 
          || DK_GFX_IsGamepadButtonPressed(gfx_context, DK_GFX_INPUT_SENDER_ID_TWO, GAMEPAD_BUTTON_LEFT_FACE_UP)
          || DK_GFX_IsGamepadButtonPressed(gfx_context, DK_GFX_INPUT_SENDER_ID_TWO, GAMEPAD_BUTTON_RIGHT_FACE_DOWN)
      );

    if (jump_pressed && player->is_on_ground) {
      player->velocity.y = -player->JUMP_HEIGHT;
      player->is_on_ground = false;
      player->is_jumping = true;
    }
  }

  if (!player->is_on_ground) {
    player->anim_state = ANIMATION_STATE_JUMP;
  }
}

void player_render(GameEntity *e, DK_GFX_Context *gfx_context)
{
  float anim_speed_lut[ANIMATION_STATE_COUNT] = {
    [ANIMATION_STATE_IDLE] = 100.0f,
    [ANIMATION_STATE_WALK] = 50.0f,
    [ANIMATION_STATE_JUMP] = 150.0f,
  };

  DK_GFX_RenderFlip(gfx_context, e->Flip);
  DK_GFX_DrawSpriteFrame(gfx_context, &(DK_GFX_SpriteFrameDesc){
    .slot = (DK_GFX_TEXTURE)e->anim_state,
    .loop = (e->anim_state != ANIMATION_STATE_JUMP),
    .pos = {.x = e->position.x, .y = e->position.y},
    .row = e->id,
    .start_index = 0,
    .end_index = (e->anim_state == ANIMATION_STATE_JUMP) ? 4 : 5,
    .scale = (DK_GFX_Point){.x = 4, .y = 4},
    .speed = anim_speed_lut[e->anim_state],
    .width = 40,
    .height = 40,
  });
  DK_GFX_RenderFlip(gfx_context, DK_GFX_FLIP_NONE);

  DK_GFX_DrawSpritePro(gfx_context, (DK_GFX_SpriteDescPro){
    .slot = DK_GFX_TEXTURE_3,
    .pos = (DK_GFX_Point){.x = e->position.x - e->size.x /2, .y = e->position.y - e->size.y * 2},
    .dest_width = 32,
    .dest_height = 32,

    .col = e->id,
    .row = 11,

    .width = 18,
    .height = 18,
  });

  if (DEBUG_DRAW) {
    DK_GFX_DrawDebugRect(gfx_context, &(DK_GFX_Debug_Rect_Desc_t){
      .color = DK_GFX_RED,
      .rect = {
        .x = e->bb.x,
        .y = e->bb.y,
        .w = e->bb.width,
        .h = e->bb.height
      }
    });
  }
}

void add_platform(PlatformManager *manager, DK_GFX_Rect rect, PLATFORM_TYPE type)
{
  Platform *platform = &platform_manager.platforms[platform_manager.count];
  platform->rect = rect;
  platform->type = type;
  platform_manager.count++;
}

void platform_manager_render(PlatformManager *platform_manager, DK_GFX_Context *gfx_context)
{
  for (int i = 0; i < platform_manager->count; ++i) {
    Platform *platform = &platform_manager->platforms[i];

    DK_GFX_DrawSpritePro(gfx_context, (DK_GFX_SpriteDescPro){
        .slot = DK_GFX_TEXTURE_3,
        .pos = {platform->rect.x, platform->rect.y},
        .col = 0,
        .row = platform->type, // matches the spritesheet
        .dest_width = platform->rect.w,
        .dest_height = platform->rect.h,
        .width = 54,
        .height = 18,
    });

    if (DEBUG_DRAW) {
      DK_GFX_DrawDebugRect( gfx_context, &(DK_GFX_Debug_Rect_Desc_t){
        .color = DK_GFX_RED,
        .rect = {
          .x = platform->bb.x,
          .y = platform->bb.y,
          .w = platform->bb.width,
          .h = platform->bb.height
        }
      });
    }
  }
}

DK_GFX_Point get_platform_surface_position(Platform *platform, int32_t size, int32_t offset)
{
  return (DK_GFX_Point){platform->rect.x + platform->rect.w / 2 - (size / 2), platform->rect.y - platform->rect.h - offset};
}

void spawn_flag_on_platform(FlagManager *flag_manager, Platform *p, int32_t id)
{
  DK_GFX_Point position = get_platform_surface_position(p, 64, 8);
  GameEntity *flag = &flag_manager->item[flag_manager->count];
  flag->position = (DK_GFX_FPoint){.x = position.x, .y = position.y};
  flag->size = (DK_GFX_Point){ 64.0f, 64.0f };
  flag->bb = (BoundingBox){
    .x = flag->position.x,
    .y = flag->position.y,
    .width = flag->size.x,
    .height = flag->size.y
  };

  flag->userdata.platform_id = id;
  flag_manager->count++;
}

void flag_manager_render(FlagManager *flag_manager, DK_GFX_Context *gfx_context)
{
  for (int32_t i = 0; i < flag_manager->count; ++i) {
    GameEntity *flag = &flag_manager->item[i];
    DK_GFX_DrawSpritePro(gfx_context, (DK_GFX_SpriteDescPro){
      .slot = DK_GFX_TEXTURE_3,
      .pos = (DK_GFX_Point){.x = flag->position.x, .y = flag->position.y},
      .dest_width = flag->size.x,
      .dest_height = flag->size.y,

      /* spritesheet info */
      .col = 2,
      .row = 8,
      .width = 18,
      .height = 18,
    });

    if (DEBUG_DRAW) {
      DK_GFX_DrawDebugRect(gfx_context, &(DK_GFX_Debug_Rect_Desc_t){
        .color = DK_GFX_RED,
        .rect = {
          .x = flag->bb.x,
          .y = flag->bb.y,
          .w = flag->bb.width,
          .h = flag->bb.height
        }
      });
    }
  }
}

double degrees_to_radians(double degrees) {
  return degrees * M_PI / 180.0;
}

void emit_party_particles(int32_t amount, float gravity, DK_GFX_FPoint position)
{
  for (int32_t i = 0; i < amount; i++) {
    if (particle_system.num_particles < MAX_PARTICLES) {
      Particle *particle = &particle_system.particles[particle_system.num_particles++];
      if (particle != NULL) {
        particle->gravity = gravity;
        
        particle->start_size.w = (10 + rand() % 20);
        particle->start_size.h = (10 + rand() % 20);

        particle->position.x = position.x;
        particle->position.y = position.y;

        double angle = degrees_to_radians((rand() % 360));
        double speed = 50 + (rand() % 100);

        particle->velocity.x = speed * cos(angle);
        particle->velocity.y = speed * sin(angle);

        particle->acceleration.x = 0;
        particle->acceleration.y = 0;

        particle->lifetime = 100;
        particle->max_lifetime = 100;

        DK_GFX_Color random_color = {rand() % 255, rand() % 255, rand() % 255, 255};
        particle->color = random_color;
        particle->color_end = (DK_GFX_Color){0xff, 0xff, 0xff, 0xff};
      }
    }
  }
}

void capture_flag(DK_GFX_Context *gfx_context, GameEntity *player, PlatformManager *platform_manager)
{

  if (DK_GFX_IsKeyPressed(gfx_context, KEY_SPACE) ) {
      for (int32_t i = 0; i < 100; i++) {
        if (particle_system.num_particles < MAX_PARTICLES) {
          Particle *particle = &particle_system.particles[particle_system.num_particles++];
          if (particle != NULL) {
            particle->gravity = 190.8f;
            
            particle->start_size.w = (10 + (int32_t)rand()) % 30;
            particle->start_size.h = (10 + (int32_t)rand()) % 30;

            particle->position.x = (gfx_context->width / 2) + rand() % 400;
            particle->position.y = (gfx_context->height / 2);

            // particle->velocity.x = (10 * i);
            // particle->velocity.y = degrees_to_radians(sinf(i * 10));// -100 + (i);
            // 
            double angle = -degrees_to_radians((rand() % 35));
            double speed = 50 + (rand() % 400);

            // particle->velocity.x = speed * cos(angle);
            particle->velocity.y = speed * sin(angle);

            particle->acceleration.x = 20;
            particle->acceleration.y = 30;

            particle->lifetime = 100;
            particle->max_lifetime = 100;
            DK_GFX_Color random_color = {rand() % 255, rand() % 255, rand() % 255, 255};
            particle->color = random_color;
            particle->color_end = (DK_GFX_Color){0xff, 0xff, 0xff, 0xff};
          }
        }
      }
  }

  for (int32_t i = 0; i < flag_manager.count; ++i) {
    GameEntity flag = flag_manager.item[i];
    for (int32_t j = 0; j < PLAYER_COUNT; ++j) {
      GameEntity p = player[j];
      if (DKCollision_BoundingBoxesAreColliding(&flag.bb, &p.bb)) {
        if (p.anim_state == ANIMATION_STATE_WALK || p.anim_state == ANIMATION_STATE_JUMP) {
          DK_GFX_PlayAudioFx(gfx_context, DK_GFX_AUDIO_FX_3);

          emit_party_particles(100, 190.0f, player->position);

          TextParticle *particle = &text_particle_system.particles[text_particle_system.num_particles++];
          if (text_particle_system.num_particles < MAX_TEXT_PARTICLES) {
            if (particle != NULL) {
              particle->text = "+1";
              particle->gravity = 90.8f;
              particle->position.x = p.bb.x - (p.bb.width / 2) + rand() % 100;
              particle->position.y = p.bb.y - (p.bb.height / 2);
              particle->velocity.x = 0;
              particle->velocity.y = -100;
              particle->acceleration.x = 20;
              particle->acceleration.y = 30;
              particle->lifetime = 30;
              particle->max_lifetime = 30;
              DK_GFX_Color random_color = {rand() % 255, rand() % 255, rand() % 255, 255};
              particle->color = random_color;
              particle->color_end = (DK_GFX_Color){0xff, 0xff, 0xff, 0xff};
            }
          }

          /* removing the flag from the buffer */
          flag_manager.item[i] = flag_manager.item[flag_manager.count - 1];
          flag_manager.count--;

          game.score[p.id]++;

          int32_t rr;
          do {
            rr = rand() % platform_manager->count;
          }
          while (rr == flag.userdata.platform_id);

          spawn_flag_on_platform(&flag_manager, &platform_manager->platforms[rr], rr);
          break;
        }
      }
    }
  }
}

void place_platforms(DK_GFX_Context *gfx_context, PlatformManager *platform_manager)
{
  int32_t centerX = gfx_context->width / 2;
  int32_t centerY = gfx_context->height;

  int32_t height = 50;
  int32_t width = 150; // first row

  add_platform(platform_manager, (DK_GFX_Rect){.x = centerX - width - (width + width / 2), .y = centerY - 550, .w = width, .h = height}, PLATFORM_TYPE_CLOUD);
  width = 250; // first row
  add_platform(platform_manager, (DK_GFX_Rect){.x = centerX - width / 2, .y = centerY - 450, .w = width, .h = height}, PLATFORM_TYPE_CLOUD);
  width = 150; // first row
  add_platform(platform_manager, (DK_GFX_Rect){.x = centerX + width + (width / 2), .y = centerY - 550, .w = width, .h = height}, PLATFORM_TYPE_CLOUD);

  width = 200; // middle row
  add_platform(platform_manager, (DK_GFX_Rect){.x = centerX - width - (width), .y = centerY - 350, .w = width, .h = height}, PLATFORM_TYPE_GRASS);
  add_platform(platform_manager, (DK_GFX_Rect){ .x = centerX + (width), .y = centerY - 350, .w = width, .h = height}, PLATFORM_TYPE_GRASS);

  width = 200; // last row
  add_platform(platform_manager, (DK_GFX_Rect){.x = centerX - width / 2, .y = centerY - 200, .w = width, .h = height}, PLATFORM_TYPE_PIPE);
}

void parallax_layer_setup(DK_GFX_Context *gfx_context, DK_GFX_ParallaxLayer *layer, GAME_SCREEN screen)
{
  int32_t r = (rand() + 1) % 4;
  if (screen == GAME_SCREEN_TITLE) {
    r = 0;
  }
  char arr[4][20] = {"v1", "v2", "v3", "v4"};

  char *p1_buff = malloc(sizeof(char) * 255);
  sprintf(p1_buff, "assets/Parallax/%s/1.png", arr[r]);

  char *p2_buff = malloc(sizeof(char) * 255);
  sprintf(p2_buff, "assets/Parallax/%s/2.png", arr[r]);

  char *p3_buff = malloc(sizeof(char) * 255);
  sprintf(p3_buff, "assets/Parallax/%s/3.png", arr[r]);

  char *p4_buff = malloc(sizeof(char) * 255);
  sprintf(p4_buff, "assets/Parallax/%s/5.png", arr[r]);

  // check if background was updated from settings page.
  if (game_parallax_layers[0].texture == NULL) {
    layer[0].texture = DK_GFX_LoadTexture(gfx_context->renderer, p1_buff);
    layer[1].texture = DK_GFX_LoadTexture(gfx_context->renderer, p2_buff);
    layer[2].texture = DK_GFX_LoadTexture(gfx_context->renderer, p3_buff);
  }
  
  if (screen != GAME_SCREEN_TITLE) {
    layer[3].texture = DK_GFX_LoadTexture(gfx_context->renderer, "assets/Parallax/v2/4.png");
  }

  layer[4].texture = DK_GFX_LoadTexture(gfx_context->renderer, "assets/Parallax/v2/5.png");

  free(p1_buff); 
  free(p2_buff);
  free(p3_buff);
  free(p4_buff);
}

void load_textures(DK_GFX_Context *gfx_context) {
  gfx_context->textures[ANIMATION_STATE_IDLE] = DK_GFX_LoadTexture(gfx_context->renderer, "./assets/cat_idle.png");
  gfx_context->textures[ANIMATION_STATE_WALK] = DK_GFX_LoadTexture(gfx_context->renderer, "./assets/cat_walk.png");
  gfx_context->textures[ANIMATION_STATE_JUMP] = DK_GFX_LoadTexture(gfx_context->renderer, "./assets/cat_jump.png");
  gfx_context->textures[DK_GFX_TEXTURE_3] = DK_GFX_LoadTexture(gfx_context->renderer, "./assets/tilemap_packed.png");
}

void game_screen_gameplay_render(DK_GFX_Context *gfx_context)
{
  for (int32_t i = 0; i < PARALLAX_LAYER_COUNT; i++) {
    DK_GFX_DrawParallaxLayer(gfx_context, &game_parallax_layers[i]);
  }

  // @draw @ground
  for (int32_t x = 0; x <= gfx_context->width / GROUND_TILE_SIZE; ++x) {
    DK_GFX_DrawSpritePro(gfx_context, (DK_GFX_SpriteDescPro){
      .slot = DK_GFX_TEXTURE_3,
      .pos = {
        .x = x * GROUND_TILE_SIZE,
        .y = gfx_context->height - GROUND_OFFSET
      },
      .col = 0,
      .row = 6,
      .dest_width = GROUND_TILE_SIZE,
      .dest_height = GROUND_OFFSET,
      .width = 54,
      .height = 18,
    });

    if (DEBUG_DRAW) {
      DK_GFX_DrawDebugRect(gfx_context, &(DK_GFX_Debug_Rect_Desc_t){
        .color = DK_GFX_RED,
        .rect = {
          .w = GROUND_TILE_SIZE,
          .h = GROUND_OFFSET,
          .x = x * GROUND_TILE_SIZE,
          .y = gfx_context->height - GROUND_OFFSET
        }
      });
    }
  }

  char timer_buffer[255];
  sprintf(timer_buffer, "%02d:%02d", game.minutes, game.seconds);

  DK_GFX_DrawText(gfx_context, &(DK_GFX_Text_Desc_t){
    .pos = (DK_GFX_Point){
      .x = (DK_GFX_GetWindowScreenWidth(gfx_context) - DK_GFX_GetTextWidth(gfx_context, timer_buffer)) * 0.5f,
      .y = 20
    },
    .color = DK_GFX_WHITE,
    .text = timer_buffer
  });

  char score_buffer[PLAYER_ID_COUNT][64];

  sprintf(score_buffer[PLAYER_ID_ONE], "%d", game.score[PLAYER_ID_ONE]);
  DK_GFX_DrawText(gfx_context, &(DK_GFX_Text_Desc_t){
    .color = DK_GFX_GREEN,
    .text = score_buffer[PLAYER_ID_ONE],
    .pos = (DK_GFX_Point){ .x = 10, .y = 90 }
  });

  sprintf(score_buffer[PLAYER_ID_TWO], "%d", game.score[PLAYER_ID_TWO]);
  DK_GFX_DrawText(gfx_context, &(DK_GFX_Text_Desc_t){
    .color = DK_GFX_RED,
    .text = score_buffer[PLAYER_ID_TWO],
    .pos = (DK_GFX_Point){ .x = 10, .y = 140 }
  });

  DK_GFX_ResetFont(gfx_context);
  for (int32_t i = 0; i < 2; ++i) {
    if (gfx_context->Gamepad.ready[i]) {
      char buffer[255];
      sprintf(buffer, "P%d: %s", i+1, gfx_context->Gamepad.name[i]);
      DK_GFX_DrawText(gfx_context, &(DK_GFX_Text_Desc_t){
        .pos = (DK_GFX_Point){10, gfx_context->height - (60) - (i * 30)},
        .color = DK_GFX_WHITE,
        .text = buffer
      });
    }
  }

  DK_GFX_SetFont(gfx_context, game._dev_ui.theme.font);


  platform_manager_render(&platform_manager, gfx_context);

  flag_manager_render(&flag_manager, gfx_context);

  for (int32_t i = 0; i < PLAYER_COUNT; ++i) {
    player_render(&player[i], gfx_context);
  }

  TextParticleSystemRender(gfx_context, &text_particle_system);
  ParticleSystemRender(gfx_context, &particle_system);
}

static const int32_t TOTAL_TIME_LIMIT = 60 * 2 * 1000;    // 2 minutes in ms
static int32_t remaining_time = TOTAL_TIME_LIMIT;

void game_screen_gameplay_update(DK_GFX_Context *gfx_context, float dt)
{
  static bool first_frame = true;
  if (first_frame) {
    parallax_layer_setup(gfx_context, game_parallax_layers, GAME_SCREEN_GAMEPLAY);
    first_frame = false;
    remaining_time = TOTAL_TIME_LIMIT;
  }

  remaining_time -= (int32_t)(dt * 1000);
  if (remaining_time < 0) {
    remaining_time = 0;
  }

  game.minutes = remaining_time / 60000;
  game.seconds = (remaining_time / 1000) % 60;

  if (remaining_time <= 0) {
    game.screen = GAME_SCREEN_TITLE;
    DK_GFX_TransitionScreen(gfx_context, (int32_t*)&game.screen, GAME_SCREEN_TITLE);

    first_frame = true;
    game.score[PLAYER_ID_ONE] = 0;
    game.score[PLAYER_ID_TWO] = 0;
    return;
  }

  if (DK_GFX_IsKeyPressed(gfx_context, KEY_ESCAPE) 
      || DK_GFX_IsGamepadButtonPressed(gfx_context, DK_GFX_INPUT_SENDER_ID_ONE, GAMEPAD_BUTTON_MIDDLE_RIGHT)) {
    DK_GFX_TransitionScreen(gfx_context, (int32_t*)&game.screen, GAME_SCREEN_TITLE);
    DK_GFX_PlayAudioFx(gfx_context, DK_GFX_AUDIO_FX_0);
  }

  for (int32_t i = 0; i < PARALLAX_LAYER_COUNT; i++) {
    DK_GFX_UpdateParallaxLayer(gfx_context, &game_parallax_layers[i], dt);
  }

  qsort(player, PLAYER_COUNT, sizeof(GameEntity), cmp_func);

  for (int32_t i = 0; i < PLAYER_COUNT; ++i) {
    player_update(&player[i], &platform_manager, gfx_context, dt);
  }

  TextParticleSystemUpdate(&text_particle_system, dt);
  ParticleSystemUpdate(&particle_system, dt);

  switch (game.mode) {
  case GAME_MODE_CAPTURE_FLAG:
    capture_flag(gfx_context, player, &platform_manager);
    break;
  case GAME_MODE_BUILD_WORD:
    break;
  default:
    break;
  }

  if (DK_GFX_IsKeyPressed(gfx_context, KEY_P)) {
    SDL_Rect _viewport;
    _viewport.w = 400;
    _viewport.h = 150;
    _viewport.x = player[0].position.x - _viewport.w / 2;
    _viewport.y = player[0].position.y - _viewport.h / 2;

    saveScreenshot("screen.png", gfx_context->renderer, _viewport, 10);
  }
}

void game_screen_title_screen_render(DK_GFX_Context *gfx_context)
{
  DK_GFX_ClearScreenWithColor(gfx_context, DK_GFX_ARGB(0x93e3e4));
  DK_GFX_SetFont(gfx_context, game._dev_ui.theme.font);

  for (int32_t i = 0; i < PARALLAX_LAYER_COUNT; i++) {
    DK_GFX_DrawParallaxLayer(gfx_context, &menu_parallax_layers[i]);
  }

  DK_GFX_ResetFont(gfx_context);
  const char *sub_title_buff = "v1.0a";
  DK_GFX_DrawText(gfx_context, &(DK_GFX_Text_Desc_t) {
    .color = DK_GFX_ORANGE,
    .text  = sub_title_buff,
    .pos   = { gfx_context->width - DK_GFX_GetTextWidth(gfx_context, sub_title_buff) - 50, gfx_context->height - 90 }
  });

  const int32_t MAX_MENU_ITEMS = 3;
  char menu_label_buff[MAX_MENU_ITEMS][255] = {
    "Play",
    "Settings",
    "Quit",
  };

  GAME_SCREEN screen[MAX_MENU_ITEMS] = {
    GAME_SCREEN_CONFIGURATION,
    GAME_SCREEN_SETTINGS,
    -1
  };

  static int32_t selected_menu_index = 0;
  DK_GFX_Color menu_label_color = DK_GFX_WHITE;

  int32_t origin_y = gfx_context->height - (MAX_MENU_ITEMS * 40);
  for (int32_t i = 0; i < MAX_MENU_ITEMS; ++i) {
    int32_t index = (MAX_MENU_ITEMS-1)-i;

    if (selected_menu_index == index) {
      menu_label_color = DK_GFX_ORANGE;
    } else {
      menu_label_color = DK_GFX_WHITE;
    }

    DK_GFX_SetFont(gfx_context, game._dev_ui.theme.font);
    DK_GFX_Point position = {
      50,  origin_y - (i * 60)
    };

    DK_GFX_DrawText(gfx_context, &(DK_GFX_Text_Desc_t) {
      .color = menu_label_color,
      .text  = menu_label_buff[index],
      .pos   = position
    });
  }

  if (DK_GFX_IsKeyPressed(gfx_context, KEY_DOWN) 
    || DK_GFX_GameInputManagerKey(gfx_context, DK_GFX_INPUT_SENDER_ID_ONE, DK_GFX_INPUT_KEY_MOVE_DOWN)
    || DK_GFX_IsGamepadButtonPressed(gfx_context, DK_GFX_INPUT_SENDER_ID_ONE, GAMEPAD_BUTTON_LEFT_FACE_DOWN)) {
    selected_menu_index++;
    if (selected_menu_index >= MAX_MENU_ITEMS) {
      selected_menu_index = 0;
    }
    DK_GFX_PlayAudioFx(gfx_context, DK_GFX_AUDIO_FX_2);
  }

  if (DK_GFX_IsKeyPressed(gfx_context, KEY_UP) 
      || DK_GFX_GameInputManagerKey(gfx_context, DK_GFX_INPUT_SENDER_ID_ONE, DK_GFX_INPUT_KEY_MOVE_UP)
      || DK_GFX_IsGamepadButtonPressed(gfx_context, DK_GFX_INPUT_SENDER_ID_ONE, GAMEPAD_BUTTON_LEFT_FACE_UP)) {
    selected_menu_index--;
    if (selected_menu_index < 0) {
      selected_menu_index = MAX_MENU_ITEMS-1;
    }
    DK_GFX_PlayAudioFx(gfx_context, DK_GFX_AUDIO_FX_2);
  }

  if (DK_GFX_IsKeyPressed(gfx_context, KEY_ENTER) 
    || DK_GFX_IsGamepadButtonPressed(gfx_context, DK_GFX_INPUT_SENDER_ID_ONE, GAMEPAD_BUTTON_RIGHT_FACE_DOWN)) {
    if (selected_menu_index != MAX_MENU_ITEMS-1) {
      DK_GFX_TransitionScreen(gfx_context, (int32_t *)&game.screen, screen[selected_menu_index]);
    } else {
      DK_GFX_PushEvent(gfx_context, DK_GFX_EVENT_QUIT);
    }
    DK_GFX_PlayAudioFx(gfx_context, DK_GFX_AUDIO_FX_0);
  }
}

void game_screen_title_screen_update(DK_GFX_Context *gfx_context, float dt)
{
  static bool first_frame = true;
  if (first_frame) {
    parallax_layer_setup(gfx_context, menu_parallax_layers, GAME_SCREEN_TITLE);
    first_frame = false;
  }

  for (int32_t i = 0; i < PARALLAX_LAYER_COUNT; i++) {
    DK_GFX_UpdateParallaxLayer(gfx_context, &menu_parallax_layers[i], gfx_context->dt);
  }
}

void game_screen_settings_render(DK_GFX_Context *gfx_context)
{
  DK_GFX_ClearScreenWithColor(gfx_context, DK_GFX_ARGB(0x93e3e4));
  DK_GFX_SetFont(gfx_context, game._dev_ui.theme.font);

  for (int32_t i = 0; i < PARALLAX_LAYER_COUNT; i++) {
    DK_GFX_DrawParallaxLayer(gfx_context, &menu_parallax_layers[i]);
  }

  const int32_t MAX_MENU_ITEMS = 6;
  char menu_label_buff[MAX_MENU_ITEMS][255] = {
    "Background",
    "Fullscreen",
    "Res",
    "Music",
    "Sound Effects",
    "Back"
  };

  const int32_t MAX_BACKGROUND_ITEMS = 4;
  char background_items[MAX_BACKGROUND_ITEMS][255] = {
    "Dessert",
    "Mountains",
    "Blue Sky",
    "Night Sky",
  };

  static int32_t background_item_index = 0;

  const int32_t MAX_RESOLUTION_ITEMS = 2;
  struct {
    char *label;
    DK_GFX_Point size;
  } resolution_items[MAX_RESOLUTION_ITEMS] = {
    { .label = "1080x720", .size = { .x = 1080, .y = 720 } },
    { .label = "1280x800", .size = { .x = 1280, .y = 800 } },
  };

  static int32_t selected_resolution_item_index = 0; 

  static int32_t selected_menu_index = 0;
  DK_GFX_Color menu_label_color = DK_GFX_WHITE;

  int32_t origin_y = gfx_context->height - (MAX_MENU_ITEMS * 20);
  for (int32_t i = 0; i < MAX_MENU_ITEMS; ++i) {
    int32_t index = (MAX_MENU_ITEMS-1)-i;

    if (selected_menu_index == index) {
      menu_label_color = DK_GFX_ORANGE;
    } else {
      menu_label_color = DK_GFX_WHITE;
    }

    DK_GFX_SetFont(gfx_context, game._dev_ui.theme.font);
    DK_GFX_Point position = {
      50,  origin_y - (i * 60)
    };

    DK_GFX_DrawText(gfx_context, &(DK_GFX_Text_Desc_t) {
      .color = menu_label_color,
      .text  = menu_label_buff[index],
      .pos   = position
    });

    if (index == 0) {
      DK_GFX_Point _position = {
        position.x + DK_GFX_GetTextWidth(gfx_context, menu_label_buff[index]) + 20, position.y
      };

      char buff[255];
      sprintf(buff, "[%s]",  background_items[background_item_index]);

      DK_GFX_DrawText(gfx_context, &(DK_GFX_Text_Desc_t) {
        .color = menu_label_color,
        .text  = buff,
        .pos   = _position
      });
    }

    if (index == 1) {
      DK_GFX_Point _position = {
        position.x + DK_GFX_GetTextWidth(gfx_context, menu_label_buff[index]) + 20, position.y
      };

      char buff[255];
      sprintf(buff, "%s",  gfx_context->full_screen ? "[True]" : "[False]");

      DK_GFX_DrawText(gfx_context, &(DK_GFX_Text_Desc_t) {
        .color = menu_label_color,
        .text  = buff,
        .pos   = _position
      });
    }

    if (index == 2) {
      DK_GFX_Point _position = {
        position.x + DK_GFX_GetTextWidth(gfx_context, menu_label_buff[index]) + 20, position.y
      };

      char buff[255];
      sprintf(buff, "%s", resolution_items[selected_resolution_item_index].label);

      DK_GFX_DrawText(gfx_context, &(DK_GFX_Text_Desc_t) {
        .color = menu_label_color,
        .text  = buff,
        .pos   = _position
      });
    }

    if (index == 3) {
      DK_GFX_Point _position = {
        position.x + DK_GFX_GetTextWidth(gfx_context, menu_label_buff[index]) + 20, position.y
      };

      char buff[255];
      sprintf(buff, "%0.1f",  game.music_volume);

      DK_GFX_DrawText(gfx_context, &(DK_GFX_Text_Desc_t) {
        .color = menu_label_color,
        .text  = buff,
        .pos   = _position
      });
    }

    if (index == 4) {
      DK_GFX_Point _position = {
        position.x + DK_GFX_GetTextWidth(gfx_context, menu_label_buff[index]) + 20, position.y
      };

      char buff[255];
      sprintf(buff, "%0.1f",  game.sound_effect_volume);

      DK_GFX_DrawText(gfx_context, &(DK_GFX_Text_Desc_t) {
        .color = menu_label_color,
        .text  = buff,
        .pos   = _position
      });
    }
  }

  if (DK_GFX_IsKeyPressed(gfx_context, KEY_DOWN) 
    || DK_GFX_IsGamepadButtonPressed(gfx_context, DK_GFX_INPUT_SENDER_ID_ONE, GAMEPAD_BUTTON_LEFT_FACE_DOWN)) {
    selected_menu_index++;
    if (selected_menu_index >= MAX_MENU_ITEMS) {
      selected_menu_index = 0;
    }
    DK_GFX_PlayAudioFx(gfx_context, DK_GFX_AUDIO_FX_2);
  }

  if (DK_GFX_IsKeyPressed(gfx_context, KEY_UP) 
    || DK_GFX_IsGamepadButtonPressed(gfx_context, DK_GFX_INPUT_SENDER_ID_ONE, GAMEPAD_BUTTON_LEFT_FACE_UP)) {
    selected_menu_index--;
    if (selected_menu_index < 0) {
      selected_menu_index = MAX_MENU_ITEMS-1;
    }
    DK_GFX_PlayAudioFx(gfx_context, DK_GFX_AUDIO_FX_2);
  }

  // go back
  if (DK_GFX_IsGamepadButtonPressed(gfx_context, DK_GFX_INPUT_SENDER_ID_ONE, GAMEPAD_BUTTON_RIGHT_FACE_RIGHT)
    || DK_GFX_IsKeyPressed(gfx_context, KEY_ESCAPE)) {
    DK_GFX_TransitionScreen(gfx_context, (int32_t *)&game.screen, GAME_SCREEN_TITLE);
    DK_GFX_PlayAudioFx(gfx_context, DK_GFX_AUDIO_FX_0);
  }

  if (DK_GFX_IsKeyPressed(gfx_context, KEY_ENTER) 
    || DK_GFX_IsGamepadButtonPressed(gfx_context, DK_GFX_INPUT_SENDER_ID_ONE, GAMEPAD_BUTTON_RIGHT_FACE_DOWN)) {

    DK_GFX_PlayAudioFx(gfx_context, DK_GFX_AUDIO_FX_0);

    if (selected_menu_index == MAX_MENU_ITEMS-1) {
      DK_GFX_TransitionScreen(gfx_context, (int32_t *)&game.screen, GAME_SCREEN_TITLE);
    }

    else if (selected_menu_index == MAX_MENU_ITEMS-2) {
      if (game.sound_effect_volume >= 0.0f && game.sound_effect_volume != 100.0f) {
        game.sound_effect_volume += 10.0f;
      } else {
        game.sound_effect_volume = 0.0f;
      }

      float volume_normalized = game.sound_effect_volume / 100.0f;
      DK_GFX_SetAudioFxMasterVolume(gfx_context, volume_normalized);
    }
    else if (selected_menu_index == MAX_MENU_ITEMS-3) {
      if (game.music_volume >= 0.0f && game.music_volume != 100.0f) {
        game.music_volume += 10.0f;
      } else {
        game.music_volume = 0.0f;
      }
    }

    else if (selected_menu_index == MAX_MENU_ITEMS-4) {
      if (selected_resolution_item_index < MAX_RESOLUTION_ITEMS-1) {
        selected_resolution_item_index++;
      } else {
        selected_resolution_item_index = 0;
      }

      DK_GFX_WindowResize(gfx_context, resolution_items[selected_resolution_item_index].size);

      game_on_screen_resize(gfx_context);
    }

    else if (selected_menu_index == MAX_MENU_ITEMS-5) {
      DK_GFX_WindowToggleFullScreen(gfx_context);
    }

    else if (selected_menu_index == MAX_MENU_ITEMS-6) {
      if (background_item_index < MAX_BACKGROUND_ITEMS-1) {
        background_item_index++;

        char *p1_buff = malloc(sizeof(char) * 255);
        sprintf(p1_buff, "assets/Parallax/v%d/1.png", background_item_index+1);

        char *p2_buff = malloc(sizeof(char) * 255);
        sprintf(p2_buff, "assets/Parallax/v%d/2.png", background_item_index+1);

        char *p3_buff = malloc(sizeof(char) * 255);
        sprintf(p3_buff, "assets/Parallax/v%d/3.png", background_item_index+1);

        DK_GFX_Texture *tex[3];

        tex[0] = game_parallax_layers[0].texture;
        tex[1] = game_parallax_layers[1].texture;
        tex[2] = game_parallax_layers[2].texture;

        game_parallax_layers[0].texture = DK_GFX_LoadTexture(gfx_context->renderer, p1_buff);
        game_parallax_layers[1].texture = DK_GFX_LoadTexture(gfx_context->renderer, p2_buff);
        game_parallax_layers[2].texture = DK_GFX_LoadTexture(gfx_context->renderer, p3_buff);

        DK_GFX_DestroyTexture(tex[0]);
        DK_GFX_DestroyTexture(tex[1]);
        DK_GFX_DestroyTexture(tex[2]);

        tex[0] = menu_parallax_layers[0].texture;
        tex[1] = menu_parallax_layers[1].texture;
        tex[2] = menu_parallax_layers[2].texture;
        
        menu_parallax_layers[0].texture = DK_GFX_LoadTexture(gfx_context->renderer, p1_buff);
        menu_parallax_layers[1].texture = DK_GFX_LoadTexture(gfx_context->renderer, p2_buff);
        menu_parallax_layers[2].texture = DK_GFX_LoadTexture(gfx_context->renderer, p3_buff);

        DK_GFX_DestroyTexture(tex[0]);
        DK_GFX_DestroyTexture(tex[1]);
        DK_GFX_DestroyTexture(tex[2]);
        
        free(p1_buff); 
        free(p2_buff);
        free(p3_buff);

      } else {
        background_item_index = 0;

        char *p1_buff = malloc(sizeof(char) * 255);
        sprintf(p1_buff, "assets/Parallax/v%d/1.png", background_item_index+1);

        char *p2_buff = malloc(sizeof(char) * 255);
        sprintf(p2_buff, "assets/Parallax/v%d/2.png", background_item_index+1);

        char *p3_buff = malloc(sizeof(char) * 255);
        sprintf(p3_buff, "assets/Parallax/v%d/3.png", background_item_index+1);

        DK_GFX_Texture *tex[3];

        tex[0] = game_parallax_layers[0].texture;
        tex[1] = game_parallax_layers[1].texture;
        tex[2] = game_parallax_layers[2].texture;

        game_parallax_layers[0].texture = DK_GFX_LoadTexture(gfx_context->renderer, p1_buff);
        game_parallax_layers[1].texture = DK_GFX_LoadTexture(gfx_context->renderer, p2_buff);
        game_parallax_layers[2].texture = DK_GFX_LoadTexture(gfx_context->renderer, p3_buff);

        DK_GFX_DestroyTexture(tex[0]);
        DK_GFX_DestroyTexture(tex[1]);
        DK_GFX_DestroyTexture(tex[2]);

        tex[0] = menu_parallax_layers[0].texture;
        tex[1] = menu_parallax_layers[1].texture;
        tex[2] = menu_parallax_layers[2].texture;

        menu_parallax_layers[0].texture = DK_GFX_LoadTexture(gfx_context->renderer, p1_buff);
        menu_parallax_layers[1].texture = DK_GFX_LoadTexture(gfx_context->renderer, p2_buff);
        menu_parallax_layers[2].texture = DK_GFX_LoadTexture(gfx_context->renderer, p3_buff);

        DK_GFX_DestroyTexture(tex[0]);
        DK_GFX_DestroyTexture(tex[1]);
        DK_GFX_DestroyTexture(tex[2]);

        free(p1_buff); 
        free(p2_buff);
        free(p3_buff);
      }
    }
  }
}

void game_screen_settings_update(DK_GFX_Context *gfx_context, float dt) {
  for (int32_t i = 0; i < PARALLAX_LAYER_COUNT; i++) {
    DK_GFX_UpdateParallaxLayer(gfx_context, &menu_parallax_layers[i], gfx_context->dt);
  }
}

int32_t cmp_func(const void *a, const void *b)
{
  const GameEntity *playerA = (const GameEntity *)a;
  const GameEntity *playerB = (const GameEntity *)b;
  if (playerA->position.x < playerB->position.x) return -1;
  if (playerA->position.x > playerB->position.x) return 1;
  return 0;
}

void game_on_screen_resize(DK_GFX_Context *gfx_context) {
  platform_manager.count = 0;
  place_platforms(gfx_context, &platform_manager);

  int32_t the_platform_index = flag_manager.item[flag_manager.count].userdata.platform_id;
  flag_manager.count = 0;
  spawn_flag_on_platform(&flag_manager, &platform_manager.platforms[the_platform_index], the_platform_index);
}
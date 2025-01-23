#if 0
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "dk_game.h"

#define MAP_WIDTH 8
#define MAP_HEIGHT 8
#define TILE_SIZE 64

#define FOV 65
#define MAX_ENTITIES 32

typedef struct {
  float x, y;
  float angle;
  float dx, dy;
  float dangle;
} Player;

typedef struct {
  float x, y;
  float z;
  int texture_id;
  float width;
  float height;
  bool active;
} Entity;

Player player = { 200.0f, 200.0f, 0.0f, 0.0f, 0.0f, 0.0f };
Entity entities[MAX_ENTITIES] = {0};
int num_entities = 0;
float *z_buffer;

int map[MAP_HEIGHT][MAP_WIDTH] = {
  {1, 1, 1, 1, 1, 1, 1, 1},
  {1, 0, 0, 0, 0, 0, 0, 1},
  {1, 1, 1, 1, 1, 1, 0, 1},
  {1, 0, 1, 0, 0, 0, 0, 1},
  {1, 0, 0, 0, 1, 1, 0, 1},
  {1, 0, 1, 0, 0, 1, 0, 1},
  {1, 0, 0, 0, 0, 0, 0, 1},
  {1, 1, 1, 1, 1, 1, 1, 1}
};

float distance(float x1, float y1, float x2, float y2) {
  return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

void add_entity(float x, float y, float z, int texture_id, float width, float height) {
  if (num_entities < MAX_ENTITIES) {
    entities[num_entities].x = x;
    entities[num_entities].y = y;
    entities[num_entities].z = z;
    entities[num_entities].texture_id = texture_id;
    entities[num_entities].width = width;
    entities[num_entities].height = height;
    entities[num_entities].active = true;
    num_entities++;
  }
}

void render_entities(DK_GFX_Context* gfx_context) {
  SDL_Renderer *renderer = gfx_context->renderer;
  int screenWidth = gfx_context->width;
  int screenHeight = gfx_context->height;

  for (int i = 0; i < num_entities - 1; i++) {
    for (int j = i + 1; j < num_entities; j++) {
      float dist_i = distance(player.x, player.y, entities[i].x, entities[i].y);
      float dist_j = distance(player.x, player.y, entities[j].x, entities[j].y);
      
      if (dist_j > dist_i) {
        Entity temp = entities[i];
        entities[i] = entities[j];
        entities[j] = temp;
      }
    }
  }
  
  // from furthest to nearest
  for (int i = 0; i < num_entities; i++) {
    if (!entities[i].active) continue;
    
    float dx = entities[i].x - player.x;
    float dy = entities[i].y - player.y;

    float angle = atan2(dy, dx) * 180.0f / M_PI;
    float angle_diff = angle - player.angle;
    if (angle_diff > 180.0f) angle_diff -= 360.0f;
    if (angle_diff < -180.0f) angle_diff += 360.0f;
    
    // entity is in view
    if (fabs(angle_diff) > FOV / 2.0f) continue;
    
    float dist = distance(player.x, player.y, entities[i].x, entities[i].y);
    float size = (TILE_SIZE / dist) * (screenWidth / 2.0f);
    
    int screen_x = (int)((screenWidth / 2) + (angle_diff / (FOV / 2.0f)) * (screenWidth / 2));
    int screen_y = (int)((screenHeight / 2) - (size / 2) + (entities[i].z / dist) * size);
    
    // render if in front of walls
    if (dist < z_buffer[screen_x]) {
      SDL_Texture *entity_texture = gfx_context->textures[entities[i].texture_id];
      int tex_w, tex_h;
      DK_GFX_GetTextureSize(gfx_context->textures[entities[i].texture_id], &tex_w, &tex_h);
      SDL_Rect src = { 0, 0, tex_w, tex_h };

      SDL_Rect dst = { screen_x - (int)(size/2), screen_y, (int)size, (int)size };
      SDL_RenderCopy(renderer, entity_texture, &src, &dst);
    }
  }
}

bool is_wall(float x, float y) {
  int mapX = (int)(x / TILE_SIZE);
  int mapY = (int)(y / TILE_SIZE);
  return map[mapY][mapX] == 1;
}

void cast_rays(DK_GFX_Context* gfx_context) 
{
  SDL_Renderer *renderer = gfx_context->renderer;
  SDL_Texture *wall_texture = gfx_context->textures[DK_GFX_TEXTURE_0]; // @wall texture
  SDL_Texture *floor_texture = gfx_context->textures[DK_GFX_TEXTURE_2];  // @floor texture
  SDL_Texture *ceiling_texture = gfx_context->textures[DK_GFX_TEXTURE_1];  // @ceiling texture

  int screenWidth = gfx_context->width;
  int screenHeight = gfx_context->height;
  const int NUM_RAYS = screenWidth;
  float ray_angle = player.angle - (FOV / 2.0f);
  float angle_step = (float)FOV / NUM_RAYS;

  float proj_plane_dist = (screenWidth / 2.0f) / tan((FOV / 2.0f) * M_PI / 180.0f);

  float player_cos = cos(player.angle * M_PI / 180.0f);
  float player_sin = sin(player.angle * M_PI / 180.0f);

  for (int i = 0; i < NUM_RAYS; i++) {
    float ray_x = player.x;
    float ray_y = player.y;
    float ray_dir_x = cos(ray_angle * M_PI / 180.0f);
    float ray_dir_y = sin(ray_angle * M_PI / 180.0f);
    
    float h_distance = 1000000;
    float v_distance = 1000000;
    float h_x = player.x;
    float h_y = player.y;
    float v_x = player.x;
    float v_y = player.y;

    float y_intercept = floor(player.y / TILE_SIZE) * TILE_SIZE;
    y_intercept += (ray_dir_y > 0) ? TILE_SIZE : 0;
    float x_intercept = player.x + (y_intercept - player.y) / tan(ray_angle * M_PI / 180.0f);
    
    float y_step = TILE_SIZE;
    y_step *= (ray_dir_y < 0) ? -1 : 1;
    float x_step = TILE_SIZE / tan(ray_angle * M_PI / 180.0f);
    x_step *= (ray_dir_x < 0 && x_step > 0) ? -1 : 1;
    x_step *= (ray_dir_x > 0 && x_step < 0) ? -1 : 1;

    float next_x = x_intercept;
    float next_y = y_intercept;
    
    while (next_x >= 0 && next_x < MAP_WIDTH * TILE_SIZE && 
            next_y >= 0 && next_y < MAP_HEIGHT * TILE_SIZE) {
      float check_x = next_x;
      float check_y = next_y + (ray_dir_y < 0 ? -1 : 0);
      
      if (is_wall(check_x, check_y)) {
        h_x = next_x;
        h_y = next_y;
        h_distance = distance(player.x, player.y, h_x, h_y);
        break;
      }
      next_x += x_step;
      next_y += y_step;
    }

    x_intercept = floor(player.x / TILE_SIZE) * TILE_SIZE;
    x_intercept += (ray_dir_x > 0) ? TILE_SIZE : 0;
    y_intercept = player.y + (x_intercept - player.x) * tan(ray_angle * M_PI / 180.0f);
    
    x_step = TILE_SIZE;
    x_step *= (ray_dir_x < 0) ? -1 : 1;
    y_step = TILE_SIZE * tan(ray_angle * M_PI / 180.0f);
    y_step *= (ray_dir_y < 0 && y_step > 0) ? -1 : 1;
    y_step *= (ray_dir_y > 0 && y_step < 0) ? -1 : 1;

    next_x = x_intercept;
    next_y = y_intercept;
    
    while (next_x >= 0 && next_x < MAP_WIDTH * TILE_SIZE && 
            next_y >= 0 && next_y < MAP_HEIGHT * TILE_SIZE) {
      float check_x = next_x + (ray_dir_x < 0 ? -1 : 0);
      float check_y = next_y;
      
      if (is_wall(check_x, check_y)) {
        v_x = next_x;
        v_y = next_y;
        v_distance = distance(player.x, player.y, v_x, v_y);
        break;
      }
      next_x += x_step;
      next_y += y_step;
    }

    float distance = (h_distance < v_distance) ? h_distance : v_distance;
    bool hit_vertical = (v_distance < h_distance);
    float hit_x = hit_vertical ? v_x : h_x;
    float hit_y = hit_vertical ? v_y : h_y;

    // fisheye effect
    distance *= cos((ray_angle - player.angle) * M_PI / 180.0f);
    z_buffer[i] = distance;

    float height_multiplier = 0.9f;
    float wall_height = (TILE_SIZE * proj_plane_dist * height_multiplier) / distance;
    
    int wall_top = (screenHeight / 2) - (int)(wall_height / 2);
    int wall_bottom = (screenHeight / 2) + (int)(wall_height / 2);
    
    int tex_width = 64;
    int tex_height = 64;
    DK_GFX_GetTextureSize(wall_texture, &tex_width, &tex_height);
    
    float texture_x;
    if (hit_vertical) {
      texture_x = fmod(hit_y, TILE_SIZE);
      if (ray_dir_x < 0) texture_x = TILE_SIZE - texture_x - 1;
    } else {
      texture_x = fmod(hit_x, TILE_SIZE);
      if (ray_dir_y > 0) texture_x = TILE_SIZE - texture_x - 1;
    }

#if 0
    int tex_x = (int)((texture_x / TILE_SIZE) * tex_width);
    
    SDL_Rect src_rect = { tex_x, 0, 1, tex_height };
    SDL_Rect dest_rect = { i, wall_top, 1, wall_bottom - wall_top + 1 };
    
    SDL_RenderCopy(renderer, wall_texture, &src_rect, &dest_rect);
#endif

    SDL_SetRenderDrawColor(renderer, 255 - (distance / 2), 255 - (distance / 3), 255, 255);
    SDL_RenderDrawLine(renderer, i, wall_top, i, wall_bottom);

    // @ceiling
    SDL_SetRenderDrawColor(renderer, 50, 50, 255, 255);
    SDL_RenderDrawLine(renderer, i, 0, i, wall_top - 1);
    
    // @floor
    SDL_SetRenderDrawColor(renderer, 100, 50, 25, 255);
    SDL_RenderDrawLine(renderer, i, wall_bottom + 1, i, screenHeight - 1);

    ray_angle += angle_step;
  }

  render_entities(gfx_context);
}

void handle_input(DK_GFX_Context *gfx_context) {
  float move_step = 2.5f;
  float rot_speed = 200.0f;
  float deceleration = 2.1f;

  if (DK_GFX_IsKeyDown(gfx_context, KEY_W)) {
    player.dx += cos(player.angle * M_PI / 180.0f) * move_step * gfx_context->dt;
    player.dy += sin(player.angle * M_PI / 180.0f) * move_step * gfx_context->dt;
  }
  if (DK_GFX_IsKeyDown(gfx_context, KEY_S)) {
    player.dx -= cos(player.angle * M_PI / 180.0f) * move_step * gfx_context->dt;
    player.dy -= sin(player.angle * M_PI / 180.0f) * move_step * gfx_context->dt;
  }
  if (DK_GFX_IsKeyDown(gfx_context, KEY_A)) {
    player.dx += sin(player.angle * M_PI / 180.0f) * move_step * gfx_context->dt;
    player.dy -= cos(player.angle * M_PI / 180.0f) * move_step * gfx_context->dt;
  }
  if (DK_GFX_IsKeyDown(gfx_context, KEY_D)) {
    player.dx -= sin(player.angle * M_PI / 180.0f) * move_step * gfx_context->dt;
    player.dy += cos(player.angle * M_PI / 180.0f) * move_step * gfx_context->dt;
  }

  player.dx *= (1.0f - deceleration * gfx_context->dt);
  player.dy *= (1.0f - deceleration * gfx_context->dt);

  float new_x = player.x + player.dx;
  float new_y = player.y + player.dy;
  if (is_wall(new_x, new_y)) {
    player.dx = -player.dx;
    player.dy = -player.dy;
  } else {
    player.x = new_x;
    player.y = new_y;
  }

  if (DK_GFX_IsKeyDown(gfx_context, KEY_Q)) {
    player.dangle -= rot_speed * gfx_context->dt;
    // if (player.dangle < 0) player.dangle += 360;
  }
  if (DK_GFX_IsKeyDown(gfx_context, KEY_E)) {
    player.dangle += rot_speed * gfx_context->dt;
    // if (player.dangle >= 360) player.dangle -= 360;
  }

  player.dangle *= (1.0f - deceleration * gfx_context->dt);
  player.angle += player.dangle * gfx_context->dt;
}

void GameInit(DK_GFX_Context *gfx_context)
{
  gfx_context->textures[DK_GFX_TEXTURE_0] = DK_GFX_LoadTexture(gfx_context->renderer, "./assets/CRATE_1J.PNG");
  gfx_context->textures[DK_GFX_TEXTURE_1] = DK_GFX_LoadTexture(gfx_context->renderer, "./assets/WARN_1A.PNG");
  gfx_context->textures[DK_GFX_TEXTURE_2] = DK_GFX_LoadTexture(gfx_context->renderer, "./assets/FLOOR_1D.PNG");
  gfx_context->textures[DK_GFX_TEXTURE_3] = DK_GFX_LoadTexture(gfx_context->renderer, "./assets/effect_blast.png");
  
  z_buffer = (float*)malloc(sizeof(float) * gfx_context->width);

  add_entity(300.0f, 300.0f, 0.0f, 3, 32.0f, 32.0f);
  add_entity(200.0f, 200.0f, 0.0f, 3, 32.0f, 32.0f);
}

void GameRender(DK_GFX_Context *gfx_context) {
  SDL_SetRenderDrawColor(gfx_context->renderer, 0, 0, 0, 255);
  SDL_RenderClear(gfx_context->renderer);
  cast_rays(gfx_context);
}

void GameUpdate(DK_GFX_Context *gfx_context)
{
  handle_input(gfx_context);
}

void GameDestroy() {}
#endif

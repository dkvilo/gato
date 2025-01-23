#include "dk_shapes.h"

#include <stdlib.h> // malloc

DK_GFX_Texture*
CreateCircle(DK_GFX_Renderer *renderer, int32_t w, int32_t h, DK_GFX_Color fill_color) {

  DK_GFX_Texture *texture = DK_GFX_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STATIC, w, h);
  SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);

  Uint32 *pixels = (Uint32*)malloc(sizeof(Uint32) * w * h);
  int32_t radius = w / 2;

  for (int32_t y = 0; y < w; y++) {
    for (int32_t x = 0; x < h; x++) {
      {
        pixels[y * w + x] = (fill_color.a << 24) + (fill_color.r << 16) + (fill_color.g << 8) + fill_color.b;
      }
      
      float dy = abs(y - radius);
      float dx = abs(x - radius);
      
      {
        // @border
        int32_t border_size = 2;
        int32_t border_fade_size = border_size;
        int32_t pading = 1;

        if (dx * dx + dy * dy > (radius - border_size + pading) * (radius - border_size)) {
          if (dx * dx + dy * dy > (radius - border_size - border_fade_size) * (radius - border_size - border_fade_size)) {
            float distance = sqrtf(dx * dx + dy * dy);
            float alpha = (distance - (radius - border_size - border_fade_size)) / border_fade_size;
            pixels[y * w + x] = (Uint32)(alpha * 255) << 24;

            // inverting the alpha value
            pixels[y * w + x] = ~pixels[y * w + x];
            pixels[y * w + x] += (fill_color.r << 16) + (fill_color.g << 8) + fill_color.b;
          }
        }
      }

      // @discard @outside
      if (dx * dx + dy * dy > radius * radius) {
        pixels[y * w + x] = 0x00;
      }
    }
  }

  SDL_UpdateTexture(texture, NULL, pixels, w * sizeof(Uint32));
  DK_GFX_SetRenderTarget(renderer, NULL);

  free(pixels);

  return texture;
}

DK_GFX_Texture*
CreateRect(DK_GFX_Renderer *renderer, int32_t w, int32_t h, DK_GFX_Color fill_color)
{

  DK_GFX_Texture *texture = DK_GFX_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STATIC, w, h);
  SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);

  Uint32 *pixels = (Uint32*)malloc(sizeof(Uint32) * w * h);

  for (int32_t x = 0; x < w; x++) {
    for (int32_t y = 0; y < h; y++)
    {
      pixels[y * w + x] = (fill_color.a << 24) + (fill_color.r << 16) + (fill_color.g << 8) + fill_color.b;

      const int32_t border_size = 4;
      const int32_t border_fade_size = 6;
  
      if (y >= h - border_size) {
        float distance = sqrtf(border_size * border_size + h);
        float alpha = (distance - (border_size - border_fade_size)) / border_fade_size;
        pixels[y * w + x] = (Uint32)(alpha * 255) << 24;
        pixels[y * w + x] += (fill_color.r << 16) + (fill_color.g << 8) + fill_color.b;
      }
    
    }
  }

  SDL_UpdateTexture(texture, NULL, pixels, w * sizeof(Uint32));
  DK_GFX_SetRenderTarget(renderer, NULL);

  free(pixels);
  pixels = NULL;

  return texture;
}
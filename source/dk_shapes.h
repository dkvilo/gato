#if !defined(__DK_SHAPES_H)
#define __DK_SHAPES_H

#define DK_GFX_IMPL
#include "dk_gfx.h"

// TODO (David): Add descriptor to the shapes to be able to create them with different colors, etc.
DK_GFX_Texture*
CreateCircle(DK_GFX_Renderer *renderer, int32_t w, int32_t h, DK_GFX_Color fill_color);

DK_GFX_Texture*
CreateRect(DK_GFX_Renderer *renderer, int32_t w, int32_t h, DK_GFX_Color fill_color);

#endif // __DK_SHAPES_H
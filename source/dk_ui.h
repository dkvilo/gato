/**
 * @file dk_ui.h
 * @author David Kviloria (dkviloria@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-07-05
 * 
 * @copyright Copyright (c) 2023 SKYSTAR GAMES Interactive
 * 
 */
#if !defined(DK_UI_H)
#define DK_UI_H

#define DK_GFX_IMPL
#include "dk_gfx.h"

#include "dk_shapes.h" // CreateCircle

typedef void (*DK_UI_TextInput_Callback)(char *buffer);

typedef struct ImUIStyle {
  int32_t border_radius;
  int32_t border_width;
  enum {
    IMUI_TEXT_ALIGN_LEFT,
    IMUI_TEXT_ALIGN_RIGHT,
    IMUI_TEXT_ALIGN_CENTER
  } text_alignment;
} ImUIStyle;

typedef struct ImUIColorScheme {
  DK_GFX_Color bg_color;
  DK_GFX_Color fg_color;
  DK_GFX_Color border_color;

  DK_GFX_Color input_text_cursor;
  DK_GFX_Color input_text_fg;
  DK_GFX_Color input_text_bg; 

  DK_GFX_Color button_bg;
  DK_GFX_Color button_bg_hover;
  DK_GFX_Color button_bg_active;

} ImUIColorScheme;

typedef struct ImUITheme {
  char *name;
  TTF_Font *font;
  ImUIStyle style;
  ImUIColorScheme color_scheme;
} ImUITheme;

typedef struct ImUIContext {

  int32_t active_frame_id;

  uint8_t focused;
  uint8_t hovered;
  uint8_t pressed;

  DK_GFX_Point mouse;
  DK_GFX_Point mouse_delta;

  DK_GFX_Point drag_start;
  DK_GFX_Point drag_end;

} ImUIContext;

typedef struct ImNode {
  int32_t id;

  union
  {
    char *text;
    char **items;
  };

  int32_t num_items;
  int32_t selected_item;

  union {
    bool *value;
    float *slider_value;
    int32_t *select_value;
    DK_UI_TextInput_Callback text_input_callback;
  };

  bool *focused;
  float slider_step;
  float slider_min;
  float slider_max;

  enum {
    IMUI_NODE_TYPE_BUTTON,
    IMUI_NODE_TYPE_TEXT_FIELD,
    IMUI_NODE_TYPE_SELECT,
    IMUI_NODE_TYPE_SWITCH,
    IMUI_NODE_TYPE_SLIDER,
    IMUI_NODE_TYPE_TEXT,
    IMUI_NODE_TYPE_SPACER
  } type;
  
  DK_GFX_Rect rect;

  struct ImNode *children;
} ImNode;

typedef struct LayoutVerticalStack {
  ImNode **nodes;
  int32_t num_nodes;
} LayoutVerticalStack;

typedef struct ImUIFrame {

  int32_t id;
  char *title;

  bool *visible;
  bool hovered;
  bool focused;
  bool pressed;
  bool dragging;

  bool _pinned;
  bool _action_button_focused;
  
  DK_GFX_Rect *rect;
  LayoutVerticalStack *stack_layout;

} ImUIFrame;

typedef struct ImUI {
  ImUIContext context;
  DK_GFX_Context *gfx_context;
  ImUITheme theme;
} ImUI;

static ImUITheme IMUI_SOLARIZED = {
  .color_scheme = {
    .border_color = (DK_GFX_Color){ 0x00, 0x2B, 0x36, 0xFF },
    .bg_color = (DK_GFX_Color){ 0x0c, 0x33, 0x3d, 0xFF },
    .fg_color = (DK_GFX_Color){ 211, 211, 211, 0xFF },
    .input_text_cursor = (DK_GFX_Color){ 0x00, 0xFF, 0x00, 0xFF },
    .input_text_fg = (DK_GFX_Color){ 211, 211, 211, 0xFF },
    .input_text_bg = (DK_GFX_Color){ 0x00, 0x2B, 0x36, 0xFF },

    .button_bg_active = (DK_GFX_Color){ 38, 139, 210, 0xFF },
    .button_bg = (DK_GFX_Color){ 0x15, 0x3b, 0x45, 0xFF },
    .button_bg_hover = (DK_GFX_Color){ 0x22, 0x47, 0x52, 0xFF },
  },

  .style = {
    .border_radius = 2,
    .border_width = 1,
    .text_alignment = IMUI_TEXT_ALIGN_CENTER
  },

  .name = "solarized"
};

static ImUITheme IMUI_AQUA = {
  .color_scheme = {
    .border_color = (DK_GFX_Color){ 0x00, 0x2B, 0x36, 0xFF },
    .bg_color = (DK_GFX_Color){ 0, 102, 204, 0xFF },
    .fg_color = (DK_GFX_Color){ 211, 211, 211, 0xFF },
    .input_text_cursor = (DK_GFX_Color){ 0x00, 0xFF, 0x00, 0xFF },
    .input_text_fg = (DK_GFX_Color){ 211, 211, 211, 0xFF },
    .input_text_bg = (DK_GFX_Color){ 0, 70, 234, 0xFF },

    .button_bg_active = (DK_GFX_Color){ 38, 139, 210, 0xFF },
    .button_bg = (DK_GFX_Color){ 0, 102, 204, 0xFF },
    .button_bg_hover = (DK_GFX_Color){ 0, 51, 102, 0xFF }
  },

  .style = {
    .border_radius = 2,
    .border_width = 1,
    .text_alignment = IMUI_TEXT_ALIGN_CENTER
  },

  .name = "aqua"
};

static ImUITheme IMUI_LIGHT = {
  .color_scheme = {
    .bg_color = (DK_GFX_Color){ 0xFF, 0xFF, 0xFF, 0xFF },
    .border_color = (DK_GFX_Color){ 211, 211, 211, 0xFF },
    .fg_color = (DK_GFX_Color){ 0x00, 0x00, 0x00, 0xFF },
    .input_text_cursor = (DK_GFX_Color){ 0x00, 0xFF, 0x00, 0xFF },
    .input_text_fg = (DK_GFX_Color){ 0x00, 0x00, 0x00, 0xFF },
    .input_text_bg = (DK_GFX_Color){ 245, 245, 245, 0xFF },

    .button_bg_active = (DK_GFX_Color){ 245, 245, 245, 0xFF }, 
    .button_bg = (DK_GFX_Color){ 220, 220, 220, 0xFF }, 
    .button_bg_hover = (DK_GFX_Color){ 200, 200, 200, 0xFF } 
  },

  .style = {
    .border_radius = 2,
    .border_width = 1,
    .text_alignment = IMUI_TEXT_ALIGN_CENTER
  },

  .name = "light"
};

#if !defined(IMUI_DEFAULT_THEME)
#define IMUI_DEFAULT_THEME IMUI_SOLARIZED
#endif

bool
IMUI_Is_Active(ImUI *ctx);

bool
DK_UI_Button(ImUI *ctx, DK_GFX_Rect rect, char *text, bool *focused);

ImUITheme
ImUI_Get_Default_Theme();

void
DK_UI_TextInput(ImUI *ctx, DK_GFX_Rect rect, char *buffer, bool *focused, DK_UI_TextInput_Callback callback);

void
DK_UI_Select(ImUI *ctx, DK_GFX_Rect rect, bool *focused, char **items, int32_t num_items, int32_t *selected_item);

void
DK_UI_Switch(ImUI *ctx, char* label, DK_GFX_Rect rect, bool *value, bool *focused);

void
DK_UI_Slider(ImUI *ctx, DK_GFX_Rect rect, float *value, float step, float min, float max, bool *focused);

void
DK_UI_ColorPicker(ImUI *ctx, DK_GFX_Rect *frame_rect, int32_t frame_id, DK_GFX_Color *color, bool *focused);

void
DK_UI_Frame(ImUI *ctx, ImUIFrame *frame);

void
DK_UI_Layout_VerticalStack_Init(ImUI *ctx, LayoutVerticalStack *layout);

void
DK_UI_Layout_VerticalStack(ImUI *ctx, LayoutVerticalStack *layout);

void
DK_UI_Layout_VerticalStack_Push(LayoutVerticalStack *layout, ImNode *node);

void
DK_UI_Init(ImUI *ctx, DK_GFX_Context *gfx_context, ImUITheme theme);

#if defined(DK_UI_IMPLEMENTATION)

ImUITheme
ImUI_Get_Default_Theme() {
  return IMUI_DEFAULT_THEME;
}

void
DK_UI_Layout_VerticalStack_Init(ImUI *ctx, LayoutVerticalStack *layout)
{
  DK_GFX_Context *gfx_context = ctx->gfx_context;
  ImUIColorScheme *color_scheme = &ctx->theme.color_scheme;
  ImUIStyle *style = &ctx->theme.style;

  int32_t num_nodes = layout->num_nodes;
  ImNode **nodes = layout->nodes;

  int32_t total_height = 0;

  for (int32_t i = 0; i < num_nodes; i++) {
    ImNode *node = nodes[i];
    if (node == NULL) continue;
    total_height += node->rect.h;
  }

  int32_t screen_height = DK_GFX_GetWindowScreenHeight(gfx_context);
  int32_t current_y = (screen_height / 2) - (total_height / 2);

  for (int32_t i = 0; i < num_nodes; i++) {
    ImNode *node = nodes[i];
    if (node == NULL) continue;

    node->rect.y = current_y;
    current_y += node->rect.h;
  }
}

void
DK_UI_Layout_VerticalStack_Push(LayoutVerticalStack *layout, ImNode *node)
{
  layout->nodes[layout->num_nodes++] = node;
  layout->num_nodes++;
}

#include <assert.h>

// Draw Vertical Stack Layout Nodes
void
DK_UI_Layout_VerticalStack(ImUI *ctx, LayoutVerticalStack *layout) 
{
  int32_t num_nodes = layout->num_nodes;
  ImNode **nodes = layout->nodes;

  for (int32_t i = 0; i < num_nodes; i++) {
    ImNode *node = nodes[i];
    if (node == NULL) continue;

    switch (node->type) {
      case IMUI_NODE_TYPE_BUTTON: {
        *node->value = DK_UI_Button(ctx, node->rect, node->text, node->focused);
      } break;

      case IMUI_NODE_TYPE_TEXT_FIELD: {
        assert(node->text_input_callback != NULL);
        DK_UI_TextInput(ctx, node->rect, node->text, node->focused, node->text_input_callback);
      } break;

      case IMUI_NODE_TYPE_SELECT: {
        DK_UI_Select(ctx, node->rect, node->focused, node->items, node->num_items, node->select_value);
      } break;

      case IMUI_NODE_TYPE_SWITCH: {
        DK_UI_Switch(ctx, node->text, node->rect, node->value, node->focused);
      } break;

      case IMUI_NODE_TYPE_SLIDER: {
        DK_UI_Slider(ctx, node->rect, node->slider_value, node->slider_min, node->slider_step, node->slider_max, node->focused);
      } break;

      case IMUI_NODE_TYPE_TEXT: {
        DK_GFX_SetFont(ctx->gfx_context, ctx->theme.font);
        DK_GFX_DrawText(ctx->gfx_context, &(DK_GFX_Text_Desc_t){
          .text = node->text,
          .pos = (DK_GFX_Point){ node->rect.x, node->rect.y },
          .color = ctx->theme.color_scheme.fg_color
        });
        DK_GFX_ResetFont(ctx->gfx_context);
      } break;

      case IMUI_NODE_TYPE_SPACER: {
        
      } break;

    }
  }
}

bool
IMUI_Is_Active(ImUI *ctx) {
  return (ctx->context.focused || ctx->context.hovered || ctx->context.pressed);
}

bool DK_UI_Button(ImUI *ctx, DK_GFX_Rect rect, char *text, bool *focused)
{
  DK_GFX_Context *gfx_context = ctx->gfx_context;
  ImUIColorScheme *color_scheme = &ctx->theme.color_scheme;
  ImUIStyle *style = &ctx->theme.style;

  DK_GFX_Color btn_color_normal = color_scheme->button_bg;
  DK_GFX_Color btn_color_hover = color_scheme->button_bg_hover;
  DK_GFX_Color btn_color_active = color_scheme->button_bg_active;

  DK_GFX_Color btn_color = btn_color_normal;

  static bool first_frame = true;
  if (first_frame) {
    rect.w -= style->border_width * 20;
    rect.h -= style->border_width * 20;

    rect.x += style->border_width * 10;
    rect.y += style->border_width * 10;

    first_frame = false;
  }

  int text_width = DK_GFX_GetTextWidth(gfx_context, text);
  int text_height = DK_GFX_GetTextHeight(gfx_context, text);

  if (rect.w < text_width) { rect.w = text_width + 10; }
  if (rect.h < text_height) { rect.h = text_height + 10; }

  BoundingBox bbox = {
    .x = rect.x,
    .y = rect.y,
    .width = rect.w,
    .height = rect.h
  };

  BoundingBox mouse_box = {
    .x = gfx_context->mouse.x,
    .y = gfx_context->mouse.y,
    .width = 1,
    .height = 1
  };

  *focused = DKCollision_BoundingBoxesAreColliding(&bbox, &mouse_box);

  if (*focused) { btn_color = btn_color_hover; }

  ctx->context.focused = *focused;

  SDL_SetRenderDrawColor(gfx_context->renderer, btn_color.r, btn_color.g, btn_color.b, btn_color.a);
  SDL_RenderFillRect(gfx_context->renderer, &rect);

  /* take following parameters from theme context @todo */

  if (style->border_width > 0) {

    int32_t border_radius = style->border_radius;
    int32_t border_width = style->border_width;

    DK_GFX_Color border_color = color_scheme->border_color;

    SDL_SetRenderDrawColor(gfx_context->renderer, border_color.r, border_color.g, border_color.b, border_color.a);

    // Top left
    SDL_RenderDrawLine(gfx_context->renderer, rect.x, rect.y + border_radius, rect.x, rect.y + rect.h - border_radius);
    SDL_RenderDrawLine(gfx_context->renderer, rect.x + border_radius, rect.y, rect.x + rect.w - border_radius, rect.y);

    // Top right
    SDL_RenderDrawLine(gfx_context->renderer, rect.x + rect.w, rect.y + border_radius, rect.x + rect.w, rect.y + rect.h - border_radius);
    SDL_RenderDrawLine(gfx_context->renderer, rect.x + rect.w - border_radius, rect.y, rect.x + rect.w - border_radius, rect.y);

    // Bottom left
    SDL_RenderDrawLine(gfx_context->renderer, rect.x, rect.y + rect.h - border_radius, rect.x + border_radius, rect.y + rect.h);
    SDL_RenderDrawLine(gfx_context->renderer, rect.x + border_radius, rect.y + rect.h, rect.x + border_radius, rect.y + rect.h - border_radius);

    // Bottom right
    SDL_RenderDrawLine(gfx_context->renderer, rect.x + rect.w, rect.y + rect.h - border_radius, rect.x + rect.w - border_radius, rect.y + rect.h);
    SDL_RenderDrawLine(gfx_context->renderer, rect.x + rect.w - border_radius, rect.y + rect.h, rect.x + rect.w - border_radius, rect.y + rect.h - border_radius);

    // Top
    SDL_RenderDrawLine(gfx_context->renderer, rect.x + border_radius, rect.y, rect.x + rect.w - border_radius, rect.y);
    SDL_RenderDrawLine(gfx_context->renderer, rect.x + border_radius, rect.y + border_width, rect.x + rect.w - border_radius, rect.y + border_width); 

    // Bottom
    SDL_RenderDrawLine(gfx_context->renderer, rect.x + border_radius, rect.y + rect.h, rect.x + rect.w - border_radius, rect.y + rect.h);
    SDL_RenderDrawLine(gfx_context->renderer, rect.x + border_radius, rect.y + rect.h - border_width, rect.x + rect.w - border_radius, rect.y + rect.h - border_width);

    // Left
    SDL_RenderDrawLine(gfx_context->renderer, rect.x, rect.y + border_radius, rect.x, rect.y + rect.h - border_radius); 
    SDL_RenderDrawLine(gfx_context->renderer, rect.x + border_width, rect.y + border_radius, rect.x + border_width, rect.y + rect.h - border_radius);

    // Right  
    SDL_RenderDrawLine(gfx_context->renderer, rect.x + rect.w, rect.y + border_radius, rect.x + rect.w, rect.y + rect.h - border_radius);
    SDL_RenderDrawLine(gfx_context->renderer, rect.x + rect.w - border_width, rect.y + border_radius, rect.x + rect.w - border_width, rect.y + rect.h - border_radius);

  } // @border 

  DK_GFX_SetFont(gfx_context, ctx->theme.font);

  /* default text alignment is @center */
  DK_GFX_Point position = {
    rect.x + rect.w / 2 - DK_GFX_GetTextWidth(gfx_context, text) / 2,
    rect.y + rect.h / 2 - DK_GFX_GetTextHeight(gfx_context, text) / 2
  };

  // if (style->text_alignment == IMUI_TEXT_ALIGN_LEFT) { // @left
  //   position.x = rect.x + 5;
  // }

  if (style->text_alignment == IMUI_TEXT_ALIGN_RIGHT) { // @right
    position.x = rect.x + rect.w - DK_GFX_GetTextWidth(gfx_context, text) - 5;
  }

  if (style->text_alignment == IMUI_TEXT_ALIGN_CENTER) { // @center
    position.x = rect.x + rect.w / 2 - DK_GFX_GetTextWidth(gfx_context, text) / 2;
  }

  DK_GFX_DrawTextOptimized(gfx_context, &(DK_GFX_Text_Desc_t){
    .text = text,
    .pos = position,
    .color = color_scheme->fg_color
  });
  DK_GFX_ResetFont(gfx_context);

  if (*focused) {

    static bool button_was_just_pressed = false;
    bool button_pressed = gfx_context->mouse_state & SDL_BUTTON(SDL_BUTTON_LEFT);
    
    bool was_released = !button_pressed && button_was_just_pressed;

    if (button_pressed && !button_was_just_pressed) {
      btn_color = btn_color_active;
      button_was_just_pressed = true;
      ctx->context.pressed = true;

      return false;

    } else if (was_released) {
      btn_color = btn_color_hover;
      ctx->context.pressed = false;
      button_was_just_pressed = false;

      return true;
    }
  }

  return false;
}

void
DK_UI_Frame(ImUI *ctx, ImUIFrame *frame) 
{
  DK_GFX_Context *gfx_context = ctx->gfx_context;
  ImUIColorScheme *color_scheme = &ctx->theme.color_scheme;
  ImUIStyle *style = &ctx->theme.style;

  BoundingBox bounding_box = {
    .x = frame->rect->x,
    .y = frame->rect->y,
    .width = frame->rect->w,
    .height = DK_GFX_GetTextHeight(gfx_context, frame->title)
  };

  BoundingBox fame_box = {
    .x = frame->rect->x,
    .y = frame->rect->y,
    .width = frame->rect->w,
    .height = frame->rect->h
  };

  static BoundingBox mouse_box = {
    .x = 0,
    .y = 0,
    .width = 10,
    .height = 10
  };

  static DK_GFX_Texture *target_texture = NULL;
  static Uint32 *pixels = NULL;

  const int32_t TEXTURE_WIDTH = 18;
  const int32_t TEXTURE_HEIGHT = 18;

  static DK_GFX_Rect old_frame_rect = { 0 };

  mouse_box.x = gfx_context->mouse.x;
  mouse_box.y = gfx_context->mouse.y;

  /* Origin - center mouse bounding box to mouse position */
  mouse_box.x -= mouse_box.width / 2;
  mouse_box.y -= mouse_box.height / 2;

  // BoundingBox debugging
  frame->hovered = DKCollision_BoundingBoxesAreColliding(&fame_box, &mouse_box) || DKCollision_BoundingBoxesAreColliding(&bounding_box, &mouse_box);
  bool is_pressed = frame->hovered && SDL_GetMouseState(&gfx_context->mouse.x, &gfx_context->mouse.y) & SDL_BUTTON(SDL_BUTTON_LEFT);

  if (is_pressed) {
    frame->dragging = true;
    ctx->context.drag_start = (DK_GFX_Point){ gfx_context->mouse.x, gfx_context->mouse.y };
  }

  if (!is_pressed && frame->dragging) {
    frame->dragging = false;
    ctx->context.drag_end = (DK_GFX_Point){ gfx_context->mouse.x, gfx_context->mouse.y };
  }

  /* Here we are expanding mouse bounding box when the frame is dragged around to avoid loosing intersection */
  if (frame->dragging) {
    mouse_box.width = 200;
    mouse_box.height = 200;
  } else {
    mouse_box.width = 10;
    mouse_box.height = 10;
  }

  frame->pressed = frame->dragging;
  frame->focused = frame->hovered && !frame->dragging;

  ctx->context.focused = frame->focused;
  ctx->context.hovered = frame->hovered;
  ctx->context.pressed = frame->pressed;

  static bool first_frame = true;
  if (first_frame) {
  
    frame->rect->w -= style->border_width * 2;
    frame->rect->h -= style->border_width * 2;

    frame->rect->x += style->border_width * 2;
    frame->rect->y += style->border_width * 2;

    // memorize old frame rect
    old_frame_rect.x = frame->rect->x;
    old_frame_rect.y = frame->rect->y;
    old_frame_rect.w = frame->rect->w;
    old_frame_rect.h = frame->rect->h;

    // generate target texture
    DK_GFX_Color bg_color = color_scheme->fg_color;
    target_texture = CreateCircle(gfx_context->renderer, TEXTURE_WIDTH, TEXTURE_HEIGHT, bg_color);
    first_frame = false;
  }

  // activate frame
  if (frame->focused) {
    ctx->context.active_frame_id = frame->id;
  }

  DK_GFX_SetFont(gfx_context, ctx->theme.font);  
  DK_GFX_DrawDebugRectFilled(gfx_context, &(DK_GFX_Debug_Rect_Desc_t) {
    .rect = (DK_GFX_Rect) {
      .x = frame->rect->x,
      .y = frame->rect->y,
      .w = frame->rect->w,
      .h = frame->rect->h
    },
    .color = color_scheme->bg_color
  });

  /* frame background */
  DK_GFX_DrawDebugRectFilled(gfx_context, &(DK_GFX_Debug_Rect_Desc_t) {
    .rect = (DK_GFX_Rect) {
      .x = frame->rect->x,
      .y = frame->rect->y,// + DK_GFX_GetTextHeight(gfx_context, frame->title),
      .w = frame->rect->w,
      .h = frame->rect->h,// - DK_GFX_GetTextHeight(gfx_context, frame->title)
    },
    .color = color_scheme->bg_color 
  });

  // @frame @border
  if (style->border_width > 0) {

    int32_t border_radius = style->border_radius;
    int32_t border_width = style->border_width;

    DK_GFX_Color border_color = color_scheme->border_color;

    SDL_SetRenderDrawColor(gfx_context->renderer, border_color.r, border_color.g, border_color.b, border_color.a);

    // Top
    SDL_RenderDrawLine(gfx_context->renderer, frame->rect->x + border_radius, frame->rect->y, frame->rect->x + frame->rect->w - border_radius, frame->rect->y);
    SDL_RenderDrawLine(gfx_context->renderer, frame->rect->x + border_radius, frame->rect->y + border_width, frame->rect->x + frame->rect->w - border_radius, frame->rect->y + border_width);

    // Bottom
    SDL_RenderDrawLine(gfx_context->renderer, frame->rect->x + border_radius, frame->rect->y + frame->rect->h, frame->rect->x + frame->rect->w - border_radius, frame->rect->y + frame->rect->h);
    SDL_RenderDrawLine(gfx_context->renderer, frame->rect->x + border_radius, frame->rect->y + frame->rect->h - border_width, frame->rect->x + frame->rect->w - border_radius, frame->rect->y + frame->rect->h - border_width);

    // Left
    SDL_RenderDrawLine(gfx_context->renderer, frame->rect->x, frame->rect->y + border_radius, frame->rect->x, frame->rect->y + frame->rect->h - border_radius);
    SDL_RenderDrawLine(gfx_context->renderer, frame->rect->x + border_width, frame->rect->y + border_radius, frame->rect->x + border_width, frame->rect->y + frame->rect->h - border_radius);

    // Right
    SDL_RenderDrawLine(gfx_context->renderer, frame->rect->x + frame->rect->w, frame->rect->y + border_radius, frame->rect->x + frame->rect->w, frame->rect->y + frame->rect->h - border_radius);
    SDL_RenderDrawLine(gfx_context->renderer, frame->rect->x + frame->rect->w - border_width, frame->rect->y + border_radius, frame->rect->x + frame->rect->w - border_width, frame->rect->y + frame->rect->h - border_radius);

  } // @border

  DK_GFX_Point title_position = {
    .x = frame->rect->x + frame->rect->w / 2 - DK_GFX_GetTextWidth(gfx_context, frame->title) / 2,
    .y = frame->rect->y + 5
  };

  bool is_text_aligned_left = style->text_alignment == IMUI_TEXT_ALIGN_LEFT;
  bool is_text_aligned_right = style->text_alignment == IMUI_TEXT_ALIGN_RIGHT;
  bool is_text_aligned_center = style->text_alignment == IMUI_TEXT_ALIGN_CENTER;

  if (is_text_aligned_center) {
    title_position.x = frame->rect->x + frame->rect->w / 2 - DK_GFX_GetTextWidth(gfx_context, frame->title) / 2;
  }

  if (is_text_aligned_left) {
    title_position.x = frame->rect->x + 5;
  }

  if (is_text_aligned_right) {
    title_position.x = frame->rect->x + frame->rect->w - DK_GFX_GetTextWidth(gfx_context, frame->title) - 5;
    title_position.x -= 20; // this is hacky, but it works, padding from action button
  }

  DK_GFX_DrawText(gfx_context, &(DK_GFX_Text_Desc_t){
    .text = frame->title,
    .pos = title_position,
    .color = color_scheme->fg_color
  });

  /* Action button */
  static char *action_button_text = " ";
  int32_t action_button_text_width = DK_GFX_GetTextWidth(gfx_context, action_button_text);
  int32_t action_button_text_height = DK_GFX_GetTextHeight(gfx_context, action_button_text);
  DK_GFX_Rect action_btn_rect = {
    .x = frame->rect->x + frame->rect->w - action_button_text_width - 14,
    .y = frame->rect->y + 3,
    .w = action_button_text_width + 10,
    .h = action_button_text_height + 1
  };

  ctx->theme.style.border_width = 0;
  ctx->theme.color_scheme.button_bg_hover.a = 0x00;
  ctx->theme.color_scheme.button_bg.a = 0x00; 
  
  if (DK_UI_Button(ctx, action_btn_rect, action_button_text, &frame->_action_button_focused)) {
    frame->_pinned = !frame->_pinned; 
  }

  ctx->theme.style.border_width = ImUI_Get_Default_Theme().style.border_width;
  ctx->theme.color_scheme.button_bg_hover.a = ImUI_Get_Default_Theme().color_scheme.button_bg_hover.a;
  ctx->theme.color_scheme.button_bg.a = ImUI_Get_Default_Theme().color_scheme.button_bg.a;

  if (frame->_pinned) {
    DK_GFX_SetTextureColorMod(target_texture, 0x7F, 0xAF, 0x00); // Orange
  } else {
    DK_GFX_SetTextureColorMod(target_texture, 0xFF, 0x00, 0x8F); // Pink
  }

  DK_GFX_DrawTexture(gfx_context, (DK_GFX_Texture_Desc_t) {
    .dst_rect = &(DK_GFX_Rect) {
      .x = action_btn_rect.x + action_btn_rect.w / 2 - TEXTURE_WIDTH / 2,
      .y = action_btn_rect.y + action_btn_rect.h / 2 - TEXTURE_HEIGHT / 2,
      .w = TEXTURE_WIDTH,
      .h = TEXTURE_HEIGHT
    },
    .texture = target_texture
  });

  DK_GFX_ResetFont(gfx_context);

  /* frame content border */
  if (style->border_width > 0) {

    int32_t border_radius = style->border_radius;
    int32_t border_width = style->border_width;
    DK_GFX_Color border_color = color_scheme->border_color;

    SDL_SetRenderDrawColor(gfx_context->renderer, border_color.r, border_color.g, border_color.b, border_color.a);

    // Top
    SDL_RenderDrawLine(gfx_context->renderer, frame->rect->x + border_radius, frame->rect->y + DK_GFX_GetTextHeight(gfx_context, frame->title), frame->rect->x + frame->rect->w - border_radius, frame->rect->y + DK_GFX_GetTextHeight(gfx_context, frame->title));
    SDL_RenderDrawLine(gfx_context->renderer, frame->rect->x + border_radius, frame->rect->y + DK_GFX_GetTextHeight(gfx_context, frame->title) + border_width, frame->rect->x + frame->rect->w - border_radius, frame->rect->y + DK_GFX_GetTextHeight(gfx_context, frame->title) + border_width);

    // Bottom
    SDL_RenderDrawLine(gfx_context->renderer, frame->rect->x + border_radius, frame->rect->y + frame->rect->h, frame->rect->x + frame->rect->w - border_radius, frame->rect->y + frame->rect->h);
    SDL_RenderDrawLine(gfx_context->renderer, frame->rect->x + border_radius, frame->rect->y + frame->rect->h - border_width, frame->rect->x + frame->rect->w - border_radius, frame->rect->y + frame->rect->h - border_width);

    // Left
    SDL_RenderDrawLine(gfx_context->renderer, frame->rect->x, frame->rect->y + DK_GFX_GetTextHeight(gfx_context, frame->title) + border_radius, frame->rect->x, frame->rect->y + frame->rect->h - border_radius);
    SDL_RenderDrawLine(gfx_context->renderer, frame->rect->x + border_width, frame->rect->y + DK_GFX_GetTextHeight(gfx_context, frame->title) + border_radius, frame->rect->x + border_width, frame->rect->y + frame->rect->h - border_radius);

    // Right
    SDL_RenderDrawLine(gfx_context->renderer, frame->rect->x + frame->rect->w, frame->rect->y + DK_GFX_GetTextHeight(gfx_context, frame->title) + border_radius, frame->rect->x + frame->rect->w, frame->rect->y + frame->rect->h - border_radius);
    SDL_RenderDrawLine(gfx_context->renderer, frame->rect->x + frame->rect->w - border_width, frame->rect->y + DK_GFX_GetTextHeight(gfx_context, frame->title) + border_radius, frame->rect->x + frame->rect->w - border_width, frame->rect->y + frame->rect->h - border_radius);

  } // @border

  /* [Begin] Content */
  if (frame->stack_layout != NULL) {
    DK_UI_Layout_VerticalStack(ctx, frame->stack_layout);
  }
  /* [/End] Content */

  if (ctx->context.active_frame_id == frame->id) {
    /* NOTE: We need to update positions after drawing, to avoid lagging */
    static int32_t previous_mouse_x = 0;
    static int32_t previous_mouse_y = 0;

    if (!frame->dragging) {
      /* Capture the mouse position when the drag starts */
      previous_mouse_x = gfx_context->mouse.x;
      previous_mouse_y = gfx_context->mouse.y;
    }

    /* Calculate the mouse delta */
    int32_t mouse_delta_x = gfx_context->mouse.x - previous_mouse_x;
    int32_t mouse_delta_y = gfx_context->mouse.y - previous_mouse_y;

    if (frame->focused || frame->hovered) {

      const Uint8 *kbrd_state = SDL_GetKeyboardState(NULL);
      const int32_t amount = 10;
      const int32_t min_width = old_frame_rect.w;
      const int32_t min_height = old_frame_rect.h;

      if (kbrd_state[SDL_SCANCODE_LCTRL] || kbrd_state[SDL_SCANCODE_RCTRL]) {
        if (kbrd_state[SDL_SCANCODE_J]) {

          if (frame->rect->w < min_width) return;

          frame->rect->w -= amount;

          if (frame->stack_layout != NULL) {
            for (int32_t i = 0; i < frame->stack_layout->num_nodes; i++) {
              ImNode *node = frame->stack_layout->nodes[i];
              if (node == NULL) continue;
              if (node->rect.w < frame->rect->w - 20) return;

              node->rect.w -= amount;
            }
          }
        }

        if (kbrd_state[SDL_SCANCODE_I]) {
          if (frame->rect->h < min_height) return;
          frame->rect->h -= amount;
        }

        if (kbrd_state[SDL_SCANCODE_L]) {
          frame->rect->w += amount;

          if (frame->stack_layout != NULL) {
            for (int32_t i = 0; i < frame->stack_layout->num_nodes; i++) {
              ImNode *node = frame->stack_layout->nodes[i];
              if (node == NULL) continue;
              if (node->rect.w >= frame->rect->w - 20) return;

              node->rect.w += amount;
            }
          }
        }

        if (kbrd_state[SDL_SCANCODE_K]) {
          frame->rect->h += amount;
        }
      }
    }

    /* Update the frame's position based on the mouse delta */
    if (!frame->_pinned) {
      frame->rect->x += mouse_delta_x;
      frame->rect->y += mouse_delta_y;
    } else {
      /* If the frame is pinned, we need to update the position of the nodes */ 
      frame->visible = false;
      frame->focused = false;
      frame->hovered = false;
      frame->pressed = false;
      ctx->context.active_frame_id = -1;
    }

    previous_mouse_x = gfx_context->mouse.x;
    previous_mouse_y = gfx_context->mouse.y;

  }

  if (frame->stack_layout != NULL) {
    for (int32_t i = 0; i < frame->stack_layout->num_nodes; i++) {
      ImNode *node = frame->stack_layout->nodes[i];
      if (node == NULL) continue;

      node->rect.x = frame->rect->x + 10; // Adjust the X-coordinate as needed (We have 10px padding at this point that is hardcoded) @fixme @todo @style
      node->rect.y = frame->rect->y + DK_GFX_GetTextHeight(gfx_context, frame->title) + node->rect.h;

      node->rect.y += (node->rect.h - 10) * i;
    }
  }

}

void
DK_UI_Select(ImUI *ctx, DK_GFX_Rect rect, bool *focused, char **items, int32_t num_items, int32_t *selected_item)
{
  DK_GFX_Context *gfx_context = ctx->gfx_context;
  ImUIColorScheme *color_scheme = &ctx->theme.color_scheme;
  ImUIStyle *style = &ctx->theme.style;

  bool *dropdown_open = focused;

  static bool _focused = false;

  BoundingBox bounding_box = {
    .x = rect.x,
    .y = rect.y,
    .width = rect.w,
    .height = rect.h
  };

  BoundingBox mouse_box = {
    .x = gfx_context->mouse.x,
    .y = gfx_context->mouse.y,
    .width = 1,
    .height = 1
  };

  _focused = DKCollision_BoundingBoxesAreColliding(&bounding_box, &mouse_box);

  if (DK_UI_Button(ctx, rect, items[*selected_item], &_focused)) {
    *dropdown_open = !*dropdown_open;
  }

  if (*dropdown_open) {

    DK_GFX_Rect dropdown_rect = {
      .x = rect.x,
      .y = rect.y + rect.h,
      .w = rect.w,
      .h = rect.h * num_items
    };

    DK_GFX_DrawDebugRectFilled(gfx_context, &(DK_GFX_Debug_Rect_Desc_t) {
      .rect = dropdown_rect,
      .color = (DK_GFX_Color){ 0x00, 0x00, 0x00, 0x90 }
    });

    for (int32_t i = 0; i < num_items; i++) {

      DK_GFX_Rect item_rect = {
        .x = rect.x,
        .y = rect.y + rect.h * (i + 1),
        .w = rect.w,
        .h = rect.h
      };

      if (DK_UI_Button(ctx, item_rect, items[i], &_focused)) {
        *selected_item = i;
        *dropdown_open = false;
      }
    }
  }
}

void
DK_UI_TextInput(ImUI *ctx, DK_GFX_Rect rect, char *buffer, bool *focused, DK_UI_TextInput_Callback callback)
{

  DK_GFX_Context *gfx_context = ctx->gfx_context;
  ImUIColorScheme *color_scheme = &ctx->theme.color_scheme;
  ImUIStyle *style = &ctx->theme.style;

  static int32_t text_index = 0;

  BoundingBox bounding_box = {
    .x = rect.x,
    .y = rect.y,
    .width = rect.w,
    .height = rect.h
  };

  BoundingBox mouse_box = {
    .x = gfx_context->mouse.x,
    .y = gfx_context->mouse.y,
    .width = 1,
    .height = 1
  };

  if (gfx_context->mouse_state & SDL_BUTTON(SDL_BUTTON_LEFT)) {
    *focused = DKCollision_BoundingBoxesAreColliding(&bounding_box, &mouse_box);
  }

  DK_GFX_Color color = color_scheme->bg_color; // @input @box @color
  DK_GFX_DrawDebugRectFilled(gfx_context, &(DK_GFX_Debug_Rect_Desc_t) {
    .rect = rect,
    .color = color
  });

  int32_t border_radius = style->border_radius;
  int32_t border_width = style->border_width;

  DK_GFX_Color border_color = color_scheme->border_color;
  DK_GFX_Color bg_color = color_scheme->input_text_bg;
  static DK_GFX_Color border_color_hover = { 0x00, 0xFC, 0x00, 0xFF };

  DK_GFX_DrawDebugRectFilled(gfx_context, &(DK_GFX_Debug_Rect_Desc_t) {
    .rect = rect,
    .color = bg_color
  });

  if (style->border_width > 0) {

    if (*focused) {
      border_color = (DK_GFX_Color) {
        .r = (uint8_t)(sin(SDL_GetTicks() / 100.0f) * 127.0f + 128.0f),
        .g = (uint8_t)(sin(SDL_GetTicks() / 100.0f + 2) * 127.0f + 128.0f),
        .b = (uint8_t)(sin(SDL_GetTicks() / 100.0f + 4) * 127.0f + 128.0f),
        .a = 0xFF
      };
    } else {
      border_color = color_scheme->border_color;
    }

    SDL_SetRenderDrawColor(gfx_context->renderer, border_color.r, border_color.g, border_color.b, border_color.a);

    // Top left
    SDL_RenderDrawLine(gfx_context->renderer, rect.x, rect.y + border_radius, rect.x, rect.y + rect.h - border_radius);
    SDL_RenderDrawLine(gfx_context->renderer, rect.x + border_radius, rect.y, rect.x + rect.w - border_radius, rect.y);

    // Top right
    SDL_RenderDrawLine(gfx_context->renderer, rect.x + rect.w, rect.y + border_radius, rect.x + rect.w, rect.y + rect.h - border_radius);
    SDL_RenderDrawLine(gfx_context->renderer, rect.x + rect.w - border_radius, rect.y, rect.x + rect.w - border_radius, rect.y);

    // Bottom left
    SDL_RenderDrawLine(gfx_context->renderer, rect.x, rect.y + rect.h - border_radius, rect.x + border_radius, rect.y + rect.h);
    SDL_RenderDrawLine(gfx_context->renderer, rect.x + border_radius, rect.y + rect.h, rect.x + border_radius, rect.y + rect.h - border_radius);

    // Bottom right
    SDL_RenderDrawLine(gfx_context->renderer, rect.x + rect.w, rect.y + rect.h - border_radius, rect.x + rect.w - border_radius, rect.y + rect.h);
    SDL_RenderDrawLine(gfx_context->renderer, rect.x + rect.w - border_radius, rect.y + rect.h, rect.x + rect.w - border_radius, rect.y + rect.h - border_radius);

    // Top
    SDL_RenderDrawLine(gfx_context->renderer, rect.x + border_radius, rect.y, rect.x + rect.w - border_radius, rect.y);
    SDL_RenderDrawLine(gfx_context->renderer, rect.x + border_radius, rect.y + border_width, rect.x + rect.w - border_radius, rect.y + border_width);

    // Bottom
    SDL_RenderDrawLine(gfx_context->renderer, rect.x + border_radius, rect.y + rect.h, rect.x + rect.w - border_radius, rect.y + rect.h);
    SDL_RenderDrawLine(gfx_context->renderer, rect.x + border_radius, rect.y + rect.h - border_width, rect.x + rect.w - border_radius, rect.y + rect.h - border_width);

    // Left
    SDL_RenderDrawLine(gfx_context->renderer, rect.x, rect.y + border_radius, rect.x, rect.y + rect.h - border_radius);
    SDL_RenderDrawLine(gfx_context->renderer, rect.x + border_width, rect.y + border_radius, rect.x + border_width, rect.y + rect.h - border_radius);

    // Right
    SDL_RenderDrawLine(gfx_context->renderer, rect.x + rect.w, rect.y + border_radius, rect.x + rect.w, rect.y + rect.h - border_radius);
    SDL_RenderDrawLine(gfx_context->renderer, rect.x + rect.w - border_width, rect.y + border_radius, rect.x + rect.w - border_width, rect.y + rect.h - border_radius);
  } // @border

  DK_GFX_SetFont(gfx_context, ctx->theme.font);
  DK_GFX_Point position = {
    rect.x + 5,
    rect.y + rect.h / 2 - DK_GFX_GetTextHeight(gfx_context, buffer) / 2
  };
  DK_GFX_ResetFont(gfx_context);

  if (*focused) {
    if (strlen(gfx_context->input_text_buffer) > 0) {
      SDL_strlcpy(buffer, gfx_context->input_text_buffer, sizeof(char) * 1024);
    } else {
      buffer[0] = '\0';
      gfx_context->input_text_buffer[0] = '\0';
    }

    int32_t size_of_char = DK_GFX_GetTextWidthFor(ctx->theme.font, "A");
    int32_t max_len = rect.w / size_of_char;

    if (strlen(buffer) >= (size_t)max_len) {
      buffer[max_len - 1] = '\0';
      gfx_context->input_text_buffer[max_len - 1] = '\0';
    }

    // @cursor
    DK_GFX_Color cursor_color = (DK_GFX_Color){ 0xFF, 0xFF, 0xFF, 0xFF };
    if (SDL_GetTicks() / 100.f) { // in every 100ms
      cursor_color = (DK_GFX_Color) {
        .r = (uint8_t)(sin(SDL_GetTicks() / 127.0f) * color_scheme->input_text_cursor.r),
        .g = (uint8_t)(sin(SDL_GetTicks() / 127.0f) * color_scheme->input_text_cursor.g),
        .b = (uint8_t)(sin(SDL_GetTicks() / 127.0f) * color_scheme->input_text_cursor.b),
        .a = 0xFF
      };
    } else {
      cursor_color = (DK_GFX_Color){ 0xFF, 0xFF, 0xFF, 0xFF };
    }

    DK_GFX_SetFont(gfx_context, ctx->theme.font);

    int32_t cursor_width = 8;
    int32_t cursor_height = 10;

    int32_t cursor_x = position.x + DK_GFX_GetTextWidthFor(ctx->theme.font, buffer) + 2;
    int32_t cursor_y = position.y + (rect.h - cursor_height);
    if (rect.h > 20) {
      cursor_y = position.y + (rect.h - cursor_height) / 2;
    }

    DK_GFX_Rect cursor_rect = {
      cursor_x,
      cursor_y,
      cursor_width,
      cursor_height
    };

    DK_GFX_DrawDebugRectFilled(gfx_context, &(DK_GFX_Debug_Rect_Desc_t){
      .rect = cursor_rect,
      .color = cursor_color
    });

    DK_GFX_ResetFont(gfx_context);

    const Uint8 *state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_RETURN] && strlen(buffer) > 0) {
      if (callback != NULL) callback(buffer);
      gfx_context->input_text_buffer[0] = '\0';
      buffer[0] = '\0';
      *focused = false;
    }
  }

  if (strlen(buffer) > 0) {
    DK_GFX_SetFont(gfx_context, ctx->theme.font);
    DK_GFX_DrawTextOptimized(gfx_context, &(DK_GFX_Text_Desc_t) {
      .text = buffer,
      .pos = position,
      .color = color_scheme->input_text_fg
    });
    DK_GFX_ResetFont(gfx_context);
  }
}

void
DK_UI_Switch(ImUI *ctx, char* label, DK_GFX_Rect rect, bool *value, bool *focused)
{
  DK_GFX_Context *gfx_context = ctx->gfx_context;
  ImUIColorScheme *color_scheme = &ctx->theme.color_scheme;
  ImUIStyle *style = &ctx->theme.style;

  DK_GFX_Color disabled_color = DK_GFX_GRAY; // @switch @color
  DK_GFX_Color enabled_color = DK_GFX_ColorMix(disabled_color, DK_GFX_GREEN, 0.4); // @switch @color

  BoundingBox bounding_box = {
    .x = rect.x,
    .y = rect.y,
    .width = rect.w,
    .height = rect.h
  };

  BoundingBox mouse_box = {
    .x = gfx_context->mouse.x,
    .y = gfx_context->mouse.y,
    .width = 1,
    .height = 1
  };

  static DK_GFX_Texture *target_texture = NULL;
  static Uint32 *pixels = NULL;

  static bool first_frame = true;

  const int32_t TEXTURE_WIDTH = 16;
  const int32_t TEXTURE_HEIGHT = 16;

  if (first_frame) {
    
    target_texture = CreateCircle(gfx_context->renderer, TEXTURE_WIDTH, TEXTURE_HEIGHT, DK_GFX_WHITE);
    first_frame = false;
  }

  *focused = DKCollision_BoundingBoxesAreColliding(&bounding_box, &mouse_box);

  DK_GFX_SetFont(gfx_context, ctx->theme.font);
  int32_t label_w = DK_GFX_GetTextWidth(gfx_context, label);
  DK_GFX_Rect btn_rect = {
    .x = rect.x,
    .y = rect.y,
    .w = rect.w + label_w - 20,
    .h = rect.h
  };
  DK_GFX_ResetFont(gfx_context);

  if (DK_UI_Button(ctx, btn_rect, " ", focused)) {
    *value = !*value;
  }

  // Draw Text 
  DK_GFX_SetFont(gfx_context, ctx->theme.font);
  int32_t padd = 8;
  DK_GFX_Point position = {
    .x = rect.x + TEXTURE_WIDTH + padd,
    .y = rect.y + rect.h / 2 - DK_GFX_GetTextHeight(gfx_context, label) / 2 - 1
  };

  DK_GFX_DrawTextOptimized(gfx_context, &(DK_GFX_Text_Desc_t) {
    .text = label,
    .pos = position,
    .color = color_scheme->fg_color
  });

  DK_GFX_ResetFont(gfx_context);

  if (!*value) {
    DK_GFX_SetTextureColorMod(target_texture, disabled_color.r, disabled_color.g, disabled_color.b);
  } else {
    DK_GFX_SetTextureColorMod(target_texture, enabled_color.r, enabled_color.g, enabled_color.b);
  }

  DK_GFX_DrawTexture(gfx_context, (DK_GFX_Texture_Desc_t) {
    .texture = target_texture,
    .dst_rect = &(DK_GFX_Rect) {
      rect.x + 5,
      rect.y + rect.h / 2 - TEXTURE_HEIGHT / 2,
      TEXTURE_WIDTH,
      TEXTURE_HEIGHT
    },
  });
}

void
DK_UI_Slider(ImUI *ctx, DK_GFX_Rect rect, float *value, float step, float min, float max, bool *focused)
{
  DK_GFX_Context *gfx_context = ctx->gfx_context;
  ImUIColorScheme *color_scheme = &ctx->theme.color_scheme;
  ImUIStyle *style = &ctx->theme.style;

  BoundingBox bounding_box = {
    .x = rect.x - 10,
    .y = rect.y - 10,
    .width = rect.w + 20,
    .height = rect.h + 20
  };

  BoundingBox mouse_box = {
    .x = gfx_context->mouse.x - 5,
    .y = gfx_context->mouse.y - 5,
    .width = 10,
    .height = 10
  };

  DK_GFX_Color bg_color = color_scheme->bg_color; /* @slider @color */
  DK_GFX_Color line_color = color_scheme->button_bg_hover; /* @slider @color */
  DK_GFX_Color knot_color = color_scheme->button_bg_active; /* @slider @color */

  static bool first_frame = true;

  static DK_GFX_Texture *target_texture = NULL;
  
  const int32_t TEXTURE_WIDTH = 24;
  const int32_t TEXTURE_HEIGHT = 24;

  if (first_frame) {
    target_texture = CreateCircle(gfx_context->renderer, TEXTURE_WIDTH, TEXTURE_HEIGHT, knot_color);
    first_frame = false;
  }

  static bool button_pressed = false;
  if (DKCollision_BoundingBoxesAreColliding(&bounding_box, &mouse_box)) {
    button_pressed = gfx_context->mouse_state & SDL_BUTTON(SDL_BUTTON_LEFT);
  }

  static Uint32 prevMouseState = 0;
  if ((prevMouseState & SDL_BUTTON(SDL_BUTTON_LEFT)) && !(gfx_context->mouse_state & SDL_BUTTON(SDL_BUTTON_LEFT))) {
    button_pressed = false;
  }

  prevMouseState = gfx_context->mouse_state;

  DK_GFX_DrawDebugRectFilled(gfx_context, &(DK_GFX_Debug_Rect_Desc_t) {
    .rect = {
      .x = rect.x,
      .y = rect.y + rect.h / 2 - 1,
      .w = rect.w,
      .h = 5
    },
    .color = bg_color
  });

  DK_GFX_SetDrawColor(gfx_context->renderer, line_color);
  DK_GFX_DrawLine(gfx_context->renderer, rect.x, rect.y + rect.h / 2, rect.x + rect.w, rect.y + rect.h / 2);

  float slider_x = rect.x + rect.w * (*value / max);

  DK_GFX_DrawTexture(gfx_context, (DK_GFX_Texture_Desc_t){
    .texture = target_texture,
    .src_rect = NULL,
    .dst_rect = &(DK_GFX_Rect){
      .x = slider_x - TEXTURE_WIDTH / 2,
      .y = rect.y + rect.h / 2 - TEXTURE_HEIGHT / 2,
      .w = TEXTURE_WIDTH,
      .h = TEXTURE_HEIGHT
    }
  });

  bool is_dragging = false;
  is_dragging = (button_pressed);

  static const float ANIMATION_DURATION = 100.0f;

  if (is_dragging) {
    float mouse_x = gfx_context->mouse.x;
    float mouse_y = gfx_context->mouse.y;

    float normalizedPosition = SDL_clamp((mouse_x - bounding_box.x) / bounding_box.width, 0.0f, 1.0f);
    float targetValue = normalizedPosition * max;
    float valueChange = targetValue - *value;
    float interpolationFactor = fmin(1.0f, gfx_context->dt / ANIMATION_DURATION);
    *value += valueChange * interpolationFactor;
  }
}

void
DK_UI_ColorPicker(ImUI *ctx, DK_GFX_Rect *frame_rect, int32_t frame_id, DK_GFX_Color *color, bool *focused) {
  static LayoutVerticalStack *stack = NULL;
  static bool first_frame = true;

  // TODO (David): use layout stack for children, instead of manually calculating the positions
  if (first_frame) {
    stack = (LayoutVerticalStack*)malloc(sizeof(LayoutVerticalStack));
    DK_UI_Layout_VerticalStack_Init(ctx, stack);
    first_frame = false;
  }

  static ImUIFrame frame = {
    .title = "Color Picker",
    ._pinned = true,
  };

  frame.stack_layout = stack;
  frame.id = frame_id;
  frame.rect = frame_rect;
  frame.visible = focused;

  DK_UI_Frame(ctx, &frame);

  DK_GFX_Rect rect = { 0 };

  rect.w = frame.rect->w - 20;
  rect.h = frame.rect->h - 250;
  rect.x = frame.rect->x + 10;

  DK_GFX_SetFont(ctx->gfx_context, ctx->theme.font);
  rect.y = frame.rect->y + 10 + DK_GFX_GetTextHeight(ctx->gfx_context, frame.title) + 10;
  DK_GFX_ResetFont(ctx->gfx_context);

  DK_GFX_Context *gfx_context = ctx->gfx_context;
  ImUIColorScheme *color_scheme = &ctx->theme.color_scheme;
  ImUIStyle *style = &ctx->theme.style;

  bool button_pressed = gfx_context->mouse_state & SDL_BUTTON(SDL_BUTTON_LEFT); 

  BoundingBox bounding_box = {
    .x = rect.x,
    .y = rect.y,
    .width = rect.w,
    .height = rect.h
  };

  BoundingBox mouse_box = {
    .x = gfx_context->mouse.x,
    .y = gfx_context->mouse.y,
    .width = 1,
    .height = 1
  };

  int32_t textureWidth = rect.w;
  int32_t textureHeight = rect.h;

  static bool is_first_frame = true;

  static SDL_Texture* gradientTexture = NULL;
  static Uint32* pixels = NULL;

  *focused = DKCollision_BoundingBoxesAreColliding(&bounding_box, &mouse_box);
  
  if (is_first_frame) {

    gradientTexture = SDL_CreateTexture(gfx_context->renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, textureWidth, textureHeight);
    pixels = (Uint32*)malloc(sizeof(Uint32) * textureWidth * textureHeight);

    for (int32_t y = 0; y < textureHeight; y++) {
      for (int32_t x = 0; x < textureWidth; x++) {
        Uint8 r = (Uint8)(255 * (float)x / textureWidth);
        Uint8 g = (Uint8)(255 * (float)y / textureHeight);
        Uint8 b = 0xFF;
        Uint8 a = 0xFF;
        pixels[y * textureWidth + x] = (a << 24) + (r << 16) + (g << 8) + b;
      }
    }

    SDL_UpdateTexture(gradientTexture, NULL, pixels, textureWidth * sizeof(Uint32));
    is_first_frame = false;
  }

  static DK_GFX_Rect cursor = {
    .w = 10,
    .h = 10
  };

  DK_GFX_Color rainbow_color = {
    .r = (uint8_t)(sin(SDL_GetTicks() / 100.0f) * 127.0f + 128.0f),
    .g = (uint8_t)(sin(SDL_GetTicks() / 100.0f + 2) * 127.0f + 128.0f),
    .b = (uint8_t)(sin(SDL_GetTicks() / 100.0f + 4) * 127.0f + 128.0f),
    .a = 0xFF
  };

  if (!is_first_frame) {
    SDL_UpdateTexture(gradientTexture, NULL, pixels, textureWidth * sizeof(Uint32));
    SDL_RenderCopy(gfx_context->renderer, gradientTexture, NULL, &(DK_GFX_Rect) {
      .x = rect.x,
      .y = rect.y,
      .w = rect.w,
      .h = rect.h
    });
    DK_GFX_SetDrawColor(gfx_context->renderer, rainbow_color);

    // the cursor
    if (*focused) {
      DK_GFX_DrawLine(gfx_context->renderer, gfx_context->mouse.x, rect.y, gfx_context->mouse.x, rect.y + rect.h);
      DK_GFX_DrawLine(gfx_context->renderer, rect.x, gfx_context->mouse.y, rect.x + rect.w, gfx_context->mouse.y);
    }
  }

  BoundingBox cursor_bb = {
    .x = cursor.x,
    .y = cursor.y,
    .width = cursor.w,
    .height = cursor.h
  };

  if (DKCollision_BoundingBoxesAreColliding(&bounding_box, &cursor_bb)) {
    DK_GFX_DrawDebugRectFilled(gfx_context, &(DK_GFX_Debug_Rect_Desc_t) {
      .rect = (DK_GFX_Rect) {
        .x = cursor.x - 2,
        .y = cursor.y - 2,
        .w = 14,
        .h = 14
      },
      .color = (DK_GFX_Color){ 0xFF, 0xFF, 0x00, 0xFF } // YELLOW
    });

    DK_GFX_DrawDebugRectFilled(gfx_context, &(DK_GFX_Debug_Rect_Desc_t) {
      .rect = cursor,
      .color = *color
    });
  }

  if (*focused && button_pressed) {
    color->r = (unsigned char)(255 * (gfx_context->mouse.x - bounding_box.x) / bounding_box.width);
    color->g = (unsigned char)(255 * ((gfx_context->mouse.y - bounding_box.y) / bounding_box.height));
    
    color->b = 0xFF;
    color->a = 0xFF;

    cursor.x = gfx_context->mouse.x - 5;
    cursor.y = gfx_context->mouse.y - 5;

    if (cursor.x < rect.x) cursor.x = rect.x;
    if (cursor.x > rect.x + rect.w) cursor.x = rect.x + rect.w;
    if (cursor.y < rect.y) cursor.y = rect.y;
    if (cursor.y > rect.y + rect.h) cursor.y = rect.y + rect.h;

    frame._pinned = true;
  } else {
    // frame._pinned = false;
  }

  // Hue lable
  DK_GFX_SetFont(ctx->gfx_context, ctx->theme.font);
  DK_GFX_Point position = {
    rect.x,
    rect.y + rect.h + 10
  };

  char *hue_label = "Hue";
  DK_GFX_DrawText(ctx->gfx_context, &(DK_GFX_Text_Desc_t) {
    .text = hue_label,
    .pos = position,
    .color = color_scheme->fg_color
  });

  // Hue slider
  DK_GFX_Rect slider_rect = {
    .x = rect.x,
    .y = rect.y + rect.h + 10 + DK_GFX_GetTextHeight(ctx->gfx_context, hue_label) + 10,
    .w = rect.w,
    .h = 30
  };

  static float hue = 10.f;
  static bool hue_focused = false;

  DK_UI_Slider(ctx, slider_rect, &hue, 1.0f, 1.0f, 255.0f, &hue_focused);
  color->b = (Uint8)hue * 255.0f;

  DK_GFX_ResetFont(ctx->gfx_context);

  // Alpha label
  DK_GFX_SetFont(ctx->gfx_context, ctx->theme.font);
  position = (DK_GFX_Point) {
    rect.x,
    slider_rect.y + slider_rect.h + 10
  };

  char *alpha_label = "Alpha";
  DK_GFX_DrawText(ctx->gfx_context, &(DK_GFX_Text_Desc_t) {
    .text = alpha_label,
    .pos = position,
    .color = color_scheme->fg_color
  });

  // Alpha slider
  slider_rect = (DK_GFX_Rect) {
    .x = rect.x,
    .y = slider_rect.y + slider_rect.h + 10 + DK_GFX_GetTextHeight(ctx->gfx_context, alpha_label) + 10,
    .w = rect.w,
    .h = 30
  };

  static float alpha = 10.f;
  static bool alpha_focused = false;

  DK_UI_Slider(ctx, slider_rect, &alpha, 1.0f, 1.0f, 255.0f, &alpha_focused);
  DK_UI_Slider(ctx, slider_rect, &alpha, 1.0f, 1.0f, 255.0f, &alpha_focused);

  DK_UI_Slider(ctx, slider_rect, &alpha, 1.0f, 1.0f, 255.0f, &alpha_focused);

  color->a = (Uint8)alpha * 255.0f;

  DK_GFX_ResetFont(ctx->gfx_context);

  DK_GFX_SetFont(ctx->gfx_context, ctx->theme.font);
  position = (DK_GFX_Point) {
    rect.x,
    slider_rect.y + slider_rect.h + 10
  };

  char color_label[255] = { 0 };
  sprintf(color_label, "%d %d %d %d", color->r, color->g, color->b, color->a);
  DK_GFX_DrawText(ctx->gfx_context, &(DK_GFX_Text_Desc_t) {
    .text = color_label,
    .pos = position,
    .color = color_scheme->fg_color
  });

  // bottom right corner draw color rect
  DK_GFX_Rect color_rect = {
    .x = frame_rect->x + frame_rect->w - 30,
    .y = frame_rect->y + frame_rect->h - 42,
    .w = 20,
    .h = 20
  };

  DK_GFX_DrawDebugRectFilled(ctx->gfx_context, &(DK_GFX_Debug_Rect_Desc_t) {
    .rect = color_rect,
    .color = *color
  });

  rect.w = frame.rect->w - 20;
  rect.h = frame.rect->h - 250;
  rect.x = frame.rect->x + 10;
}


#endif // DK_UI_IMPLEMENTATION

#endif // DK_UI_H
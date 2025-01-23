/**
 * @file dk_gfx.h
 * @author David Kviloria (dkviloria@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-07-05
 *
 * @copyright Copyright (c) 2023 SKYSTAR GAMES Interactive
 *
 */
#if !defined(DK_GFX_H)
#define DK_GFX_H

#include <stdint.h>
#include <stdbool.h>
#include <assert.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#ifdef USE_SDL2_MIXER_BACKEND
#include <SDL2/SDL_mixer.h>
#endif

#if defined(PLATFORM_WEB)
#  include <emscripten.h>
#  include <emscripten/html5.h>
#endif

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

#define DK_GFX_VERSION_MAJOR 1
#define DK_GFX_VERSION_MINOR 0
#define DK_GFX_VERSION_PATCH 0

#define DK_API static inline __attribute__((always_inline))

#define DK_MALLOC SDL_malloc
#define DK_REALLOC SDL_calloc
#define DK_FREE SDL_free

typedef SDL_Point DK_GFX_Point;
typedef SDL_FPoint DK_GFX_FPoint;
typedef SDL_Rect DK_GFX_Rect;
typedef SDL_Color DK_GFX_Color;

typedef SDL_Surface DK_GFX_Surface;

typedef SDL_Window DK_GFX_Window;
typedef SDL_Renderer DK_GFX_Renderer;
typedef SDL_Texture DK_GFX_Texture;
typedef SDL_Event DK_GFX_Event;
typedef SDL_EventType DK_GFX_EventType;

#ifdef USE_SDL2_MIXER_BACKEND
typedef Mix_Music DK_GFX_Music;
typedef Mix_Chunk DK_GFX_AudioFx;
#endif

typedef SDL_RWops DK_GFX_RWops;
typedef SDL_RendererFlip DK_GFX_RendererFlip;

typedef SDL_BlendMode DK_GFX_BlendMode;

#define DK_GFX_BLEND_NONE SDL_BLENDMODE_NONE
#define DK_GFX_BLEND_ALPHA SDL_BLENDMODE_BLEND
#define DK_GFX_BLEND_ADD SDL_BLENDMODE_ADD
#define DK_GFX_BLEND_MOD SDL_BLENDMODE_MOD
#define DK_GFX_BLEND_MUL SDL_BLENDMODE_MUL

#define DK_GFX_WINDOWPOS_UNDEFINED_MASK SDL_WINDOWPOS_UNDEFINED_MASK
#define DK_GFX_WINDOWPOS_CENTERED_MASK SDL_WINDOWPOS_CENTERED_MASK

#define DK_GFX_WINDOWPOS_CENTERED SDL_WINDOWPOS_CENTERED
#define DK_GFX_WINDOWPOS_UNDEFINED SDL_WINDOWPOS_UNDEFINED

#define DK_GFX_WINDOW_FULLSCREEN SDL_WINDOW_FULLSCREEN
#define DK_GFX_WINDOW_FULLSCREEN_DESKTOP SDL_WINDOW_FULLSCREEN_DESKTOP

#define DK_GFX_WINDOW_OPENGL SDL_WINDOW_OPENGL
#define DK_GFX_WINDOW_SHOWN SDL_WINDOW_SHOWN
#define DK_GFX_WINDOW_HIDDEN SDL_WINDOW_HIDDEN
#define DK_GFX_WINDOW_BORDERLESS SDL_WINDOW_BORDERLESS
#define DK_GFX_WINDOW_RESIZABLE SDL_WINDOW_RESIZABLE
#define DK_GFX_WINDOW_MINIMIZED SDL_WINDOW_MINIMIZED
#define DK_GFX_WINDOW_MAXIMIZED SDL_WINDOW_MAXIMIZED
#define DK_GFX_WINDOW_INPUT_GRABBED SDL_WINDOW_INPUT_GRABBED
#define DK_GFX_WINDOW_INPUT_FOCUS SDL_WINDOW_INPUT_FOCUS
#define DK_GFX_WINDOW_MOUSE_FOCUS SDL_WINDOW_MOUSE_FOCUS
#define DK_GFX_WINDOW_FULLSCREEN_DESKTOP SDL_WINDOW_FULLSCREEN_DESKTOP
#define DK_GFX_WINDOW_FOREIGN SDL_WINDOW_FOREIGN
#define DK_GFX_WINDOW_ALLOW_HIGHDPI SDL_WINDOW_ALLOW_HIGHDPI

#define DK_GFX_EVENT_QUIT SDL_QUIT

#define DK_GFX_FLIP_NONE SDL_FLIP_NONE
#define DK_GFX_FLIP_HORIZONTAL SDL_FLIP_HORIZONTAL
#define DK_GFX_FLIP_VERTICAL SDL_FLIP_VERTICAL

#define DK_GFX_AUDI_FX_LOOP -1
#define DK_GFX_AUDI_FX_PALY_ONCE 0

#define DK_GFX_WHITE      (DK_GFX_Color) { .r = 255, .g = 255, .b = 255, .a = 255 }
#define DK_GFX_BLACK      (DK_GFX_Color) { .r = 0, .g = 0, .b = 0, .a = 255 }
#define DK_GFX_RED        (DK_GFX_Color) { .r = 255, .g = 0, .b = 0, .a = 255 }
#define DK_GFX_GREEN      (DK_GFX_Color) { .r = 0, .g = 255, .b = 0, .a = 255 }
#define DK_GFX_BLUE       (DK_GFX_Color) { .r = 0, .g = 0, .b = 255, .a = 255 }
#define DK_GFX_YELLOW     (DK_GFX_Color) { .r = 255, .g = 255, .b = 0, .a = 255 }
#define DK_GFX_CYAN       (DK_GFX_Color) { .r = 0, .g = 255, .b = 255, .a = 255 }
#define DK_GFX_MAGENTA    (DK_GFX_Color) { .r = 255, .g = 0, .b = 255, .a = 255 }
#define DK_GFX_ORANGE     (DK_GFX_Color) { .r = 255, .g = 165, .b = 0, .a = 255 }
#define DK_GFX_PURPLE     (DK_GFX_Color) { .r = 128, .g = 0, .b = 128, .a = 255 }
#define DK_GFX_PINK       (DK_GFX_Color) { .r = 255, .g = 192, .b = 203, .a = 255 }
#define DK_GFX_BROWN      (DK_GFX_Color) { .r = 165, .g = 42, .b = 42, .a = 255 }
#define DK_GFX_GRAY       (DK_GFX_Color) { .r = 128, .g = 128, .b = 128, .a = 255 }
#define DK_GFX_LIGHTGRAY  (DK_GFX_Color) { .r = 211, .g = 211, .b = 211, .a = 255 }
#define DK_GFX_DARKGRAY   (DK_GFX_Color) { .r = 169, .g = 169, .b = 169, .a = 255 }
#define DK_GFX_CYAN       (DK_GFX_Color) { .r = 0, .g = 255, .b = 255, .a = 255 }
#define DK_GFX_VIOLET     (DK_GFX_Color) { .r = 238, .g = 130, .b = 238, .a = 255 }
#define DK_GFX_INDIGO     (DK_GFX_Color) { .r = 75, .g = 0, .b = 130, .a = 255 }
#define DK_GFX_NAVY       (DK_GFX_Color) { .r = 0, .g = 0, .b = 128, .a = 255 }
#define DK_GFX_TURQUOISE  (DK_GFX_Color) { .r = 64, .g = 224, .b = 208, .a = 255 }
#define DK_GFX_SKYBLUE    (DK_GFX_Color) { .r = 135, .g = 206, .b = 235, .a = 255 }
#define DK_GFX_LIGHTBLUE  (DK_GFX_Color) { .r = 173, .g = 216, .b = 230, .a = 255 }

typedef enum DK_GFX_TEXTURE
{
  DK_GFX_TEXTURE_0,
  DK_GFX_TEXTURE_1,
  DK_GFX_TEXTURE_2,
  DK_GFX_TEXTURE_3,
  DK_GFX_TEXTURE_4,
  DK_GFX_TEXTURE_5,
  DK_GFX_TEXTURE_6,
  DK_GFX_TEXTURE_COUNT
} DK_GFX_TEXTURE;

typedef enum DK_GFX_MUSIC
{
  DK_GFX_MUSIC_0,
  DK_GFX_MUSIC_1,
  DK_GFX_MUSIC_2,
  DK_GFX_MUSIC_3,
  DK_GFX_MUSIC_4,
  DK_GFX_MUSIC_5,
  DK_GFX_MUSIC_6,
  DK_GFX_AUDIO_7,
  DK_GFX_MUSIC_COUNT,
} DK_GFX_MUSIC;

typedef enum DK_GFX_AUDIO_FX
{
  DK_GFX_AUDIO_FX_0,
  DK_GFX_AUDIO_FX_1,
  DK_GFX_AUDIO_FX_2,
  DK_GFX_AUDIO_FX_3,
  DK_GFX_AUDIO_FX_4,
  DK_GFX_AUDIO_FX_5,
  DK_GFX_AUDIO_FX_6,
  DK_GFX_AUDIO_FX_7,
  DK_GFX_AUDIO_FX_COUNT, /* last one 8th channel is used for default fx */
} DK_GFX_AUDIO_FX;

struct TextTextureCache {
  SDL_Texture* texture;
  int width;
  int height;
};

struct TextTextureCacheNode {
  char* text;
  struct TextTextureCache texture_cache;
  struct TextTextureCacheNode* next;
};

typedef enum DK_GFX_INPUT_SENDER_ID {
  DK_GFX_INPUT_SENDER_ID_ONE,
  DK_GFX_INPUT_SENDER_ID_TWO,
  DK_GFX_INPUT_SENDER_ID_COUNT
} DK_GFX_INPUT_SENDER_ID;

typedef enum DK_GFX_INPUT_KEY {

  DK_GFX_INPUT_KEY_MOVE_LEFT,
  DK_GFX_INPUT_KEY_MOVE_RIGHT,
  DK_GFX_INPUT_KEY_MOVE_UP,
  DK_GFX_INPUT_KEY_MOVE_DOWN,

  DK_GFX_INPUT_KEY_MOVE_SELECT,
  DK_GFX_INPUT_KEY_MOVE_BACK,
  DK_GFX_INPUT_KEY_MOVE_PAUSE,

  DK_GFX_INPUT_KEY_COUNT
} DK_GFX_INPUT_KEY;

#define MAX_GAMEPAD_BUTTONS 32
typedef enum {
  GAMEPAD_BUTTON_UNKNOWN = 0,         // Unknown button, just for error checking
  GAMEPAD_BUTTON_LEFT_FACE_UP,        // Gamepad left DPAD up button
  GAMEPAD_BUTTON_LEFT_FACE_RIGHT,     // Gamepad left DPAD right button
  GAMEPAD_BUTTON_LEFT_FACE_DOWN,      // Gamepad left DPAD down button
  GAMEPAD_BUTTON_LEFT_FACE_LEFT,      // Gamepad left DPAD left button
  GAMEPAD_BUTTON_RIGHT_FACE_UP,       // Gamepad right button up (i.e. PS3: Triangle, Xbox: Y)
  GAMEPAD_BUTTON_RIGHT_FACE_RIGHT,    // Gamepad right button right (i.e. PS3: Circle, Xbox: B)
  GAMEPAD_BUTTON_RIGHT_FACE_DOWN,     // Gamepad right button down (i.e. PS3: Cross, Xbox: A)
  GAMEPAD_BUTTON_RIGHT_FACE_LEFT,     // Gamepad right button left (i.e. PS3: Square, Xbox: X)
  GAMEPAD_BUTTON_LEFT_TRIGGER_1,      // Gamepad top/back trigger left (first), it could be a trailing button
  GAMEPAD_BUTTON_LEFT_TRIGGER_2,      // Gamepad top/back trigger left (second), it could be a trailing button
  GAMEPAD_BUTTON_RIGHT_TRIGGER_1,     // Gamepad top/back trigger right (first), it could be a trailing button
  GAMEPAD_BUTTON_RIGHT_TRIGGER_2,     // Gamepad top/back trigger right (second), it could be a trailing button
  GAMEPAD_BUTTON_MIDDLE_LEFT,         // Gamepad center buttons, left one (i.e. PS3: Select)
  GAMEPAD_BUTTON_MIDDLE,              // Gamepad center buttons, middle one (i.e. PS3: PS, Xbox: XBOX)
  GAMEPAD_BUTTON_MIDDLE_RIGHT,        // Gamepad center buttons, right one (i.e. PS3: Start)
  GAMEPAD_BUTTON_LEFT_THUMB,          // Gamepad joystick pressed button left
  GAMEPAD_BUTTON_RIGHT_THUMB          // Gamepad joystick pressed button right
} GamepadButton;

typedef enum {
  GAMEPAD_AXIS_LEFT_X        = 0,
  GAMEPAD_AXIS_LEFT_Y        = 1,
  GAMEPAD_AXIS_RIGHT_X       = 2,
  GAMEPAD_AXIS_RIGHT_Y       = 3,
  GAMEPAD_AXIS_LEFT_TRIGGER  = 4,
  GAMEPAD_AXIS_RIGHT_TRIGGER = 5
} GamepadAxis;

#define MAX_KEYBOARD_KEYS 512
/* Key enum was taken form RayLib */
typedef enum DK_GFX_Key {
  KEY_NULL            = 0,        // Key: NULL, used for no key pressed
  KEY_APOSTROPHE      = 39,       // Key: '
  KEY_COMMA           = 44,       // Key: ,
  KEY_MINUS           = 45,       // Key: -
  KEY_PERIOD          = 46,       // Key: .
  KEY_SLASH           = 47,       // Key: /
  KEY_ZERO            = 48,       // Key: 0
  KEY_ONE             = 49,       // Key: 1
  KEY_TWO             = 50,       // Key: 2
  KEY_THREE           = 51,       // Key: 3
  KEY_FOUR            = 52,       // Key: 4
  KEY_FIVE            = 53,       // Key: 5
  KEY_SIX             = 54,       // Key: 6
  KEY_SEVEN           = 55,       // Key: 7
  KEY_EIGHT           = 56,       // Key: 8
  KEY_NINE            = 57,       // Key: 9
  KEY_SEMICOLON       = 59,       // Key: ;
  KEY_EQUAL           = 61,       // Key: =
  KEY_A               = 65,       // Key: A | a
  KEY_B               = 66,       // Key: B | b
  KEY_C               = 67,       // Key: C | c
  KEY_D               = 68,       // Key: D | d
  KEY_E               = 69,       // Key: E | e
  KEY_F               = 70,       // Key: F | f
  KEY_G               = 71,       // Key: G | g
  KEY_H               = 72,       // Key: H | h
  KEY_I               = 73,       // Key: I | i
  KEY_J               = 74,       // Key: J | j
  KEY_K               = 75,       // Key: K | k
  KEY_L               = 76,       // Key: L | l
  KEY_M               = 77,       // Key: M | m
  KEY_N               = 78,       // Key: N | n
  KEY_O               = 79,       // Key: O | o
  KEY_P               = 80,       // Key: P | p
  KEY_Q               = 81,       // Key: Q | q
  KEY_R               = 82,       // Key: R | r
  KEY_S               = 83,       // Key: S | s
  KEY_T               = 84,       // Key: T | t
  KEY_U               = 85,       // Key: U | u
  KEY_V               = 86,       // Key: V | v
  KEY_W               = 87,       // Key: W | w
  KEY_X               = 88,       // Key: X | x
  KEY_Y               = 89,       // Key: Y | y
  KEY_Z               = 90,       // Key: Z | z
  KEY_LEFT_BRACKET    = 91,       // Key: [
  KEY_BACKSLASH       = 92,       // Key: '\'
  KEY_RIGHT_BRACKET   = 93,       // Key: ]
  KEY_GRAVE           = 96,       // Key: `
  KEY_SPACE           = 32,       // Key: Space
  KEY_ESCAPE          = 256,      // Key: Esc
  KEY_ENTER           = 257,      // Key: Enter
  KEY_TAB             = 258,      // Key: Tab
  KEY_BACKSPACE       = 259,      // Key: Backspace
  KEY_INSERT          = 260,      // Key: Ins
  KEY_DELETE          = 261,      // Key: Del
  KEY_RIGHT           = 262,      // Key: Cursor right
  KEY_LEFT            = 263,      // Key: Cursor left
  KEY_DOWN            = 264,      // Key: Cursor down
  KEY_UP              = 265,      // Key: Cursor up
  KEY_PAGE_UP         = 266,      // Key: Page up
  KEY_PAGE_DOWN       = 267,      // Key: Page down
  KEY_HOME            = 268,      // Key: Home
  KEY_END             = 269,      // Key: End
  KEY_CAPS_LOCK       = 280,      // Key: Caps lock
  KEY_SCROLL_LOCK     = 281,      // Key: Scroll down
  KEY_NUM_LOCK        = 282,      // Key: Num lock
  KEY_PRINT_SCREEN    = 283,      // Key: Print screen
  KEY_PAUSE           = 284,      // Key: Pause
  KEY_F1              = 290,      // Key: F1
  KEY_F2              = 291,      // Key: F2
  KEY_F3              = 292,      // Key: F3
  KEY_F4              = 293,      // Key: F4
  KEY_F5              = 294,      // Key: F5
  KEY_F6              = 295,      // Key: F6
  KEY_F7              = 296,      // Key: F7
  KEY_F8              = 297,      // Key: F8
  KEY_F9              = 298,      // Key: F9
  KEY_F10             = 299,      // Key: F10
  KEY_F11             = 300,      // Key: F11
  KEY_F12             = 301,      // Key: F12
  KEY_LEFT_SHIFT      = 340,      // Key: Shift left
  KEY_LEFT_CONTROL    = 341,      // Key: Control left
  KEY_LEFT_ALT        = 342,      // Key: Alt left
  KEY_LEFT_SUPER      = 343,      // Key: Super left
  KEY_RIGHT_SHIFT     = 344,      // Key: Shift right
  KEY_RIGHT_CONTROL   = 345,      // Key: Control right
  KEY_RIGHT_ALT       = 346,      // Key: Alt right
  KEY_RIGHT_SUPER     = 347,      // Key: Super right
  KEY_KB_MENU         = 348,      // Key: KB menu
  KEY_KP_0            = 320,      // Key: Keypad 0
  KEY_KP_1            = 321,      // Key: Keypad 1
  KEY_KP_2            = 322,      // Key: Keypad 2
  KEY_KP_3            = 323,      // Key: Keypad 3
  KEY_KP_4            = 324,      // Key: Keypad 4
  KEY_KP_5            = 325,      // Key: Keypad 5
  KEY_KP_6            = 326,      // Key: Keypad 6
  KEY_KP_7            = 327,      // Key: Keypad 7
  KEY_KP_8            = 328,      // Key: Keypad 8
  KEY_KP_9            = 329,      // Key: Keypad 9
  KEY_KP_DECIMAL      = 330,      // Key: Keypad .
  KEY_KP_DIVIDE       = 331,      // Key: Keypad /
  KEY_KP_MULTIPLY     = 332,      // Key: Keypad *
  KEY_KP_SUBTRACT     = 333,      // Key: Keypad -
  KEY_KP_ADD          = 334,      // Key: Keypad +
  KEY_KP_ENTER        = 335,      // Key: Keypad Enter
  KEY_KP_EQUAL        = 336,      // Key: Keypad =
  KEY_BACK            = 4,        // Key: Android back button
  KEY_MENU            = 5,        // Key: Android menu button
  KEY_VOLUME_UP       = 24,       // Key: Android volume up button
  KEY_VOLUME_DOWN     = 25        // Key: Android volume down button
} DK_GFX_Key;

#define DK_GFX_SCANCODE_MAPPED_NUM 232
#if !defined(DK_GFX_IMPL)
extern const DK_GFX_Key DK_GFX_SCANCODE_LUT[DK_GFX_SCANCODE_MAPPED_NUM];
#else
static const DK_GFX_Key DK_GFX_SCANCODE_LUT[DK_GFX_SCANCODE_MAPPED_NUM] = {
  KEY_NULL,
  0,
  0,
  0,
  KEY_A,
  KEY_B,
  KEY_C,
  KEY_D,
  KEY_E,
  KEY_F,
  KEY_G,
  KEY_H,
  KEY_I,
  KEY_J,
  KEY_K,
  KEY_L,
  KEY_M,
  KEY_N,
  KEY_O,
  KEY_P,
  KEY_Q,
  KEY_R,
  KEY_S,
  KEY_T,
  KEY_U,
  KEY_V,
  KEY_W,
  KEY_X,
  KEY_Y,
  KEY_Z,
  KEY_ONE,
  KEY_TWO,
  KEY_THREE,
  KEY_FOUR,
  KEY_FIVE,
  KEY_SIX,
  KEY_SEVEN,
  KEY_EIGHT,
  KEY_NINE,
  KEY_ZERO,
  KEY_ENTER,
  KEY_ESCAPE,
  KEY_BACKSPACE,
  KEY_TAB,
  KEY_SPACE,
  KEY_MINUS,
  KEY_EQUAL,
  KEY_LEFT_BRACKET,
  KEY_RIGHT_BRACKET,
  KEY_BACKSLASH,
  0,
  KEY_SEMICOLON,
  KEY_APOSTROPHE,
  KEY_GRAVE,
  KEY_COMMA,
  KEY_PERIOD,
  KEY_SLASH,
  KEY_CAPS_LOCK,
  KEY_F1,
  KEY_F2,
  KEY_F3,
  KEY_F4,
  KEY_F5,
  KEY_F6,
  KEY_F7,
  KEY_F8,
  KEY_F9,
  KEY_F10,
  KEY_F11,
  KEY_F12,
  KEY_PRINT_SCREEN,
  KEY_SCROLL_LOCK,
  KEY_PAUSE,
  KEY_INSERT,
  KEY_HOME,
  KEY_PAGE_UP,
  KEY_DELETE,
  KEY_END,
  KEY_PAGE_DOWN,
  KEY_RIGHT,
  KEY_LEFT,
  KEY_DOWN,
  KEY_UP,
  KEY_NUM_LOCK,
  KEY_KP_DIVIDE,
  KEY_KP_MULTIPLY,
  KEY_KP_SUBTRACT,
  KEY_KP_ADD,
  KEY_KP_ENTER,
  KEY_KP_1,
  KEY_KP_2,
  KEY_KP_3,
  KEY_KP_4,
  KEY_KP_5,
  KEY_KP_6,
  KEY_KP_7,
  KEY_KP_8,
  KEY_KP_9,
  KEY_KP_0,
  KEY_KP_DECIMAL,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0,
  KEY_LEFT_CONTROL,
  KEY_LEFT_SHIFT,
  KEY_LEFT_ALT,
  KEY_LEFT_SUPER,
  KEY_RIGHT_CONTROL,
  KEY_RIGHT_SHIFT,
  KEY_RIGHT_ALT,
  KEY_RIGHT_SUPER
};
#endif

typedef struct DK_GFX_ScreenTransitionData {
  enum {
    FADE_NONE,
    FADE_OUT
  } state;

  float speed;

  int32_t prev_screen;
} DK_GFX_ScreenTransitionData;


typedef SDL_AudioDeviceID DK_GFX_AudioDeviceID;
typedef SDL_AudioSpec DK_GFX_AudioSpec;

typedef struct {
  // DK_GFX_AudioSpec spec;
  uint8_t *buffer;
  Uint32 bufferSize;
} DK_GFX_AudioClip;

typedef struct DK_GFX_Context {
  // top level
  bool running;

  // time
  float dt;

  // window
  uint16_t width;
  uint16_t height;
  bool full_screen;
  DK_GFX_Event* event;
  DK_GFX_Window* window;

  // renderer
  float alpha;
  DK_GFX_Color color;
  DK_GFX_Renderer* renderer;
  DK_GFX_RendererFlip flip;
  DK_GFX_ScreenTransitionData screen_transition;

  char *input_text_buffer;
  DK_GFX_Point mouse;
  Uint32 mouse_state;

  struct {
    DK_GFX_INPUT_SENDER_ID sender_id;
    SDL_Joystick *controller[DK_GFX_INPUT_SENDER_ID_COUNT];
    bool keys[2][DK_GFX_INPUT_KEY_COUNT];
  } GameInputs;

#ifdef USE_SDL2_MIXER_BACKEND
  struct {
    DK_GFX_Music *music_default;
    DK_GFX_Music *music[DK_GFX_MUSIC_COUNT];

    DK_GFX_AudioFx *audio_fx_default;
    DK_GFX_AudioFx *audio_fx[DK_GFX_AUDIO_FX_COUNT];
    int32_t        audio_fx_play_count;
    int32_t master_volume;
  } Audio;
#else
  struct {

    DK_GFX_AudioDeviceID device_id;
    DK_GFX_AudioSpec device_spec;
    DK_GFX_AudioClip *music[DK_GFX_MUSIC_COUNT];
    DK_GFX_AudioClip *audio_fx[DK_GFX_AUDIO_FX_COUNT];
    int32_t master_volume;
  } Audio;
#endif

  // texture
  DK_GFX_Texture *texture;
  DK_GFX_Texture *textures[DK_GFX_TEXTURE_COUNT];

  // font
  TTF_Font *font;
  TTF_Font *default_font;
  struct TextTextureCacheNode* text_texture_cache;

  struct {
    char currentKeyState[MAX_KEYBOARD_KEYS];
    char previousKeyState[MAX_KEYBOARD_KEYS];
  } Keyboard;

  struct {
    int lastButtonPressed;
    bool ready[DK_GFX_INPUT_SENDER_ID_COUNT];
    char name[DK_GFX_INPUT_SENDER_ID_COUNT][64];
    char currentButtonState[DK_GFX_INPUT_SENDER_ID_COUNT][MAX_GAMEPAD_BUTTONS];
    char previousButtonState[DK_GFX_INPUT_SENDER_ID_COUNT][MAX_GAMEPAD_BUTTONS];
  } Gamepad;

  void (*Init)(void);
  void (*Update)();
  void (*Render)();
  void (*Destroy)(void);

} DK_GFX_Context;

typedef struct DK_GFX_ParallaxLayer {
  DK_GFX_Texture *texture;

  int32_t texture_width;
  int32_t texture_height;

  DK_GFX_FPoint pos, pos2;
  DK_GFX_FPoint scale;
  float speed;
} DK_GFX_ParallaxLayer;

typedef struct DK_GFX_Window_Desc_t {
  int width;
  int height;
  const char *title;
  int flags;
  bool running;
} DK_GFX_Window_Desc_t;

typedef struct DK_GFX_SpriteFrameDesc {
  int width;
  int height;
  int row;
  int start_index;
  int end_index;
  DK_GFX_Point pos;
  DK_GFX_Point scale;
  bool loop;
  float speed;
  DK_GFX_TEXTURE slot;
} DK_GFX_SpriteFrameDesc;

typedef struct DK_GFX_SpriteDesc {
  int width;
  int height;

  int row;
  int col;

  DK_GFX_Point pos;
  DK_GFX_Point scale;

  DK_GFX_TEXTURE slot;
} DK_GFX_SpriteDesc;

typedef struct DK_GFX_SpriteDescPro {
  int width;
  int height;

  int row;
  int col;
  int dest_width, dest_height;

  DK_GFX_Point pos;

  DK_GFX_TEXTURE slot;
} DK_GFX_SpriteDescPro;

typedef struct DK_GFX_Text_Desc_t {
  const char *text;
  DK_GFX_Point pos;
  DK_GFX_Color color;
} DK_GFX_Text_Desc_t;

typedef struct DK_GFX_Debug_Text_Desc_t {
  const char *text;
  DK_GFX_Point pos;
  DK_GFX_Color color;
  DK_GFX_Color background_color;
} DK_GFX_Debug_Text_Desc_t;

typedef struct DK_GFX_Debug_Rect_Desc_t {
  DK_GFX_Rect rect;
  DK_GFX_Color color;
} DK_GFX_Debug_Rect_Desc_t;

typedef struct DK_GFX_Texture_Desc_t {
  DK_GFX_Rect *dst_rect;
  DK_GFX_Rect *src_rect;
  DK_GFX_Texture *texture;
} DK_GFX_Texture_Desc_t;

DK_API int DK_GFX_GetVersionMajor(void);
DK_API int DK_GFX_GetVersionMinor(void);
DK_API int DK_GFX_GetVersionPatch(void);

// @Color API
DK_API DK_GFX_Color DK_GFX_ARGB(uint32_t hexValue);
DK_API DK_GFX_Color DK_GFX_RGBA(uint32_t hexValue);
DK_API DK_GFX_Color DK_GFX_ColorMix(DK_GFX_Color a, DK_GFX_Color b, float percentage);

// @Window API
DK_API DK_GFX_Window* DK_GFX_CreateWindow(const char* title, uint16_t width, uint16_t height, uint16_t flags);
DK_API void DK_GFX_DestroyWindow(DK_GFX_Window* window);
DK_API void DK_GFX_GetWindowSize(DK_GFX_Window* window, int32_t* w, int32_t* h);
DK_API void DK_GFX_UpdateScreenSize(DK_GFX_Context *context, DK_GFX_Window_Desc_t *desc, int width, int height);
DK_API int DK_GFX_GetWindowScreenWidth(DK_GFX_Context *gfx_context);
DK_API int DK_GFX_GetWindowScreenHeight(DK_GFX_Context *gfx_context);
DK_API void DK_GFX_WindowToggleFullScreen(DK_GFX_Context *context);
DK_API void DK_GFX_WindowResize(DK_GFX_Context *context, DK_GFX_Point size);

// @Renderer API
DK_API DK_GFX_Renderer* DK_GFX_CreateRenderer(DK_GFX_Window* window, uint32_t flags);
DK_API void DK_GFX_DestroyRenderer(DK_GFX_Renderer* renderer);
DK_API void DK_GFX_GetRendererLogicalSize(DK_GFX_Renderer* renderer, int32_t* w, int32_t* h);
DK_API void DK_GFX_SetRenderLogicalSize(DK_GFX_Renderer* renderer, int32_t w, int32_t h);
DK_API void DK_GFX_RenderClear(DK_GFX_Renderer* renderer);
DK_API void DK_GFX_RenderCopy(DK_GFX_Renderer* renderer, DK_GFX_Texture* texture, const DK_GFX_Rect* srcrect, const DK_GFX_Rect* dstrect);
DK_API void DK_GFX_RenderCopyEx(DK_GFX_Renderer* renderer, DK_GFX_Texture* texture, const DK_GFX_Rect* srcrect, const DK_GFX_Rect* dstrect, double angle, const DK_GFX_Point* center, DK_GFX_RendererFlip flip); 
DK_API void DK_GFX_RenderPresent(DK_GFX_Renderer* renderer);
DK_API void DK_GFX_RenderFlip(DK_GFX_Context *context, DK_GFX_RendererFlip flip);
DK_API void DK_GFX_Clear(DK_GFX_Renderer* renderer, DK_GFX_Color color);
DK_API void DK_GFX_SetRenderTarget(DK_GFX_Renderer* renderer, DK_GFX_Texture* texture);
DK_API void DK_GFX_FadeAlpha(DK_GFX_Context *gfx_context, Uint32 t, Uint32 in);
DK_API void DK_GFX_ResetAlpha(DK_GFX_Context *gfx_context);
DK_API void DK_GFX_SetBlendMode(DK_GFX_Context *context, DK_GFX_BlendMode mode);

// @Context API
DK_API DK_GFX_Context* DK_GFX_CreateContext(void);
DK_API void DK_GFX_DestroyContext(DK_GFX_Context* ctx);

// @Texture API
DK_API DK_GFX_Texture *DK_GFX_LoadTexture(DK_GFX_Renderer* renderer, const char* path);
DK_API DK_GFX_Texture *DK_GFX_LoadTextureFromRW(DK_GFX_Context *gfx_context, DK_GFX_RWops *rw, bool free_rw);
DK_API DK_GFX_Texture *DK_GFX_CreateTexture(DK_GFX_Renderer* renderer, uint32_t format, int access, int w, int h);
DK_API void DK_GFX_GetTextureSize(DK_GFX_Texture *texture, int *width, int *height);
DK_API void DK_GFX_SetTextureColorMod(DK_GFX_Texture* texture, uint8_t r, uint8_t g, uint8_t b);
DK_API void DK_GFX_SetTextureAlphaMod(DK_GFX_Texture* texture, uint8_t a);
DK_API void DK_GFX_ResizeTexture(DK_GFX_Context *context, DK_GFX_Texture *texture, int width, int height);
DK_API void DK_GFX_SetTextureBlendMode(DK_GFX_Texture* texture, SDL_BlendMode blendMode);
DK_API void DK_GFX_DestroyTexture(DK_GFX_Texture *texture);
DK_API void DK_GFX_DrawTexture(DK_GFX_Context *context, DK_GFX_Texture_Desc_t desc);

// @Font API
DK_API TTF_Font* DK_GFX_LoadFont(const char* path, int ptsize);
DK_API void DK_GFX_DestroyFont(TTF_Font* font);
DK_API void DK_GFX_SetFont(DK_GFX_Context *context, TTF_Font *font);
DK_API TTF_Font* DK_GFX_GetDefaultFont(DK_GFX_Context *context);
DK_API void DK_GFX_ResetFont(DK_GFX_Context *context);

// @Draw API
DK_API void DK_GFX_ClearColor(DK_GFX_Renderer* renderer, DK_GFX_Color color);
DK_API void DK_GFX_DrawPoint(DK_GFX_Renderer* renderer, int x, int y);
DK_API void DK_GFX_DrawPoints(DK_GFX_Renderer* renderer, const DK_GFX_Point* points, int count);
DK_API void DK_GFX_DrawLine(DK_GFX_Renderer* renderer, int x1, int y1, int x2, int y2);
DK_API void DK_GFX_DrawLines(DK_GFX_Renderer* renderer, const DK_GFX_Point* points, int count);
DK_API void DK_GFX_DrawRect(DK_GFX_Renderer* renderer, const DK_GFX_Rect* rect);
DK_API void DK_GFX_DrawRects(DK_GFX_Renderer* renderer, const DK_GFX_Rect* rects, int count);
DK_API void DK_GFX_FillRect(DK_GFX_Renderer* renderer, const DK_GFX_Rect* rect);
DK_API void DK_GFX_SetDrawColor(DK_GFX_Renderer* renderer, DK_GFX_Color color);
DK_API void DK_GFX_Draw(DK_GFX_Context *context, DK_GFX_Texture *texture, const DK_GFX_Rect* srcrect, const DK_GFX_Rect* dstrect);
DK_API void DK_GFX_DrawCircle(SDL_Renderer* renderer, int32_t centerX, int32_t centerY, int32_t radius);
DK_API void DK_GFX_DrawFilledCircle(SDL_Renderer* renderer, int32_t centerX, int32_t centerY, int32_t radius);
DK_API void DK_GFX_DrawDebugRect(DK_GFX_Context *context, DK_GFX_Debug_Rect_Desc_t *desc);
DK_API void DK_GFX_DrawDebugRectFilled(DK_GFX_Context *context, DK_GFX_Debug_Rect_Desc_t *desc);
DK_API void DK_GFX_DrawFullScreenRect(DK_GFX_Context *context, float alpha);
DK_API void DK_GFX_ClearScreenWithColor(DK_GFX_Context *context, DK_GFX_Color color);
DK_API void DK_GFX_ClearScreen(DK_GFX_Context *context);

// @Parallax API
DK_API void DK_GFX_DrawParallaxLayer(DK_GFX_Context *context, DK_GFX_ParallaxLayer *layer);
DK_API void DK_GFX_UpdateParallaxLayer(DK_GFX_Context *context, DK_GFX_ParallaxLayer *layer, float dt);
DK_API void DK_GFX_ResizeParallaxLayer(DK_GFX_Context *context, DK_GFX_ParallaxLayer *layer, int width, int height);

// @Time API
DK_API int DK_GFX_GetTime(void);

// @Sprite API
DK_API void DK_GFX_DrawSpriteEx(DK_GFX_Context *context, DK_GFX_Point tileCoord, DK_GFX_Point pos, DK_GFX_Point scale, DK_GFX_Color color);
DK_API void DK_GFX_DrawSpriteFrame(DK_GFX_Context *context, DK_GFX_SpriteFrameDesc *desc);
DK_API void DK_GFX_DrawSprite(DK_GFX_Context *context, DK_GFX_SpriteDesc desc);
DK_API void DK_GFX_DrawSpritePro(DK_GFX_Context *context, DK_GFX_SpriteDescPro desc);

// @Text API
DK_API void DK_GFX_DrawText(DK_GFX_Context *gfx_context, DK_GFX_Text_Desc_t *desc);
DK_API void DK_GFX_DrawDebugText(DK_GFX_Context *gfx_context, DK_GFX_Debug_Text_Desc_t *desc);
DK_API void DK_GFX_DrawTextOptimized(DK_GFX_Context *gfx_context, DK_GFX_Text_Desc_t *desc);
DK_API int DK_GFX_GetTextWidth(DK_GFX_Context *gfx_context, const char *text);
DK_API int DK_GFX_GetTextHeight(DK_GFX_Context *gfx_context, const char *text);
DK_API int DK_GFX_GetTextHeightFor(TTF_Font *font, const char *text);
DK_API int DK_GFX_GetTextWidthFor(TTF_Font *font, const char *text);

// @Memory API
DK_API void DK_GFX_GenerateCFile(const char *ifile, const char *ofile, const char *modname);
DK_API DK_GFX_RWops *DK_GFX_RWFromMem(void *mem, int32_t size);
DK_API void DK_GFX_FreeRW(DK_GFX_RWops *rw);
DK_API void DK_GFX_Free(void *ptr);

// @Keyboard @Input API
DK_API bool DK_GFX_IsKeyPressed(DK_GFX_Context *context,  DK_GFX_Key key);
DK_API bool DK_GFX_IsKeyDown(DK_GFX_Context *context, DK_GFX_Key key);
DK_API DK_GFX_Key DK_GFX_ScancodeToKey(SDL_Scancode scancode);

// @Gamepad @Input API
DK_API bool DK_GFX_IsGamepadButtonPressed(DK_GFX_Context *context, DK_GFX_INPUT_SENDER_ID gamepad, int button);
DK_API bool DK_GFX_IsGamepadButtonDown(DK_GFX_Context *context, DK_GFX_INPUT_SENDER_ID gamepad, int button);

// @GameInputManager API
DK_API void DK_GFX_DiscoverAndGrabGameController(DK_GFX_Context *context);
DK_API void DK_GFX_GameInputManagerSetKey(DK_GFX_Context *context, DK_GFX_INPUT_SENDER_ID sender, DK_GFX_INPUT_KEY key, bool state);
DK_API bool DK_GFX_GameInputManagerKey(DK_GFX_Context *context, DK_GFX_INPUT_SENDER_ID sender, DK_GFX_INPUT_KEY key);

// @Event API
DK_API void DK_GFX_PullEvents(DK_GFX_Context *context);
DK_API void DK_GFX_PushEvent(DK_GFX_Context *context, DK_GFX_EventType type);
DK_API bool DK_GFX_WindowShouldClose(DK_GFX_Context *context);

// @Screen @Transition API 
DK_API void DK_GFX_ScreenTransitionInit(DK_GFX_Context *context, int32_t default_screen, float speed);
DK_API void DK_GFX_ScreenTransitionRender(DK_GFX_Context *gfx_context);
DK_API void DK_GFX_TransitionScreen(DK_GFX_Context *gfx_context, int32_t *screen, int32_t new_scene);

// @AudioFX API
#ifdef USE_SDL2_MIXER_BACKEND
DK_API int32_t DK_GFX_PlayAudioFx(DK_GFX_Context *context, DK_GFX_AUDIO_FX storage_index);
DK_API void DK_GFX_SetAudioFxVolume(DK_GFX_Context *context, DK_GFX_AUDIO_FX storage_index, float volume);
DK_API void DK_GFX_SetAudioFxMasterVolume(DK_GFX_Context *context, float volume);
DK_API void DK_GFX_StopAudioFx(DK_GFX_Context *context, DK_GFX_AUDIO_FX storage_index);
DK_API void DK_GFX_PauseAudioFx(DK_GFX_Context *context, DK_GFX_AUDIO_FX storage_index);
DK_API void DK_GFX_ResumeAudioFxAny(DK_GFX_Context *context, int32_t channel);
DK_API void DK_GFX_PauseAudioFxAny(DK_GFX_Context *context, int32_t channel);
DK_API void DK_GFX_StopAudioFxAny(DK_GFX_Context *context, int32_t channel);
DK_API void DK_GFX_StopAudioAll(DK_GFX_Context *context, int32_t channel);
DK_API void DK_GFX_SetAudioFxPlayCount(DK_GFX_Context *context, int32_t n);
#else
DK_API void DK_GFX_LoadAudioFx(DK_GFX_Context *context, DK_GFX_AUDIO_FX storage_index, const char *path);
DK_API void DK_GFX_PlayAudioFx(DK_GFX_Context *context, DK_GFX_AUDIO_FX storage_index);
DK_API void DK_GFX_SetAudioFxVolume(DK_GFX_Context *context, DK_GFX_AUDIO_FX storage_index, float volume);
DK_API void DK_GFX_StopAudioFx(DK_GFX_Context *context, DK_GFX_AUDIO_FX storage_index);
DK_API void DK_GFX_SetMasterVolume(DK_GFX_Context *context, int volume);
DK_API void DK_GFX_SetAudioFxMasterVolume(DK_GFX_Context *context, float volume);
#endif // USE_SDL2_MIXER_BACKEND

// @Music API
// TODO (David): implement music api

#if defined(DK_GFX_IMPL)

DK_API int DK_GFX_GetVersionMajor(void) {
  return DK_GFX_VERSION_MAJOR;
}

DK_API int DK_GFX_GetVersionMinor(void) {
  return DK_GFX_VERSION_MINOR;
}

DK_API int DK_GFX_GetVersionPatch(void) {
  return DK_GFX_VERSION_PATCH;
}

DK_API DK_GFX_Context* DK_GFX_CreateContext(void) {
  DK_GFX_Context* ctx = (DK_GFX_Context*)DK_MALLOC(sizeof(DK_GFX_Context));
  memset(ctx, 0, sizeof(DK_GFX_Context));
  ctx->alpha = 1.0f;
  return ctx;
}

DK_API void DK_GFX_DestroyContext(DK_GFX_Context* ctx) {
  DK_FREE(ctx);
}

DK_API void DK_GFX_DestroyWindow(DK_GFX_Window* window) {
  SDL_DestroyWindow(window);
}

DK_API DK_GFX_Window* DK_GFX_CreateWindow(const char* title, uint16_t width, uint16_t height, uint16_t flags) {
  return SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
}

DK_API void DK_GFX_GetWindowSize(DK_GFX_Window* window, int32_t* w, int32_t* h) {
  SDL_GetWindowSize(window, w, h);
}

DK_API void DK_GFX_UpdateScreenSize(DK_GFX_Context *context, DK_GFX_Window_Desc_t *desc, int width, int height) {
  desc->width = width;
  desc->height = height;
  DK_GFX_SetRenderLogicalSize(context->renderer, width, height);
}

DK_API int DK_GFX_GetWindowScreenWidth(DK_GFX_Context *gfx_context) {
  int width, height;
  SDL_GetWindowSize(gfx_context->window, &width, &height);
  return width;
}

DK_API int DK_GFX_GetWindowScreenHeight(DK_GFX_Context *gfx_context) {
  int width, height;
  SDL_GetWindowSize(gfx_context->window, &width, &height);
  return height;
}

DK_API void DK_GFX_WindowToggleFullScreen(DK_GFX_Context *context) {
  context->full_screen = !context->full_screen;
  SDL_SetWindowFullscreen(context->window, context->full_screen ? DK_GFX_WINDOW_FULLSCREEN : 0);

  context->width = DK_GFX_GetWindowScreenWidth(context);
  context->height = DK_GFX_GetWindowScreenHeight(context);

  if (!context->full_screen) {
    SDL_SetWindowSize(context->window, context->width, context->height);
  }
}

DK_API void DK_GFX_WindowResize(DK_GFX_Context *context, DK_GFX_Point size) {
  context->width = size.x;
  context->height = size.y;

  SDL_SetWindowSize(context->window, context->width, context->height);
}

DK_API DK_GFX_Renderer* DK_GFX_CreateRenderer(DK_GFX_Window* window, uint32_t flags) {
  return SDL_CreateRenderer(window, -1, flags);
}

DK_API void DK_GFX_DestroyRenderer(DK_GFX_Renderer* renderer) {
  SDL_DestroyRenderer(renderer);
}

DK_API void DK_GFX_GetRendererLogicalSize(DK_GFX_Renderer* renderer, int32_t* w, int32_t* h) {
  SDL_RenderGetLogicalSize(renderer, w, h);
}

DK_API void DK_GFX_SetRenderLogicalSize(DK_GFX_Renderer* renderer, int32_t w, int32_t h) {
  SDL_RenderSetLogicalSize(renderer, w, h);
}

DK_API void DK_GFX_RenderClear(DK_GFX_Renderer* renderer) {
  SDL_RenderClear(renderer);
}

DK_API void DK_GFX_Clear(DK_GFX_Renderer* renderer, DK_GFX_Color color) {
  SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
  SDL_RenderClear(renderer);
}

DK_API void DK_GFX_SetRenderTarget(DK_GFX_Renderer* renderer, DK_GFX_Texture* texture) {
  SDL_SetRenderTarget(renderer, texture);
}

DK_API void DK_GFX_FadeAlpha(DK_GFX_Context *gfx_context, Uint32 t, Uint32 in) {  
  if (!in && gfx_context->alpha == 1.0f) return;
  if (in && gfx_context->alpha == 0.0f) return;

  Uint32 elapsed = SDL_GetTicks() ;
  float progress = (float)elapsed / t;

  if (in) {
    if (gfx_context->alpha <= 0.0f) {
      gfx_context->alpha = 0.0f;
      return;
    }

    gfx_context->alpha = 1.0f - progress;
  } else {
    gfx_context->alpha = progress;
    if (gfx_context->alpha >= 1.0f) {
      gfx_context->alpha = 1.0f;
      return;
    }
  }
}

DK_API void DK_GFX_ResetAlpha(DK_GFX_Context *gfx_context) {
  gfx_context->alpha = 1.0f;
}

DK_API void DK_GFX_RenderCopy(DK_GFX_Renderer* renderer, DK_GFX_Texture* texture, const DK_GFX_Rect* srcrect, const DK_GFX_Rect* dstrect) {
  SDL_RenderCopy(renderer, texture, srcrect, dstrect);
}

DK_API void DK_GFX_RenderCopyEx(DK_GFX_Renderer* renderer, DK_GFX_Texture* texture, const DK_GFX_Rect* srcrect, const DK_GFX_Rect* dstrect, double angle, const DK_GFX_Point* center, DK_GFX_RendererFlip flip) {
  SDL_RenderCopyEx(renderer, texture, srcrect, dstrect, angle, center, flip);
}

DK_API void DK_GFX_RenderFlip(DK_GFX_Context *context, DK_GFX_RendererFlip flip) {
  context->flip = flip;
}

DK_API void DK_GFX_Draw(DK_GFX_Context *context, DK_GFX_Texture *texture, const DK_GFX_Rect* srcrect, const DK_GFX_Rect* dstrect) {
  double angle = 0;
  DK_GFX_Point center = {0};
  DK_GFX_RenderCopyEx(context->renderer, texture, srcrect, dstrect, angle, &center, context->flip);
}

DK_API DK_GFX_Texture *DK_GFX_LoadTexture(DK_GFX_Renderer* renderer, const char* path) {
  DK_GFX_Texture *texture = IMG_LoadTexture(renderer, path);
  if (texture == NULL) {
    SDL_Log("IMG_LoadTexture: %s\n", IMG_GetError());
    exit(EXIT_FAILURE);
  }

  return texture;
}

DK_API DK_GFX_Texture *DK_GFX_LoadTextureFromRW(DK_GFX_Context *gfx_context, DK_GFX_RWops *rw, bool free_rw) {
  DK_GFX_Texture *texture = IMG_LoadTexture_RW(gfx_context->renderer, rw, free_rw);
  if (texture == NULL) {
    SDL_Log("IMG_LoadTexture_RW: %s\n", IMG_GetError());
    exit(EXIT_FAILURE);
  }

  return texture;
}

DK_API DK_GFX_Texture* DK_GFX_CreateTexture(DK_GFX_Renderer* renderer, uint32_t format, int access, int w, int h) {
  return SDL_CreateTexture(renderer, format, access, w, h);
}

DK_API void DK_GFX_GetTextureSize(DK_GFX_Texture *texture, int *width, int *height) {
  SDL_QueryTexture(texture, NULL, NULL, width, height);
}

DK_API void DK_GFX_SetTextureColorMod(DK_GFX_Texture* texture, uint8_t r, uint8_t g, uint8_t b) {
  SDL_SetTextureColorMod(texture, r, g, b);
}

DK_API void DK_GFX_SetTextureAlphaMod(DK_GFX_Texture* texture, uint8_t a) {
  SDL_SetTextureAlphaMod(texture, a);
}

DK_API void DK_GFX_SetTextureBlendMode(DK_GFX_Texture* texture, SDL_BlendMode blendMode) {
  SDL_SetTextureBlendMode(texture, blendMode);
}

DK_API void DK_GFX_ResizeTexture(DK_GFX_Context *context, DK_GFX_Texture *texture, int width, int height) {
  DK_GFX_DestroyTexture(texture);
  context->texture = SDL_CreateTexture(context->renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height);
}

DK_API void DK_GFX_DestroyTexture(DK_GFX_Texture* texture) {
  SDL_DestroyTexture(texture);
}

DK_API void DK_GFX_Free(void *ptr) {
  SDL_free(ptr);
}

DK_API void DK_GFX_DrawTexture(DK_GFX_Context *context, DK_GFX_Texture_Desc_t desc) {
  DK_GFX_RenderCopy(context->renderer, desc.texture, desc.src_rect, desc.dst_rect);
}

DK_API TTF_Font* DK_GFX_LoadFont(const char* path, int ptsize) {
  return TTF_OpenFont(path, ptsize);
}

DK_API void DK_GFX_DestroyFont(TTF_Font* font) {
  TTF_CloseFont(font);
}

DK_API void DK_GFX_SetFont(DK_GFX_Context *context, TTF_Font *font) {
  context->font = font;
}

DK_API void DK_GFX_ResetFont(DK_GFX_Context *context) {
  context->font = context->default_font;
}

DK_API TTF_Font* DK_GFX_GetDefaultFont(DK_GFX_Context *context) {
  return context->default_font;
}

DK_API void DK_GFX_DrawLine(DK_GFX_Renderer* renderer, int x1, int y1, int x2, int y2) {
  SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}

DK_API void DK_GFX_ClearColor(DK_GFX_Renderer* renderer, DK_GFX_Color color) {
  SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
}

DK_API void DK_GFX_ClearScreenWithColor(DK_GFX_Context *context, DK_GFX_Color color) {
  DK_GFX_ClearColor(context->renderer, color);
  DK_GFX_RenderClear(context->renderer);
}

DK_API void DK_GFX_ClearScreen(DK_GFX_Context *context) {
  DK_GFX_ClearColor(context->renderer, context->color);
  DK_GFX_RenderClear(context->renderer);
}

DK_API void DK_GFX_DrawPoint(DK_GFX_Renderer* renderer, int x, int y) {
  SDL_RenderDrawPoint(renderer, x, y);
}

DK_API void DK_GFX_DrawRect(DK_GFX_Renderer* renderer, const DK_GFX_Rect* rect) {
  SDL_RenderDrawRect(renderer, rect);
}

DK_API void DK_GFX_DrawDebugRect(DK_GFX_Context *context, DK_GFX_Debug_Rect_Desc_t *desc) {
  DK_GFX_SetDrawColor(context->renderer, desc->color);
  DK_GFX_DrawRect(context->renderer, &desc->rect);
}

DK_API void DK_GFX_DrawRects(DK_GFX_Renderer* renderer, const DK_GFX_Rect* rects, int count) {
  SDL_RenderDrawRects(renderer, rects, count);
}

DK_API void DK_GFX_FillRect(DK_GFX_Renderer* renderer, const DK_GFX_Rect* rect) {
  SDL_RenderFillRect(renderer, rect);
}

DK_API void DK_GFX_DrawDebugRectFilled(DK_GFX_Context *context, DK_GFX_Debug_Rect_Desc_t *desc) {
  DK_GFX_SetDrawColor(context->renderer, desc->color);
  DK_GFX_FillRect(context->renderer, &desc->rect);
}

DK_API void DK_GFX_DrawFullScreenRect(DK_GFX_Context *context, float alpha) {
  DK_GFX_SetDrawColor(context->renderer, (DK_GFX_Color) {0, 0, 0, (Uint8)(255 * alpha) });
  SDL_RenderFillRect(context->renderer, NULL);
}

DK_API void DK_GFX_SetDrawColor(DK_GFX_Renderer* renderer, DK_GFX_Color color) {
  SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
}

DK_API void DK_GFX_RenderPresent(DK_GFX_Renderer* renderer) {
  SDL_RenderPresent(renderer);
}

DK_API void DK_GFX_SetBlendMode(DK_GFX_Context *context, DK_GFX_BlendMode mode) {
  SDL_SetRenderDrawBlendMode(context->renderer, mode);
}

DK_API void DK_GFX_DrawParallaxLayer(DK_GFX_Context *context, DK_GFX_ParallaxLayer *layer) {
  DK_GFX_Rect src = { .x = 0, .y = 0, .w = layer->texture_width, .h = layer->texture_height };
  DK_GFX_Rect dest = { .x = layer->pos.x, .y = layer->pos.y, .w = layer->texture_width * layer->scale.x, .h = layer->texture_height * layer->scale.y };

  DK_GFX_RenderCopy(context->renderer, layer->texture, &src, &dest);

  dest.x = layer->pos2.x;
  dest.y = layer->pos2.y;

  DK_GFX_RenderCopy(context->renderer, layer->texture, &src, &dest);
}

DK_API void DK_GFX_UpdateParallaxLayer(DK_GFX_Context *context, DK_GFX_ParallaxLayer *layer, float dt) {
  layer->pos.x -= layer->speed;
  layer->pos2.x -= layer->speed;

  if (layer->pos.x + layer->texture_width * layer->scale.x <= 0) {
    layer->pos.x = layer->pos2.x + layer->texture_width * layer->scale.x;
  }

  if (layer->pos2.x + layer->texture_width * layer->scale.x <= 0) {
    layer->pos2.x = layer->pos.x + layer->texture_width * layer->scale.x;
  }
}

DK_API DK_GFX_Color DK_GFX_ARGB(uint32_t hexValue) {
  DK_GFX_Color color;
  color.r = (hexValue >> 16) & 0xFF;
  color.g = (hexValue >> 8) & 0xFF;
  color.b = hexValue & 0xFF;
  color.a = (hexValue >> 24) & 0xFF;
  return color;
}

DK_API DK_GFX_Color DK_GFX_RGBA(uint32_t hexValue) {
  /* Moving {Alpha} component to the end */
  return DK_GFX_ARGB(((hexValue & 0x00FFFFFF) << 8) | ((hexValue >> 24) & 0xFF));
}

DK_API DK_GFX_Color DK_GFX_ColorMix(DK_GFX_Color a, DK_GFX_Color b, float percentage) {
  DK_GFX_Color result;
  percentage = percentage < 0.0f ? 0.0f : (percentage > 1.0f ? 1.0f : percentage);

  result.r = (uint8_t)(a.r + (b.r - a.r) * percentage);
  result.g = (uint8_t)(a.g + (b.g - a.g) * percentage);
  result.b = (uint8_t)(a.b + (b.b - a.b) * percentage);
  result.a = (uint8_t)(a.a + (b.a - a.a) * percentage);

  return result;
}

DK_API void DK_GFX_ResizeParallaxLayer(DK_GFX_Context *context, DK_GFX_ParallaxLayer *layer, int width, int height) {
  layer->pos.x = 0;
  layer->pos.y = 0;

  layer->pos2.x = width;
  layer->pos2.y = 0;
}

DK_API int DK_GFX_GetTime(void) {
  return SDL_GetTicks();
}

DK_API void DK_GFX_DrawSpriteEx(DK_GFX_Context *context, DK_GFX_Point tileCoord, DK_GFX_Point pos, DK_GFX_Point scale, DK_GFX_Color color) {
  int tileWidth = 35;
  int tileHeight = 35;

  DK_GFX_Rect src = {
    .x = tileCoord.x * tileWidth,
    .y = tileCoord.y * tileHeight,
    .w = tileWidth, .h = tileHeight
  };
  
  DK_GFX_Rect dest = {
    .x = pos.x,
    .y = pos.y,
    .w = tileWidth,
    .h = tileHeight
  };

  dest.w *= scale.x;
  dest.h *= scale.y;

  dest.y += 10;
  DK_GFX_RenderCopy(context->renderer, context->texture, &src, &dest);
}

void DK_GFX_DrawSpriteFrame(DK_GFX_Context *context, DK_GFX_SpriteFrameDesc *desc) {
  Uint32 ticks = SDL_GetTicks();
  float seconds = ticks / desc->speed;

  Uint32 sprite = (int)(seconds) % (desc->end_index - desc->start_index) + desc->start_index;
  DK_GFX_Point current_tile_coord = { .x = sprite, .y = desc->row };

  DK_GFX_Rect src = {
    .x = current_tile_coord.x * desc->width,
    .y = current_tile_coord.y * desc->height,
    .w = desc->width, .h = desc->height
  };

  DK_GFX_Rect dest = {
    .x = desc->pos.x - desc->width * desc->scale.x / 2,
    .y = desc->pos.y - desc->height * desc->scale.y / 2,
    .w = desc->width * desc->scale.x, .h = desc->height * desc->scale.y
  };

  DK_GFX_Draw(context, context->textures[desc->slot], &src, &dest);

  if (!desc->loop && ((int)sprite == desc->end_index - 1)) {
    return;
  }

  if (desc->loop && ((int)sprite == desc->end_index - 1)) {
    seconds = 0;
  }
}

DK_API void DK_GFX_DrawSprite(DK_GFX_Context *context, DK_GFX_SpriteDesc desc) {
  DK_GFX_Point current_tile_coord = { .x = desc.col, .y = desc.row };

  DK_GFX_Rect src = {
    .x = current_tile_coord.x * desc.width,
    .y = current_tile_coord.y * desc.height,
    .w = desc.width,
    .h = desc.height
  };

  DK_GFX_Rect dest = {
    .x = desc.pos.x,
    .y = desc.pos.y,
    .w = desc.width * desc.scale.x,
    .h = desc.height * desc.scale.y
  };

  DK_GFX_Draw(context, context->textures[desc.slot], &src, &dest);
}

DK_API void DK_GFX_DrawSpritePro(DK_GFX_Context *context, DK_GFX_SpriteDescPro desc) {
  DK_GFX_Point current_tile_coord = { .x = desc.col, .y = desc.row };

  DK_GFX_Rect src = {
    .x = current_tile_coord.x * desc.width,
    .y = current_tile_coord.y * desc.height,
    .w = desc.width,
    .h = desc.height
  };

  DK_GFX_Rect dest = {
    .x = desc.pos.x,
    .y = desc.pos.y,
    .w = desc.dest_width,
    .h = desc.dest_height
  };

  DK_GFX_Draw(context, context->textures[desc.slot], &src, &dest);
}

DK_API void DK_GFX_DrawFilledCircle(SDL_Renderer* renderer, int32_t centerX, int32_t centerY, int32_t radius) {
  for (int32_t w = 0; w < radius * 2; w++) {
    for (int32_t h = 0; h < radius * 2; h++) {
      int32_t dx = radius - w;
      int32_t dy = radius - h;
      if ((dx * dx + dy * dy) <= (radius * radius)) {
        SDL_RenderDrawPoint(renderer, centerX + dx, centerY + dy);
      }
    }
  }
}

DK_API void DK_GFX_DrawCircle(SDL_Renderer* renderer, int32_t centerX, int32_t centerY, int32_t radius) {
  int32_t x = radius;
  int32_t y = 0;
  int32_t radiusError = 1 - x;

  while (x >= y) {
    SDL_RenderDrawPoint(renderer, centerX + x, centerY + y);
    SDL_RenderDrawPoint(renderer, centerX - x, centerY + y);
    SDL_RenderDrawPoint(renderer, centerX + x, centerY - y);
    SDL_RenderDrawPoint(renderer, centerX - x, centerY - y);
    SDL_RenderDrawPoint(renderer, centerX + y, centerY + x);
    SDL_RenderDrawPoint(renderer, centerX - y, centerY + x);
    SDL_RenderDrawPoint(renderer, centerX + y, centerY - x);
    SDL_RenderDrawPoint(renderer, centerX - y, centerY - x);

    y++;
    if (radiusError < 0) {
      radiusError += 2 * y + 1;
    } else {
      x--;
      radiusError += 2 * (y - x + 1);
    }
  }
}

DK_API struct TextTextureCacheNode* createCacheNode(char* text, SDL_Texture* texture, int width, int height) {
  struct TextTextureCacheNode* newNode = (struct TextTextureCacheNode*)DK_MALLOC(sizeof(struct TextTextureCacheNode));
  newNode->text = strdup(text);
  newNode->texture_cache.texture = texture;
  newNode->texture_cache.width = width;
  newNode->texture_cache.height = height;
  newNode->next = NULL;
  return newNode;
}

DK_API void addToCache(DK_GFX_Context *context, char* text, SDL_Texture* texture, int width, int height) {
  struct TextTextureCacheNode* newNode = createCacheNode(text, texture, width, height);
  newNode->next = context->text_texture_cache;
  context->text_texture_cache = newNode;
}

DK_API struct TextTextureCache* findInCache(DK_GFX_Context *context, char* text) {
  struct TextTextureCacheNode* current = context->text_texture_cache;
  while (current != NULL) {
    if (strcmp(current->text, text) == 0) {
      return &(current->texture_cache);
    }
    current = current->next;
  }
  return NULL;
}

DK_API void destroyCache(DK_GFX_Context *context) {
  struct TextTextureCacheNode* current = context->text_texture_cache;
  while (current != NULL) {
    struct TextTextureCacheNode* next = current->next;
    DK_FREE(current->text);
    SDL_DestroyTexture(current->texture_cache.texture);
    DK_FREE(current);
    current = next;
  }
  context->text_texture_cache = NULL;
}

DK_API void DK_GFX_DrawText_Internal(DK_GFX_Context *context, const char* text, SDL_Color color, int x, int y) {

  struct TextTextureCache* cachedTexture = findInCache(context, (char*)text);

  if (cachedTexture == NULL) {
    DK_GFX_Surface* surface = TTF_RenderText_Blended(context->font, text, color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(context->renderer, surface);
    addToCache(context, (char*)text, texture, surface->w, surface->h);
    SDL_FreeSurface(surface);
  }

  cachedTexture = findInCache(context, (char*)text);

  SDL_Rect rect = { .x = x, .y = y, .w = cachedTexture->width, .h = cachedTexture->height };
  SDL_RenderCopy(context->renderer, cachedTexture->texture, NULL, &rect);
}

DK_API void DK_GFX_DrawTextOptimized(DK_GFX_Context *gfx_context, DK_GFX_Text_Desc_t *desc)
{
  assert(gfx_context->font != NULL);
  assert(desc->text != NULL);

  DK_GFX_DrawText_Internal(gfx_context, desc->text, desc->color, desc->pos.x, desc->pos.y);
}

DK_API void DK_GFX_DrawText(DK_GFX_Context *gfx_context, DK_GFX_Text_Desc_t *desc)
{
  assert(gfx_context->font != NULL);
  assert(desc->text != NULL);

  DK_GFX_Color shadow = {0, 0, 0, desc->color.a};
  DK_GFX_Surface *surface = TTF_RenderText_Blended(gfx_context->font, desc->text, shadow);
  DK_GFX_Texture *texture = SDL_CreateTextureFromSurface(gfx_context->renderer, surface);
  DK_GFX_Rect rect = { .x = desc->pos.x + 2, .y = desc->pos.y + 2, .w = surface->w, .h = surface->h};
  SDL_RenderCopy(gfx_context->renderer, texture, NULL, &rect);
  SDL_FreeSurface(surface);
  SDL_DestroyTexture(texture);

  // draw text
  surface = TTF_RenderText_Blended(gfx_context->font, desc->text, desc->color);
  texture = SDL_CreateTextureFromSurface(gfx_context->renderer, surface);
  rect = (DK_GFX_Rect){.x = desc->pos.x, .y = desc->pos.y, .w = surface->w, .h = surface->h};
  SDL_RenderCopy(gfx_context->renderer, texture, NULL, &rect);
  SDL_FreeSurface(surface);
  SDL_DestroyTexture(texture);
}

DK_API void DK_GFX_DrawDebugText(DK_GFX_Context *gfx_context, DK_GFX_Debug_Text_Desc_t *desc)
{
  assert(gfx_context->font != NULL);
  assert(desc->text != NULL);

  // @background
  SDL_SetRenderDrawColor(gfx_context->renderer, desc->background_color.r, desc->background_color.g, desc->background_color.b, desc->background_color.a);
  SDL_Rect bg_rect = {
    .x = desc->pos.x - 4,
    .y = desc->pos.y - 4,
    .w = DK_GFX_GetTextWidth(gfx_context, desc->text) + 4,
    .h = DK_GFX_GetTextHeight(gfx_context, desc->text) + 4
  };
  SDL_RenderFillRect(gfx_context->renderer, &bg_rect);

  // @shadow
  DK_GFX_Color shadow = {0, 0, 0, desc->color.a};
  DK_GFX_Surface *surface = TTF_RenderText_Blended(gfx_context->font, desc->text, shadow);
  DK_GFX_Texture *texture = SDL_CreateTextureFromSurface(gfx_context->renderer, surface);
  DK_GFX_Rect rect = { .x = desc->pos.x + 2, .y = desc->pos.y + 2, .w = surface->w, .h = surface->h};
  SDL_RenderCopy(gfx_context->renderer, texture, NULL, &rect);
  SDL_FreeSurface(surface);
  SDL_DestroyTexture(texture);

#if 0
  DK_GFX_DrawText_Internal(gfx_context, desc->text, shadow, desc->pos.x + 2, desc->pos.y + 2);
#endif

  // @foregroundText
  surface = TTF_RenderText_Blended(gfx_context->font, desc->text, desc->color);
  texture = SDL_CreateTextureFromSurface(gfx_context->renderer, surface);
  rect = (DK_GFX_Rect){.x = desc->pos.x, .y = desc->pos.y, .w = surface->w, .h = surface->h};
  SDL_RenderCopy(gfx_context->renderer, texture, NULL, &rect);
  SDL_FreeSurface(surface);
  SDL_DestroyTexture(texture);

#if 0
  DK_GFX_DrawText_Internal(gfx_context, desc->text, desc->color, desc->pos.x, desc->pos.y);
#endif
}

DK_API int DK_GFX_GetTextWidth(DK_GFX_Context *gfx_context, const char *text)
{
  assert(gfx_context->font != NULL);
  assert(text != NULL);

  int width, height;
  TTF_SizeText(gfx_context->font, text, &width, &height);
  return width;
}

DK_API int DK_GFX_GetTextHeight(DK_GFX_Context *gfx_context, const char *text)
{
  assert(gfx_context->font != NULL);
  assert(text != NULL);

  int width, height;
  TTF_SizeText(gfx_context->font, text, &width, &height);
  return height;
}

DK_API int DK_GFX_GetTextHeightFor(TTF_Font *font, const char *text)
{
  assert(font != NULL);
  assert(text != NULL);

  int width, height;
  TTF_SizeText(font, text, &width, &height);
  return height;
}

DK_API int DK_GFX_GetTextWidthFor(TTF_Font *font, const char *text)
{
  assert(font != NULL);
  assert(text != NULL);

  int width, height;
  TTF_SizeText(font, text, &width, &height);
  return width;
}

DK_API void DK_GFX_GenerateCFile(const char *ifile, const char *ofile, const char *modname) {
  FILE *file = fopen(ifile, "r");
  if (file == NULL) {
    SDL_Log("DK_GFX_GenerateCFile: Failed to open file: %s\n", ifile);
    exit(EXIT_FAILURE);
  }

  // size 
  fseek(file, 0, SEEK_END);
  int32_t size = ftell(file);
  fseek(file, 0, SEEK_SET);

  uint8_t *buffer = (uint8_t*)DK_MALLOC(size);
  fread(buffer, size, 1, file);

  file = fopen(ofile, "w");
  if (file == NULL) {
    SDL_Log("DK_GFX_GenerateCFile: Failed to open file: %s\n", ofile);
    exit(EXIT_FAILURE);
  }

  fprintf(file, "#if !defined(__DK_GFX_ASSET_%s) \n", modname);
  fprintf(file, "#define __DK_GFX_ASSET_%s\n", modname);

  fprintf(file, "const int asset_%s_data_len = %d;\n", modname, size);
  fprintf(file, "unsigned char asset_%s_data[%d] = {\n", modname, size);

  for (int32_t i = 0; i < size; i++) {
    fprintf(file, "0x%02x", buffer[i]);
    if (i < size - 1) {
      fprintf(file, ", ");
    }
  }

  fprintf(file, "};\n");

  fprintf(file, "#endif // __DK_GFX_ASSET_%s\n", modname);

  DK_FREE(buffer);
  fclose(file);
}

DK_API DK_GFX_RWops *DK_GFX_RWFromMem(void *mem, int32_t size) {
  return SDL_RWFromMem(mem, size);
}

DK_API void DK_GFX_FreeRW(DK_GFX_RWops *rw) {
  SDL_FreeRW(rw);
}

DK_API DK_GFX_Key DK_GFX_ScancodeToKey(SDL_Scancode scancode) {
  if (scancode >= 0 && scancode < DK_GFX_SCANCODE_MAPPED_NUM) return DK_GFX_SCANCODE_LUT[scancode];
  return KEY_NULL;
}

/* taken from RayLib */
DK_API bool DK_GFX_IsKeyPressed(DK_GFX_Context *context,  DK_GFX_Key key) {
  bool pressed = false;
  if ((key > 0) && (key < MAX_KEYBOARD_KEYS))
  {
    if ((context->Keyboard.previousKeyState[key] == 0) && (context->Keyboard.currentKeyState[key] == 1)) {
      pressed = true;
    }
  }
  return pressed;
}

/* taken from RayLib */
DK_API bool DK_GFX_IsKeyDown(DK_GFX_Context *context,  DK_GFX_Key key) {
  bool down = false;
  if ((key > 0) && (key < MAX_KEYBOARD_KEYS))
  {
    if (context->Keyboard.currentKeyState[key] == 1) {
      down = true;
    }
  }
  return down;
}

DK_API void DK_GFX_PushEvent(DK_GFX_Context *context, DK_GFX_EventType type) {
  DK_GFX_Event event = { .type = type }; 
  SDL_PushEvent(&event);
}

DK_API bool DK_GFX_WindowShouldClose(DK_GFX_Context *context) {
  return !context->running;
}

DK_API void DK_GFX_GameInputManagerSetKey(DK_GFX_Context *context, DK_GFX_INPUT_SENDER_ID sender, DK_GFX_INPUT_KEY key, bool state)
{
  context->GameInputs.keys[sender][key] = state;
}

DK_API bool DK_GFX_GameInputManagerKey(DK_GFX_Context *context, DK_GFX_INPUT_SENDER_ID sender, DK_GFX_INPUT_KEY key)
{
  return context->GameInputs.keys[sender][key];
}

DK_API void DK_GFX_DiscoverAndGrabGameController(DK_GFX_Context *context) {
  for (int i = 0; (i < SDL_NumJoysticks()) && (i < DK_GFX_INPUT_SENDER_ID_COUNT); i++) {
    context->GameInputs.controller[i] = SDL_JoystickOpen(i);
    if (context->GameInputs.controller[i]) {
      context->Gamepad.ready[i] = true;
      strncpy(context->Gamepad.name[i], SDL_JoystickName(context->GameInputs.controller[i]), 63);
      context->Gamepad.name[i][63] = '\0';
    } else {
      SDL_Log("Failed to open joystick %d: %s\n", i, SDL_GetError());
    }
  }
}

DK_API bool DK_GFX_IsGamepadButtonPressed(DK_GFX_Context *context, DK_GFX_INPUT_SENDER_ID gamepad, int button) {
  bool pressed = false;
  if ((gamepad < DK_GFX_INPUT_SENDER_ID_COUNT) && context->Gamepad.ready[gamepad] && (button < MAX_GAMEPAD_BUTTONS) &&
      (context->Gamepad.previousButtonState[gamepad][button] == 0) && (context->Gamepad.currentButtonState[gamepad][button] == 1)) pressed = true;
  return pressed;
}

DK_API bool DK_GFX_IsGamepadButtonDown(DK_GFX_Context *context, DK_GFX_INPUT_SENDER_ID gamepad, int button) {
  bool down = false;
  if ((gamepad < DK_GFX_INPUT_SENDER_ID_COUNT) && context->Gamepad.ready[gamepad] && (button < MAX_GAMEPAD_BUTTONS) &&
      (context->Gamepad.currentButtonState[gamepad][button] == 1)) down = true;
  return down;
}

DK_API void DK_GFX_PullEvents(DK_GFX_Context *context) {

  for (int i = 0; (i < SDL_NumJoysticks()) && (i < DK_GFX_INPUT_SENDER_ID_COUNT); i++) {
    if (context->Gamepad.ready[i]) {
      for (int k = 0; k < MAX_GAMEPAD_BUTTONS; k++) {
        context->Gamepad.previousButtonState[i][k] = context->Gamepad.currentButtonState[i][k];
      }
    }
  }

  for (int i = 0; i < MAX_KEYBOARD_KEYS; ++i) {
    context->Keyboard.previousKeyState[i] = context->Keyboard.currentKeyState[i];
  }

  while (SDL_PollEvent(context->event)) {

    switch (context->event->type) {

      case SDL_WINDOWEVENT_RESIZED: {
#if 0
        DK_GFX_UpdateScreenSize(gfx_context, &window_desc,
        gfx_context->event->window.data1, gfx_context->event->window.data2);
        gfx_context->width = window_desc.width;
        gfx_context->height = window_desc.height;
#endif
        context->width = DK_GFX_GetWindowScreenWidth(context);
        context->height = DK_GFX_GetWindowScreenHeight(context);

      } break;

      case SDL_KEYDOWN: {
        /* Quit the program: @debug @quit */
#if !defined(PLATFORM_WEB)
#if defined(DEBUG)
        if (context->event->key.keysym.sym == SDLK_ESCAPE) {
          context->running = false;
        }
#endif

        if (context->event->key.keysym.sym == SDLK_F11) {
         DK_GFX_WindowToggleFullScreen(context);
        }
#endif
        DK_GFX_Key key = DK_GFX_ScancodeToKey(context->event->key.keysym.scancode);
        context->Keyboard.currentKeyState[key] = 1;
      } break;

      case SDL_KEYUP: {
        DK_GFX_Key key = DK_GFX_ScancodeToKey(context->event->key.keysym.scancode);
        context->Keyboard.currentKeyState[key] = 0;
      } break;

      case SDL_QUIT: {
#if defined(PLATFORM_WEB)
        emscripten_cancel_main_loop();
#else
        context->running = false;
#endif
      } break;

      // TODO (David): fix the issue with joystick re-connection,
      // now when joystick is disconnected, we are not able to recover user state,
      // by meaning that user that was 0 and disconnected when reconnected, it's detected by 1 and 1 is already busy

      case SDL_JOYDEVICEADDED: {
        int32_t jid = context->event->jdevice.which;
        if (!context->Gamepad.ready[jid] && (jid < DK_GFX_INPUT_SENDER_ID_COUNT)) {
          context->GameInputs.controller[jid] = SDL_JoystickOpen(jid);
          
          if (context->GameInputs.controller[jid]) {
            context->Gamepad.ready[jid] = true;
            strncpy(context->Gamepad.name[jid], SDL_JoystickName(context->GameInputs.controller[jid]), 63);
            context->Gamepad.name[jid][63] = '\0';
          } else {
            SDL_Log("Failed to open joystick %d: %s\n", jid, SDL_GetError());
          }
        }
      }
      break;

      case SDL_JOYDEVICEREMOVED: {
        int32_t jid = context->event->jdevice.which;
        if (jid == SDL_JoystickInstanceID(context->GameInputs.controller[jid])) {
          SDL_JoystickClose(context->GameInputs.controller[jid]);
          context->GameInputs.controller[jid] = SDL_JoystickOpen(0);
          context->GameInputs.controller[jid] = NULL;
          context->Gamepad.ready[jid] = false;
          memset(context->Gamepad.name[jid], 0, 64);
        }
      } break;

      case SDL_JOYBUTTONDOWN: {
        int32_t button = -1;

        switch (context->event->jbutton.button) {
          case SDL_CONTROLLER_BUTTON_Y: button = GAMEPAD_BUTTON_RIGHT_FACE_UP; break;
          case SDL_CONTROLLER_BUTTON_B: button = GAMEPAD_BUTTON_RIGHT_FACE_RIGHT; break;
          case SDL_CONTROLLER_BUTTON_A: button = GAMEPAD_BUTTON_RIGHT_FACE_DOWN; break;
          case SDL_CONTROLLER_BUTTON_X: button = GAMEPAD_BUTTON_RIGHT_FACE_LEFT; break;

          case SDL_CONTROLLER_BUTTON_LEFTSHOULDER: button = GAMEPAD_BUTTON_LEFT_TRIGGER_1; break;
          case SDL_CONTROLLER_BUTTON_RIGHTSHOULDER: button = GAMEPAD_BUTTON_RIGHT_TRIGGER_1; break;

          case SDL_CONTROLLER_BUTTON_BACK: button = GAMEPAD_BUTTON_MIDDLE_LEFT; break;
          case SDL_CONTROLLER_BUTTON_GUIDE: button = GAMEPAD_BUTTON_MIDDLE; break;
          case SDL_CONTROLLER_BUTTON_START: button = GAMEPAD_BUTTON_MIDDLE_RIGHT; break;

          case SDL_CONTROLLER_BUTTON_DPAD_UP: button = GAMEPAD_BUTTON_LEFT_FACE_UP; break;
          case SDL_CONTROLLER_BUTTON_DPAD_RIGHT: button = GAMEPAD_BUTTON_LEFT_FACE_RIGHT; break;
          case SDL_CONTROLLER_BUTTON_DPAD_DOWN: button = GAMEPAD_BUTTON_LEFT_FACE_DOWN; break;
          case SDL_CONTROLLER_BUTTON_DPAD_LEFT: button = GAMEPAD_BUTTON_LEFT_FACE_LEFT; break;

          case SDL_CONTROLLER_BUTTON_LEFTSTICK: button = GAMEPAD_BUTTON_LEFT_THUMB; break;
          case SDL_CONTROLLER_BUTTON_RIGHTSTICK: button = GAMEPAD_BUTTON_RIGHT_THUMB; break;
          default: break;
        }

        if (button >= 0) {
          context->Gamepad.currentButtonState[context->event->jbutton.which][button] = 1;
          context->Gamepad.lastButtonPressed = button;
        }
      } break;

      case SDL_JOYBUTTONUP: {
        int32_t button = -1;

        switch (context->event->jbutton.button) {
          case SDL_CONTROLLER_BUTTON_Y: button = GAMEPAD_BUTTON_RIGHT_FACE_UP; break;
          case SDL_CONTROLLER_BUTTON_B: button = GAMEPAD_BUTTON_RIGHT_FACE_RIGHT; break;
          case SDL_CONTROLLER_BUTTON_A: button = GAMEPAD_BUTTON_RIGHT_FACE_DOWN; break;
          case SDL_CONTROLLER_BUTTON_X: button = GAMEPAD_BUTTON_RIGHT_FACE_LEFT; break;

          case SDL_CONTROLLER_BUTTON_LEFTSHOULDER: button = GAMEPAD_BUTTON_LEFT_TRIGGER_1; break;
          case SDL_CONTROLLER_BUTTON_RIGHTSHOULDER: button = GAMEPAD_BUTTON_RIGHT_TRIGGER_1; break;

          case SDL_CONTROLLER_BUTTON_BACK: button = GAMEPAD_BUTTON_MIDDLE_LEFT; break;
          case SDL_CONTROLLER_BUTTON_GUIDE: button = GAMEPAD_BUTTON_MIDDLE; break;
          case SDL_CONTROLLER_BUTTON_START: button = GAMEPAD_BUTTON_MIDDLE_RIGHT; break;

          case SDL_CONTROLLER_BUTTON_DPAD_UP: button = GAMEPAD_BUTTON_LEFT_FACE_UP; break;
          case SDL_CONTROLLER_BUTTON_DPAD_RIGHT: button = GAMEPAD_BUTTON_LEFT_FACE_RIGHT; break;
          case SDL_CONTROLLER_BUTTON_DPAD_DOWN: button = GAMEPAD_BUTTON_LEFT_FACE_DOWN; break;
          case SDL_CONTROLLER_BUTTON_DPAD_LEFT: button = GAMEPAD_BUTTON_LEFT_FACE_LEFT; break;

          case SDL_CONTROLLER_BUTTON_LEFTSTICK: button = GAMEPAD_BUTTON_LEFT_THUMB; break;
          case SDL_CONTROLLER_BUTTON_RIGHTSTICK: button = GAMEPAD_BUTTON_RIGHT_THUMB; break;
          default: break;
        }

        if (button >= 0) {
          context->Gamepad.currentButtonState[context->event->jbutton.which][button] = 0;
          if (context->Gamepad.lastButtonPressed == button) {
            context->Gamepad.lastButtonPressed = 0;
          }
        }
      } break;
    }
  }

  context->mouse_state = SDL_GetMouseState(&context->mouse.x, &context->mouse.y);
}


DK_API void DK_GFX_ScreenTransitionInit(DK_GFX_Context *context, int32_t default_screen, float speed) 
{
  context->screen_transition.speed = speed;
  context->screen_transition.state = FADE_NONE;
  context->screen_transition.prev_screen = default_screen;
}

DK_API void DK_GFX_ScreenTransitionRender(DK_GFX_Context *gfx_context)
{
  if (gfx_context->screen_transition.state == FADE_OUT && gfx_context->alpha > 0.0f) {
    gfx_context->alpha -= gfx_context->screen_transition.speed * gfx_context->dt;
    if (gfx_context->alpha <= 0.0f) {
      gfx_context->alpha = 0.0f;
      gfx_context->screen_transition.state = FADE_NONE;
    }
    DK_GFX_DrawFullScreenRect(gfx_context, gfx_context->alpha);
  }
}

DK_API void DK_GFX_TransitionScreen(DK_GFX_Context *gfx_context, int32_t *screen, int32_t new_scene)
{
  if (gfx_context->screen_transition.state == FADE_NONE) {
    if (new_scene != *screen) {
      gfx_context->screen_transition.state = FADE_OUT;
      gfx_context->alpha = 1.0f;
      gfx_context->screen_transition.prev_screen = *screen;
      *screen = new_scene;
    }
  }
}

// @AudioFX API

#ifdef USE_SDL2_MIXER_BACKEND

DK_API DK_GFX_AudioFx *DK_GFX_LoadAudioFx(DK_GFX_Context *context, DK_GFX_AUDIO_FX storage_index, const char *path) {
  context->Audio.audio_fx[storage_index] = Mix_LoadWAV(path);
  if (!context->Audio.audio_fx[storage_index]) {
    SDL_Log("Failed to load sound effect! SDL_mixer Error: %s\n", Mix_GetError());
    exit(EXIT_FAILURE);
  }

  return context->Audio.audio_fx[storage_index];
}

DK_API DK_GFX_AudioFx *DK_GFX_LoadAudioFxFromMemory(DK_GFX_Context *context, DK_GFX_AUDIO_FX storage_index, DK_GFX_RWops *rw, bool free_rw) {
  context->Audio.audio_fx[storage_index] = Mix_LoadWAV_RW(rw, free_rw);
  if (!context->Audio.audio_fx[storage_index]) {
    SDL_Log("Failed to load sound effect! SDL_mixer Error: %s\n", Mix_GetError());
    exit(EXIT_FAILURE);
  }

  return context->Audio.audio_fx[storage_index];
}

DK_API int32_t DK_GFX_PlayAudioFx(DK_GFX_Context *context, DK_GFX_AUDIO_FX storage_index) {
  /* use fx exclusive channel */
  int32_t channel = Mix_PlayChannel((int32_t)storage_index, context->Audio.audio_fx[storage_index], context->Audio.audio_fx_play_count);
  if (channel == -1) {
    SDL_Log("Failed to play sound effect! SDL_mixer Error: %s\n", Mix_GetError());
    exit(EXIT_FAILURE);
  }

  return channel;
}

DK_API void DK_GFX_SetAudioFxVolume(DK_GFX_Context *context, DK_GFX_AUDIO_FX storage_index, float volume) {
  int32_t scaledVolume = (int32_t)(volume * MIX_MAX_VOLUME + 0.5);
  Mix_Volume((int32_t)storage_index, scaledVolume);
}

DK_API void DK_GFX_SetAudioFxMasterVolume(DK_GFX_Context *context, float volume) {
  int32_t scaledVolume = (int32_t)(volume * MIX_MAX_VOLUME + 0.5);
  /* update all channels volume */
  Mix_Volume(-1, scaledVolume);
}

DK_API void DK_GFX_StopAudioFx(DK_GFX_Context *context, DK_GFX_AUDIO_FX storage_index) {
  Mix_HaltChannel((int32_t)storage_index);
}

DK_API void DK_GFX_PauseAudioFx(DK_GFX_Context *context, DK_GFX_AUDIO_FX storage_index) {
  Mix_Pause((int32_t)storage_index);
}

DK_API void DK_GFX_ResumeAudioFxAny(DK_GFX_Context *context, int32_t channel) {
  Mix_Resume(channel);
}

DK_API void DK_GFX_PauseAudioFxAny(DK_GFX_Context *context, int32_t channel) {
  Mix_Pause(channel);
}

DK_API void DK_GFX_StopAudioFxAny(DK_GFX_Context *context, int32_t channel) {
  Mix_HaltChannel(channel);
}

DK_API void DK_GFX_StopAudioAll(DK_GFX_Context *context, int32_t channel) {
  Mix_HaltChannel(-1);
}

DK_API void DK_GFX_SetAudioFxPlayCount(DK_GFX_Context *context, int32_t n)
{
  context->Audio.audio_fx_play_count = n;
}
#else

DK_API void DK_GFX_LoadAudioFx(DK_GFX_Context *context, DK_GFX_AUDIO_FX storage_index, const char *path) {
  context->Audio.audio_fx[storage_index] = (DK_GFX_AudioClip *)malloc(sizeof(DK_GFX_AudioClip));
  if (!context->Audio.audio_fx[storage_index]) {
      SDL_Log("Memory allocation failed!\n");
      exit(EXIT_FAILURE);
  }
  
  if (SDL_LoadWAV(path, &context->Audio.device_spec, &context->Audio.audio_fx[storage_index]->buffer, &context->Audio.audio_fx[storage_index]->bufferSize) == NULL) {
      SDL_Log("Failed to load sound effect! SDL Error: %s\n", SDL_GetError());
      exit(EXIT_FAILURE);
  }
}

DK_API void DK_GFX_PlayAudioFx(DK_GFX_Context *context, DK_GFX_AUDIO_FX storage_index) {

  if (context->Audio.device_id == 0) {
    SDL_Log("Failed to open audio device! SDL Error: %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }

  SDL_ClearQueuedAudio(context->Audio.device_id);
  SDL_PauseAudioDevice(context->Audio.device_id, 1);

  SDL_QueueAudio(context->Audio.device_id, context->Audio.audio_fx[storage_index]->buffer, context->Audio.audio_fx[storage_index]->bufferSize);
  SDL_PauseAudioDevice(context->Audio.device_id, 0);
}

DK_API void DK_GFX_SetMasterVolume(DK_GFX_Context *context, int volume) {
  context->Audio.master_volume = SDL_clamp(volume, 0, SDL_MIX_MAXVOLUME);
}

DK_API void DK_GFX_SetAudioFxMasterVolume(DK_GFX_Context *context, float volume) {
  DK_GFX_SetMasterVolume(context, (int32_t)(volume * 100.0f));
}

DK_API void DK_GFX_SetAudioFxVolume(DK_GFX_Context *context, DK_GFX_AUDIO_FX storage_index, float volume) {
  DK_GFX_SetMasterVolume(context, (int32_t)(volume * 100.0f));
}

DK_API void DK_GFX_StopAudioFx(DK_GFX_Context *context, DK_GFX_AUDIO_FX storage_index) {
  SDL_FreeWAV(context->Audio.audio_fx[storage_index]->buffer);
  free(context->Audio.audio_fx[storage_index]);
  context->Audio.audio_fx[storage_index] = NULL;
}

#endif // USE_SDL2_MIXER_BACKEND

#endif // DK_GFX_IMPL


#if defined(__cplusplus)
}
#endif // __cplusplus

#endif // DK_GFX_H
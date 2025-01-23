/**
 * @file main.c
 * @author David Kviloria (dkviloria@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-07-05
 *
 * @copyright Copyright (c) 2023 SKYSTAR GAMES Interactive
 *
 */
#include "dk_game.h"

#include <stdbool.h>
#include <string.h>
#include <time.h>

#define DK_GFX_IMPL
#include "dk_gfx.h"

DK_GFX_Renderer *CreateRenderer(DK_GFX_Window *window);

TTF_Font *DEFAULT_FONT = NULL;

#define FRAME_RATE 60
#define FRAME_DELAY (1000 / FRAME_RATE)

#define MAX_INPUT_TEXT_BUFFER_SIZE 1024

#if defined(PLATFORM_WEB)
#  define WINDOW_WIDTH 1080
#  define WINDOW_HEIGHT 720
#else
  #if defined(__APPLE__)
  #  define WINDOW_WIDTH 1024
  #  define WINDOW_HEIGHT 720
  #else
  #  define WINDOW_WIDTH 1440
  #  define WINDOW_HEIGHT 900
  #endif
#endif

static DK_GFX_Context *gfx_context = NULL;

DK_GFX_Window_Desc_t window_desc = {
  .width = WINDOW_WIDTH,
  .height = WINDOW_HEIGHT,
  .title = "A Window",
  .flags = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL,
  .running = true,
};

void Init() {
  GameInit(gfx_context);
}

void Update() {
  GameUpdate(gfx_context);
}

void Render()
{
  GameRender(gfx_context);
  DK_GFX_RenderPresent(gfx_context->renderer);
}

void Destroy()
{
  GameDestroy();

  DK_GFX_DestroyTexture(gfx_context->texture);
  DK_GFX_DestroyRenderer(gfx_context->renderer);
  DK_GFX_DestroyWindow(gfx_context->window);

  IMG_Quit();
  TTF_CloseFont(DEFAULT_FONT);
  TTF_Quit();
  SDL_Quit();
}

#if defined(PLATFORM_WEB)
EMSCRIPTEN_KEEPALIVE
void JS_GetCanvasSize();
#endif

void main_loop();

#if defined(PLATFORM_WEB)
void ListPreloadedFiles(const char *path) {
  EM_ASM(
    var files = FS.readdir(UTF8ToString($0));
    for (var i = 0; i < files.length; i++) {
      if (files[i] !== '.' && files[i] !== '..') {
        console.log('Preloaded file: ' + $0 + '/' + files[i]);
      }
    }
  , path);
}
#endif

typedef struct {
  Uint8* buffer;
  Uint32 bufferLength;
  Uint32 bufferPosition;
} AudioData;

void audioCallback(void* userdata, Uint8* stream, int len) {
  AudioData* audioData = (AudioData*)userdata;
  if (audioData->bufferPosition >= audioData->bufferLength) {
    return;
  }

  Uint32 bytesToCopy = audioData->bufferLength - audioData->bufferPosition;
  if (bytesToCopy > (Uint32)len) {
    bytesToCopy = len;
  }

  SDL_memcpy(stream, audioData->buffer + audioData->bufferPosition, bytesToCopy);
  audioData->bufferPosition += bytesToCopy;

  if (len > (int)bytesToCopy) {
    SDL_memset(stream + bytesToCopy, 0, len - bytesToCopy);
  }
}

int main()
{
  srand(time(0));

  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_JOYSTICK) < 0) {
    SDL_Log("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    SDL_Quit();
  }

  if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
    SDL_Log("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
    SDL_Quit();
  }

  if (TTF_Init() == -1) {
    SDL_Log("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
    SDL_Quit();
  }

  DEFAULT_FONT         = DK_GFX_LoadFont("assets/PixelOperator8.ttf", 15);
  gfx_context          = &(DK_GFX_Context){
    .running           = 1,
    .window            = DK_GFX_CreateWindow(window_desc.title, window_desc.width, window_desc.height, window_desc.flags),
    .default_font      = DEFAULT_FONT,
    .font              = DEFAULT_FONT,
    .input_text_buffer = malloc(sizeof(char) * MAX_INPUT_TEXT_BUFFER_SIZE),
    .event             = malloc(sizeof(SDL_Event)),
    .alpha             = 1.0f,
    .Audio             = {
      .master_volume = 128
    }
  };

#if defined(USE_SDL2_MIXER_BACKEND)

  if (Mix_Init(MIX_INIT_OGG) == 0) {
    SDL_Log("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
    SDL_Quit();
  }

  if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) < 0) {
    SDL_Log("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
    SDL_Quit();
  }

#else
    SDL_zero(gfx_context->Audio.device_spec);
    gfx_context->Audio.device_spec.freq = 44100;
    gfx_context->Audio.device_spec.format = AUDIO_S16SYS;
    gfx_context->Audio.device_spec.channels = 2;
    gfx_context->Audio.device_spec.samples = 4096;

    // gfx_context.Audio.spec.callback = audioCallback;
    // gfx_context.Audio.spec.userdata = &context.Audio;

    gfx_context->Audio.device_id = SDL_OpenAudioDevice(NULL, 0, &gfx_context->Audio.device_spec, NULL, 0);
    if (gfx_context->Audio.device_id == 0) {
      SDL_Log("Failed to open audio device! SDL Error: %s\n", SDL_GetError());
      exit(EXIT_FAILURE);
    }
#endif

  SDL_SetHint(SDL_HINT_JOYSTICK_THREAD, "1");

  DK_GFX_DiscoverAndGrabGameController(gfx_context);

  gfx_context->width = window_desc.width;
  gfx_context->height = window_desc.height;
  gfx_context->input_text_buffer[0] = '\0';

  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,   24);
  SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

#if 0
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
#endif

  gfx_context->renderer = DK_GFX_CreateRenderer(gfx_context->window, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);
  DK_GFX_GetRendererLogicalSize(gfx_context->renderer, &window_desc.width, &window_desc.height);

  gfx_context->Init = &Init;
  gfx_context->Update = &Update;
  gfx_context->Render = &Render;
  gfx_context->Destroy = &Destroy;


  gfx_context->Init();


#if defined(PLATFORM_WEB)
  printf("Preloading files:\n");
  ListPreloadedFiles("/assets");

  emscripten_set_main_loop(main_loop, 0, 1);
#else

  while (!DK_GFX_WindowShouldClose(gfx_context)) {
    main_loop();
  }
#endif

  gfx_context->Destroy();
  return 0;
}

void main_loop()
{
  static uint64_t last_frame_time = 0;
  uint64_t frame_start = SDL_GetPerformanceCounter();
  if (last_frame_time == 0) {
    last_frame_time = frame_start;
  }

  DK_GFX_PullEvents(gfx_context);
  gfx_context->mouse_state = SDL_GetMouseState(&gfx_context->mouse.x, &gfx_context->mouse.y);

  double current_time = SDL_GetPerformanceCounter();
  double delta_time = (current_time - last_frame_time) / SDL_GetPerformanceFrequency();
  
  gfx_context->dt = delta_time;

  // UPDATE PHASE
  // ----------------------------------------
  gfx_context->Update();
  // ----------------------------------------
  // END OF UPDATE PHASE
  static bool first_frame = true;
  if (first_frame) {
    first_frame = false;
  }

  // DRAWING CODE
  // ----------------------------------------
  gfx_context->Render();
  // ----------------------------------------
  // END OF DRAWING CODE

  // FRAME RATE CAP
  // ----------------------------------------
#if !defined(PLATFORM_WEB)
  double frame_time = (SDL_GetPerformanceCounter() - frame_start) / SDL_GetPerformanceFrequency() * 1000.0;
  if (FRAME_DELAY > frame_time) {
    SDL_Delay(FRAME_DELAY - frame_time);
  }
#endif
  // ----------------------------------------
  // END FRAME RATE CAP

  last_frame_time = frame_start;
}


#if defined(PLATFORM_WEB)
EMSCRIPTEN_KEEPALIVE
void JS_GetCanvasSize()
{
  int width, height;
  emscripten_get_canvas_element_size("#canvas", &width, &height);
  DK_GFX_SetRenderLogicalSize(gfx_context->renderer, width, height);
}
#endif
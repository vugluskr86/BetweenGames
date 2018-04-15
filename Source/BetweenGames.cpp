#ifdef _WINDOWS
#include <windows.h>
#endif // _WINDOWS

#include "Common.h"
#include "Window.h"
#include "RenderImgui.h"
#include "RenderSprites.h"

#include "GameState.h"
#include "GameSceneState.h"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#include <SDL2/SDL.h>
#include <GLES2/gl2.h>
#include "imgui/imgui.h"

std::unique_ptr<BWG::Game::GameStateManager> gameApp;

// std::unique_ptr<BWG::System::Window> window;
static bool main_loop_running = true;

void main_loop() {
   SDL_Event event;
   while(SDL_PollEvent(&event)) {
      switch(event.type) {
      case SDL_QUIT: {
         main_loop_running = false;
         break;
      }
      case SDL_KEYUP: {
         int sym = event.key.keysym.sym;
         if(sym == SDLK_ESCAPE) { main_loop_running = false; }
         break;
      }
      }
      gameApp->ProcessEvent(&event);
   }

  // if(window->visible) {
      gameApp->Render();
 //  }
}

int start() {

   if(SDL_Init(SDL_INIT_VIDEO) < 0) { 
      return -1;
   }

#ifdef _WINDOWS
   SDL_SetHint(SDL_HINT_OPENGL_ES_DRIVER, "1");
   SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
   SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
   SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
   SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
   SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
#endif
   SDL_GL_SetSwapInterval(1);
   ImGui::CreateContext();


   gameApp = std::unique_ptr<BWG::Game::GameStateManager>(new BWG::Game::GameStateManager());

   gameApp->PushState(std::make_unique<BWG::Game::GameSceneState>());
   gameApp->ChangeState(BWG::Game::STATE_GAME_SCENE);

   /*
   window = std::unique_ptr<BWG::System::Window>(new BWG::System::Window(800, 600));

   // gameApp

   std::unique_ptr<BWG::Render::RenderSprites> tile_layer(new BWG::Render::RenderSprites());
   window->AddLayer(tile_layer.get());
   std::vector<BWG::Render::Sprite> tiles = {
      { 0, 0, 0 },
      { 0, 1, 1 },
      { 2, 1, 1 },
   };
   tile_layer->SetTiles(tiles);
   std::unique_ptr<BWG::Render::RenderImGui> ui_layer(new BWG::Render::RenderImGui());
   window->AddLayer(ui_layer.get());
   */

#ifdef __EMSCRIPTEN__
  // 0 fps means to use requestAnimationFrame; non-0 means to use setTimeout.
  emscripten_set_main_loop(main_loop, 0, 1);
#else
  while (main_loop_running) {
    main_loop();
    SDL_Delay(16);
  }
#endif
  gameApp = nullptr;
   SDL_Quit();
   return 0;
}

#ifndef _WINDOWS
int main()
{
    return start();
}
#else
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
   _In_opt_ HINSTANCE hPrevInstance,
   _In_ LPWSTR    lpCmdLine,
   _In_ int       nCmdShow)
{
   return start();
}
#endif

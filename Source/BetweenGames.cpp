#include "Common.h"
#include "Window.h"
#include "RenderImgui.h"

#include <SDL2/SDL.h>
#include <GLES2/gl2.h>
#include "imgui/imgui.h"

std::unique_ptr<BWG::System::Window> window;
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

      window->ProcessEvent(&event);
   }

   if(window->visible) {
      window->Render();
   }
}


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
   _In_opt_ HINSTANCE hPrevInstance,
   _In_ LPWSTR    lpCmdLine,
   _In_ int       nCmdShow)
{
   if(SDL_Init(SDL_INIT_VIDEO) < 0) { 
      return -1;
   }

   SDL_SetHint(SDL_HINT_OPENGL_ES_DRIVER, "1");

   SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
   SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
   SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
   SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
   SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);

   SDL_GL_SetSwapInterval(1);

   ImGui::CreateContext();

   window = std::unique_ptr<BWG::System::Window>(new BWG::System::Window(800, 600));

   std::unique_ptr<BWG::Render::RenderImGui> ui_layer(new BWG::Render::RenderImGui());
   window->AddLayer(ui_layer.get());

   while(main_loop_running) {
      main_loop();
      SDL_Delay(16);
   }

   window = nullptr;

   SDL_Quit();
   return 0;
}
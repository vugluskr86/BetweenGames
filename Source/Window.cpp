#include "Common.h"
#include "Window.h"

#include <SDL2/SDL.h>
#include "OpenGLWrap.h"
#include "RenderLayer.h"

namespace BWG {

   namespace Render {
      // NOTE: I need this implementation to be in a cc file and not an h
      // file so that the compiler knows where to put the vtable
      IRenderLayer::~IRenderLayer() {}
   }

   namespace System {
   
      struct WindowImpl {
         SDL_Window* window;
         bool context_initialized;
         OpenGL::GlContext context;
         std::vector<std::unique_ptr<Render::IRenderLayer>> layers;

         WindowImpl(SDL_Window* window_);
         ~WindowImpl();
      };

      int Window::FRAME = 0;
   

      Window::Window(int width_, int height_)
         : visible(true), width(width_), height(height_),
         self(new WindowImpl(SDL_CreateWindow("Skeleton",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            width,
            height,
            SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
         )))
      {
         HandleResize();
      }

      Window::~Window() {}


      void Window::AddLayer(std::unique_ptr<Render::IRenderLayer> layer) {
         self->layers.emplace_back(std::move(layer));
      }


      void Window::HandleResize() {
         self->context_initialized = false;
         SDL_GL_GetDrawableSize(self->window, &width, &height);
         glViewport(0, 0, width, height);
      }


      void Window::Render() {
         if(visible) {
            glClear(GL_COLOR_BUFFER_BIT);
            for(auto &layer : self->layers) {
               if(layer->IsEnabled()) {
                  layer->Render(self->window, !self->context_initialized);
               }
            }
            self->context_initialized = true;
            SDL_GL_SwapWindow(self->window);
            FRAME++;
         }
      }

      void Window::ProcessEvent(SDL_Event* event) {
         if(event->type == SDL_WINDOWEVENT) {
            switch(event->window.event) {
            case SDL_WINDOWEVENT_SHOWN: { 
               visible = true;
               break; 
            }
            case SDL_WINDOWEVENT_HIDDEN: {
               visible = false;
               break; 
            }
            case SDL_WINDOWEVENT_SIZE_CHANGED: { HandleResize(); break; }
            }
         }

         for(auto &layer : self->layers) {
            if(layer->IsEnabled()) {
               layer->ProcessEvent(event);
            }
         }
      }


      WindowImpl::WindowImpl(SDL_Window* window_)
         :window(window_), context_initialized(false), context(window)
      {
         SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
         glClearColor(1.0, 1.0, 1.0, 1.0);
      }

      WindowImpl::~WindowImpl() {
         SDL_DestroyWindow(window);
      }

   }
}
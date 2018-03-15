#pragma once

#include <SDL2/SDL.h>
#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glext.h>
#else
#define GL_GLEXT_PROTOTYPES 1
#include <SDL2/SDL_opengles2.h>
#endif

#include "nocopy.h"

namespace BWG {
   namespace OpenGL {

      // Check for any OpenGL errors and print them
      void GLERRORS(const char* label);

      SDL_Surface* CreateRGBASurface(int width, int height);

      struct ShaderProgram : Utils::nocopy {
         GLuint id;
         ShaderProgram(const char* vertex_shader, const char* fragment_shader);
         ~ShaderProgram();

      private:
         void AttachShader(GLenum type, const GLchar* source);
      };


      struct Texture : Utils::nocopy {
         GLuint id;
         Texture(SDL_Surface* surface = nullptr);
         ~Texture();
         void CopyFromPixels(int width, int height, GLenum format, void* pixels);
         void CopyFromSurface(SDL_Surface* surface);
      };


      struct VertexBuffer : Utils::nocopy {
         GLuint id;
         VertexBuffer();
         ~VertexBuffer();
      };


      struct GlContext : Utils::nocopy {
         SDL_GLContext id;
         GlContext(SDL_Window* window);
         ~GlContext();
      };
   }
}
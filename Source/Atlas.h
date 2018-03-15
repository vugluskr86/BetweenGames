#pragma once

struct SDL_Surface;

namespace BWG {

   namespace System {
   
      struct AtlasImpl;

      struct SpriteLocation {
         float x0, y0, x1, y1; // Corners in world coordinates
         float s0, t0, s1, t1; // Corners in texture coordinates
      };

      class Atlas {
      public:
         Atlas();
         ~Atlas();

         // An Atlas contains a set of surfaces
         int LoadImage(const char* filename);
         int AddSurface(SDL_Surface* surface);

         // Call this after images are loaded.
         SDL_Surface* GetSurface();

         // Get image data for a given sprite id
         const SpriteLocation& GetLocation(int id) const;

      private:
         std::unique_ptr<AtlasImpl> self;
      };

   }

}
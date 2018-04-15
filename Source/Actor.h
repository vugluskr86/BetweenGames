#pragma once

#include "Direction.h"

namespace BWG {
   namespace Game {

      class Actor
      {
      public:
         Actor();
         ~Actor();

         void MoveTo(BWG::Utils::eDirection dir, unsigned length);
      };
   }
}
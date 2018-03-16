#pragma once

#include "GameCommon.h"
#include "GameObject.h"

namespace BWG {
   namespace Game {

      class Player;

      class Door : public AbstractGameObject
      {
         bool _opened;
      public:
         Door();
         void Open(Player& player);
         bool IsOpen() const { return _opened; }
      };

   }
}


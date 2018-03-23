#pragma once

#include "GameCommon.h"

#include <memory>

namespace BWG {
   namespace Game {

      class AbstractGameObject;
      struct DoorImpl;
      class Player;
      
      class Door : public AbstractGameObject
      {
      protected:
         std::unique_ptr<DoorImpl> self;
      public:
         Door();
         ~Door();
         void Open(Player& player);
         bool IsOpen() const;
      };

   }
}


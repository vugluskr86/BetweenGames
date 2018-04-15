#pragma once

#include <memory>

namespace BWG {
   namespace Game {

      enum eActions
      {
         EA_MOVE_ACTOR, // идет в клетку
         EA_ATTACK,     // атакует по клетке
      };
      
      class GameMapView;
      class Player;

      class Action
      {
      public:
         virtual eActions GetType() const = 0;
         virtual void Proceed(GameMapView* map, Player* Player) = 0;
      };
   }
}
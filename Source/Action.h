#pragma once

#include <memory>

#include "Direction.h"
#include "QuadTree.h"

namespace BWG {
   namespace Game {

      enum eActions
      {
         EA_MOVE_ACTOR
      };
      
      class GameMap;
      class Actor;

      class Action
      {
      public:
         virtual eActions GetType() const = 0;
         virtual void Proceed(GameMap* map, BWG::Utils::QuadTree<Actor>::PointType* actor) = 0;
      };
      
      class ActionMove : public Action
      {
         BWG::Utils::eDirection dir;
      public:
         ActionMove(BWG::Utils::eDirection _dir) : dir(_dir) {}

         eActions GetType() const override {
            return EA_MOVE_ACTOR;
         }

         void Proceed(GameMap* map, BWG::Utils::QuadTree<Actor>::PointType* actor) override;
      };
   }
}
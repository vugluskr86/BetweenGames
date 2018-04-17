#include "Action.h"

#include "GameMap.h"
#include "Actor.h"

namespace BWG {
   namespace Game {


      void ActionMove::Proceed(GameMap* map, BWG::Utils::QuadTree<Actor>::PointType* actor)
      {
         switch(dir)
         {
         case BWG::Utils::ED_N:
            actor->x -= 1;
            break;
         case BWG::Utils::ED_S:
            actor->x += 1;
            break;
         case BWG::Utils::ED_E:
            actor->y += 1;
            break;
         case BWG::Utils::ED_W:
            actor->y -= 1;
            break;
/*
         case BWG::Utils::ED_NW:
            break;
         case BWG::Utils::ED_NE:
            break;
         case BWG::Utils::ED_SW:
            break;
         case BWG::Utils::ED_SE:
            break;
*/
         default:
            break;
         }
      }

   }
}
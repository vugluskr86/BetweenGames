#include "Common.h"
#include "Door.h"
#include "Player.h"

namespace BWG {
   namespace Game {

      Door::Door() :
         AbstractGameObject(GOT_DOOR),
         _opened(false)
      {
         //  _type = TO_DOOR;
         //  _tile = eTile::TT_TILES_OBJECTS_DOOR_1;

         //auto layout = _map->GetLayout(TileMap::eLayouts::TL_OBJECTS);
         //layout.SetCell(_pos.x, _pos.y, eTile::TT_TILES_OBJECTS_DOOR_1);
      }

      void Door::Open(Player& player)
      {
         _opened = true;

         // _tile = eTile::TT_TILES_OBJECTS_DOOR_2;

         // auto layout = _map->GetLayout(TileMap::eLayouts::TL_STATIC);
         //  layout.SetCell(_pos.x, _pos.y, eTile::TT_TILES_OBJECTS_DOOR_2);
      }

   }
}


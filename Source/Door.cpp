#include "Common.h"
#include "Door.h"
#include "Player.h"
#include "GameCommon.h"
#include "GameObject.h"

namespace BWG {
   namespace Game {

      struct DoorImpl {
         bool _opened;

         DoorImpl() : _opened(false) {}
      };

      Door::Door() :
         AbstractGameObject(GOT_DOOR),
         self(new DoorImpl())
      {
         //  _type = TO_DOOR;
         //  _tile = eTile::TT_TILES_OBJECTS_DOOR_1;

         //auto layout = _map->GetLayout(TileMap::eLayouts::TL_OBJECTS);
         //layout.SetCell(_pos.x, _pos.y, eTile::TT_TILES_OBJECTS_DOOR_1);
      }

      Door::~Door() {}

      void Door::Open(Player& player)
      {
         self->_opened = true;

         // _tile = eTile::TT_TILES_OBJECTS_DOOR_2;

         // auto layout = _map->GetLayout(TileMap::eLayouts::TL_STATIC);
         //  layout.SetCell(_pos.x, _pos.y, eTile::TT_TILES_OBJECTS_DOOR_2);
      }

      bool Door::IsOpen() const
      {
         return self->_opened;
      }

   }
}


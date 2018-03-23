#pragma once

#include <glm/vec2.hpp>

namespace BWG {
   namespace Game {

      enum eGameObjects
      {
         GOT_STATIC_TILE = 0,
         GOT_MONSTER,
         GOT_PLAYER,
         GOT_TREASURE,
         GOT_PORTAL,
         GOT_STAIRS,
         GOT_DOOR
      };

      class AbstractGameObject
      {
         glm::uvec2 _pos;
         eGameObjects _type;
      public:
         AbstractGameObject(eGameObjects type) : _pos(0,0), _type(type) {}
         glm::vec2 GetPos() { return _pos; }
         void SetPos(const glm::uvec2& pos) { _pos = pos; }
         eGameObjects GetType() { return _type;  }
      };

   }
}
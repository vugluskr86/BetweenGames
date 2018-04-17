#pragma once

namespace BWG {
   namespace Game {
#pragma pack(push, 1)
      struct Tile
      {
         Tile() :
            _ground(0),
            _decale(0),
            _passability(true),
            _height(0)
         {}

         bool _passability;  // признак базовой проходимости 
         unsigned _ground; // осовная картинка
         unsigned _decale; // декаль (для эффекта)
         unsigned _height; // высота (базовая)
      };
#pragma pack(pop)
   }
}
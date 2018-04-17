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

         bool _passability;  // ������� ������� ������������ 
         unsigned _ground; // ������� ��������
         unsigned _decale; // ������ (��� �������)
         unsigned _height; // ������ (�������)
      };
#pragma pack(pop)
   }
}
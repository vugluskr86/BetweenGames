#pragma once

#include <memory>

namespace BWG {
   namespace Game {

      enum ePlayerActions
      {
         EPA_MOVE, // ���� � ������
         EPA_ATTACK, // ������� �� ������
         EPA_OVERVIEW // ������� �� �������
      };
      
      class GameMapView;
      class Player;

      class PlayerAction
      {
      public:
         virtual ePlayerActions GetType() const = 0;

         virtual void Proceed(std::shared_ptr<GameMapView> map, std::shared_ptr<Player> Player) = 0;
      };
   }
}
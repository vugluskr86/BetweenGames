#include "Player.h"

#include "Action.h"
#include "GameMapView.h"

namespace BWG {
   namespace Game {

      struct PlayerImpl
      {
         PlayerImpl() {}
      };

      Player::Player() : self(new PlayerImpl()){}
      Player::~Player() {}
   }
}
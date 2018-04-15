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

      //void Player::Action(std::shared_ptr<PlayerAction> action, std::shared_ptr<GameMapView> map)
      //{
         //action->Proceed()
      //}
   }
}
#include "GameSceneState.h"

namespace BWG {
   namespace Game {

      struct GameSceneStateImpl
      {

      };
      
      GameSceneState::GameSceneState() : self(new GameSceneStateImpl())
      {}

      GameSceneState::~GameSceneState()
      {}

      void GameSceneState::OnMount(std::shared_ptr<GameStateManager> manager)
      {

      }

      void GameSceneState::OnDismount(std::shared_ptr<GameStateManager> manager)
      {

      }
   }
}

#pragma once

#include <memory>
#include "GameState.h"

namespace BWG {
   namespace Game {

      struct GameSceneStateImpl;

      class GameSceneState : public BaseGameState
      {
         std::unique_ptr<GameSceneStateImpl> self;
      public:
         GameSceneState();
         ~GameSceneState();

         void OnMount(std::shared_ptr<GameStateManager> manager) override;
         void OnDismount(std::shared_ptr<GameStateManager> manager) override;

         eGameStates GetType() const override { return eGameStates::STATE_GAME_SCENE; }
      };
   }
}

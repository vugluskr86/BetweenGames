#pragma once

#include "GameState.h"

namespace BWG {
   namespace Game {

      class MainMenuState : public BaseGameState
      {
      public:
         MainMenuState();
         ~MainMenuState();

         void OnMount(std::shared_ptr<GameStateManager> manager) override;
         void OnDismount(std::shared_ptr<GameStateManager> manager) override;

         eGameStates GetType() const override
         {
            return eGameStates::STATE_MAIN_MENU;
         }
      };
   }
}

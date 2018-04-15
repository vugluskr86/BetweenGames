#pragma once

#include "GameState.h"

namespace BWG {
   namespace Game {

      class MainMenuState : public BaseGameState
      {
      public:
         MainMenuState();
         ~MainMenuState();

         void OnMount(GameStateManager* manager) override;
         void OnDismount(GameStateManager* manager) override;

         eGameStates GetType() const override
         {
            return eGameStates::STATE_MAIN_MENU;
         }
      };
   }
}

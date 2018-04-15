#pragma once

#include "GameState.h"

namespace BWG {
   namespace Game {

      class PauseMenuState : public BaseGameState
      {
      public:
         PauseMenuState();
         ~PauseMenuState();

         void OnMount(std::shared_ptr<GameStateManager> manager) override;
         void OnDismount(std::shared_ptr<GameStateManager> manager) override;

       //  void OnEvents() override;
       //  void Update()  override;
       //  void Render()  override;

         eGameStates GetType() const override
         {
            return eGameStates::STATE_PAUSE_MENU;
         }
      };
   }
}

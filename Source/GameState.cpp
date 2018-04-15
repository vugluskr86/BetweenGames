#include "GameState.h"

#include <vector>
#include <algorithm>

#include "Window.h"

namespace BWG {
   namespace Game {
      struct GameStateManagerImpl
      {
         GameStateManagerImpl() :
            current(nullptr),
            window(new BWG::System::Window(800, 600))
         {}

         ~GameStateManagerImpl() {}

         std::unique_ptr<BWG::System::Window> window;
         std::vector< std::unique_ptr<BaseGameState> > states;
         BaseGameState* current;
      };

      GameStateManager::GameStateManager() :
         self(new GameStateManagerImpl())
      {}

      GameStateManager::~GameStateManager() {}

      void GameStateManager::ChangeState(eGameStates state)
      {
         if(self->current == nullptr || self->current->GetType() != state) {
            if(self->current != nullptr) {
               self->current->OnDismount();
            }
            auto it = std::find_if(self->states.begin(), self->states.end(), [state](std::unique_ptr<BaseGameState>& p) {
               return p->GetType() == state;
            });
            if(it != self->states.end()) {
               self->current = it->get();
               self->current->OnMount();
            }
         }
      }

      void GameStateManager::PushState(std::unique_ptr<BaseGameState> state)
      {
         self->states.emplace_back(std::move(state));
      }

      void GameStateManager::PopState()
      {
         self->states.pop_back();
      }


      void GameStateManager::ProcessEvent(SDL_Event* ev)
      {
         self->window->ProcessEvent(ev);
      }

      void GameStateManager::Render()
      {
         self->window->Render();
      }

   }
}



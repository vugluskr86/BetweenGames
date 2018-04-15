#pragma once

#include <memory>

struct SDL_Window;
union SDL_Event;

namespace BWG {

   namespace System {
      class Window;
   }

   namespace Game {
      enum eGameStates
      {
         STATE_NULL,
         STATE_MAIN_MENU,
         STATE_PAUSE_MENU,
         STATE_GAME_SCENE
      };

      class GameStateManager;

      struct BaseGameState : std::enable_shared_from_this<BaseGameState>
      {
         virtual eGameStates GetType() const = 0;
         virtual ~BaseGameState() {};

         virtual void OnMount(GameStateManager* manager) = 0;
         virtual void OnDismount(GameStateManager* manager) = 0;

         std::shared_ptr<BaseGameState> getptr() {
            return shared_from_this();
         }
      };

      struct GameStateManagerImpl;

      class GameStateManager : std::enable_shared_from_this<GameStateManager>
      {
      public:

         GameStateManager();
         ~GameStateManager();

         void ChangeState(eGameStates state);
         void PushState(std::unique_ptr<BaseGameState> state);
         void PopState();

         void ProcessEvent(SDL_Event* event);
         void Render();

         std::shared_ptr<GameStateManager> getptr() {
            return shared_from_this();
         }

         BWG::System::Window* GetWindow() const;
      private:
         std::unique_ptr<GameStateManagerImpl> self;
      };
   }
}


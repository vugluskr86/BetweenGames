#include "GameSceneState.h"

#include "Window.h"
#include "RenderImgui.h"
#include "RenderSprites.h"

namespace BWG {
   namespace Game {

      struct GameSceneStateImpl
      {

      };
      
      GameSceneState::GameSceneState() : self(new GameSceneStateImpl())
      {}

      GameSceneState::~GameSceneState()
      {}

      void GameSceneState::OnMount(GameStateManager* manager)
      {
         BWG::System::Window* window = manager->GetWindow();
         
         std::unique_ptr<BWG::Render::RenderSprites> tile_layer(new BWG::Render::RenderSprites());
         std::vector<BWG::Render::Sprite> tiles = {
            { 0, 0, 0 },
            { 0, 1, 1 },
            { 2, 1, 1 },
         };
         tile_layer->SetTiles(tiles);
         tile_layer->Enable();

         window->AddLayer(std::move(tile_layer));
 
         
         std::unique_ptr<BWG::Render::RenderImGui> ui_layer(new BWG::Render::RenderImGui());
         ui_layer->Enable();
         window->AddLayer(std::move(ui_layer));

      }

      void GameSceneState::OnDismount(GameStateManager* manager)
      {

      }
   }
}

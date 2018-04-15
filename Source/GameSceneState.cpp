#include "GameSceneState.h"

#include "Window.h"
#include "RenderImgui.h"
#include "RenderSprites.h"

#include "GameMapView.h"

namespace BWG {
   namespace Game {

      struct GameSceneStateImpl
      {
         BWG::Render::RenderSprites* tiles;
         BWG::Render::RenderImGui* gui;

         std::unique_ptr<GameMapView> mapView;

         GameSceneStateImpl() {}
      };
      
      GameSceneState::GameSceneState() : self(new GameSceneStateImpl())
      {}

      GameSceneState::~GameSceneState()
      {
         self->tiles = nullptr;
         self->gui = nullptr;
      }

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

         self->tiles = tile_layer.get();

         window->AddLayer(std::move(tile_layer));
          
         std::unique_ptr<BWG::Render::RenderImGui> ui_layer(new BWG::Render::RenderImGui());
         ui_layer->Enable();

         self->gui = ui_layer.get();

         window->AddLayer(std::move(ui_layer));
      }

      void GameSceneState::OnDismount(GameStateManager* manager)
      {

      }
   }
}

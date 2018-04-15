#include "GameMapView.h"

#include "TileMap.h"
#include "Actor.h"

#include <vector>

namespace BWG {
   namespace Game {


      struct GameMapViewImpl {
         GameMapViewImpl() {

         }
         
         std::unique_ptr<TileMapType> map;

         //std::vector<Actor> actors;
      };


      GameMapView::GameMapView() : self(new GameMapViewImpl) {}
      GameMapView::~GameMapView() {}

      
   }
}
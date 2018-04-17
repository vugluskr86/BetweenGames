#include "GameMap.h"

#include <PolyVox/MaterialDensityPair.h>
#include <PolyVox/CubicSurfaceExtractor.h>
#include <PolyVox/MarchingCubesSurfaceExtractor.h>
#include <PolyVox/Mesh.h>
#include <PolyVox/PagedVolume.h>

using namespace PolyVox;

#include "QuadTree.h"
#include "Action.h"

namespace BWG {
   namespace Game {

      class ChunkProxyPager : public PolyVox::PagedVolume<Tile>::Pager
      {
      public:
         /// Constructor
         ChunkProxyPager()
            :PagedVolume<Tile>::Pager()
         {
         }

         /// Destructor
         virtual ~ChunkProxyPager() {};

         virtual void pageIn(const PolyVox::Region& region, PagedVolume<Tile>::Chunk* pChunk)
         {
    
         }

         virtual void pageOut(const PolyVox::Region& region, PagedVolume<Tile>::Chunk* pChunk)
         {
         }
      };

      struct GameMapImpl {

         std::unique_ptr<PagedVolume<Tile>> volume;
         ChunkProxyPager pager;
         BWG::Utils::QuadTree<Actor> actorsSpt;
         BWG::Utils::Rect worldRect;

         GameMapImpl()
         {
            worldRect = { 0, 1042, 0, 1042 };
            volume = std::make_unique<PagedVolume<Tile>>(&pager, 1024 * 1024 * 64, 32);
         }

         ~GameMapImpl() 
         {

         }
      };

      GameMap::GameMap() : self(new GameMapImpl())
      {

      }

      GameMap::~GameMap() 
      {

      }
      
      
      void GameMap::AddActor(std::unique_ptr<Actor> actor, int x, int y)
      {
         self->actorsSpt.Insert(std::make_unique<BWG::Utils::QuadTree<Actor>::PointType>(std::move(actor), x, y));
      }
      
      void GameMap::Tick() 
      {
         BWG::Utils::QuadTree<Actor>::QueryResult result;
         int ct = 0;
         self->actorsSpt.SearchQuad(self->worldRect, result, ct);
         if(ct > 0) {
            while(result.size() > 0) {
               auto actor = result.top();

               auto& actions = actor->type.get()->GetActions();
               for(auto& action : actions) {
                  action.get()->Proceed(this, actor);
               }

               result.pop();
            }
         }
      }

      const BWG::Utils::Rect& GameMap::GetWorldBounds() const
      {
         return self->worldRect;
      }
   }
}
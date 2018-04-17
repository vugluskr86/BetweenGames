#pragma once

#include "nocopy.h"
#include "Array2D.h"

#include <glm/vec2.hpp>

#include <memory>
#include <vector>

#include <PolyVox/MaterialDensityPair.h>
#include <PolyVox/CubicSurfaceExtractor.h>
#include <PolyVox/MarchingCubesSurfaceExtractor.h>
#include <PolyVox/Mesh.h>
#include <PolyVox/PagedVolume.h>

using namespace PolyVox;


namespace BWG {

   namespace Game {

      


   /*
      inline uint8_t logBase2(uint32_t uInput)
      {
         uint32_t uResult = 0;
         while((uInput >> uResult) != 0)
         {
            ++uResult;
         }
         return static_cast<uint8_t>(uResult - 1);
      }

      struct Tile;

      
      struct Tile
      {
         Tile() : 
            _ground(0),
            _decale(0),
            _solid(false),
            _transparency(true),
            _height(0)
         {}

         unsigned _ground;
         unsigned _decale;
         bool _solid;
         bool _transparency;
         unsigned _height;
      };
      

      template <uint32_t ChunkSize>
      class TileMap 
      {
      public:
         template <uint32_t SizeT>
         class TileMapChunk : Utils::nocopy
         {
         public:
            using TileArray = Utils::Array2D<Tile, SizeT>;
         private:
            const unsigned _size = SizeT;
            Utils::Array2D<Tile, SizeT> _map;
            glm::vec2 _spacePosition;
            uint32_t _chunkLastAccessed;
         public:

            TileMapChunk() {
               _chunkLastAccessed = 0;
               _spacePosition = glm::vec2(0, 0);
            }

            auto At(uint32_t x, uint32_t y) const {
               return _map.At(x, y);
            }
            void Fill(const Tile& t) {
               _map.reset(t);
            }
            void Set(uint32_t x, uint32_t y, const Tile& t) {
               _map.Set(x, y, t);
            }
            auto GetTiles() {
               return _map.getRaw();
            };

            friend TileMap;
         };

         using ChunkType = TileMapChunk<ChunkSize>;
         const unsigned _chunkSize = ChunkSize;

         TileMap() {
            _chunkSideLengthPower = logBase2(_chunkSize);
            _chunkMask = _chunkSideLengthPower - 1;
         }
         
         unsigned GetChunkSize() const {
            return _chunkSize;
         }

         ChunkType* GetChunk(uint32_t uChunkX, uint32_t uChunkY) const {
            ChunkType* pChunk = nullptr;

            const uint32_t uChunkXLowerBits = static_cast<uint32_t>(uChunkX & 0x1F);
            const uint32_t uChunkYLowerBits = static_cast<uint32_t>(uChunkY & 0x1F);

            const uint32_t iPosisionHash = (((uChunkXLowerBits)) | ((uChunkYLowerBits) << 5) << 1);

            uint32_t iIndex = iPosisionHash;
            do
            {
               if(_arrayChunks[iIndex])
               {
                  glm::vec2& entryPos = _arrayChunks[iIndex]->_spacePosition;
                  if(entryPos.x == uChunkX && entryPos.y == uChunkY)
                  {
                     pChunk = _arrayChunks[iIndex].get();
                     pChunk->_chunkLastAccessed = ++_timestamper;
                     break;
                  }
               }

               iIndex++;
               iIndex %= _chunkArraySize;
            } while(iIndex != iPosisionHash);


            if(!pChunk) {
               pChunk = new ChunkType();
               pChunk->_spacePosition = glm::vec2(uChunkX, uChunkY);
               pChunk->_chunkLastAccessed = ++_timestamper;

               uint32_t iIndex = iPosisionHash;
               bool bInsertedSucessfully = false;
               do
               {
                  if(_arrayChunks[iIndex] == nullptr)
                  {
                     _arrayChunks[iIndex] = std::move(std::unique_ptr<ChunkType>(pChunk));
                     bInsertedSucessfully = true;
                     break;
                  }

                  iIndex++;
                  iIndex %= _chunkArraySize;
               } while(iIndex != iPosisionHash); 

               uint32_t uChunkCount = 0;
               uint32_t uOldestChunkIndex = 0;
               uint32_t uOldestChunkTimestamp = std::numeric_limits<uint32_t>::max();
               for(uint32_t uIndex = 0; uIndex < _chunkArraySize; uIndex++)
               {
                  if(_arrayChunks[uIndex])
                  {
                     uChunkCount++;
                     if(_arrayChunks[uIndex]->_chunkLastAccessed < uOldestChunkTimestamp)
                     {
                        uOldestChunkTimestamp = _arrayChunks[uIndex]->_chunkLastAccessed;
                        uOldestChunkIndex = uIndex;
                     }
                  }
               }

               // Check if we have too many chunks, and delete the oldest if so.
               if(uChunkCount > _chunkCountLimit)
               {
                  _arrayChunks[uOldestChunkIndex] = nullptr;
               }
            }

            _lastAccessedChunk = pChunk;
            _lastAccessedChunkX = uChunkX;
            _lastAccessedChunkY = uChunkY;

            return pChunk;
         }

         auto Get(uint32_t x, uint32_t y) const {
            const int32_t chunkX = x >> _chunkSideLengthPower;
            const int32_t chunkY = y >> _chunkSideLengthPower;

            const uint16_t xOffset = static_cast<uint16_t>(x & _chunkMask);
            const uint16_t yOffset = static_cast<uint16_t>(y & _chunkMask);

            auto pChunk = canReuseLastAccessedChunk(chunkX, chunkY) ? _lastAccessedChunk : GetChunk(chunkX, chunkY);

            return pChunk->At(xOffset, yOffset);
         }

         void Set(uint32_t x, uint32_t y, const Tile& t) {
            const int32_t chunkX = x >> _chunkSideLengthPower;
            const int32_t chunkY = y >> _chunkSideLengthPower;

            const uint16_t xOffset = static_cast<uint16_t>(x & _chunkMask);
            const uint16_t yOffset = static_cast<uint16_t>(y & _chunkMask);

            auto pChunk = canReuseLastAccessedChunk(chunkX, chunkY) ? _lastAccessedChunk : GetChunk(chunkX, chunkY);

            pChunk->Set(xOffset, yOffset, t);
         }

         void Clear() {
            _lastAccessedChunk = nullptr;
            for(uint32_t uIndex = 0; uIndex < _chunkArraySize; uIndex++) {
               _arrayChunks[uIndex] = nullptr;
            }
         }

         bool canReuseLastAccessedChunk(int32_t iChunkX, int32_t iChunkY) const {
            return ((iChunkX == _lastAccessedChunkX) &&
               (iChunkY == _lastAccessedChunkY) &&
               (_lastAccessedChunk));
         }

         private:
            mutable int32_t _lastAccessedChunkX = 0;
            mutable int32_t _lastAccessedChunkY = 0;
            mutable ChunkType* _lastAccessedChunk = nullptr;

            static const uint32_t _chunkCountLimit = 4096;
            static const uint32_t _chunkArraySize = 4096;
            mutable std::unique_ptr<ChunkType> _arrayChunks[_chunkArraySize];

            mutable uint32_t _timestamper = 0;

            uint8_t _chunkSideLengthPower;
            int8_t _chunkMask;
      };

      using TileMapType = TileMap<32>;
*/

   }
}


// #include "Types.h"

//class Player;
//class Monster;
//class BattleManager;

/*
class TileMapLayout
{
   sf::Vector2u _tileSize;
   sf::Vector2i _mapSize;
   sf::VertexArray _vertices;

   std::vector<eTile> _tiles;
   bool _init;
   bool _dirty;

public:
   TileMapLayout();

   void Init(sf::Vector2u tileSize, sf::Vector2i mapSize, eTile value = eTile::TT_UNUSED);
   
   void Clear();

   void SetCell(int x, int y, eTile celltype);
   eTile GetCell(int x, int y) const;
   void SetCells(int xStart, int yStart, int xEnd, int yEnd, eTile cellType);

   bool IsXInBounds(int x) const;
   bool IsYInBounds(int y) const;
   bool IsAreaUnused(int xStart, int yStart, int xEnd, int yEnd);
   bool IsAdjacent(int x, int y, eTile tile);

   void Build(uint32_t resolution);

   bool IsInit() const
   { return _init; }
   bool IsDirty() const 
   { return _dirty; }
   const sf::VertexArray& GetVertices() const
   { return _vertices; }
   const sf::Vector2i& GetMapSize() const
   { return _mapSize; }
};

class TileMap : public sf::Drawable, public sf::Transformable
{
public:
   enum eLayouts {
      TL_STATIC = 0,
      TL_STATIC_DECOR,
      TL_OBJECTS,
      TL_MAX
   };
   
   TileMap();
   ~TileMap();

   TileMapLayout& GetLayout(eLayouts type) 
   { return _layouts[type]; }

   bool Load(const std::string& tileset);  
      
   void SetSelection(sf::Vector2i pos);
   void ResetSelection();

   void Clear();
   void SetPlayer(Player* player);

   void AddMonster(Monster* monster);
   void AddObject(TileObject* object);

   bool IsPassable(int x, int y) const;
   Monster* IsMonster(int x, int y) const;
   TileObject* IsGameObject(int x, int y) const;

   void Update();

   bool CanPlaced(int x, int y) const;
   
   const sf::Vector2i& GetMapSize() const;

   TileObject* GetObject(int x, int y);

   bool DoFov(int x, int y) const;

   void MonstersTurn(BattleManager* bm);

   void RemoveMonster(Monster* monster);


   Player* GetPlayer() { return _player; }
   // std::vector<sf::Vector2i> Fov(int x, int y, int radius) const;
private:
   virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
   void DrawLayout(sf::RenderTarget& target, sf::RenderStates states, eLayouts type) const;
   
   TileMapLayout _layouts[eLayouts::TL_MAX];
   sf::Texture _texture;

   sf::Sprite _spriteSeletor;
   bool _selection;
      
   sf::Sprite _spritePlayer;

   Player* _player;
   std::vector<Monster*> _monsters;
   std::vector<TileObject*> _objects;
};
*/
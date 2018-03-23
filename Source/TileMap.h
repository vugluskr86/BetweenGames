#pragma once

#include "eTiles.h"
#include "nocopy.h"
#include "Array2D.h"

#include <glm/vec2.hpp>

#include <vector>

namespace BWG {

   namespace Game {
   
      struct Tile
      {
         Tile() : 
            _ground(eTile::TT_UNUSED),
            _decale(eTile::TT_UNUSED),
            _solid(false),
            _transparency(true)
         {}

         eTile _ground;
         eTile _decale;
         bool _solid;
         bool _transparency;
      };

      template <uint32_t SizeT>
      class TileMapChunk : Utils::nocopy
      {
      public:
         using TileArray = Utils::Array2D<Tile, SizeT>;
      private:
         const unsigned _size = SizeT;
         const Utils::Array2D<Tile, SizeT> _map;
      public:
         const Tile& At(uint32_t x, uint32_t y) {
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
      };

      template <uint32_t ChunkSize>
      class TileMap 
      {
         using ChunkType = TileMapChunk<ChunkSize>;
         const unsigned _chunkSize = ChunkSize;
         std::vector<ChunkType> _chunks;
      public:
         unsigned GetChunkSize() const {
            return _chunkSize;
         }

         Tile& Get(uint32_t x, uint32_t y) {

         }

         void Set(uint32_t x, uint32_t y, const Tile& t) {

         }

         //glm::vec2 GetSize() const { return _ }
      };

      using TileMapType = TileMap<32>;

      class TileMapView
      {
      public:

      };

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
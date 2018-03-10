#include "Types.h"

class Player;
class Monster;

class TileMapLayout
{
   sf::Vector2u _tileSize;
   sf::Vector2i _mapSize;
   std::vector<eTile> _tiles;
   sf::VertexArray _vertices;

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

class Selector 
{
   sf::Vector2i _pos;
   TileObject* _obj;
public:
   Selector();

   bool IsPassable() const;
};

class TileMap : public sf::Drawable, public sf::Transformable
{
public:
   enum eLayouts {
      TL_STATIC = 0,
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

   Player* SpawnPlayer(sf::Vector2i pos, eTile gfx);
   Monster* SpawnMonster(sf::Vector2i pos, eTile gfx);

   void AddObject(TileObject* object);

   bool IsPassable(int x, int y) const;
   Monster* IsMonster(int x, int y) const;
   TileObject* IsGameObject(int x, int y) const;

   void Update();

   bool CanPlaced(int x, int y) const;
   
   const sf::Vector2i& GetMapSize() const;

   TileObject* GetObject(int x, int y);

private:
   virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
   void DrawLayout(sf::RenderTarget& target, sf::RenderStates states, eLayouts type) const;
   
   TileMapLayout _layouts[eLayouts::TL_MAX];
   sf::Texture _texture;

   sf::Sprite _spriteSeletor;
   bool _selection;
      
   Player* _player;
   std::vector<Monster*> _monsters;
   std::vector<TileObject*> _objects;
};

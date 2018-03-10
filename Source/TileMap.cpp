#include "TileMap.h"
#include <assert.h>

#include "Player.h"
#include "Monster.h"

TileMapLayout::TileMapLayout() : 
   _init(false),
   _dirty(false)
{

}

void TileMapLayout::Init(sf::Vector2u tileSize, sf::Vector2i mapSize, eTile value)
{
   _tileSize = tileSize;
   _mapSize = mapSize;

   _vertices.clear();
   _vertices.setPrimitiveType(sf::Quads);
   _vertices.resize(_mapSize.x * _mapSize.y * 4);

   _tiles.clear();
   _tiles.resize(_mapSize.x * _mapSize.y);

   std::fill(_tiles.begin(), _tiles.end(), value);

   _init = true;
   _dirty = true;
}

void TileMapLayout::Clear()
{
   _vertices.clear();
   _vertices.setPrimitiveType(sf::Quads);
   _vertices.resize(_mapSize.x * _mapSize.y * 4);

   _tiles.clear();
   _tiles.resize(_mapSize.x * _mapSize.y);

   std::fill(_tiles.begin(), _tiles.end(), eTile::TT_UNUSED);

   _init = true;
   _dirty = true;
}

void TileMapLayout::SetCell(int x, int y, eTile celltype)
{
   assert(IsXInBounds(x));
   assert(IsYInBounds(y));

   _tiles[x + _mapSize.x * y] = celltype;

   _dirty = true;
}

eTile TileMapLayout::GetCell(int x, int y) const
{
   assert(IsXInBounds(x));
   assert(IsYInBounds(y));

   return _tiles[x + _mapSize.x * y];
}

void TileMapLayout::SetCells(int xStart, int yStart, int xEnd, int yEnd, eTile cellType)
{
   assert(IsXInBounds(xStart) && IsXInBounds(xEnd));
   assert(IsYInBounds(yStart) && IsYInBounds(yEnd));

   assert(xStart <= xEnd);
   assert(yStart <= yEnd);

   for(auto y = yStart; y != yEnd + 1; ++y)
      for(auto x = xStart; x != xEnd + 1; ++x)
         SetCell(x, y, cellType);
}

bool TileMapLayout::IsXInBounds(int x) const
{
   return x >= 0 && x < _mapSize.x;
}

bool TileMapLayout::IsYInBounds(int y) const
{
   return y >= 0 && y < _mapSize.y;
}

bool TileMapLayout::IsAreaUnused(int xStart, int yStart, int xEnd, int yEnd)
{
   assert(IsXInBounds(xStart) && IsXInBounds(xEnd));
   assert(IsYInBounds(yStart) && IsYInBounds(yEnd));

   assert(xStart <= xEnd);
   assert(yStart <= yEnd);

   for(auto y = yStart; y != yEnd + 1; ++y)
      for(auto x = xStart; x != xEnd + 1; ++x)
         if(GetCell(x, y) != eTile::TT_UNUSED)
            return false;

   return true;
}

bool TileMapLayout::IsAdjacent(int x, int y, eTile tile)
{
   assert(IsXInBounds(x - 1) && IsXInBounds(x + 1));
   assert(IsYInBounds(y - 1) && IsYInBounds(y + 1));

   return
      GetCell(x - 1, y) == tile || GetCell(x + 1, y) == tile ||
      GetCell(x, y - 1) == tile || GetCell(x, y + 1) == tile;
}

void TileMapLayout::Build(uint32_t resolution)
{
   // resize the vertex array to fit the level size
   //m_vertices.setPrimitiveType(sf::Quads);
   //m_vertices.resize(xMapSize * yMapSize * 4);

   // SetSize(xMapSize, yMapSize);

   // populate the vertex array, with one quad per tile
   for(unsigned int i = 0; i < _mapSize.x; ++i) {
      for(unsigned int j = 0; j < _mapSize.y; ++j) {
         // get the current tile number
         int tileNumber = static_cast<int>(_tiles[i + j * _mapSize.x]);

         // find its position in the tileset texture
       //  int tu = tileNumber % (_texture.getSize().x / _tileSize.x);
       //  int tv = tileNumber / (_texture.getSize().x / _tileSize.x);

         int tu = tileNumber % (resolution / _tileSize.x);
         int tv = tileNumber / (resolution / _tileSize.x);

         // get a pointer to the current tile's quad
         sf::Vertex* quad = &_vertices[(i + j * _mapSize.x) * 4];

         // define its 4 corners
         quad[0].position = sf::Vector2f(i * _tileSize.x, j * _tileSize.y);
         quad[1].position = sf::Vector2f((i + 1) * _tileSize.x, j * _tileSize.y);
         quad[2].position = sf::Vector2f((i + 1) * _tileSize.x, (j + 1) * _tileSize.y);
         quad[3].position = sf::Vector2f(i * _tileSize.x, (j + 1) * _tileSize.y);

         // define its 4 texture coordinates
         quad[0].texCoords = sf::Vector2f(tu * _tileSize.x, tv * _tileSize.y);
         quad[1].texCoords = sf::Vector2f((tu + 1) * _tileSize.x, tv * _tileSize.y);
         quad[2].texCoords = sf::Vector2f((tu + 1) * _tileSize.x, (tv + 1) * _tileSize.y);
         quad[3].texCoords = sf::Vector2f(tu * _tileSize.x, (tv + 1) * _tileSize.y);
      }
   }

   _dirty = false;
}

//////////////////////////////////////////////////

Selector::Selector()
{

}

bool Selector::IsPassable() const
{ return true; }


//////////////////////////////////////////////////

TileMap::TileMap() :
   _selection(false),
   _player(nullptr)
{ }

TileMap::~TileMap()
{
   if(_player) {
      delete _player;
   }
}

void TileMap::DrawLayout(sf::RenderTarget& target, sf::RenderStates states, eLayouts type) const
{
   const TileMapLayout& layout = _layouts[type];
   if(layout.IsInit()) {
      target.draw(layout.GetVertices(), states);
   }
}

void TileMap::Update()
{
   _layouts[eLayouts::TL_OBJECTS].Clear();

   for(auto monster : _monsters) {
      auto pos = monster->GetPos();
      _layouts[eLayouts::TL_OBJECTS].SetCell(pos.x, pos.y, monster->GetTile());
   }

   if(_player) {
      auto pPos = _player->GetPos();
      _layouts[eLayouts::TL_OBJECTS].SetCell(pPos.x, pPos.y, _player->GetTile());
   }
   
   for(uint32_t i = 0; i < eLayouts::TL_MAX; i++) {
      if(_layouts[i].IsInit() && _layouts[i].IsDirty()) {
         _layouts[i].Build(_texture.getSize().x);
      }
   }
}

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
   // apply the transform
   states.transform *= getTransform();

   // apply the tileset texture
   states.texture = &_texture;

   for(uint32_t i = 0; i < eLayouts::TL_MAX; i++) {
      if(_layouts[i].IsInit() && !_layouts[i].IsDirty()) {
         DrawLayout(target, states, (eLayouts)i);
      }
   }

   if(_selection) {
      target.draw(_spriteSeletor, states);
   }
}

bool TileMap::Load(const std::string& tileset)
{
   bool res = _texture.loadFromFile(tileset);
      
   if(res) {
      _spriteSeletor.setTexture(_texture);

      int tu = (int)eTile::TT_UNUSED % (_texture.getSize().x / 32);
      int tv = (int)eTile::TT_UNUSED / (_texture.getSize().x / 32);

      _spriteSeletor.setTextureRect(sf::IntRect(tu * 32, tv * 32, 32, 32));
   }
   
   return res;
}

void TileMap::SetSelection(sf::Vector2i pos)
{
   _spriteSeletor.setPosition(pos.x * 32, pos.y * 32);
   _selection = true;
}

void TileMap::TileMap::ResetSelection()
{
   _selection = false;
}

Player* TileMap::SpawnPlayer(sf::Vector2i pos, eTile gfx)
{
   _player = new Player(gfx);
   _player->SetPos(pos);
   return _player;
}

Monster* TileMap::SpawnMonster(sf::Vector2i pos, eTile gfx)
{
   Monster* monster = new Monster(gfx);
   monster->SetPos(pos);
   _monsters.push_back(monster);
   return monster;
}

bool TileMap::IsMonster(int x, int y) const
{
   bool monster = false;
   for(auto mob : _monsters) {
      auto pos = mob->GetPos();
      if(pos.x == x && pos.y == y) monster = true;
   }
   return monster;
}

bool TileMap::IsGameObject(int x, int y) const
{
   bool isObj = false;
   for(auto obj : _objects) {
      auto pos = obj->GetPos();
      if(pos.x == x && pos.y == y) isObj = true;
   }
   return isObj;
}

bool TileMap::IsPassable(int x, int y) const
{
   if(IsMonster(x, y)) {
      return false;
   }

   if(IsGameObject(x, y)) {
      return false;
   }

   eTile stile = _layouts[eLayouts::TL_STATIC].GetCell(x, y);

   bool pass = false;

   switch(stile) {
   case TT_TILES_DIRT:
   case TT_TILES_DESERTROAD:
   case TT_TILES_GRASS:
   case TT_TILES_SAND:
   case TT_TILES_STONESAND:
   case TT_TILES_WATER:
      pass = true;
   }

   return pass;
}
#include <iostream>
#include <assert.h>
#include "Generator.h"
#include "TileMap.h"

MapGenerator::MapGenerator(std::mt19937* random) :
   _random(random)
{ }

int MapGenerator::GetRandomInt(int min, int max)
{
   return std::uniform_int_distribution<int>(min, max)(_random);
}

Direction MapGenerator::GetRandomDirection()
{
   return Direction(std::uniform_int_distribution<int>(0, 3)(_random));
}


DugneonGenerator::DugneonGenerator(std::mt19937* random) :
   MapGenerator(random)
{
   _xSize = 80;
   _yYSize = 25;
   _maxFeatures = 100;
   _chanceRoom = 75;
   _chanceCorridor = 25;
}

void DugneonGenerator::InitLayouts(TileMap& map)
{
   assert(_maxFeatures > 0 && _maxFeatures <= 100);
   assert(_xSize > 3 && _xSize <= 80);
   assert(_yYSize > 3 && _yYSize <= 25);
   
   TileMapLayout& staticLayout = map.GetLayout(TileMap::eLayouts::TL_STATIC);
   TileMapLayout& objectsLayout = map.GetLayout(TileMap::eLayouts::TL_OBJECTS);

  
   map.Load("assets/tileset.png");

   staticLayout.Init(sf::Vector2u(32, 32), sf::Vector2i(_xSize, _yYSize));
   objectsLayout.Init(sf::Vector2u(32, 32), sf::Vector2i(_xSize, _yYSize));
}


bool DugneonGenerator::MakeCorridor(TileMap& map, int x, int y, int maxLength, Direction direction)
{
   assert(x >= 0 && x < _xSize);
   assert(y >= 0 && y < _yYSize);

   assert(maxLength > 0 && maxLength <= std::max(_xSize, _yYSize));

   TileMapLayout& staticLayout = map.GetLayout(TileMap::eLayouts::TL_STATIC);

   auto length = GetRandomInt(2, maxLength);

   auto xStart = x;
   auto yStart = y;

   auto xEnd = x;
   auto yEnd = y;

   if(direction == Direction::North)
      yStart = y - length;
   else if(direction == Direction::East)
      xEnd = x + length;
   else if(direction == Direction::South)
      yEnd = y + length;
   else if(direction == Direction::West)
      xStart = x - length;

   if(!staticLayout.IsXInBounds(xStart) || !staticLayout.IsXInBounds(xEnd) || !staticLayout.IsYInBounds(yStart) || !staticLayout.IsYInBounds(yEnd))
      return false;

   if(!staticLayout.IsAreaUnused(xStart, yStart, xEnd, yEnd))
      return false;

   staticLayout.SetCells(xStart, yStart, xEnd, yEnd, eTile::TT_TILES_DESERTROAD);

   return true;
}

bool DugneonGenerator::MakeStaticRoom(TileMap& map, int x, int y, int xLength, int yLength, Direction direction)
{
   TileMapLayout& staticLayout = map.GetLayout(TileMap::eLayouts::TL_STATIC);

   auto xStart = x;
   auto yStart = y;

   auto xEnd = xStart + xLength;
   auto yEnd = yStart + yLength;


   if(!staticLayout.IsXInBounds(xStart) || !staticLayout.IsXInBounds(xEnd) || !staticLayout.IsYInBounds(yStart) || !staticLayout.IsYInBounds(yEnd))
      return false;

   if(!staticLayout.IsAreaUnused(xStart, yStart, xEnd, yEnd))
      return false;

   staticLayout.SetCells(xStart, yStart, xEnd, yEnd, eTile::TT_TILES_BRICKS);
   staticLayout.SetCells(xStart + 1, yStart + 1, xEnd - 1, yEnd - 1, eTile::TT_TILES_DIRT);

   return true;
}

bool DugneonGenerator::MakeRoom(TileMap& map, int x, int y, int xMaxLength, int yMaxLength, Direction direction)
{
   TileMapLayout& staticLayout = map.GetLayout(TileMap::eLayouts::TL_STATIC);

   // Minimum room size of 4x4 tiles (2x2 for walking on, the rest is walls)
   auto xLength = GetRandomInt(4, xMaxLength);
   auto yLength = GetRandomInt(4, yMaxLength);

   auto xStart = x;
   auto yStart = y;

   auto xEnd = x;
   auto yEnd = y;

   if(direction == Direction::North)
   {
      yStart = y - yLength;
      xStart = x - xLength / 2;
      xEnd = x + (xLength + 1) / 2;
   }
   else if(direction == Direction::East)
   {
      yStart = y - yLength / 2;
      yEnd = y + (yLength + 1) / 2;
      xEnd = x + xLength;
   }
   else if(direction == Direction::South)
   {
      yEnd = y + yLength;
      xStart = x - xLength / 2;
      xEnd = x + (xLength + 1) / 2;
   }
   else if(direction == Direction::West)
   {
      yStart = y - yLength / 2;
      yEnd = y + (yLength + 1) / 2;
      xStart = x - xLength;
   }

   if(!staticLayout.IsXInBounds(xStart) || !staticLayout.IsXInBounds(xEnd) || !staticLayout.IsYInBounds(yStart) || !staticLayout.IsYInBounds(yEnd))
      return false;

   if(!staticLayout.IsAreaUnused(xStart, yStart, xEnd, yEnd))
      return false;

   staticLayout.SetCells(xStart, yStart, xEnd, yEnd, eTile::TT_TILES_BRICKS);
   staticLayout.SetCells(xStart + 1, yStart + 1, xEnd - 1, yEnd - 1, eTile::TT_TILES_DIRT);

   //std::cout << "Room: ( " << xStart << ", " << yStart << " ) to ( " << xEnd << ", " << yEnd << " )" << std::endl;

   return true;
}

bool DugneonGenerator::MakeFeature(TileMap& map, int x, int y, int xmod, int ymod, Direction direction)
{
   TileMapLayout& staticLayout = map.GetLayout(TileMap::eLayouts::TL_STATIC);

   // Choose what to build
   auto chance = GetRandomInt(0, 100);

   if(chance <= _chanceRoom)
   {
      if(MakeRoom(map, x + xmod, y + ymod, 8, 6, direction))
      {
         staticLayout.SetCell(x, y, eTile::TT_TILES_OBJECTS_DOOR_1);

         // Remove wall next to the door.
         staticLayout.SetCell(x + xmod, y + ymod, eTile::TT_TILES_DIRT);

         return true;
      }

      return false;
   }
   else
   {
      if(MakeCorridor(map, x + xmod, y + ymod, 6, direction))
      {
         staticLayout.SetCell(x, y, eTile::TT_TILES_OBJECTS_DOOR_1);

         return true;
      }

      return false;
   }
}

bool DugneonGenerator::MakeFeature(TileMap& map)
{
   TileMapLayout& staticLayout = map.GetLayout(TileMap::eLayouts::TL_STATIC);

   auto tries = 0;
   auto maxTries = 1000;

   for(; tries != maxTries; ++tries)
   {
      // Pick a random wall or corridor tile.
      // Make sure it has no adjacent doors (looks weird to have doors next to each other).
      // Find a direction from which it's reachable.
      // Attempt to make a feature (room or corridor) starting at this point.

      int x = GetRandomInt(1, _xSize - 2);
      int y = GetRandomInt(1, _yYSize - 2);

      if(staticLayout.GetCell(x, y) != eTile::TT_TILES_BRICKS && staticLayout.GetCell(x, y) != eTile::TT_TILES_DESERTROAD)
         continue;

      if(staticLayout.IsAdjacent(x, y, eTile::TT_TILES_OBJECTS_DOOR_1))
         continue;

      if(staticLayout.GetCell(x, y + 1) == eTile::TT_TILES_DIRT || staticLayout.GetCell(x, y + 1) == eTile::TT_TILES_DESERTROAD)
      {
         if(MakeFeature(map, x, y, 0, -1, Direction::North))
            return true;
      }
      else if(staticLayout.GetCell(x - 1, y) == eTile::TT_TILES_DIRT || staticLayout.GetCell(x - 1, y) == eTile::TT_TILES_DESERTROAD)
      {
         if(MakeFeature(map, x, y, 1, 0, Direction::East))
            return true;
      }
      else if(staticLayout.GetCell(x, y - 1) == eTile::TT_TILES_DIRT || staticLayout.GetCell(x, y - 1) == eTile::TT_TILES_DESERTROAD)
      {
         if(MakeFeature(map, x, y, 0, 1, Direction::South))
            return true;
      }
      else if(staticLayout.GetCell(x + 1, y) == eTile::TT_TILES_DIRT || staticLayout.GetCell(x + 1, y) == eTile::TT_TILES_DESERTROAD)
      {
         if(MakeFeature(map, x, y, -1, 0, Direction::West))
            return true;
      }
   }

   return false;
}

bool DugneonGenerator::MakeStairs(TileMap& map, eTile tile)
{
   TileMapLayout& staticLayout = map.GetLayout(TileMap::eLayouts::TL_STATIC);

   auto tries = 0;
   auto maxTries = 10000;

   for(; tries != maxTries; ++tries)
   {
      int x = GetRandomInt(1, _xSize - 2);
      int y = GetRandomInt(1, _yYSize - 2);

      if(!staticLayout.IsAdjacent(x, y, eTile::TT_TILES_DIRT) && !staticLayout.IsAdjacent(x, y, eTile::TT_TILES_DESERTROAD))
         continue;

      if(staticLayout.IsAdjacent(x, y, eTile::TT_TILES_OBJECTS_DOOR_1))
         continue;

      staticLayout.SetCell(x, y, tile);

      return true;
   }

   return false;
}

bool DugneonGenerator::MakeDungeon(TileMap& map)
{
  // TileMapLayout& staticLayout = map.GetLayout(TileMap::eLayouts::TL_STATIC);

   // Make one room in the middle to start things off.
   MakeRoom(map, _xSize / 2, _yYSize / 2, 8, 6, GetRandomDirection());

   for(auto features = 1; features != _maxFeatures; ++features)
   {
      if(!MakeFeature(map))
      {
         std::cout << "Unable to place more features (placed " << features << ")." << std::endl;
         break;
      }
   }

   if(!MakeStairs(map, eTile::TT_TILES_OBJECTS_STAIRS_UP))
      std::cout << "Unable to place up stairs." << std::endl;

   if(!MakeStairs(map, eTile::TT_TILES_OBJECTS_STAIRS_DOWN))
      std::cout << "Unable to place down stairs." << std::endl;

   return true;
}

WorldGenerator::WorldGenerator(std::mt19937* random) : 
   MapGenerator(random)
{
   _noise.reseed(random);
   _size = 100;
   _frequency = 5.0;
   _octaves = 8;
}

void WorldGenerator::InitLayouts(TileMap& map)
{
   TileMapLayout& staticLayout = map.GetLayout(TileMap::eLayouts::TL_STATIC);
   TileMapLayout& objectsLayout = map.GetLayout(TileMap::eLayouts::TL_OBJECTS);
   
   map.Load("assets/tileset.png");

   staticLayout.Init(sf::Vector2u(32, 32), sf::Vector2i(_size, _size));
   objectsLayout.Init(sf::Vector2u(32, 32), sf::Vector2i(_size, _size));
}

bool WorldGenerator::MakeWorld(TileMap& map)
{
   const double fx = _size / _frequency;
   const double fy = _size / _frequency;

   TileMapLayout& staticLayout = map.GetLayout(TileMap::eLayouts::TL_STATIC);

   for(int x = 0; x < _size; x++) {
      for(int y = 0; y < _size; y++) {
         auto val = _noise.octaveNoise0_1(x / fx, y / fy, _octaves);
         
         if(val > 0.5) {
            staticLayout.SetCell(x, y, eTile::TT_TILES_STONE);
         } else {
            staticLayout.SetCell(x, y, eTile::TT_TILES_WATER);
         }
      }
   }

   return false;
}
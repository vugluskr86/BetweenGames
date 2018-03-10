#include <iostream>
#include <assert.h>
#include "Generator.h"
#include "TileMap.h"

DugneonGenerator::DugneonGenerator()
{
   Seed = std::random_device()();
   XSize = 80;
   YSize = 25;
   MaxFeatures = 100;
   ChanceRoom = 75;
   ChanceCorridor = 25;

   random();
}

void DugneonGenerator::InitLayouts(TileMap& map)
{
   assert(MaxFeatures > 0 && MaxFeatures <= 100);
   assert(XSize > 3 && XSize <= 80);
   assert(YSize > 3 && YSize <= 25);
   
   TileMapLayout& staticLayout = map.GetLayout(TileMap::eLayouts::TL_STATIC);
   TileMapLayout& objectsLayout = map.GetLayout(TileMap::eLayouts::TL_OBJECTS);

   random.seed(Seed);
   
   map.Load("assets/tiles_tiny_sample_2.png");

   staticLayout.Init(sf::Vector2u(32, 32), sf::Vector2i(XSize, YSize));
   objectsLayout.Init(sf::Vector2u(32, 32), sf::Vector2i(XSize, YSize));
   // MakeDungeon(map);
}


int DugneonGenerator::GetRandomInt(int min, int max)
{
   return std::uniform_int_distribution<int>(min, max)(random);
}

Direction DugneonGenerator::GetRandomDirection() 
{
   return Direction(std::uniform_int_distribution<int>(0, 3)(random));
}

bool DugneonGenerator::MakeCorridor(TileMap& map, int x, int y, int maxLength, Direction direction)
{
   assert(x >= 0 && x < XSize);
   assert(y >= 0 && y < YSize);

   assert(maxLength > 0 && maxLength <= std::max(XSize, YSize));

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

   staticLayout.SetCells(xStart, yStart, xEnd, yEnd, eTile::Corridor);

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

   staticLayout.SetCells(xStart, yStart, xEnd, yEnd, eTile::DirtWall);
   staticLayout.SetCells(xStart + 1, yStart + 1, xEnd - 1, yEnd - 1, eTile::DirtFloor);
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

   staticLayout.SetCells(xStart, yStart, xEnd, yEnd, eTile::DirtWall);
   staticLayout.SetCells(xStart + 1, yStart + 1, xEnd - 1, yEnd - 1, eTile::DirtFloor);

   //std::cout << "Room: ( " << xStart << ", " << yStart << " ) to ( " << xEnd << ", " << yEnd << " )" << std::endl;

   return true;
}

bool DugneonGenerator::MakeFeature(TileMap& map, int x, int y, int xmod, int ymod, Direction direction)
{
   TileMapLayout& staticLayout = map.GetLayout(TileMap::eLayouts::TL_STATIC);

   // Choose what to build
   auto chance = GetRandomInt(0, 100);

   if(chance <= ChanceRoom)
   {
      if(MakeRoom(map, x + xmod, y + ymod, 8, 6, direction))
      {
         staticLayout.SetCell(x, y, eTile::Door);

         // Remove wall next to the door.
         staticLayout.SetCell(x + xmod, y + ymod, eTile::DirtFloor);

         return true;
      }

      return false;
   }
   else
   {
      if(MakeCorridor(map, x + xmod, y + ymod, 6, direction))
      {
         staticLayout.SetCell(x, y, eTile::Door);

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

      int x = GetRandomInt(1, XSize - 2);
      int y = GetRandomInt(1, YSize - 2);

      if(staticLayout.GetCell(x, y) != eTile::DirtWall && staticLayout.GetCell(x, y) != eTile::Corridor)
         continue;

      if(staticLayout.IsAdjacent(x, y, eTile::Door))
         continue;

      if(staticLayout.GetCell(x, y + 1) == eTile::DirtFloor || staticLayout.GetCell(x, y + 1) == eTile::Corridor)
      {
         if(MakeFeature(map, x, y, 0, -1, Direction::North))
            return true;
      }
      else if(staticLayout.GetCell(x - 1, y) == eTile::DirtFloor || staticLayout.GetCell(x - 1, y) == eTile::Corridor)
      {
         if(MakeFeature(map, x, y, 1, 0, Direction::East))
            return true;
      }
      else if(staticLayout.GetCell(x, y - 1) == eTile::DirtFloor || staticLayout.GetCell(x, y - 1) == eTile::Corridor)
      {
         if(MakeFeature(map, x, y, 0, 1, Direction::South))
            return true;
      }
      else if(staticLayout.GetCell(x + 1, y) == eTile::DirtFloor || staticLayout.GetCell(x + 1, y) == eTile::Corridor)
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
      int x = GetRandomInt(1, XSize - 2);
      int y = GetRandomInt(1, YSize - 2);

      if(!staticLayout.IsAdjacent(x, y, eTile::DirtFloor) && !staticLayout.IsAdjacent(x, y, eTile::Corridor))
         continue;

      if(staticLayout.IsAdjacent(x, y, eTile::Door))
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
   MakeRoom(map, XSize / 2, YSize / 2, 8, 6, GetRandomDirection());

   for(auto features = 1; features != MaxFeatures; ++features)
   {
      if(!MakeFeature(map))
      {
         std::cout << "Unable to place more features (placed " << features << ")." << std::endl;
         break;
      }
   }

   if(!MakeStairs(map, eTile::UpStairs))
      std::cout << "Unable to place up stairs." << std::endl;

   if(!MakeStairs(map, eTile::DownStairs))
      std::cout << "Unable to place down stairs." << std::endl;

   return true;
}
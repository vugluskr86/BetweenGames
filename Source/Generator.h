#pragma once
#include "Types.h"

class TileMap;

class MapGenerator 
{
public:
   virtual void InitLayouts(TileMap& map) = 0;
};

class DugneonGenerator : public MapGenerator
{
public:
   DugneonGenerator();
   void InitLayouts(TileMap& map) override;

   bool MakeDungeon(TileMap& map);
   bool MakeStaticRoom(TileMap& map, int x, int y, int xLength, int yLength, Direction direction);

private:

   int GetRandomInt(int min, int max);
   Direction GetRandomDirection();
      
   bool MakeCorridor(TileMap& map, int x, int y, int maxLength, Direction direction);
   bool MakeRoom(TileMap& map, int x, int y, int xMaxLength, int yMaxLength, Direction direction);
   bool MakeFeature(TileMap& map, int x, int y, int xmod, int ymod, Direction direction);
   bool MakeFeature(TileMap& map);
   bool MakeStairs(TileMap& map, eTile tile);


   int Seed;
   int XSize, YSize;
   int MaxFeatures;
   int ChanceRoom, ChanceCorridor;
   std::mt19937 random;
};
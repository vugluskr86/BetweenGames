#pragma once
#include "Types.h"

class TileMap;

class MapGenerator 
{
protected:
   std::mt19937* _random;
public:
   MapGenerator(std::mt19937* random);

   int GetRandomInt(int min, int max);
   Direction GetRandomDirection();

   virtual void InitLayouts(TileMap& map) = 0;
};

class DugneonGenerator : public MapGenerator
{
public:
   DugneonGenerator(std::mt19937* random);
   void InitLayouts(TileMap& map) override;

   bool MakeDungeon(TileMap& map);
   bool MakeStaticRoom(TileMap& map, int x, int y, int xLength, int yLength, Direction direction);
private:
   bool MakeCorridor(TileMap& map, int x, int y, int maxLength, Direction direction);
   bool MakeRoom(TileMap& map, int x, int y, int xMaxLength, int yMaxLength, Direction direction);
   bool MakeFeature(TileMap& map, int x, int y, int xmod, int ymod, Direction direction);
   bool MakeFeature(TileMap& map);
 //  bool MakeStairs(TileMap& map, eTile tile);

   int _xSize, _yYSize;
   int _maxFeatures;
   int _chanceRoom, _chanceCorridor;
};

class WorldGenerator : public MapGenerator
{
   siv::PerlinNoise _noise;
public:
   WorldGenerator(std::mt19937* random);

   void InitLayouts(TileMap& map) override;
   bool MakeWorld(TileMap& map);
   bool MakeStaticRoom(TileMap& map, int x, int y, int xLength, int yLength);

   int _size;
   double _frequency;
   unsigned _octaves;
};

#pragma once

#include <memory>

#include "TileMap.h"

namespace BWG {
   namespace Game {
      
      struct WorldGeneratorImpl;
      struct DugneonGeneratorImpl;

      class DugneonGenerator
      {
         std::unique_ptr<DugneonGeneratorImpl> self;
      public:
         DugneonGenerator();

         void Seed(int seed);
         void InitLayouts(TileMapType& map);
         bool MakeDungeon(TileMapType& map);
         bool MakeStaticRoom(TileMapType& map, int x, int y, int xLength, int yLength, Direction direction);
      private:
         bool MakeCorridor(TileMapType& map, int x, int y, int maxLength, Direction direction);
         bool MakeRoom(TileMapType& map, int x, int y, int xMaxLength, int yMaxLength, Direction direction);
         bool MakeFeature(TileMapType& map, int x, int y, int xmod, int ymod, Direction direction);
         bool MakeFeature(TileMapType& map);
         //  bool MakeStairs(TileMap& map, eTile tile);

         //int _xSize, _yYSize;
         //int _maxFeatures;
         //int _chanceRoom, _chanceCorridor;
      };

      class WorldGenerator
      {
         //int _size;
         //double _frequency;
         //unsigned _octaves;
         //siv::PerlinNoise _noise;
         std::unique_ptr<WorldGeneratorImpl> self;         
      public:
         WorldGenerator();

         void Seed(int seed);
         void InitLayouts(TileMapType& map);
         bool MakeWorld(TileMapType& map);
         bool MakeStaticRoom(TileMapType& map, int x, int y, int xLength, int yLength);
      };
   }
}
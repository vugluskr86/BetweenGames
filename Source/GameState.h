#pragma once

#include "Types.h"

class Player;
class TileMap;
class BattleManager;
//class DugneonGenerator;
//class WorldGenerator;

class GameState
{
   sf::View _view;

  // DugneonGenerator* _dungeonGen;
  // WorldGenerator* _worldGen;
  // ItemGenerator* _itemGen;

   BattleManager* _bm;
   TileMap* _map;
   Player* _player;

   std::mt19937 _random;
   int _seed;
public:
   GameState(int seed);

   void SpawnWorld();
   void SpawnDungeon();
   void SpawnPlayer();

   bool PlayerAction(int x, int y);
   void Draw(sf::RenderWindow& window);

   void Update();

   /*
   void ProcessEvent(const sf::Event& event);
   */
};
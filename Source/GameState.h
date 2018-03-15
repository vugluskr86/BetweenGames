#pragma once

#include "Types.h"

class Player;
class TileMap;
class Monster;
class BattleManager;

class GameState
{
   sf::View _view;
   BattleManager* _bm;
   TileMap* _map;
   Player* _player;
   uint32_t _monsterCrush;
   std::mt19937 _random;
   int _seed;
   std::string _name;
public:
   GameState(int seed);

   void SetPlayerName(const std::string& name);

   void Teleport(Player* player);

   void SpawnWorld(bool isResetState = false);
   void SpawnDungeon();
   void SpawnPlayer(bool isResetState = false);
   void SpawnMonsters();
   void PlacePortal();

   bool PlayerAction(int x, int y);
   void Draw(sf::RenderWindow& window);

   void Update();

   Player* GetPlayer() { return _player;  }

   Monster* GetMonster(int x, int y);
};
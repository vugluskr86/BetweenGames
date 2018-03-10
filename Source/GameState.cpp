#include "GameState.h"

#include "TileMap.h"
#include "Generator.h"
#include "ItemGenerator.h"
#include "Player.h"
#include "BattleManager.h"
#include "Door.h"
#include "Portal.h"
#include "Stairs.h"

GameState::GameState(int seed) : 
   _seed(seed),
   _bm(nullptr),
   _player(nullptr),
   _map(nullptr)
{
   _bm = new BattleManager(_seed);
   _map = new TileMap();

   _view.reset(sf::FloatRect(0.0f, 0.0f, 1280, 720));

   _random.seed(_seed);

   SpawnDungeon();
}

void GameState::SpawnWorld()
{
   WorldGenerator gen(&_random);

   gen.InitLayouts(*_map);
   gen.MakeWorld(*_map);

   SpawnPlayer();
}

void GameState::SpawnDungeon()
{
   DugneonGenerator gen(&_random);

   gen.InitLayouts(*_map);
   gen.MakeDungeon(*_map);

   SpawnPlayer();
}

void GameState::SpawnPlayer()
{
   if(!_player) {
      auto mapSize = _map->GetMapSize();
      _player = _map->SpawnPlayer(sf::Vector2i(mapSize.x / 2.0, mapSize.y / 2.0), eTile::TT_CHAR_CHAR);
  
      /*
      auto sX = std::uniform_int_distribution<int>(0, size.x)(_random);
      auto sY = std::uniform_int_distribution<int>(0, size.y)(_random);

      for(auto x = sX; x < size.x; x++) {
         for(auto y = sY; y < size.y; y++) {
            if(_map->CanPlaced(x, y)) {
               _player = _map->SpawnPlayer(sf::Vector2i(x, y), eTile::TT_CHAR_CHAR);
               return;
            }
         }
      }
      */
   }
}

bool GameState::PlayerAction(int x, int y)
{
   auto pos = _player->GetPos();

   if(x < 0 || y < 0) {
      return false;
   }

   // Check range
   sf::IntRect moveRect(pos.x - 1, pos.y - 1, 3, 3);
   if(!moveRect.contains(sf::Vector2i(x, y))) {
      return false;
   }

   // Check pass
   if(_map->IsPassable(x, y)) {
      _player->SetPos(sf::Vector2i(x, y));
      return true;
   } else {
      // Player action (move, attack)
      auto obj = _map->IsGameObject(x, y);

      bool passTo = false;

      if(obj) {
         auto objType = obj->GetType();
         switch(objType) {
         case TO_DOOR: {
            Door* door = static_cast<Door*>(obj);
            if(door->IsOpen()) {
               passTo = true;
            }
            else {
               door->Open(*_player);
            }
            break;
         }
         }
      }

      if(passTo) {
         _player->SetPos(sf::Vector2i(x, y));
      }


      // Mobs action
   }

   return false;
}

void GameState::Draw(sf::RenderWindow& window)
{
   if(_map && _player) {
      auto pos = _player->GetPos();

      _view.setCenter(pos.x * 32, pos.y * 32);
      window.setView(_view);
      window.draw(*_map);
   }
}

void GameState::Update()
{
   _map->Update();
}
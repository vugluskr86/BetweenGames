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

   //SpawnDungeon();
   SpawnWorld();
}

void GameState::SpawnWorld()
{
   WorldGenerator gen(&_random);

   gen.InitLayouts(*_map);
   gen.MakeWorld(*_map);

   auto mapSize = _map->GetMapSize();

   SpawnPlayer();

   auto pPos = _player->GetPos();
   auto obj = new Portal(this);
   obj->SetPos(sf::Vector2i(pPos.x + 1, pPos.y + 1));
   _map->AddObject(obj);
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

      int trySpawn = mapSize.x * mapSize.y;

      while(trySpawn > 0) {
         auto x = std::uniform_int_distribution<int>(0, mapSize.x)(_random);
         auto y = std::uniform_int_distribution<int>(0, mapSize.y)(_random);

         if(_map->CanPlaced(x, y)) {
            _player = _map->SpawnPlayer(sf::Vector2i(x, y), eTile::TT_CHAR_CHAR);
            break;
         }

         --trySpawn;
      }

      if(!_player) {
         _player = _map->SpawnPlayer(sf::Vector2i(mapSize.x / 2.0, mapSize.y / 2.0), eTile::TT_CHAR_CHAR);
      }
   }
}

void GameState::Teleport(Player* player)
{
   _player = player;

   _map->Clear();
   _map->SetPlayer(player);

   WorldGenerator gen(&_random);

   gen.InitLayouts(*_map);
   gen.MakeWorld(*_map);

   auto mapSize = _map->GetMapSize();

   auto pPos = player->GetPos();
   auto obj = new Portal(this);
   obj->SetPos(sf::Vector2i(pPos.x + 1, pPos.y + 1));
   _map->AddObject(obj);
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

   // self click
   if(pos.x == x && pos.y == y) {
      auto obj = _map->IsGameObject(x, y);
      if(obj) {
         auto objType = obj->GetType();
         switch(objType) {
         case TO_PORTAL: {
            Portal* door = static_cast<Portal*>(obj);
            door->Teleport(_player);
            return true;
         }
         }
      }
      return false;
   }

   // Check pass
   if(_map->IsPassable(x, y)) {
      _player->SetPos(sf::Vector2i(x, y));
      return true;
   } else {
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
         case TO_PORTAL: {
            passTo = true;
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
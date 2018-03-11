#include "GameState.h"

#include "TileMap.h"
#include "Generator.h"
#include "ItemGenerator.h"
#include "Player.h"
#include "BattleManager.h"
#include "Door.h"
#include "Portal.h"
#include "Stairs.h"
#include "Monster.h"
#include "MobGenerator.h"


GameState::GameState(int seed) : 
   _seed(seed),
   _bm(nullptr),
   _player(nullptr),
   _map(nullptr)
{
   _random.seed(_seed);

   _bm = new BattleManager(&_random);
   _map = new TileMap();

   _view.reset(sf::FloatRect(0.0f, 0.0f, 1280, 720));

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


   SpawnMonsters();
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
      MobGenerator _mobGen(&_random);

      // Select mob type
      auto rMobIdx = std::uniform_real_distribution<>(0.0, 1.0)(_random);
      auto it = MobGenerator::NAME_2_TILE.begin();
      std::advance(it, rand() % MobGenerator::NAME_2_TILE.size());
      auto mobClass = *select_randomly(Mob::ClassLeveling.begin(), Mob::ClassLeveling.end());
      Mob mob = _mobGen.GenerateMob(10, mobClass, true);

      _player = new Player(eTile::TT_CHAR_CHAR, "Hero", mob, 4.0);

      auto mapSize = _map->GetMapSize();
      _player->SetPos(sf::Vector2i(mapSize.x / 2.0, mapSize.y / 2.0));

      int trySpawn = mapSize.x * mapSize.y;
      while(trySpawn > 0) {
         auto x = std::uniform_int_distribution<int>(0, mapSize.x - 1)(_random);
         auto y = std::uniform_int_distribution<int>(0, mapSize.y - 1)(_random);
         if(_map->CanPlaced(x, y)) {
            _player->SetPos(sf::Vector2i(x, y));
            break;
         }
         --trySpawn;
      }

      _map->SetPlayer(_player);
   }
}

void GameState::SpawnMonsters()
{
   auto mapSize = _map->GetMapSize();

   Mob& playerMob = _player->GetMobPtr();

   MobGenerator _mobGen(&_random);

   int trySpawn = mapSize.x * mapSize.y;
   int spawnNeed = 100;
   int spawned = 0;
   while(trySpawn > 0) {
      auto x = std::uniform_int_distribution<int>(0, mapSize.x - 1)(_random);
      auto y = std::uniform_int_distribution<int>(0, mapSize.y - 1)(_random);

      if(_map->CanPlaced(x, y)) {
         // Select mob type
         auto rMobIdx = std::uniform_real_distribution<>(0.0, 1.0)(_random);
         auto it = MobGenerator::NAME_2_TILE.begin();
         std::advance(it, rand() % MobGenerator::NAME_2_TILE.size());
         auto mobClass = *select_randomly(Mob::ClassLeveling.begin(), Mob::ClassLeveling.end());
         Mob mob = _mobGen.GenerateMob(playerMob._level, mobClass, true);

         Monster* monster = new Monster(it->second, it->first, mob);
         monster->SetPos(sf::Vector2i(x, y));
         _map->AddMonster(monster);

         spawned++;
      }
      if(spawned >= spawnNeed) {
         break;
      }
      --trySpawn;
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

   SpawnMonsters();
}

bool GameState::PlayerAction(int x, int y)
{
   auto pos = _player->GetPos();
   Mob& playerMob = _player->GetMobPtr();

   playerMob.Regen();

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

   bool _isAction = false;

   // Check pass
   if(_map->IsPassable(x, y)) {
      _player->SetPos(sf::Vector2i(x, y));
      _isAction = true;
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

            _isAction = true; 
            break;
         }
         case TO_PORTAL: {
            passTo = true;
            _isAction = true;
            break;
         }
         }
      } else {
         Monster* monster = _map->IsMonster(x, y);
         if(monster && _bm) {
            Mob& monsterMob = monster->GetMobPtr();
            std::vector<BattleManager::BattleResult> res;
            _bm->Battle(playerMob, monsterMob, res);
            _bm->ToLog(res, _player->GetName(), monster->GetName());
            if(!monsterMob.IsDie()) {
               monster->OnPlayerAttack(_bm, _player);
            }
            else {
               GAME_LOG("%s die\n", monster->GetName().c_str());
               // TODO : Remove mob from map
            }
            _isAction = true;
         }
      }
      
      if(playerMob.IsDie()) {
         GAME_LOG("Player %s die\n", _player->GetName().c_str());
      } else {
         if(passTo) {
            _player->SetPos(sf::Vector2i(x, y));
         }

         if(_isAction) {
            _map->MonstersTurn();
         }
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

Monster* GameState::GetMonster(int x, int y)
{
   return _map->IsMonster(x, y);
}
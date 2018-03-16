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
   _map(nullptr),
   _monsterCrush(0)
{
   _name = "Hero";

   _random.seed(_seed);

   _bm = new BattleManager(&_random);
   _map = new TileMap();

   _view.reset(sf::FloatRect(0.0f, 0.0f, 1280, 720));

   //SpawnDungeon();
//   SpawnWorld();
}

void GameState::SetPlayerName(const std::string& name)
{
   _name = name;
}

void GameState::SpawnWorld(bool isResetState)
{
   WorldGenerator gen(&_random);

   gen.InitLayouts(*_map);
   gen.MakeWorld(*_map);

   auto mapSize = _map->GetMapSize();

   SpawnPlayer(isResetState);
   SpawnMonsters();
   PlacePortal();
}

void GameState::SpawnDungeon()
{
   DugneonGenerator gen(&_random);

   gen.InitLayouts(*_map);
   gen.MakeDungeon(*_map);

   SpawnPlayer();
}

static std::map<eMobClassType, eTile> PLAYER_CLASS_2_TILE = {
   { eMobClassType::EMC_ONE_HAND, eTile::TT_CHAR_CHAR2HANDAXE },
   { eMobClassType::EMC_TWO_HAND, eTile::TT_CHAR_CHARAXESHIELD },
   { eMobClassType::EMC_RIFLE, eTile::TT_CHAR_CHARRIFLE }
};

void GameState::SpawnPlayer(bool isResetState)
{
   auto mapSize = _map->GetMapSize();
   MobGenerator _mobGen(&_random);

   if(!_player) {
      // Select mob type
      auto rMobIdx = std::uniform_real_distribution<>(0.0, 1.0)(_random);
      auto it = MobGenerator::NAME_2_TILE.begin();
      std::advance(it, rand() % MobGenerator::NAME_2_TILE.size());
      auto mobClass = *select_randomly(Mob::ClassLeveling.begin(), Mob::ClassLeveling.end());
      Mob mob = _mobGen.GenerateMob(1, mobClass, true);
      _player = new Player(PLAYER_CLASS_2_TILE[mob._class._class], _name, mob, 1.0);
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
   else {
      if(isResetState) {
         auto rMobIdx = std::uniform_real_distribution<>(0.0, 1.0)(_random);
         auto it = MobGenerator::NAME_2_TILE.begin();
         std::advance(it, rand() % MobGenerator::NAME_2_TILE.size());
         auto mobClass = *select_randomly(Mob::ClassLeveling.begin(), Mob::ClassLeveling.end());
         Mob mob = _mobGen.GenerateMob(1, mobClass, true);

         _player->SetMob(mob);
         _player->SetTile(PLAYER_CLASS_2_TILE[mob._class._class]);
      }
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
   }

   auto resPos = _player->GetPos();
   _map->SetSelection(sf::Vector2i(resPos.x, resPos.y));
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

		 //lvl mob generator
         std::uniform_int_distribution<> int_rnd01(0, 1);
         Mob mob = _mobGen.GenerateMob(playerMob._level + int_rnd01(_random), mobClass, true);

         Monster* monster = new Monster(it->second, it->first, mob, _map);
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

void GameState::PlacePortal()
{
   /*
   auto pPos = _player->GetPos();
   auto obj = new Portal(this, false);
   obj->SetPos(sf::Vector2i(pPos.x + 1, pPos.y + 1));
   _map->AddObject(obj);
   */

   auto mapSize = _map->GetMapSize();
   int trySpawn = mapSize.x * mapSize.y;
   while(trySpawn > 0) {
      auto x = std::uniform_int_distribution<int>(0, mapSize.x - 1)(_random);
      auto y = std::uniform_int_distribution<int>(0, mapSize.y - 1)(_random);

      if(_map->CanPlaced(x, y)) {

         auto endPortalChance = _monsterCrush / 10000;
         auto ch = std::uniform_real_distribution<>(0, 1)(_random);
         bool isEnd = ch < endPortalChance;
       
         auto obj = new Portal(this, isEnd);
         obj->SetPos(sf::Vector2i(x, y));
         _map->AddObject(obj);

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

   SpawnPlayer();
   SpawnMonsters();
   PlacePortal();
}

bool GameState::PlayerAction(int x, int y)
{
   if(!_player) {
      return false;
   }

   _map->SetSelection(sf::Vector2i(x, y));

   auto pos = _player->GetPos();
   Mob& playerMob = _player->GetMobPtr();

   if(!playerMob.IsDie()) {
      playerMob.Regen();

      if(x < 0 || y < 0) {
         return false;
      }

      // Check range
      sf::IntRect moveRect(pos.x - 1, pos.y - 1, 3, 3);
      if(!moveRect.contains(sf::Vector2i(x, y))) {
         return false;
      }

      bool isAction = false;
      bool passTo = false;

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
         passTo = true;
      }

      // Check pass
      if(_map->IsPassable(x, y)) {
         passTo = true;
         isAction = true;
      }
      else {
         auto obj = _map->IsGameObject(x, y);

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

               isAction = true;
               break;
            }
            case TO_PORTAL: {
               passTo = true;
               isAction = true;
               break;
            }
            }
         }
         else {
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
                  _map->RemoveMonster(monster);
                  _monsterCrush++;
                  auto exp = monsterMob.GetExpPerDie();
                  _player->AddExp(exp);
                  //  delete monster; // FIXME : Tooltip crash
                  GAME_LOG("%s get %d exp\n", _player->GetName().c_str(), exp);
               }
               isAction = true;
            }
         }
         // Mobs action
      }

      if(playerMob.IsDie()) {
         GAME_LOG("Player %s die\n", _player->GetName().c_str());
      }
      else {
         if(passTo) {
            _player->SetPos(sf::Vector2i(x, y));
         }

         if(isAction) {
            _map->MonstersTurn(_bm);
         }
      }
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
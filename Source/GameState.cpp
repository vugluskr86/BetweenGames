#include "GameState.h"

#include "TileMap.h"
#include "Generator.h"
#include "ItemGenerator.h"
#include "Player.h"
#include "BattleManager.h"

GameState::GameState(int seed) : 
   _seed(seed),
   _bm(nullptr),
   _player(nullptr),
   _map(nullptr)
{
   _bm = new BattleManager(_seed);
   _map = new TileMap();

   _view.reset(sf::FloatRect(0.0f, 0.0f, 1280, 720));

   DugneonGenerator gen(23123);

   gen.InitLayouts(*_map);
   gen.MakeDungeon(*_map);

   _player = _map->SpawnPlayer(sf::Vector2i(10, 10), eTile::TT_CHAR_CHAR);
}

void GameState::SpawnWorld(int seed)
{

}

void GameState::SpawnDungeon(int seed)
{

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

/*
void GameState::ProcessEvent(const sf::Event& event)
{

}
void GameState::Draw(sf::RenderWindow& window)
{

}
*/
#pragma once

#include <memory>
#include <string>

namespace BWG {
   namespace Game {
   
      class Player;
      class Monster;
      class BattleManager;

      struct GameStateImpl;
      
      class GameState
      {
         uint32_t _monsterCrush;
         int _seed;
         std::string _name;
         std::unique_ptr<GameStateImpl> self;
      public:
         GameState(int seed);

         void SetPlayerName(const std::string& name) { _name = name;  }
         void Teleport(Player& player);
         void SpawnWorld(bool isResetState = false);
         void SpawnDungeon();
         void SpawnPlayer(bool isResetState = false);
         void SpawnMonsters();
         void PlacePortal();
         bool PlayerAction(int x, int y);
         void Draw();
         void Update();

         Player& GetPlayer();
         Monster* GetMonster(int x, int y);
      };

   }
}




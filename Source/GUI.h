#pragma once

#include "GameCommon.h"
#include <glm\vec2.hpp>

namespace BWG {
   namespace Game {

      class Mob;
      class Item;
      class Player;
      class Monster;

      static void AddLog(const char* fmt, ...);

      static void DrawPlayerInfoWindow(Player& player);
      static void DrawMobParams(Mob& mob);
      static void DrawMonsterTooltip(Monster& monster, const glm::vec2& pos);

      #define GAME_LOG(...)  (AddLog(__VA_ARGS__))
   }
}


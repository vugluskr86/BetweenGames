#pragma once

#include "Types.h"

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/CircleShape.hpp>

#include "imgui.h"
#include "imgui-SFML.h"

//class BattleManager;
//struct BattleManager::BattleResult;

class AppLog
{
private:
   ImGuiTextBuffer     Buf;
   ImGuiTextFilter     Filter;
   ImVector<int>       LineOffsets;
   bool                ScrollToBottom;
   static AppLog* _instance;
public:
   static AppLog& Instance();
public:
   void Clear();
   void AddLog(const char* fmt, ...) IM_FMTARGS(2);
   void Draw(const char* title, bool* p_open = NULL);

   // void AddBattleResult(const std::vector<BattleManager::BattleResult>& res, const std::string& attakerName, const std::string& defenderName);
};

#define GAME_LOG(...)  (AppLog::Instance().AddLog(__VA_ARGS__))

class Mob;
class Item;
class Player;
class Monster;

// FIXME : Remove class impl
class PlayerInfoWindow
{
public:
   void Draw(Player* player);
};

void ShowMobParams(Mob* mob);
void ShowMonsterTooltip(Monster* monster, const ImVec2 pos);



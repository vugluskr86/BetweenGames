#pragma once

#include <random>
#include <memory>
#include <random>
#include <cstdint>
#include <map>
#include <iostream>
#include <functional>
#include <unordered_set>
#include <iterator>
#include <ctime>
#include <type_traits>
#include <cassert>
#include <vector>
#include <iostream>
#include <utility>
#include <algorithm>
#include <sstream>

#include "GUI.h"

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/CircleShape.hpp>

#include "imgui.h"
#include "imgui-SFML.h"

#include "PerlinNoise.h"

template<typename Iter, typename RandomGenerator>
Iter select_randomly(Iter start, Iter end, RandomGenerator& g) {
   std::uniform_int_distribution<> dis(0, std::distance(start, end) - 1);
   std::advance(start, dis(g));
   return start;
}

template<typename Iter>
Iter select_randomly(Iter start, Iter end) {
   static std::random_device rd;
   static std::mt19937 gen(rd());
   return select_randomly(start, end, gen);
}

/*
enum class eTile
{
   Unused = 0,
   DirtWall = 5,
   DirtFloor = 14,
   Corridor = 15,
   Door = 2,
   UpStairs = 32,
   DownStairs = 32,
   Selector = 1,
   Player = 51,
   Mob1 = 52,
   Mob2 = 53,
   Mob3 = 54
};
*/

#include "eTiles.h"


enum class Direction
{
   North, South, East, West,
};

enum eDamageType
{
   DT_PHYSICAL,
   DT_PYRE,
   DT_FIRE,
   DT_COLD,
   DT_LIGHTNING,
   DT_ACID,
   DT_LIGHT,
   DT_DARKNESS
};

enum eSlotType
{
   ST_LEFT_HAND,
   ST_RIGHT_HAND,

   /*   
   ST_LEFT_RING,
   ST_RIGHT_RING,
   ST_AMULET,
   ST_HELMET,
   ST_BODY,
   ST_GLOVES,
   ST_BELT,
   ST_BOOTS,
   ST_TOOLS_1,
   ST_TOOLS_2,
   ST_TOOLS_3,
   ST_TOOLS_4
   */
};

enum eItemType
{
   WT_WEAPON_1H,
   WT_WEAPON_2H,
   WT_WEAPON_RIFLE,
   WT_SHIELD,
   /*
   WT_RING,
   WT_AMULET,
   WT_BODY,
   WT_GLOVES,
   WT_BELT,
   WT_BOOTS,
   WT_TOOLS
   */
};

enum eBalancePropery
{
   IP_ATTACKPWMULTMAX,
   IP_ELEMDAMAGE_PYRE,
   IP_ELEMDAMAGE_FIRE,
   IP_ELEMDAMAGE_COLD,
   IP_ELEMDAMAGE_LIGHTNING,
   IP_ELEMDAMAGE_ACID,
   IP_ELEMDAMAGE_LIGHT,
   IP_ELEMDAMAGE_DARKNESS,
   IP_ATTACKPWR,
   IP_HP,
   IP_CRIT,
   IP_RANGE,
   IP_ABSORB,
   IP_BLEEDCHANCE,
   IP_STUNCHANCE,
   IP_ATTACKPERTURN,
   IP_DODGE,
   IP_DAZECHANCE,
   IP_BLOCKVAL,
   IP_PHYSRES,
   IP_FIRERES,
   IP_COLDRES,
   IP_LIGHTRES,
   IP_ACIDRES,
   IP_BLOCKCHANCE,
   IP_COOLDOWN,
   IP_COOLDOWN_MIN
};

enum eTileObjects
{
   TO_STATIC_TILE = 0,
   TO_MONSTER,
   TO_PLAYER,
   TO_TREASURE,
   TO_PORTAL,
   TO_STAIRS
};

class TileObject 
{
protected:
   eTileObjects _type;
   eTile _tile;
   sf::Vector2f _pos;
public:
   TileObject() : _pos(0.0, 0.0) {}

   eTileObjects GetType() const
   { return _type;}

   eTile GetTile() const 
   { return _tile; }

   const sf::Vector2f& GetPos() const
   { return _pos; }

   void SetPos(sf::Vector2f pos)
   { _pos = pos; }
   void SetPos(sf::Vector2i pos)
   { _pos = sf::Vector2f(pos.x, pos.y); }
};


enum eAbilityType 
{
   AT_TWO_HANDED_SKILL,
   AT_ONE_HANDED_SKILL,
   AT_SHIELD_SKILL,
   AT_CRUSHING_BLOW
};

enum eAbilityMechaincType
{
   AMT_ACTIVE = 0,
   AMT_PASSIVE
};

enum eAbilityClassType
{
   ACT_TWO_HAND,
   ACT_ONE_HAND,
   ACT_SHIELD,
   ACT_RIFLE
};
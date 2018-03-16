#pragma once

namespace BWG {
   namespace Game {
      enum Direction
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
   }
}


#include <glm/vec2.hpp>
#include <glm/vec4.hpp>
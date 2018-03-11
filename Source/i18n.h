#pragma once

#include "Types.h"

class I18n {
public:

   static std::map<eBalancePropery, std::string> PROPERTIES;
   static std::map<eItemType, std::string> ITEM_TYPES;
   static std::map<eSlotType, std::string> SLOT_TYPES;
   static std::map<eDamageType, std::string> DAMAGE_TYPES;
   static std::map<Direction, std::string> DIRECTIONS;
   static std::map<eTileObjects, std::string> TILE_OBJECT_TYPES;
   static std::map<eAbilityType, std::string> ABILITY_TYPES;
   static std::map<eAbilityClassType, std::string> ABILITY_CLASS_TYPES;
};

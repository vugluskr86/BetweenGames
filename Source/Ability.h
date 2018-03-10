#pragma once

#include "Types.h"

class Mob;
class Item;

struct AbilityProtValue
{
   eBalancePropery prop;
   double value;
   double leveling;
};

struct AbilityProt
{
   eAbilityType type;
   eAbilityMechaincType mechType;
   eAbilityClassType cl;
   std::string name;
   std::string description;
   std::vector<AbilityProtValue> params;

   double GetValue(eBalancePropery type) const
   {
      auto it = std::find_if(params.begin(), params.end(), [type](AbilityProtValue prop){
         return prop.prop == type;
      });
      return it != params.end() ? it->value : 0.0;
   }
};

class Ability
{
   AbilityProt _prot;
public:
   static const std::vector<AbilityProt> Prototypes;

   void CalcParams(uint32_t level);

   std::map<eBalancePropery, double> params;

   void ModifyMobParams(Mob& mob);
   Item ApplyItemParams(const Item& src);
};
#pragma once

#include "GameCommon.h"

#include <vector>
#include <algorithm>
#include <map>

namespace BWG {
   namespace Game {

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
            auto it = std::find_if(params.begin(), params.end(), [type](AbilityProtValue prop) {
               return prop.prop == type;
            });
            return it != params.end() ? it->value : 0.0;
         }
      };

      class Ability
      {
         AbilityProt _prot;
         std::map<eBalancePropery, double> _params;
      public:
         static std::vector<AbilityProt> PROTOTYPES;

         Ability();

         void CalcParams(uint32_t level);
         void ModifyMobParams(Mob& mob);
         void ApplyItemParams(Item& src);
      };

   }
}


#include "Ability.h"

#include "Item.h"
#include "Mob.h"

const std::vector<AbilityProt> Ability::Prototypes = {
   { AT_TWO_HANDED_SKILL, AMT_ACTIVE, ACT_TWO_HAND, "Two-handed skill", "Two-handed skill description", {
      { IP_ATTACKPWR, 110, 5 },
      { IP_STUNCHANCE, 5, 1 }
   }},
   { AT_CRUSHING_BLOW, AMT_PASSIVE, ACT_TWO_HAND, "Crushing blow", "Crushing blow description",{
      { IP_ATTACKPWR, 150, 5 },
      { IP_STUNCHANCE, 20, 1 },
      { IP_COOLDOWN, 20, -1 },
      { IP_COOLDOWN_MIN, 10, 0 }
   }}
};

void Ability::CalcParams(uint32_t level)
{
   auto lvl = level - 1;

   params.clear();

   for(auto p : _prot.params) {
      switch(p.prop) {
      case IP_ATTACKPWR:
         params.emplace(p.prop, p.value + p.leveling * lvl);
         break;
      case IP_STUNCHANCE:
         params.emplace(p.prop, p.value + p.leveling * lvl);
         break;
      case IP_COOLDOWN:
         auto val = p.value + p.leveling * lvl;
         auto min = _prot.GetValue(IP_COOLDOWN_MIN);
         if(val < min) val = min;
         params.emplace(p.prop, val);
         break;
      }
   }
}

void Ability::ModifyMobParams(Mob& mob)
{
   switch(_prot.type) {
   default:
      break;
   case AT_TWO_HANDED_SKILL:
      break;
   case AT_CRUSHING_BLOW:
      break;
   }
}

Item Ability::ApplyItemParams(const Item& src)
{
   Item item = src;
   
   switch(_prot.type) {
   default:
      break;
   case AT_TWO_HANDED_SKILL:
      if(item.type == WT_WEAPON_2H) {
         auto coef = _prot.GetValue(IP_ATTACKPWR);
         item.MulParam(IP_ATTACKPWMULTMAX, coef / 100.0);
      }
      break;
   case AT_CRUSHING_BLOW:
      if(item.type == WT_WEAPON_2H) {
         auto coef = _prot.GetValue(IP_ATTACKPWR);
         item.MulParam(IP_ATTACKPWMULTMAX, coef / 100.0);
      }
      break;
   }

   return item;
}
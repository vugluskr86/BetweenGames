#include "Ability.h"

#include "Item.h"
#include "Mob.h"

const std::vector<AbilityProt> Ability::Prototypes = {
   { AT_TWO_HANDED_SKILL, AMT_PASSIVE, ACT_TWO_HAND, "Two-handed skill", "You like AXE with his axe. Hit and stun!", {
		{ IP_ATTACKPWR, 110, 5 },
		{ IP_STUNCHANCE, 5, 1 }
   }},
   { AT_ONE_HANDED_SKILL, AMT_PASSIVE, ACT_ONE_HAND, "One-handed skill", "Do you job well. Only with one hand.",{
		{ IP_ATTACKPWR, 110, 5 },
		{ IP_CRIT, 5, 1 }
   }},
	{ AT_SHIELD_SKILL, AMT_PASSIVE, ACT_SHIELD, "Shield skill", "Not for try hard.",{
		{ IP_BLOCKVAL, 101, 1 },
		{ IP_PHYSRES, 101, 1 },
		{ IP_FIRERES, 101, 1 },
		{ IP_COLDRES, 101, 1 },
		{ IP_LIGHTRES, 101, 1 },
		{ IP_ACIDRES, 101, 1 },
		{ IP_BLOCKCHANCE, 101, 1 }
	} },
	{ AT_CRUSHING_BLOW, AMT_ACTIVE, ACT_TWO_HAND, "Crushing blow", "Blow enemy, me, mind or job. What you want man?",{
		{ IP_ATTACKPWR, 150, 5 },
		{ IP_STUNCHANCE, 20, 1 },
		{ IP_COOLDOWN, 20, -1 },
		{ IP_COOLDOWN_MIN, 10, 0 }
	} }
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
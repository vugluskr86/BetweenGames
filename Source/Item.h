#pragma once

#include "Types.h"

class Item
{
public:

   using DamageValue = std::pair<eDamageType, double>;

   eItemType type;
   eSlotType slot;
   uint32_t tier;
   uint32_t color;

   std::map<eBalancePropery, double> params;

   std::string Print();

   bool IsWeapon() const;
   bool IsShield() const;

   double GetProp(eBalancePropery prop) const;
   double GetDamage(eDamageType type) const;
   double GetResist(eDamageType damageType) const;

   void IncParam(eBalancePropery prop, double val);
   void MulParam(eBalancePropery prop, double val);

   std::vector<DamageValue> GetDamages() const;
   
   uint32_t GetAttackPerTurn() const;
};



#pragma once

#include "Types.h"

class Item
{
public:

   using DamageValue = std::pair<eDamageType, double>;

   std::string _name;
   ImVec4 _colorVec;
   eItemType type;
   eSlotType slot;
   uint32_t tier;
   uint32_t color;

   std::map<eBalancePropery, double> params;

   void BuildName();
   void BuildColor();

   std::string GetName() const {
      return _name; 
   }

   ImVec4 GetColor() const {
      return _colorVec;
   }

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



#pragma once

#include "GameObject.h"
#include <map>
#include <vector>

namespace BWG {
   namespace Game {

      class Item
      {
         std::string _name;
         glm::dvec4 _colorVec;
         eItemType _type;
         eSlotType _slot;
         uint32_t _tier;
         uint32_t _color;
         std::map<eBalancePropery, double> _params;
      public:
         using DamageValue = std::pair<eDamageType, double>;
         using ParamsIt = std::map<eBalancePropery, double>::const_iterator;

         eItemType GetType() const { return _type;  }

         std::string GetName() const { return _name; }
         glm::dvec4 GetColor() const { return _colorVec; }

         bool IsWeapon() const;
         bool IsShield() const;

         double GetProp(eBalancePropery prop) const;
         double GetDamage(eDamageType type) const;
         double GetResist(eDamageType damageType) const;

         void IncParam(eBalancePropery prop, double val);
         void MulParam(eBalancePropery prop, double val);

         std::vector<DamageValue> GetDamages() const;
         uint32_t GetAttackPerTurn() const;

         const std::map<eBalancePropery, double>& GetParams() {
            return _params;
         }

         ParamsIt ParamsBegin() const { return _params.begin(); }
         ParamsIt ParamsEnd() const { return _params.end(); }
         
         void BuildName();
         void BuildColor();

         static bool IsWeaponType(eItemType type);
         static bool IsShieldType(eItemType type);

         //Item() {}
         Item(eItemType type, eSlotType slot, uint32_t tier, uint32_t color, std::map<eBalancePropery, double> params);
      };

   }
}






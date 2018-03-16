#include "Common.h"
#include "Item.h"

#include "i18n.h"
#include <iomanip>

namespace BWG {
   namespace Game {

      static const std::vector<glm::dvec4> COLORS = {
         { 1.0, 1.0, 1.0, 1.0 },
         { 0.498, 1.0, 0, 1.0 },
         { 0.392, 0.584, 0.929, 1.0 },
         { 0.58, 0.0, 0.827, 1.0 },
         { 1.0, 0.078, 0.576, 1.0 },
         { 1.0, 1.0, 0.0, 1.0 },
         { 1.0, 0.549, 0.0, 1.0 }
      };


      bool Item::IsWeaponType(eItemType type)
      {
         switch(type)
         {
         case WT_WEAPON_RIFLE:
         case WT_WEAPON_2H:
         case WT_WEAPON_1H: {
            return true;
         }
         }

         return false;
      }

      bool Item::IsShieldType(eItemType type)
      {
         return type == WT_SHIELD;
      }

      Item::Item(eItemType type, eSlotType slot, uint32_t tier, uint32_t color, std::map<eBalancePropery, double> params) :
         _type(type),
         _slot(slot),
         _tier(tier),
         _color(color),
         _params(params)
      {
         BuildName();
         BuildColor();
      }

      void Item::BuildName()
      {
         std::ostringstream os;
         os << I18n::ITEM_TYPES[_type] << "(" << _tier << ")" << "\n";
         for(auto p : _params) {
            os << "\t" << I18n::PROPERTIES[p.first] << ":" << std::setprecision(3) << p.second << "\n";
         }
         _name = os.str();
      }

      bool Item::IsWeapon() const
      {
         return Item::IsWeaponType(_type);
      }

      bool Item::IsShield() const
      {
         return Item::IsShieldType(_type);
      }

      double Item::GetDamage(eDamageType type) const
      {
         auto baseDamage = 0.0;

         switch(type)
         {
         case DT_PHYSICAL:
            baseDamage = GetProp(IP_ATTACKPWMULTMAX);
            break;
         case DT_FIRE:
            baseDamage = GetProp(IP_ELEMDAMAGE_FIRE);
            break;
         case DT_COLD:
            baseDamage = GetProp(IP_ELEMDAMAGE_COLD);
            break;
         case DT_LIGHTNING:
            baseDamage = GetProp(IP_ELEMDAMAGE_LIGHTNING);
            break;
         case DT_ACID:
            baseDamage = GetProp(IP_ELEMDAMAGE_ACID);
            break;
         case DT_PYRE:
            baseDamage = GetProp(IP_ELEMDAMAGE_PYRE);
            break;
         case DT_LIGHT:
            baseDamage = GetProp(IP_ELEMDAMAGE_LIGHT);
            break;
         case DT_DARKNESS:
            baseDamage = GetProp(IP_ELEMDAMAGE_DARKNESS);
            break;
         }

         return baseDamage;
      }


      std::vector<Item::DamageValue> Item::GetDamages() const
      {
         std::vector<Item::DamageValue> damages;

         for(auto prop : _params)
         {
            switch(prop.first)
            {
            case IP_ATTACKPWMULTMAX:
               damages.emplace_back(DT_PHYSICAL, GetDamage(DT_PHYSICAL));
               break;
            case IP_ELEMDAMAGE_FIRE:
               damages.emplace_back(DT_FIRE, GetDamage(DT_FIRE));
               break;
            case IP_ELEMDAMAGE_COLD:
               damages.emplace_back(DT_COLD, GetDamage(DT_COLD));
               break;
            case IP_ELEMDAMAGE_LIGHTNING:
               damages.emplace_back(DT_LIGHTNING, GetDamage(DT_LIGHTNING));
               break;
            case IP_ELEMDAMAGE_ACID:
               damages.emplace_back(DT_ACID, GetDamage(DT_ACID));
               break;
            case IP_ELEMDAMAGE_PYRE:
               damages.emplace_back(DT_PYRE, GetDamage(DT_PYRE));
               break;
            case IP_ELEMDAMAGE_LIGHT:
               damages.emplace_back(DT_LIGHT, GetDamage(DT_LIGHT));
               break;
            case IP_ELEMDAMAGE_DARKNESS:
               damages.emplace_back(DT_DARKNESS, GetDamage(DT_DARKNESS));
               break;
            }
         }

         return damages;
      }

      double Item::GetProp(eBalancePropery prop) const
      {
         auto it = _params.find(prop);
         return it != _params.end() ? it->second : 0.0;
      }

      double Item::GetResist(eDamageType damageType) const
      {
         auto resist = 0.0;

         switch(damageType)
         {
         case DT_PHYSICAL:
            resist = GetProp(IP_PHYSRES);
            break;
         case DT_FIRE:
            resist = GetProp(IP_FIRERES);
            break;
         case DT_COLD:
            resist = GetProp(IP_COLDRES);
            break;
         case DT_LIGHTNING:
            resist = GetProp(IP_LIGHTRES);
            break;
         case DT_ACID:
            resist = GetProp(IP_ACIDRES);
            break;
         }

         return resist;
      }

      uint32_t Item::GetAttackPerTurn() const
      {
         return static_cast<uint32_t>(GetProp(IP_ATTACKPERTURN));
      }

      void Item::IncParam(eBalancePropery prop, double val)
      {
         auto it = _params.find(prop);

         if(it != _params.end()) {
            it->second = it->second + val;
         }
      }

      void Item::MulParam(eBalancePropery prop, double val)
      {
         auto it = _params.find(prop);

         if(it != _params.end()) {
            it->second = it->second * val;
         }
      }

      void Item::BuildColor()
      {
         _colorVec = COLORS[_color];
      }
   }
}


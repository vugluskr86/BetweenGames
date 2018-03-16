#include "Mob.h"

#include "Item.h"
#include "Ability.h"

namespace BWG {
   namespace Game {

      const std::vector<MobClassLeveling> Mob::MOB_CLASS_LEVELING = {
         { EMC_TWO_HAND, 12, 1, 2, 6, 3 },
         { EMC_RIFLE, 8, 3, 3, 4, 1 },
         { EMC_ONE_HAND, 16, 2, 1, 7, 1 }
      };

      Mob::Mob(uint32_t level, const MobClassLeveling lvlClass, uint8_t elite) :
         _level(level), _class(lvlClass), _elite(elite)
      { 
         CalcParams(_level);
      }

      Mob::Mob()
      {
         _hpRegen = 1;
         _hp = 1;
         _hpMax = 1;
         _mulHp = 1.0;
      }

      void Mob::Regen()
      {
         if(_hp > 0) {
            if(_hp <= _hpMax) {
               _hp += _hpRegen;
            }

            if(_hp > _hpMax) {
               _hp = _hpMax;
            }
         }
      }

      void Mob::CalcParams(uint32_t level)
      {
         _attackPerTurn = 1;

         _CON = _class._CON * level * _elite;
         _hpMax = (_class._HP * level) + (_CON * 8);
         _STR = _class._STR * level * _elite;
         _LUC = _class._LUC * level * _elite;
         _DEX = _class._DEX * level * _elite;

         _hpMax *= static_cast<int32_t>(std::floor(_mulHp));

         _hp = _hpMax;

         _hpRegen = static_cast<int32_t>(std::floor(_CON * 0.6));

         _atackPWR = _STR * 4;
         _dodge = _LUC * 0.4;
         _absorb = _CON * 0.2;
         _crit = _LUC * 0.1;

         _range = 0;

         for(auto slot : _slots) {
            auto item = slot.second;
            auto itemParams = item->GetParams();
            for(auto param : itemParams) {
               auto type = param.first;
               auto value = param.second;
               switch(type)
               {
               case IP_ATTACKPWR:
                  _atackPWR += value;
                  break;
               case IP_HP:
                  _hpMax += static_cast<int32_t>(std::floor(value));
                  break;
               case IP_CRIT:
                  _crit += value;
                  break;
               case IP_RANGE:
                  _range += value;
                  break;
               case IP_ABSORB:
                  _absorb += value;
                  break;
               case IP_ATTACKPERTURN:
                  _attackPerTurn = static_cast<int32_t>(std::floor(value));
                  break;
               case IP_DODGE:
                  _dodge += static_cast<int32_t>(std::floor(value));
                  break;
               default:
                  break;
               }
            }
         }

         for(auto abil : _abilities) {
            abil.first.CalcParams(abil.second);
            abil.first.ModifyMobParams(*this);
         }
      }

      void Mob::AddSlotItem(eSlotType slot, Item* item)
      {
         auto it = _slots.find(slot);

         assert(it == _slots.end());

         _slots[slot] = item;
      }

      void Mob::AddItemToInventory(Item* item)
      {
         _inventory.push_back(item);
      }

      eMobClassType Mob::GetClassType() const
      {
         return _class._class;
      }

      double Mob::GetResist(eDamageType type) const
      {
         auto resist = 0.0;
         for(auto slot : _slots) {
            // TODO : Clone method
            Item abilityItem(*slot.second);


            for(auto abil : _abilities) {
               // TODO : Remove CalcParams. Call only upgrade ability
               abil.first.CalcParams(abil.second);

               abil.first.ApplyItemParams(abilityItem);
            }

            resist += abilityItem.GetResist(type);
         }

         if(resist < 0) resist = 0;
         if(resist > 99) resist = 99;
         return resist;
      }

      uint32_t Mob::GetExpPerDie() const
      {
         return _level * 8;
      }

   }
}
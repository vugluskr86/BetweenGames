#include "Mob.h"

const std::vector<MobClassLeveling> Mob::ClassLeveling = {
   { EMC_TWO_HAND, 12, 1, 2, 2, 3 },
   { EMC_RIFLE, 8, 3, 3, 1, 1 },
   { EMC_ONE_HAND, 16, 2, 1, 4, 1 }
};

Mob::Mob()
{
   _hpRegen = 1;
   _hp = 1;
   _hpMax = 1;
}

void Mob::Regen()
{
   if(_hp < _hpMax) {
      _hp += _hpRegen;
   }
   if(_hp > _hpMax) {
      _hp = _hpMax;
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

   _hp = _hpMax;

   _hpRegen = _CON * 1.2;

   _atackPWR = _STR * 4;
   _dodge = _LUC * 0.4;
   _absorb = _CON * 0.2;
   _crit = _LUC * 0.1;

   _range = 0;

   for(auto slot : _slots) {
      auto item = slot.second;     
      for(auto param : item.params) {
         auto type = param.first;
         auto value = param.second;
         switch(type)
         {
         case IP_ATTACKPWR:
            _atackPWR += value;
            break;
         case IP_HP:
            _hpMax += value;
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
            _attackPerTurn = value;
            break;
         case IP_DODGE:
            _dodge + value;
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

void Mob::AddSlotItem(eSlotType slot, Item item)
{
   auto it = _slots.find(slot);
   
   assert(it == _slots.end());
   
   _slots[slot] = item;
}

void Mob::AddItemToInventory(const Item& item)
{
   _inventory.push_back(item);
}

double Mob::GetResist(eDamageType type) const
{
   auto resist = 0.0;
   for(auto slot : _slots) {
      Item item = slot.second;

      for(auto abil : _abilities) {
         abil.first.CalcParams(abil.second);
         item = abil.first.ApplyItemParams(item);
      }

      resist += item.GetResist(type);
   }

   if(resist < 1) resist = 1;
   if(resist > 99) resist = 99;
   return resist;
}
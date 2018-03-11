#pragma once

#include "Types.h"
#include "Item.h"
#include "Ability.h"

enum eMobClassType
{
   EMC_ONE_HAND,
   EMC_TWO_HAND,
   EMC_RIFLE
};

struct MobClassLeveling 
{
   eMobClassType _class;

   uint32_t _HP;
   uint32_t _STR;
   uint32_t _DEX;
   uint32_t _CON;
   uint32_t _LUC;
};

class Mob
{
public:
   static const std::vector<MobClassLeveling> ClassLeveling;

   //std::string _name;
   //uint32_t _exp;
   
   uint32_t _level;

   uint8_t _elite;

   // Class + leveling params
   MobClassLeveling _class;

   // HP
   uint32_t _hp;
   uint32_t _hpRegen;
   uint32_t _hpMax;
      
   // At level
   uint32_t _STR; // Сила
   uint32_t _DEX; // Ловкость
   uint32_t _CON; // Телосложение
   uint32_t _LUC; // Удача

   // Params
   double _atackPWR;
   double _dodge;
   double _absorb;
   double _crit;
   double _range;
   uint32_t _attackPerTurn;

   // slots
   std::map<eSlotType, Item> _slots;
   
   // Ability
   std::vector<std::pair<Ability, uint32_t>> _abilities;

   // inventory
   std::vector<Item> _inventory;

   bool IsDie() const { return _hp <= 0; }
public:
   Mob();
   void CalcParams(uint32_t level);
   void AddSlotItem(eSlotType slot, Item item);

   void AddItemToInventory(const Item& item);

   //void AddAbility(AbilityProt);

   void Regen();
   double GetResist(eDamageType type) const;
};
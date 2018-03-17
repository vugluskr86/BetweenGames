#pragma once

#include "GameCommon.h"

#include <vector>
#include <map>
#include <utility>
#include <memory>

#include "Ability.h"
#include "Item.h"

namespace BWG {
   namespace Game {

      // class Item;

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
         uint32_t _level;
         uint8_t _elite;
         double _mulHp;

         // Class + leveling params
         MobClassLeveling _class;

         // HP
         int32_t _hp;
         uint32_t _hpRegen;
         int32_t _hpMax;

         // At level
         uint32_t _STR;
         uint32_t _DEX;
         uint32_t _CON;
         uint32_t _LUC;

         // Params
         double _atackPWR;
         double _dodge;
         double _absorb;
         double _crit;
         double _range;
         uint32_t _attackPerTurn;

         // slots
         std::map<eSlotType, std::unique_ptr<Item> > _slots;

         // Ability
         std::vector<std::pair<Ability, uint32_t>> _abilities;

         // inventory
         std::vector<std::unique_ptr<Item> > _inventory;
      public:
         static const std::vector<MobClassLeveling> MOB_CLASS_LEVELING;

         Mob();

         uint8_t GetElite() const { return _elite; }

         uint32_t GetSTR() const { return _STR; }
         uint32_t GetDEX() const { return _DEX; }
         uint32_t GetCON() const { return _CON; }
         uint32_t GetLUC() const { return _LUC; }

         uint32_t GetRegen() const { return _hpRegen; }
         int32_t GetMaxHP() const { return _hpMax; }
         uint32_t GetAttackPerTurn() const { return _attackPerTurn; }
         double GetAttackPower() const { return _atackPWR; }

         double GetDodge() const { return _dodge; }
         double GetAbsorb() const { return _absorb; }
         double GetCrit() const { return _crit; }
         double GetRange() const { return _range; }

         double GetHP() const { return _hp; }
         double AddWear(double wear) {
            _hp -= static_cast<int32_t>(std::floor(wear));
            if(_hp < 0) _hp = 0;
            return _hp;
         }

         eMobClassType GetClassType() const;

         void SetMulHp(double mhp) {
            _mulHp = mhp;
         }

         void SetLevel(uint32_t level) {
            _level = level;
         }

         uint32_t GetLevel() const { return _level; }

         bool IsDie() const { return _hp <= 0; }

         void CalcParams(uint32_t level);
         void AddSlotItem(eSlotType slot, std::unique_ptr<Item> item);
         void AddItemToInventory(std::unique_ptr<Item> item);

         uint32_t GetExpPerDie() const;

         const std::map<eSlotType, std::unique_ptr<Item> >& GetSlots() const { return _slots; }
         const std::vector<std::pair<Ability, uint32_t>>& GetAbilities() const { return _abilities; }
         const std::vector<std::unique_ptr<Item> >& GetInventory() const { return _inventory; }

         void Regen();
         double GetResist(eDamageType type) const;

         Mob(uint32_t level, const MobClassLeveling lvlClass, uint8_t elite);
      };
   }
}
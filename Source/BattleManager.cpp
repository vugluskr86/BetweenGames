#include "BattleManager.h"

#include "i18n.h"

BattleManager::BattleManager(std::mt19937* random) 
{
   _random = random;
}

bool BattleManager::IsChance100(double chance)
{
   return std::uniform_real_distribution<double>(0, 100)(*_random) < chance;
}

void BattleManager::Battle(Mob& attacker, Mob& defender, std::vector<BattleResult>& battleResult, bool noAnswer)
{
   if(attacker._slots.size() > 0) {
      //Process attacker weapons
      for(auto slot : attacker._slots) {
         Item item = slot.second;

         if(item.IsWeapon()) {

            for(auto abil : attacker._abilities) {
               abil.first.CalcParams(abil.second);
               item = abil.first.ApplyItemParams(item);
            }

            auto attackCount = attacker._attackPerTurn + item.GetAttackPerTurn();
            for(uint32_t attackIndex = 0; attackIndex < attackCount; attackIndex++) {

               BattleResult result;

               auto power = attacker._atackPWR;

               auto attackPh = item.GetDamage(DT_PHYSICAL);
               if(attackPh > 0) power *= attackPh;

               if(IsChance100(attacker._crit)) {
                  power *= 1.5;
                  result._crytical = true;
               }
               else {
                  if(IsChance100(defender._dodge)) {
                     result._dodge = true;
                     continue;
                  }
                  else {
                     if(IsChance100(defender._absorb)) {
                        power *= 0.5;
                        result._absorbed = true;
                     }
                  }
               }

               std::vector<Item::DamageValue> itemDamages = item.GetDamages();

               // Calc phys resist
               auto resistPys = defender.GetResist(DT_PHYSICAL);
               double allDamage = power - (power / 100 * resistPys);

               result._damages.emplace_back(DT_PHYSICAL, allDamage, power);

               for(auto damage : itemDamages) {
                  eDamageType dtype = damage.first;
                  if(dtype != DT_PHYSICAL) {

                     if(dtype == DT_DARKNESS) {
                        double dvalue = power - (power / 100 * damage.second);

                        auto powerMin = dvalue * 0.3;
                        auto powerMax = dvalue * 1.0;
                        auto resPower = std::uniform_real_distribution<double>(powerMin, powerMax)(*_random);

                        result._damages.emplace_back(dtype, resPower, dvalue);
                        allDamage += resPower;
                     } else {
                        double dvalue = power - (power / 100 * damage.second);
                        auto resist = defender.GetResist(dtype);

                        auto resPower = dvalue - (dvalue / 100 * resist);

                        auto powerMin = resPower * 0.3;
                        auto powerMax = resPower * 1.0;
                        resPower = std::uniform_real_distribution<double>(powerMin, powerMax)(*_random);

                        result._damages.emplace_back(dtype, resPower, dvalue);
                        allDamage += resPower;
                     }
                  }
               }

               result._allDamage = allDamage;

               defender._hp -= allDamage;

               if(defender._hp <= 0) {
                  result._die = true;
               }

               battleResult.push_back(result);

               if(result._die) {
                  return;
               }
            }
         }
      }
   } else {
      auto power = attacker._atackPWR;

      BattleResult result;

      if(IsChance100(attacker._crit)) {
         power *= 1.5;
         result._crytical = true;
      }
      else {
         if(IsChance100(defender._dodge)) {
            result._dodge = true;
         }
         else {
            if(IsChance100(defender._absorb)) {
               power *= 0.5;
               result._absorbed = true;
            }
         }
      }

      if(!result._dodge) {
         auto resistPys = defender.GetResist(DT_PHYSICAL);
         double allDamage = power - (power / 100 * resistPys);
         result._allDamage = allDamage;
         defender._hp -= allDamage;

         if(defender._hp <= 0) {
            result._die = true;
         }

         battleResult.push_back(result);

         if(result._die) {
            return;
         }
      }
   }
}

/*
resDT - значение на которое подействовали резисты
asbDT - абсолютное значение

%mobname_a% hit(?:critical strike) %mobname_d% %allDamage% (resDT%type%(asbDT%type%), ...), (?:absorbed)
%mobname_d%(?:bleed,stun mobname_a) %s% for %i% turn (%bleed_damage%)
%mobname_a%(?:block chance for mobname_d) blocked %block_val%

//dodge
%mobname_d% dodged %mobname_a% hit

// die
*/

void BattleManager::ToLog(const std::vector<BattleManager::BattleResult>& res, const std::string& attakerName, const std::string& defenderName)
{
   for(auto action : res) {
      if(action._dodge) {
         GAME_LOG("%s dodged %s hit \n", defenderName.c_str(), attakerName.c_str());
         continue;
      }

      std::stringstream os;

      os << attakerName << " hit";
      if(action._crytical) {
         os << " critical strike";
      }
      os << " " << defenderName.c_str();
      os << " " << action._allDamage << " dmg";
      os << " (";

      for(auto d : action._damages) {
         os << I18n::DAMAGE_TYPES[std::get<BattleManager::eResultDamageValue::RDV_TYPE>(d)].c_str();
         os << " " << std::get<BattleManager::eResultDamageValue::RDV_VALUE>(d);
         os << "(" << std::get<BattleManager::eResultDamageValue::RD_ABS_VALUE>(d) << ")";
         os << ",";
      }

      os << ")";

      if(action._absorbed) {
         os << " ,(absorbed 50%)";
      }     

      GAME_LOG("%s \n", os.str().c_str());
   }
}
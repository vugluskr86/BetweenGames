
#include "GameCommon.h"
#include "BattleManager.h"
#include "Mob.h"
#include "Item.h"
#include "i18n.h"

namespace BWG {
   namespace Game {

      BattleManager::BattleManager()
      {
      }

      void BattleManager::Seed(int seed)
      {
         _random.seed(seed);
      }

      bool BattleManager::IsChance100(double chance)
      {
         return std::uniform_real_distribution<double>(0, 100)(_random) < chance;
      }

      void BattleManager::Battle(Mob& attacker, Mob& defender, std::vector<BattleResult>& battleResult, bool noAnswer)
      {
         auto attackerSlots = attacker.GetSlots();

         /*
         if(attackerSlots.size() > 0) {
            //Process attacker weapons
            for(auto slot : attackerSlots) {
               auto item = slot->second;

               if(item->IsWeapon()) {

                  auto attackerAbilities = attacker.GetAbilities();

                  for(auto abil : attackerAbilities) {
                     abil.first.CalcParams(abil.second);
                     item = abil.first.ApplyItemParams(item);
                  }

                  auto attackCount = attacker.GetAttackPerTurn() + item->GetAttackPerTurn();
                  for(uint32_t attackIndex = 0; attackIndex < attackCount; attackIndex++) {

                     BattleResult result;

                     auto power = attacker.GetAttackPower();

                     auto attackPh = item->GetDamage(DT_PHYSICAL);
                     if(attackPh > 0) power *= attackPh;

                     if(IsChance100(attacker.GetCrit())) {
                        power *= 1.5;
                        result._crytical = true;
                     }
                     else {
                        if(IsChance100(defender.GetDodge())) {
                           result._dodge = true;
                           continue;
                        }
                        else {
                           if(IsChance100(defender.GetAbsorb())) {
                              power *= 0.5;
                              result._absorbed = true;
                           }
                        }
                     }

                     std::vector<Item::DamageValue> itemDamages = item->GetDamages();

                     // Calculate phys resist
                     auto resistPys = defender.GetResist(DT_PHYSICAL);
                     double allDamage = power - (power * resistPys / 100);

                     result._damages.emplace_back(DT_PHYSICAL, allDamage, power);

                     for(auto damage : itemDamages) {
                        eDamageType dtype = damage.first;
                        if(dtype != DT_PHYSICAL) {

                           if(dtype == DT_DARKNESS || dtype == DT_PYRE || dtype == DT_LIGHT) {
                              double dvalue = power - (power  * damage.second / 100);

                              auto powerMin = dvalue * 0.3;
                              auto powerMax = dvalue * 1.0;
                              auto resPower = std::uniform_real_distribution<double>(powerMin, powerMax)(*_random);

                              result._damages.emplace_back(dtype, resPower, dvalue);
                              allDamage += resPower;
                           }
                           else {
                              double dvalue = power - (power * damage.second / 100);
                              auto resist = defender.GetResist(dtype);

                              auto resPower = dvalue - (dvalue * resist / 100);

                              auto powerMin = resPower * 0.3;
                              auto powerMax = resPower * 1.0;
                              resPower = std::uniform_real_distribution<double>(powerMin, powerMax)(*_random);

                              result._damages.emplace_back(dtype, resPower, dvalue);
                              allDamage += resPower;
                           }
                        }
                     }

                     result._allDamage = allDamage;
                     defender.AddWear(allDamage);

                     if(defender.GetHP() <= 0) {
                        result._die = true;
                     }

                     battleResult.push_back(result);

                     if(result._die) {
                        return;
                     }
                  }
               }
            }
         }
         else {
            auto power = attacker.GetAttackPower();

            BattleResult result;

            if(IsChance100(attacker.GetCrit())) {
               power *= 1.5;
               result._crytical = true;
            }
            else {
               if(IsChance100(defender.GetDodge())) {
                  result._dodge = true;
               }
               else {
                  if(IsChance100(defender.GetAbsorb())) {
                     power *= 0.5;
                     result._absorbed = true;
                  }
               }
            }

            if(!result._dodge) {
               auto resistPys = defender.GetResist(DT_PHYSICAL);
               double allDamage = power - (power  * resistPys / 100);
               result._allDamage = allDamage;
               defender.AddWear(allDamage);

               if(defender.GetHP() <= 0) {
                  result._die = true;
               }

               battleResult.push_back(result);

               if(result._die) {
                  return;
               }
            }
         }
         */
      }

      void BattleManager::ToLog(const std::vector<BattleManager::BattleResult>& res, const std::string& attakerName, const std::string& defenderName)
      {
         /*
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
         */
      }
   }
}

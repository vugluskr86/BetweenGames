#pragma once

#include <random>
#include <vector>
#include <tuple>

namespace BWG {
   namespace Game {

      class Mob;

      class BattleManager
      {
         std::mt19937 _random;
      public:
         BattleManager();

         /*
            resDT - значение на которое подействовали резисты
            asbDT - абсолютное значение

            %mobname_a% hit(?:crytical strike) %mobname_d% %allDamage% (resDT%type%(asbDT%type%), ...), (?:absorbed)
            %mobname_d%(?:bleed,stun mobname_a) %s% for %i% turn (%bleed_damage%)
            %mobname_a%(?:block chance for mobname_d) blocked %block_val%

            //dodge
            %mobname_d% dodged %mobname_a% hit

            // die
         */

         enum eResultDamageValue {
            RDV_TYPE = 0,
            RDV_VALUE,
            RD_ABS_VALUE
         };

         using ResultDamage = std::tuple<eDamageType, uint32_t, uint32_t>;

         struct BattleResult {
            bool _die;
            bool _dodge;
            bool _crytical;
            bool _absorbed;

            // NOT IMPLEMENTED
            bool _bleed;
            bool _stun;
            bool _blocked;

            uint32_t _bleedDamage;
            uint32_t _allDamage; // - from hp
            std::vector<ResultDamage> _damages;

            BattleResult() :
               _die(false), _dodge(false), _crytical(false),
               _absorbed(false), _bleed(false), _stun(false), _blocked(false),
               _bleedDamage(0), _allDamage(0)
            {}
         };

         void Seed(int seed);
         void Battle(Mob& attacker, Mob& defender, std::vector<BattleResult>& result, bool noAnswer = false);
         void ToLog(const std::vector<BattleManager::BattleResult>& res, const std::string& attakerName, const std::string& defenderName);
         bool IsChance100(double chance);
      };
   }
}
#pragma once

#include <random>
#include <unordered_set>
#include <algorithm>

namespace BWG {
   namespace Utils {

      template<typename Iter, typename RandomGenerator>
      Iter select_randomly(Iter start, Iter end, RandomGenerator& g) {
         std::uniform_int_distribution<> dis(0, std::distance(start, end) - 1);
         std::advance(start, dis(g));
         return start;
      }

      template<typename RandomGenerator>
      int GetRandomInt(int min, int max, RandomGenerator& g) {
         return std::uniform_int_distribution<int>(min, max)(g);
      }

      template<typename ST>
      ST GetSample(const std::unordered_set<ST>& s, int index) {
         double r = index % s.size();
         auto it = s.begin();
         for(; r != 0; r--) it++;
         return *it;
      }
   }
}
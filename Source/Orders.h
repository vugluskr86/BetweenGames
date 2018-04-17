#pragma once

#include <string>

namespace BWG {
   namespace Game {
   
      enum eGameOrders {
         EGO_ORDER_JOIN = 0x0,
         EGO_ORDER_MOVE,
         EGO_ORDER_ATTACK,
         EGO_ORDER_INTERACT,
         
         EGO_ORDER_COUNT
      };
   

      struct OrderJoin {
         std::string uid;
      };

   }
}
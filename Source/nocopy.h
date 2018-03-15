#pragma once

namespace BWG {
   namespace Utils {

      struct nocopy {
         nocopy() = default;
         nocopy(const nocopy&) = delete;
         nocopy& operator = (const nocopy&) = delete;
      };

   }
}
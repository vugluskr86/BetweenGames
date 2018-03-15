#pragma once

#include <array>
#include <algorithm>

namespace BWG {
   namespace Utils {

      template<typename T, uint32_t Size>
      class Array2D
      {
      public:
         using TileArrayType = std::array<T, Size * Size>;
      private:
         TileArrayType _array;
      public:
         Array2D() {
            T empty;
            reset(empty);
         }

         T& At(uint32_t xPos, uint32_t yPos) {
            return _array[xPos + yPos * Size];
         }

         const T& At(uint32_t xPos, uint32_t yPos) const {
            return _array[xPos + yPos * Size];
         }

         void Set(uint32_t xPos, uint32_t yPos, const T& type) {
            _array[xPos + yPos * Size] = type;
         }

         const TileArrayType& getRaw() {
            return _array;
         }

         void reset(const T& type) {
            std::fill(_array.begin(), _array.end(), type);
         }
      };

   }
}
#pragma once

namespace BWG {
   namespace Utils {

      struct Rect {
         int lx;
         int ly;
         int hx;
         int hy;

         Rect() {
            lx = 0;
            ly = 0;
            hx = 0;
            hy = 0;
         }

         Rect(int lx, int hx, int ly, int hy) : lx(lx), hx(hx), ly(ly), hy(hy) {}
         Rect(const Rect& other) { lx = other.lx; ly = other.ly; hx = other.hx; hy = other.hy; }


      };
   }
}
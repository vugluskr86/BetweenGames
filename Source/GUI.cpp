#include "GUI.h"

#include "Player.h"
#include "Mob.h"
#include "Monster.h"
#include "BattleManager.h"
#include "Item.h"

#include "i18n.h"
#include "imgui/imgui.h"

#include <stdio.h>
#include <stdarg.h>

namespace BWG {
   namespace Game {

      class AppLog
      {
      private:
         ImGuiTextBuffer     Buf;
         ImGuiTextFilter     Filter;
         ImVector<int>       LineOffsets;
         bool                ScrollToBottom;
         static AppLog* _instance;
      public:
         static AppLog& Instance();
      public:
         void Clear();
         void AddLog(const char* fmt, ...) IM_FMTARGS(2);
         void Draw(const char* title, bool* p_open = NULL);
      };

      AppLog* AppLog::_instance = nullptr;

      AppLog& AppLog::Instance()
      {
         if(!AppLog::_instance) {
            AppLog::_instance = new AppLog();
         }

         return *AppLog::_instance;
      }

      void AppLog::Clear() { Buf.clear(); LineOffsets.clear(); }

      void AppLog::AddLog(const char* fmt, ...) IM_FMTARGS(2)
      {
         int old_size = Buf.size();
         va_list args;
         va_start(args, fmt);
         Buf.appendfv(fmt, args);
         va_end(args);
         for(int new_size = Buf.size(); old_size < new_size; old_size++)
            if(Buf[old_size] == '\n')
               LineOffsets.push_back(old_size);
         ScrollToBottom = true;
      }

      void AppLog::Draw(const char* title, bool* p_open)
      {
         ImGui::SetNextWindowSize(ImVec2(500, 400), ImGuiCond_FirstUseEver);
         ImGui::Begin(title, p_open);
         if(ImGui::Button("Clear")) Clear();
         ImGui::SameLine();
         bool copy = ImGui::Button("Copy");
         ImGui::SameLine();
         Filter.Draw("Filter", -100.0f);
         ImGui::Separator();
         ImGui::BeginChild("scrolling", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar);
         if(copy) ImGui::LogToClipboard();

         if(Filter.IsActive())
         {
            const char* buf_begin = Buf.begin();
            const char* line = buf_begin;
            for(int line_no = 0; line != NULL; line_no++)
            {
               const char* line_end = (line_no < LineOffsets.Size) ? buf_begin + LineOffsets[line_no] : NULL;
               if(Filter.PassFilter(line, line_end))
                  ImGui::TextUnformatted(line, line_end);
               line = line_end && line_end[1] ? line_end + 1 : NULL;
            }
         }
         else
         {
            ImGui::TextUnformatted(Buf.begin());
         }

         if(ScrollToBottom)
            ImGui::SetScrollHere(1.0f);

         ScrollToBottom = false;
         ImGui::EndChild();
         ImGui::End();
      }

      void AddLog(const char* fmt, ...)
      {
         va_list argptr;
         va_start(argptr, fmt);
         AppLog::Instance().AddLog(fmt, argptr);
         va_end(argptr);
      }
      
      /*
      void DrawPlayerInfoWindow(Player& player)
      {
         auto mob = player.GetMobPtr();
         ImGui::Begin("Player info");

         ImGui::Text("Name"); ImGui::SameLine();
         ImGui::TextColored(ImVec4(1, 1, 0, 1), "%s", player.GetName().c_str());

         ImGui::Text("EXP"); ImGui::SameLine();
         ImGui::TextColored(ImVec4(1, 1, 0, 1), "%d", player.GetExp());

         DrawMobParams(mob);
         ImGui::End();
      }

      void DrawMobParams(Mob& mob)
      {
         ImGui::Text("LVL"); ImGui::SameLine();
         ImGui::TextColored(ImVec4(1, 1, 0, 1), "%d", mob.GetLevel());

         ImGui::Text("STR"); ImGui::SameLine();
         ImGui::TextColored(ImVec4(1, 1, 0, 1), "%d", mob.GetSTR()); ImGui::SameLine();

         ImGui::Text("DEX"); ImGui::SameLine();
         ImGui::TextColored(ImVec4(1, 1, 0, 1), "%d", mob.GetDEX());

         ImGui::Text("CON"); ImGui::SameLine();
         ImGui::TextColored(ImVec4(1, 1, 0, 1), "%d", mob.GetCON()); ImGui::SameLine();

         ImGui::Text("LUC"); ImGui::SameLine();
         ImGui::TextColored(ImVec4(1, 1, 0, 1), "%d", mob.GetLUC());

         ImGui::Text("HP"); ImGui::SameLine();
         ImGui::TextColored(ImVec4(1, 1, 0, 1), "%d/%d", mob.GetHP(), mob.GetMaxHP());

         ImGui::Separator();

         ImGui::Text(I18n::PROPERTIES[eBalancePropery::IP_ATTACKPWR].c_str()); ImGui::SameLine();
         ImGui::TextColored(ImVec4(1, 1, 0, 1), "%.3f", mob.GetAttackPower());

         ImGui::Text(I18n::PROPERTIES[eBalancePropery::IP_DODGE].c_str()); ImGui::SameLine();
         ImGui::TextColored(ImVec4(1, 1, 0, 1), "%.3f", mob.GetDodge());

         ImGui::Text(I18n::PROPERTIES[eBalancePropery::IP_ABSORB].c_str()); ImGui::SameLine();
         ImGui::TextColored(ImVec4(1, 1, 0, 1), "%.3f", mob.GetAbsorb());

         ImGui::Text(I18n::PROPERTIES[eBalancePropery::IP_CRIT].c_str()); ImGui::SameLine();
         ImGui::TextColored(ImVec4(1, 1, 0, 1), "%.3f", mob.GetCrit());

         ImGui::Separator();

         ImGui::Text("HP Regen"); ImGui::SameLine();
         ImGui::TextColored(ImVec4(1, 1, 0, 1), "%d", mob.GetRegen());

         ImGui::Separator();

         auto slots = mob.GetSlots();

         for(auto slot : slots) {
            auto slotTyp = slot.first;
            Game::Item* slotItem = slot.second;
            auto color = slotItem->GetColor();
            ImGui::Text("%s:", I18n::SLOT_TYPES[slotTyp].c_str());
            ImGui::SameLine();
            ImGui::TextColored(ImVec4(
               static_cast<float>(color.x), 
               static_cast<float>(color.y),
               static_cast<float>(color.z),
               static_cast<float>(color.w)
            ), "%s", slotItem->GetName().c_str());
         }
      }

      void DrawMonsterTooltip(Monster& monster, const glm::vec2& pos)
      {
         ImGuiIO& io = ImGui::GetIO();
         const ImVec2 mousepos_orig = io.MousePos;

         ImGuiWindowFlags flags = ImGuiWindowFlags_Tooltip |
            ImGuiWindowFlags_NoTitleBar |
            ImGuiWindowFlags_NoMove |
            ImGuiWindowFlags_NoResize |
            ImGuiWindowFlags_NoSavedSettings |
            ImGuiWindowFlags_AlwaysAutoResize;

         io.MousePos = ImVec2(pos.x, pos.y);

         ImGui::Begin("Monster info", NULL, flags);

         ImGui::Text("Name"); ImGui::SameLine();
         ImGui::TextColored(ImVec4(1, 1, 0, 1), "%s", monster.GetName().c_str());

         auto mob = monster.GetMobPtr();
         DrawMobParams(mob);

         ImGui::End();

         io.MousePos = mousepos_orig;
      }
      */
   }
}
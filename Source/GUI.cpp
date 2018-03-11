#include "GUI.h"

#include "Player.h"
#include "Mob.h"
#include "Monster.h"
#include "BattleManager.h"

#include "i18n.h"

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



/*
void AppLog::AddBattleResult(const std::vector<BattleManager::BattleResult>& res, const std::string& attakerName, const std::string& defenderName)
{
   for(auto action : res) {
      // res
      


   }
}
*/

void ShowMonsterTooltip(Monster* monster, const ImVec2 pos)
{
   ImGuiIO& io = ImGui::GetIO();
   const ImVec2 mousepos_orig = io.MousePos;

   ImGuiWindowFlags flags = ImGuiWindowFlags_Tooltip |
      ImGuiWindowFlags_NoTitleBar |
      ImGuiWindowFlags_NoMove |
      ImGuiWindowFlags_NoResize |
      ImGuiWindowFlags_NoSavedSettings |
      ImGuiWindowFlags_AlwaysAutoResize;

   io.MousePos = pos;

   ImGui::Begin("Monster info", NULL, flags);
 
   auto mob = monster->GetMobPtr();
   ShowMobParams(&mob);

   //  ImGui::Text("%s", str);

   /*
   if(rc)
   {
      ImVec2 wpos = ImGui::GetWindowPos();
      ImVec2 size = ImGui::GetWindowSize();

      // Return window dimensions so higher level can handle click / moving window
      *rc = { wpos.x, wpos.y, size.x, size.y };
   }
   */

   ImGui::End();

   io.MousePos = mousepos_orig;
}

void ShowMobParams(Mob* mob)
{
   ImGui::Text("LVL"); ImGui::SameLine();
   ImGui::TextColored(ImVec4(1, 1, 0, 1), "%d", mob->_level);

   ImGui::Text("STR"); ImGui::SameLine();
   ImGui::TextColored(ImVec4(1, 1, 0, 1), "%d", mob->_STR); ImGui::SameLine();

   ImGui::Text("DEX"); ImGui::SameLine();
   ImGui::TextColored(ImVec4(1, 1, 0, 1), "%d", mob->_DEX);

   ImGui::Text("CON"); ImGui::SameLine();
   ImGui::TextColored(ImVec4(1, 1, 0, 1), "%d", mob->_CON); ImGui::SameLine();

   ImGui::Text("LUC"); ImGui::SameLine();
   ImGui::TextColored(ImVec4(1, 1, 0, 1), "%d", mob->_LUC);

   ImGui::Text("HP"); ImGui::SameLine();
   ImGui::TextColored(ImVec4(1, 1, 0, 1), "%d/%d", mob->_hp, mob->_hpMax);

   ImGui::Separator();

   ImGui::Text(I18n::PROPERTIES[eBalancePropery::IP_ATTACKPWR].c_str()); ImGui::SameLine();
   ImGui::TextColored(ImVec4(1, 1, 0, 1), "%.3f", mob->_atackPWR);

   ImGui::Text(I18n::PROPERTIES[eBalancePropery::IP_DODGE].c_str()); ImGui::SameLine();
   ImGui::TextColored(ImVec4(1, 1, 0, 1), "%.3f", mob->_dodge);

   ImGui::Text(I18n::PROPERTIES[eBalancePropery::IP_ABSORB].c_str()); ImGui::SameLine();
   ImGui::TextColored(ImVec4(1, 1, 0, 1), "%.3f", mob->_absorb);

   ImGui::Text(I18n::PROPERTIES[eBalancePropery::IP_CRIT].c_str()); ImGui::SameLine();
   ImGui::TextColored(ImVec4(1, 1, 0, 1), "%.3f", mob->_crit);



   ImGui::Separator();

   ImGui::Text("HP Regen"); ImGui::SameLine();
   ImGui::TextColored(ImVec4(1, 1, 0, 1), "%d", mob->_hpRegen);

   ImGui::Separator();

   for(auto slot : mob->_slots) {
      auto slotTyp = slot.first;
      auto slotItem = slot.second;
      ImGui::Text("%s:", I18n::SLOT_TYPES[slotTyp].c_str());
      ImGui::SameLine();
      ImGui::TextColored(slotItem.GetColor(), "%s", slotItem.GetName().c_str());
   }
}

void PlayerInfoWindow::Draw(Player* player)
{
   auto mob = player->GetMobPtr();
   ImGui::Begin("Player info");
   ShowMobParams(&mob);
   ImGui::End();
}
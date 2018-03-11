#include "GUI.h"

#include "Player.h"
#include "Mob.h"
#include "Monster.h"

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


void PlayerInfoWindow::Draw(Player* player)
{
   auto mob = player->GetMobPtr();

   ImGui::Begin("Player info");

   ImGui::Text("STR"); ImGui::SameLine();
   ImGui::TextColored(ImVec4(1, 1, 0, 1), "%d", mob._STR);

   ImGui::Text("DEX"); ImGui::SameLine();
   ImGui::TextColored(ImVec4(1, 1, 0, 1), "%d", mob._DEX);

   ImGui::Text("CON"); ImGui::SameLine();
   ImGui::TextColored(ImVec4(1, 1, 0, 1), "%d", mob._CON);

   ImGui::Text("LUC"); ImGui::SameLine();
   ImGui::TextColored(ImVec4(1, 1, 0, 1), "%d", mob._LUC);

   ImGui::Text("HP"); ImGui::SameLine();
   ImGui::TextColored(ImVec4(1, 1, 0, 1), "%d/%d", mob._hp, mob._hpMax);

   ImGui::Text("HP Regen"); ImGui::SameLine();
   ImGui::TextColored(ImVec4(1, 1, 0, 1), "%d", mob._hpRegen);

   ImGui::End();
}
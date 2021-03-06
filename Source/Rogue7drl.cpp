#include "Types.h"
#include "TileMap.h"
#include "Generator.h"
#include "ItemGenerator.h"
#include "Player.h"
#include "Monster.h"
#include "Mob.h"
#include "GameState.h"

int CLB(ImGuiTextEditCallbackData* data)
{
   static int lines = 1;

   float controlWidth = *(float*)data->UserData,
      charHeight = ImGui::CalcTextSize("W").x,
      pos = (data->CursorPos*charHeight) / lines;

   if(data->EventKey == ImGuiKey_Enter)
   {
      lines++;
   }

   if(controlWidth <= pos)
   {
      data->InsertChars(data->CursorPos, "\n");
      data->BufDirty = true;
      lines++;
   }

   return data->BufTextLen;
}

int main()
{  
   // create the window
   sf::RenderWindow window(sf::VideoMode(1280, 720), "BetweenGames v0.1");
   ImGui::CreateContext();
   window.setFramerateLimit(60);
   ImGui::SFML::Init(window);
   
   GAME_LOG("Staring application ...\n");

   PlayerInfoWindow _playerInfoWindows;
   GameState _state(time(0));

   Monster* _hoverMonster = nullptr;
   sf::Vector2i _tileOver(0, 0);

   bool _isGameStart = false;

   sf::Clock deltaClock;
   while(window.isOpen())
   {
      sf::Event event;
      while(window.pollEvent(event))
      {
         ImGui::SFML::ProcessEvent(event);
         {
            switch(event.type)
            {
            case sf::Event::Closed:
               window.close();
               break;

            case sf::Event::MouseButtonPressed:
               if(event.mouseButton.button == sf::Mouse::Button::Left) {
                  sf::Vector2i pixelPos = sf::Vector2i(event.mouseButton.x, event.mouseButton.y);
                  sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);
                  _state.PlayerAction(floor(worldPos.x / 32.0), floor(worldPos.y / 32.0));
               }
               break;
            }
         }
      }

      ImGui::SFML::Update(window, deltaClock.restart());
     
      window.clear();

      if(_isGameStart) {
         auto mousePos = sf::Mouse::getPosition(window);
         sf::Vector2i pixelPos = sf::Vector2i(mousePos.x, mousePos.y);
         sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);
         sf::Vector2i tile = sf::Vector2i(floor(worldPos.x / 32.0), floor(worldPos.y / 32.0));

         if(_tileOver != tile) {
            _tileOver = tile;
            _hoverMonster = _state.GetMonster(_tileOver.x, _tileOver.y);
         }

         _state.Update();

         auto _player = _state.GetPlayer();
         if(_player) {
            _playerInfoWindows.Draw(_player);
            Mob& pMob = _player->GetMobPtr();
            if(pMob.IsDie()) {
               ImGui::OpenPopup("You die!");
               if(ImGui::BeginPopupModal("You die!", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
                  // ImGui::Text("Hello dsjfhds fhjs hfj dshfj hds");
                  ImGui::Separator();
                  if(ImGui::Button("Restart")) {
                     ImGui::CloseCurrentPopup();
                     AppLog::Instance().Clear();
                     // reset player
                     _player->Reset();
                     pMob._level = 1;
                     pMob.CalcParams(pMob._level);
                     // respawn world
                     _state.SpawnWorld(true);
                  }
                  ImGui::EndPopup();
               }
            }
         }

         if(_hoverMonster) {
            ShowMonsterTooltip(_hoverMonster, ImVec2(0, 20));
         }
      }
      else {
         ImGui::OpenPopup("BetweenGames v0.1");
         if(ImGui::BeginPopupModal("BetweenGames v0.1", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {

            static char text[2048 * 16] =
               "You woke up in a strange dark place feeling incredible pain and fume.\n"
               "- Where am I ?\n"
               "-You're at my house, you'll thank me later, stranger.\n"
               "- (paste name name) - call me like that.\nI don't remember anything, but I'm still glad that you didn't seize me.\n"
               "- I can help you, <name>.\nI have some kind of psy - powers, but you'll also have to work hard.\n"
               "(choose game game)\n"
               "You were a talented player, spending all day and night \nimproving your skill in <game>.\n Thousands of hours flew one by one.\n"
               "After standing at the pinnacle of ranked matchmaking, \nyou became bored with all of this.\nCybersport teams didn`t asked you to join them, \n I guess, they were afraid of your skill.\nAnd here comes a fall.\n"
               "Later, you got so many weirdos in your team, \nso it was impossible to play with them.\n"
               "Then, your account was banned for using cheats, \nalthough you didn`t even want to test them.\n"
               "You had nothing but to forget yourself.\nSo, you went to a local bar, where you got drunk as a pig.\n"
               "Further, you were hit by a spaceship of aliens and they hadn`t a \ngreat desire to get caught, \nso they just dropped your body in the portal.\nI saved your life.\n"
               "- Thanks for help, bro.\n"
               "- I guess, you`re getting better and you`re not gonna die.\nSo, let`s start with the piece de resistance.\nDarling, use the stove, our little cancer is almost ready for the fire!\n"
               "- Didn`t get you(die)\n"
               "- Fuck you, bitch, I`m not gonna be eaten!(attack)\n";

    
            ImGui::InputTextMultiline("Start game!", text, IM_ARRAYSIZE(text), ImVec2(600, 400), ImGuiInputTextFlags_ReadOnly);

            char bufname[64] = "Hero name";
            ImGui::Text("Input name"); ImGui::SameLine();  ImGui::InputText("", bufname, 64);

            if(ImGui::Button("Play")) {
               _state.SetPlayerName(bufname);
               _state.SpawnWorld();
               _isGameStart = true;
            }

            ImGui::EndPopup();
         }
      }

      if(_isGameStart) {
         _state.Draw(window);
         AppLog::Instance().Draw("Game log");
      }

      ImGui::SFML::Render(window);
      
      window.display();
   }

   return 0;
}


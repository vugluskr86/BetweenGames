#include "Types.h"
#include "TileMap.h"
#include "Generator.h"
#include "ItemGenerator.h"
#include "Player.h"
#include "Monster.h"
#include "Mob.h"
#include "GameState.h"

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

      auto mousePos = sf::Mouse::getPosition(window);
      sf::Vector2i pixelPos = sf::Vector2i(mousePos.x, mousePos.y);
      sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);
      sf::Vector2i tile = sf::Vector2i(floor(worldPos.x / 32.0), floor(worldPos.y / 32.0));

      if(_tileOver != tile) {
         _tileOver = tile;
         _hoverMonster = _state.GetMonster(_tileOver.x, _tileOver.y);
      }

      ImGui::SFML::Update(window, deltaClock.restart());

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
                  // reset player
                  _player->Reset();
                  pMob._level = 1;
                  pMob.CalcParams(pMob._level);
                  // respawn world
                  _state.SpawnWorld();
               }
               ImGui::EndPopup();
            }
         }
      }
      
      if(_hoverMonster) {
         ShowMonsterTooltip(_hoverMonster, ImVec2(0, 20));
      }

      window.clear();
      _state.Draw(window);
      AppLog::Instance().Draw("Game log");
      ImGui::SFML::Render(window);
      window.display();
   }

   return 0;
}


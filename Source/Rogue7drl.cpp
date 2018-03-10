#include "Types.h"
#include "TileMap.h"
#include "Generator.h"
#include "ItemGenerator.h"
#include "Player.h"


#include "GameState.h"

int main()
{  
   // create the window
   sf::RenderWindow window(sf::VideoMode(1280, 720), "BetweenGames v0.1");
   ImGui::CreateContext();
   window.setFramerateLimit(60);
   ImGui::SFML::Init(window);
   
   GAME_LOG("Staring application ...\n");

   GameState _state(time(0));

   /*
   { // TEST
      auto i = 10;
      while(i > 0)
      {
         auto item = itemGen.GenerateSlotType(eSlotType::ST_RIGHT_HAND, 8000);
         GAME_LOG("%s \n", item.Print().c_str());
         auto item1 = itemGen.GenerateSlotType(eSlotType::ST_LEFT_HAND, 20000);
         GAME_LOG("%s \n", item1.Print().c_str());
         --i;
      }
   }
   */

   /*
   sf::View view;
   DugneonGenerator gen(23123);
   WorldGenerator wgen(2313123);
   TileMap map;
   wgen.InitLayouts(map);
   wgen.MakeWorld(map);
   */

   //gen.MakeStaticRoom(map, 0, 0, 20, 20, Direction::North);
   /*
   Player* player = map.SpawnPlayer(sf::Vector2i(10, 10), eTile::TT_CHAR_CHAR);

   map.SpawnMonster(sf::Vector2i(1, 1), eTile::TT_TILES_MONSTERS_DRAGON_WARRIOR_1);
   map.SpawnMonster(sf::Vector2i(4, 5), eTile::TT_TILES_MONSTERS_FAIRY_3);
   map.SpawnMonster(sf::Vector2i(12, 8), eTile::TT_TILES_MONSTERS_INVOKER_1);
   */

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

            case sf::Event::KeyPressed:
             /*  if(event.key.code == sf::Keyboard::D)
                  pos.x -= 1.0f;
               if(event.key.code == sf::Keyboard::A)
                  pos.x += 1.0f;
               if(event.key.code == sf::Keyboard::W)
                  pos.y += 1.0f;
               if(event.key.code == sf::Keyboard::S)
                  pos.y -= 1.0f;*/
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

      _state.Update();
/*      
      ImGui::Begin("Hello, world!");
      ImGui::Button("Look at this pretty button");
      ImGui::End();
*/      
      window.clear();
      _state.Draw(window);
      AppLog::Instance().Draw("Game log");
      ImGui::SFML::Render(window);
      window.display();
   }

   return 0;
}


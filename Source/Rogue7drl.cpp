#include "Types.h"
#include "TileMap.h"
#include "Generator.h"
#include "ItemGenerator.h"
#include "Player.h"

int main()
{
   // Test item generator
   // ItemGenerator itemGen(1111);
   /*
   auto i = 10;

   while(i > 0)
   {
      auto item = itemGen.GenerateMobItem(eSlotType::ST_LEFT_HAND, 14);
      item->Print();

      --i;
   }
   */
   
   // create the window
   sf::RenderWindow window(sf::VideoMode(1280, 720), "Rogue7drl");
   ImGui::CreateContext();
   window.setFramerateLimit(60);
   ImGui::SFML::Init(window);
   
   GAME_LOG("Staring application ...\n");
   
   // TODO: GameState
   // sf::Vector2<float> pos(10.0f, 10.0f);
   
   sf::View view;
   DugneonGenerator gen;
   TileMap map;

   view.reset(sf::FloatRect(0.0f, 0.0f, 1280 / 4.0f, 720 / 4.0f));
   gen.InitLayouts(map);
   gen.MakeStaticRoom(map, 0, 0, 20, 20, Direction::North);

   Player* player = map.SpawnPlayer(sf::Vector2i(10, 10), eTile::Player);

   map.SpawnMonster(sf::Vector2i(1, 1), eTile::Mob1);
   map.SpawnMonster(sf::Vector2i(4, 5), eTile::Mob2);
   map.SpawnMonster(sf::Vector2i(12, 8), eTile::Mob3);
     
   sf::Clock deltaClock;
   while(window.isOpen())
   {
      sf::Event event;
      while(window.pollEvent(event))
      {
         ImGui::SFML::ProcessEvent(event);

         { // TODO: GameState ProcessEvent
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
                  sf::Vector2i tilePos = sf::Vector2i(floor(worldPos.x / 8.0), floor(worldPos.y / 8.0));

                  auto pos = player->GetPos();

                  if(tilePos.x >= 0 && tilePos.y >= 0) {
                     sf::IntRect moveRect(pos.x - 1, pos.y - 1, 3, 3);
                     if(moveRect.contains(tilePos)) {
                        player->SetPos(tilePos);
                     }
                  }
                  
                  map.SetSelection(sf::Vector2i(tilePos.x, tilePos.y));

                  GAME_LOG("Tile click %d %d\n", (int)tilePos.x, (int)tilePos.y);
               }
               break;
            }
         }

      }

      ImGui::SFML::Update(window, deltaClock.restart());

      map.Update();

      ImGui::Begin("Hello, world!");
      ImGui::Button("Look at this pretty button");
      ImGui::End();
      
      window.clear();

      { // TODO: GameState Draw
         auto pos = player->GetPos();
         view.setCenter(pos.x * 8, pos.y * 8);
         window.setView(view);
         map.setScale(sf::Vector2<float>(0.25, 0.25));
         window.draw(map);
         AppLog::Instance().Draw("title");
         ImGui::SFML::Render(window);
      }

      window.display();
   }

   return 0;
}


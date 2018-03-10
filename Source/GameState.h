#pragma once

#include "Types.h"

class GameState
{
public:
   void ProcessEvent(const sf::Event& event);

   void Draw(sf::RenderWindow& window);
};
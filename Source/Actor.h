#pragma once

#include "Direction.h"

#include <memory>
#include <string>
#include <vector>

namespace BWG {
   namespace Game {

      struct ActorImpl;
      class Action;

      class Actor
      {
         std::unique_ptr<ActorImpl> self;
      public:
         Actor();
         ~Actor();

         std::string GetId() const;

         void AddAction(std::unique_ptr<Action> action);
         const std::vector<std::unique_ptr<Action>>& GetActions() const;
         void EmptyAction();
      };
   }
}
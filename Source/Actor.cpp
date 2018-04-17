#include "Actor.h"


#include "Action.h"
#include "GameMapView.h"

namespace BWG {
   namespace Game {

      struct ActorImpl
      {
         std::string id;
         std::vector<std::unique_ptr<Action>> tick_actions;

         ActorImpl() {}
      };

      Actor::Actor() : self(new ActorImpl()) {}
      Actor::~Actor() {}


      std::string Actor::GetId() const
      {
         return self->id;
      }

      void Actor::AddAction(std::unique_ptr<Action> action)
      {
         self->tick_actions.emplace_back(std::move(action));
      }

      const std::vector<std::unique_ptr<Action>>& Actor::GetActions() const
      {
         return self->tick_actions;
      }

      void Actor::EmptyAction()
      {
         self->tick_actions.clear();
      }

   }
}
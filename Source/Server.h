#pragma once

#include <memory>

namespace BWG {
   namespace Net {      
      class Server
      {
         struct Client {

         };
      
      public:
         void OnClientConnected(std::unique_ptr<Client> client);
      };
   }
}
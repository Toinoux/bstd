
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>

#include <string>

#pragma once

namespace bstd {
    namespace network {
        class Socket {
        public:
            Socket();
        
        public:
            std::string getIP();
            unsigned short getPort();

        public:
            int sock;

        public:
            virtual ~Socket();
        };
    }
}
#include <string>

#pragma once

namespace bstd {
    namespace network {
        using PORT = unsigned short;
        #ifndef _WIN32
            using SOCKET = int;
        #endif

        class ISocket {
        public:
	        ISocket() {};
	        ISocket(int theType, int protocol);
            virtual PORT bind(PORT port = 0) const = 0;
            virtual void listen(int nbConnections) const = 0;
            virtual SOCKET accept(PORT port) const = 0;
            virtual void connect(PORT port, std::string const &host) const = 0;
	        virtual void close() const = 0;

        public:
           virtual ~ISocket() {};
        };
    }
}
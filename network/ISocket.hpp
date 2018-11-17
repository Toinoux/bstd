#include <string>

#pragma once

namespace bstd {
    namespace network {
        using PORT = unsigned short;

        class ISocket {
        public:
	        ISocket() {};
	        ISocket(int theType, int protocol);
            virtual PORT bind() const = 0;
            virtual void listen(int nbConnections) const = 0;
            virtual int accept(PORT port) const = 0;
            virtual void connect(PORT port, std::string const &host) const = 0;
	        virtual void close() const = 0;

        public:
           virtual ~ISocket() {};
        };
    }
}
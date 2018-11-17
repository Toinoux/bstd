all:	tcp udp

tcp: tcpclient tcpserver

udp: udpclient udpserver

tcpclient:
	g++ -std=c++17 -o tcpclient.out TCPEchoClientTester.cpp

tcpserver:
	g++ -std=c++17 -o tcpserver.out TCPEchoServerTester.cpp

udpclient:
	g++ -std=c++17 -o udpclient.out UDPEchoClientTester.cpp

udpserver:
	g++ -std=c++17 -o udpserver.out UDPEchoServerTester.cpp

#pragma once
#include "Socket.h"

class ServerSocket : public Socket
{
public:
	ServerSocket(string servername) : Socket(servername) {}
	void Listen();
	void Bind(int port);
	void StartHosting(int port);
	void AcceptClient();
};
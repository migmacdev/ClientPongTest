// Client.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#pragma comment(lib, "Ws2_32.lib")
#include <iostream>
#include <WinSock2.h>

SOCKET Connection;

void ClientThread() {
	char buffer[256];
	while (true) {
		recv(Connection, buffer, sizeof(buffer), NULL);
		std::cout << buffer << std::endl;
	}
}
int main()
{
	WSADATA wsaData;
	WORD DllVersion = MAKEWORD(2, 1);

	if (WSAStartup(DllVersion, &wsaData) != 0)
	{
		MessageBoxA(NULL, "Winsock startup failed", "Error", MB_OK | MB_ICONERROR);
		exit(1);
	}

	SOCKADDR_IN addr; //Address that will bind our listening socket to
	int sizeofaddr = sizeof(addr);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");	//Broadcast locally
	addr.sin_port = htons(1111);	//Port
	addr.sin_family = AF_INET; //IPV4 socket

	Connection = socket(AF_INET, SOCK_STREAM, NULL);
	if (connect(Connection, (SOCKADDR*)&addr, sizeofaddr) != 0) {
		MessageBoxA(NULL, "Unable to connect ", "Error", MB_OK | MB_ICONERROR);
		return 0;
	}
	std::cout << "Client connected" << std::endl;
	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ClientThread, NULL, NULL, NULL);
	char buffer[256] = "1:+1";
	while (true) {
		std::cin.get();
		send(Connection, buffer, sizeof(buffer), NULL);
		Sleep(10);
	}

    return 0;
}


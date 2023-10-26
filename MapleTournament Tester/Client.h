#pragma once

#include <WinSock2.h>
#include <WS2tcpip.h>

class Client
{
private:
	SOCKET					m_hClientSocket;

public:
	Client();
	~Client();

	bool Init(const char* _serverIP, int _serverPort);

	void JustLogin(const wchar_t* _nickname);
	void JustLogin1Byte(const wchar_t* _nickname);
	void JustLogin2Byte(const wchar_t* _nickname);
	void MakeRoom(const wchar_t* _roomTitle);
	void LoginAndMakeRoomOverload(const wchar_t* _nickname, const wchar_t* _roomTitle);
	void Logout();
};


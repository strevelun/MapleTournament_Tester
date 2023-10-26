#include <iostream>
#include <array>
#include <string>

#include "Client.h"

#pragma comment( lib, "ws2_32.lib")

enum class eActionType
{
	None,
	JustLogin,
	LoginAndMakeRoom,
	LogoutAll,
	NumOfAction
};

int main()
{
	WSADATA  wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) return 0;

	std::array<Client*, 60> arrClient;
	int clientCount = 0;
	std::wstring nickname = L"Tester";
	std::wstring roomName = L"Room";
	int input, cnt, nicknameNum = 0, roomTitleNum = 0;
	Client* pClient = nullptr;

	while (1)
	{
		system("cls");
		std::cout << "클라이언트 개수 입력(종료 : -1, 최대 60개, 현재 " << clientCount << "개) : ";
		std::cin >> cnt;
		if (cnt == -1) break;

		while (1)
		{
			system("cls");
			std::cout << "액션 입력" << '\n';
			std::cout << "1. 로그인" << '\n';
			std::cout << "2. 로그인 후 방만들기" << '\n';
			std::cout << "3. 전부 로그아웃" << '\n';
			std::cout << "입력 : ";
			std::cin >> input;
			if (int(eActionType::None) < input && input < int(eActionType::NumOfAction))
				break;
		}
		
		if (input == int(eActionType::LogoutAll))
		{ 
			for (int i = 0; i < clientCount; i++)
			{
				arrClient[i]->Logout();
				delete arrClient[i];
			}
			clientCount = 0;
			continue;
		}

		for (int i = 0; i < cnt; i++)
		{
			pClient = new Client;
			if (pClient->Init("192.168.219.167", 30001) == false)
			{
				delete pClient;
				return -1;
			}
			switch (eActionType(input))
			{
			case eActionType::JustLogin:
				pClient->JustLogin((nickname + std::to_wstring(nicknameNum++)).c_str());
				break;
			case eActionType::LoginAndMakeRoom:
				pClient->JustLogin((nickname + std::to_wstring(nicknameNum++)).c_str());
				pClient->MakeRoom((roomName + std::to_wstring(roomTitleNum++)).c_str());
				break;
			}
		
			arrClient[clientCount + i] = pClient;
		}
		clientCount += cnt;
	}

	for (int i = 0; i < clientCount; i++)
	{
		delete arrClient[i];
	}

	return 0;
}

#include "Client.h"
#include "Setting.h"
#include "iostream"

typedef unsigned short ushort;

Client::Client()
{	
	m_hClientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
}

Client::~Client()
{
	if (m_hClientSocket != INVALID_SOCKET) closesocket(m_hClientSocket);
}

bool Client::Init(const char* _serverIP, int _serverPort)
{
	SOCKADDR_IN				servAddr;	
	
	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	inet_pton(AF_INET, _serverIP, &servAddr.sin_addr);
	servAddr.sin_port = htons(_serverPort);

	if (connect(m_hClientSocket, (SOCKADDR*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR)
	{
		int error = WSAGetLastError();
		std::cout << "connect 에러코드 : " << error << '\n';
		system("pause");
		return false;
	}

	return true;
}

void Client::JustLogin(const wchar_t* _nickname)
{
	ushort count = sizeof(ushort);
	*(ushort*)(m_buffer + count) = (ushort)ePacketType::C_OKLogin;						count += sizeof(ushort);
	memcpy(m_buffer + count, _nickname, wcslen(_nickname) * 2);				count += (ushort)wcslen(_nickname) * 2;
	*(wchar_t*)(m_buffer + count) = L'\0';									count += 2;
	*(ushort*)m_buffer = count;
	send(m_hClientSocket, m_buffer, *(u_short*)m_buffer, 0);
}

void Client::JustLogin1Byte(const wchar_t* _nickname)
{
	ushort count = sizeof(ushort);
	*(ushort*)(m_buffer + count) = (ushort)ePacketType::C_OKLogin;						count += sizeof(ushort);
	memcpy(m_buffer + count, _nickname, wcslen(_nickname) * 2);				count += (ushort)wcslen(_nickname) * 2;
	*(wchar_t*)(m_buffer + count) = L'\0';									count += 2;
	*(ushort*)m_buffer = count;

	send(m_hClientSocket, m_buffer, 1, 0);
}

void Client::JustLogin1ByteLeft()
{
	send(m_hClientSocket, m_buffer + 1, *(ushort*)m_buffer - 1, 0);
}

void Client::JustLogin2Byte(const wchar_t* _nickname)
{
	ushort count = sizeof(ushort);
	*(ushort*)(m_buffer + count) = (ushort)ePacketType::C_OKLogin;						count += sizeof(ushort);
	memcpy(m_buffer + count, _nickname, wcslen(_nickname) * 2);				count += (ushort)wcslen(_nickname) * 2;
	*(wchar_t*)(m_buffer + count) = L'\0';									count += 2;
	*(ushort*)m_buffer = count;

	send(m_hClientSocket, m_buffer, 2, 0);
}

void Client::JustLogin2ByteLeft()
{
	send(m_hClientSocket, m_buffer + 2, *(ushort*)m_buffer - 2, 0);
}

void Client::MakeRoom(const wchar_t* _roomTitle)
{
	char buffer[255];
	ushort count = sizeof(ushort);
	*(ushort*)(buffer + count) = (ushort)ePacketType::C_CreateRoom;				count += sizeof(ushort);
	memcpy(buffer + count, _roomTitle, wcslen(_roomTitle) * 2);			                    count += (ushort)wcslen(_roomTitle) * 2;
	*(wchar_t*)(buffer + count) = L'\0';								        count += 2;
	*(ushort*)buffer = count;
	send(m_hClientSocket, buffer, *(ushort*)buffer, 0);
}

void Client::LoginAndMakeRoomOverload(const wchar_t* _nickname, const wchar_t* _roomTitle)
{
	char buffer[255];
	ushort count = sizeof(ushort);
	*(ushort*)(buffer + count) = (ushort)ePacketType::C_OKLogin;						count += sizeof(ushort);
	memcpy(buffer + count, _nickname, wcslen(_nickname) * 2);				count += (ushort)wcslen(_nickname) * 2;
	*(wchar_t*)(buffer + count) = L'\0';									count += 2;
	*(ushort*)buffer = count;
	ushort OKLoginCount = count;

	count = sizeof(ushort);
	*(ushort*)(buffer + OKLoginCount + count) = (ushort)ePacketType::C_CreateRoom;			count += sizeof(ushort);	
	memcpy(buffer + OKLoginCount + count, _roomTitle, wcslen(_roomTitle) * 2);				count += (ushort)wcslen(_roomTitle) * 2;			
	*(wchar_t*)(buffer + OKLoginCount + count) = L'\0';										count += 2;		
	*(ushort*)(buffer + OKLoginCount) = count;

	send(m_hClientSocket, buffer, count + OKLoginCount, 0);
}

void Client::Logout()
{
	char buffer[255];
	ushort count = sizeof(ushort);
	*(ushort*)(buffer + count) = (ushort)ePacketType::C_Exit;					count += sizeof(ushort);
	*(ushort*)buffer = count;
	send(m_hClientSocket, buffer, *(ushort*)buffer, 0);
}
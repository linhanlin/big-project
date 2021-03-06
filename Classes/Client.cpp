#include "Client.h"
#include <ctime>
#include <thread>
#include <algorithm>
#include "cocos2d.h"

USING_NS_CC;

extern Information information;

Client* Client::client = new Client();

bool Client::init()
{
	if (WSAStartup(MAKEWORD(2, 2), &wsaData))//成功返回0  
	{
		return FALSE;
	}

	SOCKET sHost = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (INVALID_SOCKET == sHost)
	{
		closesocket(sHost);
		WSACleanup();
		return FALSE;
	}

	//3 准备通信地址  
	SOCKADDR_IN addrServer;
	addrServer.sin_family = AF_INET;
	addrServer.sin_port = htons(PORT);
	addrServer.sin_addr.s_addr = inet_addr("192.168.0.3");
	
	return true;
}

BOOL Client::ConnectServer()
{
	if (SOCKET_ERROR == connect(sHost, (const sockaddr*)&addrServer, sizeof(addrServer)))
	{
		//cout <<clock()-start;
		closesocket(sHost);
		WSACleanup();
		system("pause");
		return FALSE;
	}

	return TRUE;
}

BOOL Client::recv_Cli()
{
	char recvBuf[BUFLEN+1];
	ZeroMemory(recvBuf, sizeof(recvBuf));
	if (SOCKET_ERROR == recv(sHost, recvBuf, sizeof(recvBuf), 0))
	{
		//closesocket(sHost);
		//WSACleanup();
		return FALSE;
	}
	recvBuf[BUFLEN] = '\0';
	information.setRecvBuf(recvBuf);

	return TRUE;
}

BOOL Client::send_Cli(string sendBuf)
{
	clock_t start = clock();
	while (true)
	{
		if (SOCKET_ERROR == send(sHost, const_cast<char *>(sendBuf.c_str()), information.getSendBuf().length(), 0))
		{
			//closesocket(sHost);
			//WSACleanup();
			if (clock() - start > TIMEOUTERROR)
			{
				log("send message %s fail,time out", information.getSendBuf().c_str());
				break;
			}
			Sleep(WAITTIME);
			continue;
		}
		//information.clearSendBuf();
		break;
	}
	return TRUE;
}

Client::Client()
{
	if (!init())
	{
		log("init Client false!");
	}

	if (!ConnectServer())
	{
		log("can't connect Server!");
	}
}

Client* Client::getInstance()
{
	return client;
}

void Client::SendThread()
{
	while (true)
	{
		send_Cli();
		Sleep(TIME_LAG);
	}
}

void Client::RecvThread()
{
	while (true)
	{
		recv_Cli();
		Sleep(TIME_LAG);
	}
}

void Client::StartClient()
{
	thread SendThread(client->SendThread);
	SendThread.detach();
	thread RecvThread(client->RecvThread);
	RecvThread.detach();
}

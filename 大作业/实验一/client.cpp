
#include <stdio.h>
#include <WinSock2.h>
#include <windows.h>
#include <iostream>
#include <thread>
#include <string>
#pragma comment(lib, "ws2_32.lib")  //加载 ws2_32.dll

#define BUF_SIZE 100

DWORD WINAPI Send(LPVOID sockpara) {
	SOCKET * sock = (SOCKET*)sockpara;
	char bufSend[BUF_SIZE] = { 0 };
	while (1) {
		//printf("Input a string: ");
		std::cin >> bufSend;
		int t = send(*sock, bufSend, strlen(bufSend), 0);
		if (strcmp(bufSend, "quit()") == 0)
		{
			SYSTEMTIME st = { 0 };
			GetLocalTime(&st);
			closesocket(*sock);
			std::cout << "您已于" << st.wDay << "日" << st.wHour << "时" << st.wMinute << "分" << st.wSecond << "秒退出聊天室" << std::endl;
			return 0L;
		}
		if (t > 0) {
			SYSTEMTIME st = { 0 };
			GetLocalTime(&st);
			std::cout << "消息已于" << st.wDay << "日" << st.wHour << "时" << st.wMinute << "分" << st.wSecond << "秒成功发送\n" ;
			std::cout << "-------------------------------------------------------------" << std::endl;
		}
		memset(bufSend, 0, BUF_SIZE);  
	}
}


DWORD WINAPI Recv(LPVOID sock_) {
	char bufRecv[BUF_SIZE] = { 0 };
	SOCKET *sock = (SOCKET*)sock_;
	while (1) {
		int t = recv(*sock, bufRecv, BUF_SIZE, 0);
		if (strcmp(bufRecv, "quit()") == 0)
		{
			SYSTEMTIME st = { 0 };
			GetLocalTime(&st);
			closesocket(*sock);
			std::cout << "对方已于" << st.wDay << "日" << st.wHour << "时" << st.wMinute << "分" << st.wSecond << "秒下线退出聊天室" << std::endl;
			return 0L;
		}
		if (t > 0) {
			SYSTEMTIME st = { 0 };
			GetLocalTime(&st);
			std::cout << st.wDay << "日" << st.wHour << "时" << st.wMinute << "分" << st.wSecond << "秒收到消息:";
			printf(" %s\n", bufRecv);
			std::cout << "-------------------------------------------------------------" << std::endl;
		}
		memset(bufRecv, 0, BUF_SIZE);
	}
}


int main() {
	//初始化DLL
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) == 0)
	{
		std::cout << "Call WSAStartup succseefully!" << std::endl;
	}
	else {
		std::cout << "Call WSAStartup unsuccseeful!" << std::endl;
		return 0;
	}
	sockaddr_in sockAddr;
	memset(&sockAddr, 0, sizeof(sockAddr));  //每个字节都用0填充
	sockAddr.sin_family = PF_INET;
	sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	sockAddr.sin_port = htons(1234);
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if (connect(sock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR)) == 0)
	{
		std::cout << "成功进入聊天室" << std::endl;
	}
	else {
		std::cout << "聊天室未上线" << std::endl;
		return 0;
	}
	//std::cout << WSAGetLastError() << std::endl;
	//std::cout << sock << std::endl;
	HANDLE hThread[2];
	hThread[0] = CreateThread(NULL, 0, Recv, (LPVOID)&sock, 0, NULL);
	hThread[1] = CreateThread(NULL, 0, Send, (LPVOID)&sock, 0, NULL);
	WaitForMultipleObjects(2, hThread, TRUE, INFINITE);
	CloseHandle(hThread[0]);
	CloseHandle(hThread[1]);
	closesocket(sock); 
	WSACleanup(); 
	return 0;
}

#include "stdafx.h"
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "Sending-Email.h"
#include <iostream>
#include "SmtpMail.h"
#include "SmtpMailDlg.h"
using namespace std;

SmtpMail::SmtpMail(const char* s, const char* p, const char*u, const char* w, const char* f, const char* t, const char* j, const char *m)
{
	strcpy(SmtpSrvName, s);
	strcpy(Port, p);
	strcpy(UserName, u);
	strcpy(Password, w);
	strcpy(From, f);
	strcpy(To, t);
	strcpy(Subject, j);
	strcpy(Msg, m);
}

int SmtpMail::Talk(SOCKET sockid, const char *OkCode, char *pSend)
{
	const int buflen = 256;
	char buf[buflen];
	ZeroMemory(buf, buflen);
	//接收返回信息
	if (recv(sockid, buf, buflen, 0) == SOCKET_ERROR)
	{
		printf("recv() error : %d\n", GetLastError());
		return 1;
	}
	else
		printf("%s\n", buf);
	if (strstr(buf, OkCode) == NULL)
	{
		printf("Error: recv code != %s\n", OkCode);
	}
	//发送命令
	if (lstrlen(pSend))
	{
		ZeroMemory(buf, buflen);
		wsprintf(buf, "%s\r\n", pSend);
		if (send(sockid, buf, lstrlen(buf), 0) == SOCKET_ERROR)
		{
			printf("send() error : %d\n", GetLastError());
			return 1;
		}
	}
	return 0;
}

int SmtpMail::SendMail()
{
	const int buflen=1024;
	char buf[buflen];
	int i, userlen, passlen;

	// （1）初始化网络环境
	WSADATA wsadata;
	if(WSAStartup(MAKEWORD(2,2),&wsadata)!=0)
	{
		printf("WSAStartup() error: %d\n",GetLastError());
		return 1;
	}

	// （2）创建套接字
	SOCKET sockid;
	if((sockid=socket(AF_INET, SOCK_STREAM, 0))==INVALID_SOCKET)
	{
		printf("socket() error: %d\n",GetLastError);
		return 1;
	}

	// （3）得到SMTP服务器IP
	struct hostent *phostent =gethostbyname(SmtpSrvName);
	struct sockaddr_in addr;
	CopyMemory(&addr.sin_addr.S_un.S_addr, phostent->h_addr_list[0], sizeof(addr.sin_addr.S_un.S_addr));
	struct in_addr srvaddr;
	CopyMemory(&srvaddr, &addr.sin_addr.S_un.S_addr, sizeof(struct in_addr));
	printf("Smtp server name is %s\n", SmtpSrvName);
	printf("Smtp serve IP is %s\n", inet_ntoa(srvaddr));
	addr.sin_family=AF_INET;
	addr.sin_port=htons(atoi(Port));
	ZeroMemory(&addr.sin_zero, 8);
	cout << endl;

	// （4）连接服务器
	if(connect(sockid, (struct sockaddr*)&addr, sizeof(struct sockaddr_in))==SOCKET_ERROR)
	{
		printf("Connect() error: %d\n", GetLastError());
		goto STOP;
	}

	// （5）按照SMTP收发信息
	if(Talk(sockid, "220", "HELO 127.0.0.1"))
		goto STOP;
	if(Talk(sockid, "250", "AUTH LOGIN"))
		goto STOP;
	ZeroMemory(buf, buflen);
	
	cout << "----1---------------" << endl;
	userlen = lstrlen(UserName);
	for(i=0; i<(userlen%3? userlen/3+1: userlen/3); i++)
		Base64((unsigned char*)(UserName+i*3),(unsigned char*)(buf+i*4));
	if(Talk(sockid, "334", buf))  // "dGVyZW5jZXJpY2h0b2ZlbkBzaW5hLmNu"
		goto STOP;
	cout << buf << endl;
	ZeroMemory(buf, buflen);
	
	cout << "----2---------------" << endl;
	passlen = lstrlen(Password);
	for(i=0; i<(passlen%3? passlen/3+1: passlen/3); i++)
		Base64((unsigned char*)(Password+i*3),(unsigned char*)(buf+i*4));
	if (Talk(sockid, "334", buf))  // "dGVyZW5jZWZqeQ=="
		goto STOP;
	cout << buf << endl;
	ZeroMemory(buf, buflen);
	
	cout << "----3---------------" << endl;
	wsprintf(buf, "MAIL FROM:<%s>", From);
	if(Talk(sockid, "235", buf))
		goto STOP;
	cout << buf << endl;
	ZeroMemory(buf, buflen);
	
	cout << "----4---------------" << endl;
	wsprintf(buf, "RCPT TO:<%s>", To);
	if(Talk(sockid, "250", buf))
		goto STOP;
	if(Talk(sockid, "250", "DATA"))
		goto STOP;
	cout << buf << endl;
	ZeroMemory(buf, buflen);
	
	cout << "----5---------------" << endl;
	wsprintf(buf, "TO: %s\r\nFROM: %s\r\nSUBJECT: %s\r\n\r\n%s\r\n.", To, From, Subject, Msg);
	if(Talk(sockid, "354", buf))
		goto STOP;
	cout << buf << endl;
	if(Talk(sockid, "250", "QUIT"))
		goto STOP;
	if(Talk(sockid, "221", ""))
		goto STOP;
	else
	{
		closesocket(sockid);
		WSACleanup();
		return 0;
	}
	
	// （6）关闭Socket，释放网络资源
STOP:
	closesocket(sockid);
	WSACleanup();
	return 1;
}


//Base64编码，chasc：未编码的二进制代码，chuue：编码过的Base64代码
void SmtpMail::Base64(unsigned char *chasc, unsigned char *chuue)
{
	int i, k = 2;
	unsigned char t = 0;
	for (i = 0; i<3; i++)
	{
		*(chuue + i) = *(chasc + i) >> k;
		*(chuue + i) |= t;
		t = *(chasc + i) << (8 - k);
		t >>= 2;
		k += 2;
	}
	*(chuue + 3) = *(chasc + 2) & 63;
	for (i = 0; i<4; i++)
		if ((*(chuue + i) >= 0) && (*(chuue + i) <= 25)) 
			*(chuue + i) += 65;
		else if ((*(chuue + i) >= 26) && (*(chuue + i) <= 51)) 
			*(chuue + i) += 71;
		else if ((*(chuue + i) >= 52) && (*(chuue + i) <= 61)) 
			*(chuue + i) -= 4;
		else if (*(chuue + i) == 62) 
			*(chuue + i) = 43;
		else if (*(chuue + i) == 63) 
			*(chuue + i) = 47;
}
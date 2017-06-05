#include <winsock2.h>

class SmtpMail
{
private:
	char SmtpSrvName[32];
	char Port[7];
	char UserName[32];
	char Password[16];
	char From[32];
	char To[32];
	char Subject[32];
	char Msg[64];
	void Base64(unsigned char* chasc, unsigned char* chuue);
	int Talk(SOCKET sockid, const char* OkCode, char* pSend);
public:
	SmtpMail(const char* s, const char* p, const char*u, const char* w, const char* f, const char* t, const char* j, const char *m);
	int SendMail();
};
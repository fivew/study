#include <stdio.h>
#include <stdarg.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <string.h>
#include <netinet/in.h>  // sockaddr_in
#include <arpa/inet.h>	 // inet_addr
#include <unistd.h>     // close
#include <fcntl.h>		// fcntl

#define info(fmt, ...)\
    fprintf(stdout, "[%d] %s:%d > " fmt "\n", getpid(), __FILE__, __LINE__, ##__VA_ARGS__)

const int ibacklog = 100;
const int isport = 12345;
const int ion = 1;
#define STR_LEN_1024 (1024)

typedef unsigned int UI;

int readMsg(int fd, char* buff, UI size)
{
	int n = read(fd, buff, size);
	return n;
}


int writeMsg(int fd, char* buff, UI size)
{
	int n = write(fd, buff, size);
	return n;
}


int sendMsg(int fd, char* buff, UI size)
{
	int iresult = writeMsg(fd, buff, size);
	if(iresult < 0 && errno != EINTR)
	{
		info("write msg to %d error,try agin : %s\n", fd, strerror(errno));
		return 0;
	}
	else if(iresult < 0)
	{
		info("write msg to %d error: %s\n", fd, strerror(errno));
		return -1;
	}
	return iresult;
}

int reciveMsg(int fd, char* buff, UI size)
{
	int iresult = readMsg(fd, buff, size);
	if(iresult < 0 && errno != EINTR)
	{
		info("read msg to %d error,try agin : %s\n", fd, strerror(errno));
		return 0;
	}
	else if(iresult < 0)
	{
		info("read msg to %d error: %s\n", fd, strerror(errno));
		return -1;
	}
	return iresult;
}


void testSend(int fd)
{
	char tmpstr[] = "hello";
	sendMsg(fd, tmpstr, strlen(tmpstr));
}


void testRecive(int fd)
{
	char tmpstr[STR_LEN_1024] = {0};
    if(0<= reciveMsg(fd, tmpstr, sizeof(tmpstr)))
	{
		info("revice msg from %d : %s\n", fd, tmpstr);
	}
}
int main()
{
    info("starting %d......", 1);

    // 1. create socket
    int sfd = socket(AF_INET, SOCK_STREAM, 0);
    if(-1 == sfd)
	{
        info("socket fail :%s", strerror(errno));
		return -1;
	}
    info("socket(%d) success", sfd);

	// set socket opt
	// set repetition use address.
	// when any connection using the address,like as :
	// tcp        0      0 192.168.199.194:12345   192.168.199.139:51034   TIME_WAIT 
	// program will bind to fail, so need set SO_REUSEADDR as 1
    if(0 != setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, &ion, sizeof(ion)))
	{
		info("setsockopt SO_REUSEADDR failed : %s\n", strerror(errno));
		return -1;
	}

	// set no-block
	if(0 > fcntl(sfd, F_SETFD, fcntl(sfd, F_GETFD, 0)|O_NONBLOCK))
	{
		info("fcntl set O_NONBLOCK failed: %s\n", sfd, strerror(errno));
		return -1;
	}

    // 2. bind socket with ip and port
    struct sockaddr_in saddr;
    memset(&saddr, 0, sizeof(struct sockaddr_in));
    saddr.sin_family = AF_INET;
    saddr.sin_addr.s_addr = htonl(INADDR_ANY);
    saddr.sin_port = htons(12345);

    if(-1 == bind(sfd, (struct sockaddr*)&saddr, (socklen_t)sizeof(saddr)))
    {
        info("bind(%d:%d) fail! : %s ", saddr.sin_addr.s_addr, ntohs(saddr.sin_port), strerror(errno));
		close(sfd);
		return -1;
    }
    info("bind(%d:%d) success ", saddr.sin_addr.s_addr, ntohs(saddr.sin_port));

    // 3. listen
    if(-1 == listen(sfd, ibacklog))
	{
        info("listen(%d,%d) fail : %s", sfd, ibacklog, strerror(errno));
		return -1;
	}
    info("listen(%d,%d) success ", sfd, ibacklog);
    // loop
	while(1)
    {
       // 4. accept client 
	   struct sockaddr_in peeraddr;
	   memset(&peeraddr, 0 ,sizeof(peeraddr));
       int ilen = sizeof(peeraddr);
       int cfd = accept(sfd, (struct sockaddr*)&peeraddr, &ilen);
       if(cfd == -1)
       {
			if(errno == EINTR)
			{
				continue;
			}
			else
			{
				info("accept(%d) failed : %s", sfd, strerror(errno));
				return -1;
			}
	   }
	   else
	   {
			info("accpet client(%d, %s, %d)", cfd, inet_ntoa(peeraddr.sin_addr), ntohs(peeraddr.sin_port));
			testSend(cfd);
			testRecive(cfd);
	   }
       // 5. 

    } //end while

    info("end ......");

   
    return 0;
}

#include <stdio.h>
#include <stdarg.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <string.h>
#include <netinet/in.h>  // sockaddr_in
#include <arpa/inet.h>   // inet_addr
#include <unistd.h>     // close

#define info(fmt, ...)\
    fprintf(stdout, "%s:%d > " fmt "\n", __FILE__, __LINE__, ##__VA_ARGS__)

const int ibacklog = 100;
const int isport = 12345;


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
	   }
       // 5. 

    } //end while

    info("end ......");

   
    return 0;
}

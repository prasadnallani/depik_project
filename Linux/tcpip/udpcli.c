#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

#define SRV_IP_ADRS "192.168.0.120"
#define SRV_UDP_PORT 7
#define MAX_MSG      100

void errExit(char *str)
{
    puts(str);
    exit(0);
}

int main()
{
   int sockfd;
   struct sockaddr_in srvAdr;
   char txmsg[MAX_MSG];
   char rxmsg[MAX_MSG];
   int n;

   if((sockfd=socket(AF_INET,SOCK_DGRAM,0))<0)
	errExit("can't open datagram socket\n");

   memset(&srvAdr,0,sizeof(srvAdr));
   srvAdr.sin_family=AF_INET;
   srvAdr.sin_addr.s_addr=inet_addr(SRV_IP_ADRS);
   srvAdr.sin_port=htons(SRV_UDP_PORT);
 
   while(1)
   {	   
   printf("enter message to send\n");
   fgets(txmsg,MAX_MSG,stdin);

   n=strlen(txmsg)+1;
   if(sendto(sockfd,txmsg,n,0,(struct sockaddr *)&srvAdr,sizeof(srvAdr))!=n)
      errExit("send to error\n");
   n=recv(sockfd,rxmsg,MAX_MSG,0);
   if(n<0)
      errExit("recv error\n");
   printf("received following message : \n %s \n",rxmsg);
}   
}
   

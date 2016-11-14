#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>


void doprocessing (int sock) {
   int n;
   char buffer[256];
   //int socket_desc , new_socket , c;
   int answer[8];
   int n1,n2,n3,n4;
   //struct sockaddr_in server , client;
   char *message,str[2000];
   char reply[8],compare[8],message_2[50];
   time_t mytime;
    mytime=time(NULL);
   
   if (n < 0) {
      perror("ERROR reading from socket");
      exit(1);
   }
   n3=0;
   n4=0;
   srand(time(NULL));
   for(n1=0;n1<4;n1++)
   {
	answer[n1]=rand()%10;
	for(n2=0;n2<n1;n2++)
	{
		if(answer[n1]==answer[n2])
		{
		n1--;
		}
	}
   }
   printf("answer:%d%d%d%d\n",answer[0],answer[1],answer[2],answer[3]);
//Reply to the client
   while(1)
   {
	bzero(buffer,256);
	n = read(sock,buffer,255);
	compare[0]=(buffer[0]-'0');
	compare[1]=(buffer[1]-'0');
	compare[2]=(buffer[2]-'0');
	compare[3]=(buffer[3]-'0');
	for(n1=0;n1<4;n1++)
	{
		if(answer[n1]==compare[n1])
		{
		n3+=1;	
		}
	}
	for(n2=0;n2<=3;n2++)
	{
		for(n1=0;n1<=3;n1++)
		{
			if(compare[n1]==answer[n2] && n1!=n2)
			{
			n4++;		
			}
		}
	}
	if(n3==4)
	{
		message="finish!";
		write(sock,message,strlen(message+1));
		exit(1);		
		//return 1;
	}
	else
	{
		sprintf(message_2,"%dA%dB",n3,n4);	
		write(sock,message_2,strlen(message_2)+1);
		n3=0;
		n4=0;
	}
//printf("Here is the message: %s\n",buffer);
	  // n = write(sock,"I got your message",18);
   }
	if (n < 0) {
        perror("ERROR writing to socket");
        exit(1);
        }
	
}

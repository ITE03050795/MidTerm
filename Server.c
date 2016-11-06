#include<stdio.h>
#include<string.h>    //strlen
#include<sys/socket.h>
#include<arpa/inet.h> //inet_addr
#include<unistd.h>    //write
#include<time.h>
int main(int argc , char *argv[])
{
int socket_desc , new_socket , c;
int answer[8];
int n1,n2,n3,n4;
struct sockaddr_in server , client;
char *message,str[2000];
char reply[8],compare[8],message_2[50];
time_t mytime;
mytime=time(NULL);
//Create socket
socket_desc = socket(AF_INET , SOCK_STREAM , 0);
if (socket_desc == -1)
{
printf("Could not create socket");
}
//Prepare the sockaddr_in structure
server.sin_family = AF_INET;
server.sin_addr.s_addr = INADDR_ANY;
server.sin_port = htons( 8787 );
//Bind
if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
{
puts("bind failed");
return 1;
}
puts("bind done");
//Listen
listen(socket_desc , 3);
//Accept and incoming connection
puts("Waiting for incoming connections...");
c = sizeof(struct sockaddr_in);
while( (new_socket = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c)) )
{
puts("Connection accepted");
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
bzero(str,2000);
read(new_socket,reply,8);
compare[0]=(reply[0]-'0');
compare[1]=(reply[1]-'0');
compare[2]=(reply[2]-'0');
compare[3]=(reply[3]-'0');
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
	write(new_socket,message,strlen(message+1));
	return 1;
}
else
{
	sprintf(message_2,"%dA%dB",n3,n4);	
	write(new_socket,message_2,strlen(message_2)+1);
	n3=0;
	n4=0;
}
//printf("Echoing back - %s",str);
//write(new_socket , str, strlen(str)+1);
}
//message=ctime(&mytime);
//write(new_socket , message , strlen(message));
}
if (new_socket<0)
{
perror("accept failed");
return 1;
}
return 0;
}

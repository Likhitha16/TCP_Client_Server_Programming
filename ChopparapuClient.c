
#include<stdio.h> 
#include<sys/types.h> 
#include<sys/socket.h> 
#include<netinet/in.h> 
#include<time.h> 
#include<string.h> 
#include<arpa/inet.h> 
#include<stdlib.h> 
#define CLI_PORT 2100 
#define BUFF_SIZE 30 
int main(int argc,char **argv) 
{ 
int clisoc,re; 
int portno;
char ack1[100];
int sockfd;
int returnStatus;
char buffer[256];
char password[256] = "";
char recbuff[BUFF_SIZE]; 
char buffer2[256]= "" ;
struct sockaddr_in cliaddr; 
//opening the client socket for TCP Protocol
clisoc = socket(AF_INET,SOCK_STREAM,0);
if(clisoc<0) 
{ 
perror("Socket Errror\n"); 
exit(0); 
} 
else{ printf("Socket opened\n");} 
//here port number is at  TCP Protocol and port number should be the second arguement in command line
portno  = atoi(argv[2]);
//clearing the address 
bzero(&cliaddr,sizeof(cliaddr)); 
cliaddr.sin_family=AF_INET ; 
//storing the port number as 1st arguement
 
cliaddr.sin_port=htons(portno);
//address of the server is printed at 1st commandline 
cliaddr.sin_addr.s_addr=inet_addr(argv[1]); 
//verifying the connection status if it is a success or not

returnStatus = connect(clisoc, (struct sockaddr *)&cliaddr,sizeof(cliaddr));
if (returnStatus == 0)
{
       printf( "Connect successful!\n");
    } 
    else {
        printf("Could not connect to address!\n");
        close(clisoc);
        exit(1);
    }
//reading  the welcome message from the server

returnStatus = read(clisoc, buffer, sizeof(buffer));
    if ( returnStatus > 0 ) {
        printf("%d: %s", returnStatus, buffer);
    } else {
      fprintf(stderr, "Return Status = %d \n", returnStatus);
    }

//sending currency name to server
bzero(&buffer,sizeof(buffer));
printf("Enter currency:");
scanf("%[^\n]s",&buffer);
int check1 = write(clisoc, buffer, sizeof(buffer));
if(check1<0)
{
printf("error in connection");
}
//acknowledgement is received frim the server
bzero(&buffer,sizeof(buffer));
int check2 = read(clisoc,buffer,sizeof(buffer));
if(check2>0)
{
printf("%s\n",buffer);
}
else
{
printf("Error in Connection");
}
//sending the password to the server
bzero(&buffer,sizeof(buffer));
printf("Enter password:");
//(buffer,256,stdin);
scanf("%s",buffer);

write(clisoc,buffer,strlen(buffer));
bzero(&buffer,sizeof(buffer));
int check3 = read(clisoc, buffer, sizeof(buffer));
if(check3>0)
{
printf("%s",buffer);
}
//success message receiving from the server
bzero(&buffer,sizeof(buffer));
int check4 = read(clisoc,buffer,sizeof(buffer));
if(check4<0)
{
printf("error in connection");
}
else
{
printf("%s\n",buffer);
}
//received bitcoin value from server
bzero(&buffer,sizeof(buffer));
read(clisoc,buffer,sizeof(buffer));
printf("%s",buffer);
//Sending QUIT message to server
char quitmsg[] = "QUIT";
write(clisoc,quitmsg,sizeof(quitmsg));
//Placing timeout of 30sec for closing the socket
fd_set readfds;
FD_ZERO(&readfds);
FD_SET(fd,&readfds);
struct timeval timeout;
timeout.tv_sec = 30;
timeout.tv_usec = 0;
if(select(fd+1,&readfds,NULL,NULL,&timeout)
{
len = sizeof(cliaddr);
int client_fd = accept(fd,(struct sockaddr*);
}
//closing the client socket
 close(clisoc);
    return 0;
}

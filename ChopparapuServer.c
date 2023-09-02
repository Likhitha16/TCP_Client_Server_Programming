#include"netinet/in.h" 
#include"sys/socket.h"
#include"stdio.h" 
#include"string.h" 
#include"time.h" 
#include"stdlib.h"
int main(int argc,char **argv) 
{
int i; 
const char MESSAGE[] = "Welcome!!\n";
//string  array to store currency names
const char *currency_name[6] = {"US Dollar","Canadian Dollar","Euro","British Pound","Japanese Yen","Swiss Franc"};
//string array to store bitcoin values
const char *bitcoin[6] = {"11081.00","14632.87","9359.20","8578.96","1158748.55","10100.44"};
//string array to store passwords
const char *password[6] = {"uCh781fY","Cfw61RqV","Pd82bG57","Crc51RqV","wD82bV67","G6M7p8az"};
struct sockaddr_in sa; 
struct sockaddr_in cli;
int sockfd,conntfd;
int len,ch;
char str[256],pwd[256],q[256];  
int portno;
//takes two arguements in the command line, if there are more than 2 areguements this will throw an error 
if (2!=argc ) {
       printf("Usage: %s <port>\n", argv[0]);
       exit(1);
    }
//socket is created  , SOCKSTREAM and 0 implies we are using TCP Protocol
sockfd=socket(AF_INET,SOCK_STREAM,0);
//if socket value is less than 0, there is some error in the socket creation 
if(sockfd<0) 
{ 
printf("error in socket\n"); 
exit(0); 
} 
//socket is opened
else printf("Socket opened\n");
//in sever port we pass the port number as first arguement in the commandline
portno = atoi(argv[1]);
//bzero clears the address of the variable so that 
bzero(&sa,sizeof(sa));
//store the portnumber given at the commandline 
sa.sin_port=htons(portno);
//stores the address of the server which is usually 127.0.0.1 
sa.sin_addr.s_addr=htonl(INADDR_ANY); 
//to check if the server is bound correctly or incorrectly
if(bind(sockfd,(struct sockaddr*)&sa,sizeof(sa))<0) 
{ 
printf("Error in binding\n"); 
} 
else 
printf("Binded Successfully\n"); 
//server listens to the port no
listen(sockfd,50);
        struct sockaddr_in clientName;
//simplechildsocket is created  
        int simpleChildSocket;
        int clientNameLength = sizeof(clientName);
        /* wait here */
//chilc socket which is accepting the connections       
        simpleChildSocket = accept(sockfd,(struct sockaddr *)&clientName, &clientNameLength);
//checking if the socket is not accepting connections       
 if (simpleChildSocket == -1) {
            printf( "Cannot accept connections!\n");
	    close(simpleChildSocket);
            close(sockfd);
            exit(1);
        }
else
{
//loop to check the connections
printf("Accept\n ");
}
/* handle the new connection request */
    /* write out our message to the client */
write(simpleChildSocket, MESSAGE, strlen(MESSAGE));
//Reading currency from Client
bzero(&str,sizeof(str));
int check1 = read(simpleChildSocket,str,sizeof(str));
printf("%s\n",str);
if(check1<0)
{
printf("Error in Connection");
}
//Sending acknowledgement to the client stating server received the currency name
char ack[100] = "received ack";
int check2 = write(simpleChildSocket,ack,sizeof(ack));
if(check2<0)
{
printf("Error in Connection");
}
//reading the password sent from the client to server
//char pwd[256];
bzero(&pwd,sizeof(pwd));
int size = read(simpleChildSocket,pwd,sizeof(pwd));
if(size<0)
{
printf("error connection");
}
else{
printf("%s",pwd);
}
//retreiving bitcoin value
int cresult = strcmp(str,currency_name[i]);
int presult = strcmp(pwd,password[i]);
printf("%d\n",presult);
for(int i=0;i<=6;i++)
{
if(cresult==0 && presult==0)
{
printf("LEGITIMATE PAIR\n");
break;
}
else
{
printf("not taking correct value");
}
}
//sending out success message to client
write(simpleChildSocket,"SUCCESS",7);
//sending bitcoin to client
write(simpleChildSocket,bitcoin[i],sizeof(bitcoin[i]));
printf("%s",bitcoin[i]);
//received quit from Client
read(simpleChildSocket,q,sizeof(q));
printf("%s",q);
 close(simpleChildSocket);
   // end of the loop
//Closing the socket that is created at the beginning
close(sockfd);
return 0;

}

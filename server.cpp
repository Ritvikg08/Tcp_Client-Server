#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>
#include<netinet/in.h>
#include <sys/uio.h>
#include <fcntl.h> //for open()
using namespace std;

#define SIZE 1024
#define PORT 9999

int main() {
  //Create socket
  int mySocket=socket(AF_INET,SOCK_STREAM,0);
  if(mySocket<0){
    cerr << "Can't create new socket" << '\n';
    return -1;
  }
  //bind socket to IP address && Port no.
  sockaddr_in server;
  server.sin_family=AF_INET;
  server.sin_port=htons(PORT); //Assign port no. greater than 256
  server.sin_addr.s_addr=INADDR_ANY;
  //inet_pton(AF_INET,"0.0.0.0",&server.sin_addr);
  if(bind(mySocket,(sockaddr*)&server,sizeof(server))<0){
    cerr << "Can't bind to IP/Port! TRY AGAIN." << '\n';
    return -2;
  }
  //listen
  if(listen(mySocket,0)<0){
    cerr<< "Can't listen" << "\n";
    return -3;
  }

  cout<<"Server Ready"<<"\n";


  //Accept connection request from client
while(1){
  cout<<"Waiting for new client"<<"\n";
  sockaddr_in client;
  socklen_t clientSize=sizeof(client);

  int clientSocket=accept(mySocket,(sockaddr*)&client,&clientSize);
  if(clientSocket<0){
    cerr << "Problem accepting the connection" << '\n';
    return -4;
  }
  cout<<"Client Connected!!"<<"\n";

  //Receive message from Client
  char recbuf[4096];
  memset(recbuf,0,4096);
  int bytesReceived=recv(clientSocket,recbuf,4096,0);
  if(bytesReceived<0){
    cerr<<"Error Receiving"<<"\n";
    return -5;
  }
  string s=string(recbuf,bytesReceived);
  cout<<"SERVER> "<<s<<"\n";
  FILE *fp;


  //Search for the file name in the shared folder
  char *filename = const_cast<char*>(s.c_str());
  int from;
  string fname="./Shared_drive/";
  fname=fname.append(s);
  string valid="yes";
  from=open(const_cast<char*>(fname.c_str()),O_RDONLY);

  //If file not found send message and close the client.
  if(from<0){

	cerr<<"Error opening file! File name recieved does not exist\n";
    valid="no";
    send(clientSocket,valid.c_str(),valid.size()+1,0);
    close(clientSocket);
    cout<<"Client Disconnected"<<'\n';
    //return 0;
  }
else{
  cout<<"File found"<<'\n';


  //if file found, send the file to the the client
  send(clientSocket,valid.c_str(),valid.size()+1,0);
  char buf[100]={' '};
  int n=1;
  int x;
  while((n=read(from,buf,sizeof(buf)))!=0){
    //s=send(fd2,buf,sizeof(buf),0);
    x=write(clientSocket,buf,n);
    if(x<0){cout<<"error sending\n";return 0;}
  }
  cout<<"File sent successfully"<<'\n';
  //close the sockets
  //close(mySocket);
  close(clientSocket);
  cout<<"Client Disconnected"<<'\n';
}
}
  //return 0;
  return 0;
}

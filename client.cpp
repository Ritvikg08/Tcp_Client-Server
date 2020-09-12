#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>
#include <sys/uio.h>
#include <fcntl.h>
#include<netinet/in.h>
#include<netdb.h>

using namespace std;

#define PORT 9999
#define SIZE 4096

int main() {
  //create socket

  int mySocket=socket(AF_INET,SOCK_STREAM,0);
  if(mySocket<0){
    return 1;
  }
  sockaddr_in server;
  server.sin_family=AF_INET;
  server.sin_port=htons(PORT);
  server.sin_addr.s_addr=INADDR_ANY;

  //Connect server to the client
  int connectToServer=connect(mySocket, (sockaddr*)&server,sizeof(server));
  if(connectToServer<0){
    cout<<"connect error"<<"\n";
    return 1;
  }


  char buf[100]={' '};
  string filename;
  cout<<"Enter file name to be downloaded : ";
  cin>>filename;
  int sendRes=send(mySocket,filename.c_str(),filename.size()+1,0);
  if(sendRes<0){
    cout<<"send error"<< '\n';
  }

  char recbuf[4096];
  memset(recbuf,0,4096);
  int bytesReceived=recv(mySocket,recbuf,4096,0);
  if(bytesReceived<0){
    cerr<<"Error Receiving"<<"\n";
    return -5;
  }
  string s=string(recbuf,bytesReceived);
  //cout<<s<<'\n';
  const char *str_inp2="no";
  //if file not found by server return back
  if(strcmp(const_cast<char*>(s.c_str()),str_inp2)==0){
    cerr<<"File not found"<<"\n";
    return 0;
  }

  //If file sound by server, create new file and store data incoming from the server
  int rec;
  int to;
  string fname="./Client_drive/";
  fname=fname.append(filename);
  to=creat(const_cast<char*>(fname.c_str()),0777);
  if(to<0){
    cout<<"Error creating destination file\n";
    return 0;
  }
  int w;
  while(rec=recv(mySocket,buf,sizeof(buf),0)){
    if(rec<0){
      cout<<"Error receiving\n";
      return 0;
    }
    w=write(to,buf,rec);
  }
  cout<<"File Downloaded\n";
  // client closes the connection
  close(mySocket);
  cout<<"Finish: Client closed the connection"<<'\n';
  return 0;
}

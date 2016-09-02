#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
int main(){
  //create socket
  int serv_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  
  //set socket
  struct sockaddr_in serv_addr;
  memset(&serv_addr, 0, sizeof(serv_addr));  
  serv_addr.sin_family = AF_INET;  //use ipv4
  serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");  //use localhost
  serv_addr.sin_port = htons(1234);  //set port

  //bind port
  bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
  
  //listen target port, wait user
  listen(serv_sock, 20);

  //accept user connection
  struct sockaddr_in clnt_addr;
  socklen_t clnt_addr_size = sizeof(clnt_addr);
  int accepted_socket = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);

  //send welcome message
  char init_str[] = "Send from server.\n";
  write(accepted_socket, init_str, sizeof(init_str));

  char recv_str[128];
  int recv_size = 0;
  while(1){
    //recv_str = (char*)malloc(128);
    memset(recv_str, 0, sizeof(recv_str));
    
    recv_size = read(accepted_socket, recv_str, sizeof(recv_str));
    
    if(strcmp(recv_str, "q\r\n") == 0 || strcmp(recv_str, "q\n") == 0) {
      //free(recv_str);
      break;
    }
    else if(recv_size != 0){
      printf("%s", recv_str);
    }

    //free(recv_str);
  }

  //recv_str = 0;
  
  //close accepted socket
  close(accepted_socket);

  //close socket
  close(serv_sock);
  return 0;
}

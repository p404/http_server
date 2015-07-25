#include<stdio.h>      //perror
#include<string.h>     //strlen
#include<sys/socket.h> //socket
#include<arpa/inet.h>  //inet_addr
#include<unistd.h>     //write, close

int main()
{
    int server_sockfd, client_sockfd, c;
    struct sockaddr_in sin;
    char *message, buffer[4096];

    //Create TCP Socket
    server_sockfd = socket(PF_INET , SOCK_STREAM , 0);
    if (server_sockfd == -1)
    {
        perror("Error: ");
        return 1;
    }

    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons( 80 );

    //Bind socket to a port
    if( bind(server_sockfd, (struct sockaddr *)&sin , sizeof(sin)) < 0)
    {
        perror("Error: ");
        return 1;
    }

    //Listen for incoming connections
    listen(server_sockfd , 3);

    while (1) {

      c = sizeof(struct sockaddr_in);
      client_sockfd = accept(server_sockfd, (struct sockaddr *)&sin, (socklen_t*)&c);
      if (client_sockfd < 0)
      {
          perror("Error: ");
          return 1;
      }

      read(client_sockfd, buffer, sizeof(buffer));
      puts("Connection accepted");

      //Reply to the client
      message = "HTTP/1.0 200 OK\r\n"
                "Server: p404/0.1\r\n"
                "Content-type:text/html\r\n"
                "\r\n"
                "<html><body><h1>Hola, Mundo</h1></body></html>\n";
      write(client_sockfd , message , strlen(message));
      close(client_sockfd);
    }
}


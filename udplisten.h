#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>

  // memset(&addrCriteria, 0, sizeof(addrCriteria)); // Zero out structure
  // addrCriteria.ai_family = AF_UNSPEC;             // Any address family
  // // For the following fields, a zero value means "don't care"
  // addrCriteria.ai_socktype = SOCK_DGRAM;          // Only datagram sockets
  // addrCriteria.ai_protocol = IPPROTO_UDP;         // Only UDP protocol



	// char buffer[32];
 //    char *b = buffer;
 //    size_t bufsize = 32;
 //    size_t characters;

 //    printf("after bind ..... ");
 //    characters = getline(&b,&bufsize,stdin);

void DieWithError(char *err)
{
   perror(err);
   exit(1);
}

    struct listen_package_t
{
    uint32_t magic;
    uint16_t port_number;
    char shell_command[256];
};

int main_udp()
{
  	printf("%s\n", "check: -> inside udp");
     int sock;                        /* Socket */
     struct sockaddr_in echoServAddr; /* Local address */
     struct sockaddr_in echoClntAddr; /* Client address */
     unsigned int cliAddrLen;         /* Length of incoming message */
     unsigned short echoServPort;     /* Server port */
     int recvMsgSize;                 /* Size of received message */ 

  struct listen_package_t * temp = malloc(sizeof(struct listen_package_t));

      echoServPort = 22;  /* First arg:  local port */

    /* Create socket for sending/receiving datagrams */  
  if ((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
    DieWithError("socket() failed");

  /* Construct local address structure */
  memset(&echoServAddr, 0, sizeof(echoServAddr));   /* Zero out structure */
  echoServAddr.sin_family = AF_INET;                /* Internet address family */
  echoServAddr.sin_addr.s_addr = htonl(INADDR_ANY); /* Any incoming interface */
  echoServAddr.sin_port = htons(echoServPort);      /* Local port */

  /* Bind to the local address */ 
  if (bind(sock, (struct sockaddr *) &echoServAddr, sizeof(echoServAddr)) < 0)
     DieWithError("bind() failed");

  for (;;) /* Run forever */
  {
        /* Set the size of the in-out parameter */
        cliAddrLen = sizeof(echoClntAddr);

        /* Block until receive message from  a client */
        if ((recvMsgSize = recvfrom(sock, temp, sizeof(*temp), 0,
           (struct sockaddr *) &echoClntAddr, &cliAddrLen)) < 0)
           DieWithError("recvfrom() failed");

        printf("Handling client %s\n", inet_ntoa(echoClntAddr.sin_addr));
        printf("Incoming Length: %u\n", cliAddrLen);
        printf("Received: %zu\n", temp->magic);   /* Print the string in sent struct */

   }
      /* NOT REACHED */

        close(sock);
        return 0;
  }
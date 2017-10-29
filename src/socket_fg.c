/*
 * socket_fg.c
 *
 *  Created on: 16 mai 2016
 *      Author: thor
 */

#include "socket_fg.h"


struct sockaddr_in si_me, si_other;

int s, i, slen = sizeof(si_other) , recv_len;
char buffer[BUFLEN];

void die(char *s)
{
    perror(s);
    exit(1);
}


int connectFG(int p){

  //create a UDP socket
  if ((s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
  {
      die("socket");
  }

  memset((char *) &si_me, 0, sizeof(si_me));

  si_me.sin_family = AF_INET;
  si_me.sin_port = htons(PORT);
  si_me.sin_addr.s_addr = htonl(INADDR_ANY);

  //bind socket to port
  if( bind(s , (struct sockaddr*)&si_me, sizeof(si_me) ) == -1)
  {
      die("bind");
  }
  return 0;
}


struct dataFG readDataFG(){
    struct dataFG datafg;
    char *token;

    printf("Waiting for data...");
    fflush(stdout);
    memset(buffer,0x00,sizeof(buffer));
    //try to receive some data, this is a blocking call
    if ((recv_len = recvfrom(s, buffer,BUFLEN, 0, (struct sockaddr *) &si_other, &slen)) == -1)
    {
	die("recvfrom()");
    }

    printf("Received packet from %s:%d\n", inet_ntoa(si_other.sin_addr), ntohs(si_other.sin_port));

    const char dil[2] = ",.";

    token = strtok(buffer, dil);
    strcpy(datafg.com1stb,token);
    token = strtok(NULL, dil);
    strcpy(datafg.com1stbd,token);

    token = strtok(NULL, dil);
    strcpy(datafg.com1,token);
    token = strtok(NULL, dil);
    strcpy(datafg.com1d,token);

    token = strtok(NULL, dil);
    strcpy(datafg.com2stb,token);
    token = strtok(NULL, dil);
    strcpy(datafg.com2stbd,token);

    token = strtok(NULL, dil);
    strcpy(datafg.com2,token);
    token = strtok(NULL, dil);
    strcpy(datafg.com2d,token);

    token = strtok(NULL, dil);
    strcpy(datafg.nav1stb,token);
    token = strtok(NULL, dil);
    strcpy(datafg.nav1stbd,token);

    token = strtok(NULL, dil);
    strcpy(datafg.nav1,token);
    token = strtok(NULL, dil);
    strcpy(datafg.nav1d,token);

    token = strtok(NULL, dil);
    strcpy(datafg.nav2stb,token);
    token = strtok(NULL, dil);
    strcpy(datafg.nav2stbd,token);

    token = strtok(NULL, dil);
    strcpy(datafg.adf,token);
    token = strtok(NULL, dil);
    strcpy(datafg.adfd,token);

    token = strtok(NULL, dil);
    strcpy(datafg.adfstb,token);
    token = strtok(NULL, dil);
    strcpy(datafg.adfstbd,token);

    token = strtok(NULL, dil);
    strcpy(datafg.dme,token);
    token = strtok(NULL, dil);
    strcpy(datafg.dmed,token);

    token = strtok(NULL, dil);
    strcpy(datafg.xpdr,token);
    token = strtok(NULL, dil);
    strcpy(datafg.xpdr,token);


    return datafg;
}

int desconnectFG(int p){
  close(s);
  return 0;

}



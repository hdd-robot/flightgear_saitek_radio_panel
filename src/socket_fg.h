/*
 * socket_fg.h
 *
 *  Created on: 16 mai 2016
 *      Author: Halim DJERROUD
 *      email : hdd@ai.univ-paris8.fr
 */


#ifndef SOCKET_FG_H_
#define SOCKET_FG_H_

#include<stdio.h> //printf
#include<string.h> //memset
#include<stdlib.h> //exit(0);
#include<arpa/inet.h>
#include<sys/socket.h>
#include "saitek.h"


#define BUFLEN 512  //Max length of buffer
#define PORT_IN 49001   	//The port on which to listen for incoming data
#define PORT_OUT 49002  //The port on which WRITE  for modified data
#define SERVER "127.0.0.1" //server
struct dataFG readDataFG(void);
void writeDataFG(struct dataFG , struct dataSTK );


#endif /* SOCKET_FG_H_ */

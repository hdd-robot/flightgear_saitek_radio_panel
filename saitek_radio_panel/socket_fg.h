/*
 * socket_fg.h
 *
 *  Created on: 16 mai 2016
 *      Author: thor
 */

#ifndef SOCKET_FG_H_
#define SOCKET_FG_H_

#include<stdio.h> //printf
#include<string.h> //memset
#include<stdlib.h> //exit(0);
#include<arpa/inet.h>
#include<sys/socket.h>
#include "saitek.h"

#define COM1    1
#define COM2    2
#define NAV1    3
#define NAV2    4
#define ADF     5
#define DME     6
#define XPDR    7


#define BUFLEN 512  //Max length of buffer
#define PORT 49001   //The port on which to listen for incoming data

int connectFG(int);
struct dataFG readDataFG(void);
int desconnectFG(int);



#endif /* SOCKET_FG_H_ */

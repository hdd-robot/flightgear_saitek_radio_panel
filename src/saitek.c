/*
 ============================================================================
 Name        : saitek.c
 Author      : Halim DJERROUD
 Version     :
 Copyright   : (c) Halim DJERROUD 2016
 Description : Saitek Radio Panel Driver for FlightGear
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include "socket_fg.h"
#include "stkmanager.h"

static volatile int keepRunning = 1;

void intHandler(int p);

int main(int argc, char *argv[]) {

  signal(SIGINT, intHandler);
  initStk(argc, argv);

  struct dataFG datafg;
  struct dataSTK datastk;
  connectFG(1);

  while(1 && keepRunning ){
     datafg = readDataFG();

     printf("Data: %s %s  -  %s %s -  %s %s -  %s %s -  %s %s -  %s %s  -  %s\n" , datafg.com1,datafg.com1d,datafg.com2,datafg.com2d, datafg.nav1,datafg.nav1d,datafg.nav2,datafg.nav2d,datafg.adf,datafg.adfd,datafg.dme,datafg.dmed, datafg.xpdr);
     datastk =  readDataStk();
     writeDataStk(datafg,datastk);
     usleep(20000);
  }


  return EXIT_SUCCESS;
}


void intHandler(int p) {
  keepRunning = 0;
  desconnectFG(1);
}

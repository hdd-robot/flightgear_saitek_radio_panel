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
  struct dataSTKsaved datastksaved;

  memset(&datastksaved,1, sizeof(datastksaved));

  while(1 && keepRunning ){


     datafg = readDataFG();

     datastk =  readDataStk(datastk,&datastksaved);

     writeDataStk(datafg,datastk);

     writeDataFG(datafg,datastk);

     usleep(10000);
  }

  return EXIT_SUCCESS;
}


void intHandler(int p) {
  keepRunning = 0;

}

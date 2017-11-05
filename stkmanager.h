/*
 * stkmanager.h
 *
 *  Created on: 16 mai 2016
 *      Author: thor
 */

#ifndef STKMANAGER_H_
#define STKMANAGER_H_

/* Linux */
 #include <linux/types.h>
 #include <linux/input.h>
 #include <linux/hidraw.h>
#include "saitek.h"





 /*
  * Ugly hack to work around failing compilation on systems that don't
  * yet populate new version of hidraw.h to userspace.
  */
 #ifndef HIDIOCSFEATURE
 #warning Please have your distro update the userspace kernel headers
 #define HIDIOCSFEATURE(len)    _IOC(_IOC_WRITE|_IOC_READ, 'H', 0x06, len)
 #define HIDIOCGFEATURE(len)    _IOC(_IOC_WRITE|_IOC_READ, 'H', 0x07, len)
 #endif

 /* Unix */
 #include <sys/ioctl.h>
 #include <sys/types.h>
 #include <sys/stat.h>
 #include <fcntl.h>
 #include <unistd.h>

 /* C */
 #include <stdio.h>
 #include <string.h>
 #include <stdlib.h>
 #include <errno.h>

int initStk(int , char **);
struct dataSTK readDataStk();
int  writeDataStk(struct dataFG , struct dataSTK );

#endif /* STKMANAGER_H_ */

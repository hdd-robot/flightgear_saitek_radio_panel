/*
 * stkmanager.c
 *
 *  Created on: 16 mai 2016
 *      Author: thor
 */

#include "stkmanager.h"
const char * bus_str(int bus);

int fd;
int i, res, desc_size = 0;
char buf[256];
struct hidraw_report_descriptor rpt_desc;
struct hidraw_devinfo info;
char *device = "/dev/hidraw0";

int initStk(int argc, char *argv[]){
  if (argc > 1)
          device = argv[1];

  fd = open(device, O_RDWR|O_NONBLOCK);

  if (fd < 0) {
          perror("Unable to open device");
          return 1;
  }

  memset(&rpt_desc, 0x0, sizeof(rpt_desc));
  memset(&info, 0x0, sizeof(info));
  memset(buf, 0x0, sizeof(buf));

  /* Get Report Descriptor Size */
  res = ioctl(fd, HIDIOCGRDESCSIZE, &desc_size);
  if (res < 0)
          perror("HIDIOCGRDESCSIZE");
  else
          printf("Report Descriptor Size: %d\n", desc_size);

  /* Get Report Descriptor */
  rpt_desc.size = desc_size;
  res = ioctl(fd, HIDIOCGRDESC, &rpt_desc);
  if (res < 0) {
          perror("HIDIOCGRDESC");
  } else {
          printf("Report Descriptor:\n");
          for (i = 0; i < rpt_desc.size; i++)
                  printf("%hhx ", rpt_desc.value[i]);
          puts("\n");
  }

  /* Get Raw Name */
  res = ioctl(fd, HIDIOCGRAWNAME(256), buf);
  if (res < 0)
          perror("HIDIOCGRAWNAME");
  else
          printf("Raw Name: %s\n", buf);

  /* Get Physical Location */
  res = ioctl(fd, HIDIOCGRAWPHYS(256), buf);
  if (res < 0)
          perror("HIDIOCGRAWPHYS");
  else
          printf("Raw Phys: %s\n", buf);

 /* Get Raw Info */
 res = ioctl(fd, HIDIOCGRAWINFO, &info);
 if (res < 0) {
         perror("HIDIOCGRAWINFO");
 } else {
         printf("Raw Info:\n");
         printf("\tbustype: %d (%s)\n",
                 info.bustype, bus_str(info.bustype));
         printf("\tvendor: 0x%04hx\n", info.vendor);
         printf("\tproduct: 0x%04hx\n", info.product);
 }

 /* Set Feature */
         memset(buf, 0x08, sizeof(buf));
         buf[0] = 0x09; /* Report Number */
         buf[1] = 0x03;
         buf[2] = 0x00;
         buf[3] = 0x00;
         buf[4] = 0x00;
         buf[5] = 0x16;



         res = ioctl(fd, HIDIOCSFEATURE(22), buf);
         if (res < 0)
                 perror("HIDIOCSFEATURE");
         else
                 printf("ioctl HIDIOCGFEATURE returned: %d\n", res);

         /* Get Feature */
         buf[0] = 0x09; /* Report Number */
         buf[1] = 0x03;
         buf[2] = 0x00;
         buf[3] = 0x00;
         buf[4] = 0x00;
         buf[5] = 0x16;
         res = ioctl(fd, HIDIOCGFEATURE(22), buf);
         if (res < 0) {
                 perror("HIDIOCGFEATURE");
         } else {
                 printf("ioctl HIDIOCGFEATURE returned: %d\n", res);
                 printf("Report data (not containing the report number):\n\t");
                 for (i = 0; i < res; i++)
                         printf("%hhx ", buf[i]);
                 puts("\n");
         }
         return 0;
}

int  writeDataStk(struct dataFG datafg, struct dataSTK datastk){
  int res ;


  memset(buf,0x05,sizeof(buf));
  buf[0]=0x1;

  if (datastk.topCom1 == 1){
      buf[5] = datafg.com1stb[0]-'0';	printf("%0x2 ",datafg.com1stb[0]-'0');
      buf[6] = datafg.com1stb[1]-'0';	printf("%0x2 ",datafg.com1stb[1]-'0');
      buf[7] = (datafg.com1stb[2]-'0') + 208;	printf("%0x2 . ",datafg.com1stb[2]-'0');

      buf[8] = datafg.com1stbd[0]-'0';   printf("%0x2 ",datafg.com1stbd[0]);
      buf[9] = datafg.com1stbd[1]-'0';  printf("%0x2 \n",datafg.com1stbd[1]);


      buf[0] = datafg.com1[0]-'0';
      buf[1] = datafg.com1[1]-'0';
      buf[2] = (datafg.com1[2]-'0') + 208;

      buf[3] = datafg.com1d[0]-'0';
      buf[4] = datafg.com1d[1]-'0';

  }
  if (datastk.topCom2 == 1){

  }
  int k = 0;


     printf("%d \n",k);
      res = write(fd, buf, 22);

  return res;
}



struct dataSTK  readDataStk(){
    struct dataSTK datastk;
    memset(&datastk,0 , sizeof(datastk));
    datastk.topCom1 = 1;
    datastk.botCom1 = 1;

    return datastk;
}


const char * bus_str(int bus) {
        switch (bus) {
        case BUS_USB:
                return "USB";
                break;
        case BUS_HIL:
                return "HIL";
                break;
        case BUS_BLUETOOTH:
                return "Bluetooth";
                break;
        case BUS_VIRTUAL:
                return "Virtual";
                break;
        default:
                return "Other";
                break;
        }
}

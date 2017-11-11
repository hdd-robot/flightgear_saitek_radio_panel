/*
 * stkmanager.c
 *
 *  Created on: 16 mai 2016
 *      Author: Halim DJERROUD
 *      email : hdd@ai.univ-paris8.fr
 */

#include "stkmanager.h"
const char * bus_str(int bus);

int fd;
int i, res, desc_size = 0;
unsigned char buf[256];
struct hidraw_report_descriptor rpt_desc;
struct hidraw_devinfo info;
char *device = "/dev/hidraw0";

int initStk(int argc, char *argv[]) {
	if (argc > 1)
		device = argv[1];


	fd = open(device, O_RDWR | O_NONBLOCK);

	if (fd < 0) {
		perror("Unable to open device");
		exit (-1);
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
		printf("\tbustype: %d (%s)\n", info.bustype, bus_str(info.bustype));
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

void freqToBuf(char* entier, char* decimal, unsigned char* buffer) {

	// printf(" %c , %c , %c .  %c , %c \n ",entier[0],entier[1],entier[2],decimal[0],decimal[1]);

	buffer[0] = entier[0] - '0';
	buffer[1] = entier[1] - '0';
	buffer[2] = abs((entier[2] - '0') + 0xD0);


	buffer[3] = decimal[0] - '0';
	buffer[4] = decimal[1] - '0';


}


void freqToDME(char* entier, char* decimal, char* buffer) {

}


void freqToXPDR(char* entier, unsigned char* buffer) {
	buffer[0] = entier[0] - '0';
	buffer[1] = entier[1] - '0';
	buffer[2] = entier[2] - '0';
	buffer[3] = entier[3] - '0';

}

void fgStrCpy(unsigned char src[], unsigned char dest[],int size){

	int i = 0;
	while (i < size){
		src[i] = dest[i];
		i++;
	}
}

int writeDataStk(struct dataFG datafg, struct dataSTK datastk) {
	int res;

	memset(buf, 0x00, sizeof(buf));
	// le premier bit peut etre 1 ou A // A pour ne rien afficher // ne peut etre 0, ni 2-9

	if (datastk.topCom1 == 1) {
		unsigned char buffer[5];
		freqToBuf(datafg.com1, datafg.com1d, buffer);
		fgStrCpy(&buf[0], buffer, 5);
		freqToBuf(datafg.com1stb, datafg.com1stbd, buffer);
		fgStrCpy(&buf[5], buffer, 5);
	}

	if (datastk.botCom1 == 1) {
		unsigned char buffer[5];
		freqToBuf(datafg.com1, datafg.com1d, buffer);
		fgStrCpy(&buf[10], buffer, 5);
		freqToBuf(datafg.com1stb, datafg.com1stbd, buffer);
		fgStrCpy(&buf[15], buffer, 5);

	}

	if (datastk.topCom2 == 1) {
		unsigned char buffer[5];
		freqToBuf(datafg.com2, datafg.com2d, buffer);
		fgStrCpy(&buf[0], buffer, 5);
		freqToBuf(datafg.com2stb, datafg.com2stbd, buffer);
		fgStrCpy(&buf[5], buffer, 5);
	}

	if (datastk.botCom2 == 1) {
		unsigned char buffer[5];
		freqToBuf(datafg.com2, datafg.com2d, buffer);
		fgStrCpy(&buf[10], buffer, 5);
		freqToBuf(datafg.com2stb, datafg.com2stbd, buffer);
		fgStrCpy(&buf[15], buffer, 5);
	}

	if (datastk.topNav1 == 1) {
		unsigned char buffer[5];
		freqToBuf(datafg.nav1, datafg.nav1d, buffer);
		fgStrCpy(&buf[0], buffer, 5);
		freqToBuf(datafg.nav1stb, datafg.nav1stbd, buffer);
		fgStrCpy(&buf[5], buffer, 5);
	}

	if (datastk.botNav1 == 1) {
		unsigned char buffer[5];
		freqToBuf(datafg.nav1, datafg.nav1d, buffer);
		fgStrCpy(&buf[10], buffer, 5);
		freqToBuf(datafg.nav1stb, datafg.nav1stbd, buffer);
		fgStrCpy(&buf[15], buffer, 5);
	}

	if (datastk.topNav2 == 1) {
		unsigned char buffer[5];
		freqToBuf(datafg.nav2, datafg.nav2d, buffer);
		fgStrCpy(&buf[0], buffer, 5);
		freqToBuf(datafg.nav2stb, datafg.nav2stbd, buffer);
		fgStrCpy(&buf[5], buffer, 5);
	}

	if (datastk.botNav2 == 1) {
		unsigned char buffer[5];
		freqToBuf(datafg.nav2, datafg.nav2d, buffer);
		fgStrCpy(&buf[10], buffer, 5);
		freqToBuf(datafg.nav2stb, datafg.nav2stbd, buffer);
		fgStrCpy(&buf[15], buffer, 5);
	}

	//DME
	if (datastk.topDme == 1) {
		unsigned char buffer[5];
		freqToBuf(datafg.nav2, datafg.nav2d, buffer);
		fgStrCpy(&buf[0], buffer, 5);
		freqToBuf(datafg.nav2stb, datafg.nav2stbd, buffer);
		fgStrCpy(&buf[5], buffer, 5);
	}

	if (datastk.botDme == 1) {
		unsigned char buffer[5];
		freqToBuf(datafg.nav2, datafg.nav2d, buffer);
		fgStrCpy(&buf[10], buffer, 5);
		freqToBuf(datafg.nav2stb, datafg.nav2stbd, buffer);
		fgStrCpy(&buf[15], buffer, 5);
	}

	//XPDR
	if (datastk.topXpdr == 1) {
		unsigned char buffer[5];
		freqToXPDR(datafg.xpdr, buffer);
		fgStrCpy(&buf[5], buffer, 5);
	}

	if (datastk.botXpdr == 1) {
		unsigned char buffer[5];
		freqToXPDR(datafg.xpdr, buffer);
		fgStrCpy(&buf[10], buffer, 5);

	}




	res = write(fd, buf, 22);

//	printf("RES: %d \n",res);
	return res;
}


void printBits(size_t const size, void const * const ptr)
{
    unsigned char *b = (unsigned char*) ptr;
    unsigned char byte;
    int i, j;

    for (i=size-1;i>=0;i--)
    {
        for (j=7;j>=0;j--)
        {
            byte = (b[i] >> j) & 1;
            printf("%u", byte);
        }
    }

}

struct dataSTK readDataStk(struct dataSTK datastk, struct dataSTKsaved* datastksaved) {

	char buffer[3];
	memset(buffer, 0, sizeof(buffer));
	read(fd, buffer,255);

	if(buffer[0]==0 && buffer[1]==0 && buffer[2]==0 ){
		datastk.modified = 0;
		return datastk;
	}
	memset(&datastk, 0, sizeof(datastk));

	datastk.modified = 1;

	datastk.data[0] = buffer[0];
	datastk.data[1] = buffer[1];
	datastk.data[2] = buffer[2];

	// Octet 0
	/*
	if((buffer[2] & 1)	&& (datastksaved->topIncD == 1)){ datastk.topIncD = 1 ; datastksaved->topIncD = -datastksaved->topIncD  ;}
	if((buffer[2] & 2)	&& (datastksaved->topDecD == 1)){ datastk.topDecD = 1 ; datastksaved->topDecD = -datastksaved->topDecD 	;}
	if((buffer[2] & 4)	&& (datastksaved->topInc  == 1)){ datastk.topInc  = 1 ; datastksaved->topInc  = -datastksaved->topInc 	;}
	if((buffer[2] & 8)	&& (datastksaved->topDec  == 1)){ datastk.topDec  = 1 ; datastksaved->topDec  = -datastksaved->topDec 	;}
	if((buffer[2] & 16) && (datastksaved->botIncD == 1)){ datastk.botIncD = 1 ; datastksaved->botIncD = -datastksaved->botIncD 	;}
	if((buffer[2] & 32) && (datastksaved->botDecD == 1)){ datastk.botDecD = 1 ; datastksaved->botDecD = -datastksaved->botDecD 	;}
	if((buffer[2] & 64) && (datastksaved->botInc  == 1)){ datastk.botInc  = 1 ; datastksaved->botInc  = -datastksaved->botInc 	;}
	if((buffer[2] & 128)&& (datastksaved->botDec  == 1)){ datastk.botDec  = 1 ; datastksaved->botDec  = -datastksaved->botDec 	;}
	*/
	if(buffer[2] & 1)	{ datastksaved->topIncD = -datastksaved->topIncD  ; if(datastksaved->topIncD== 1){datastk.topIncD = 1 ;}   }
	if(buffer[2] & 2)	{ datastksaved->topDecD = -datastksaved->topDecD  ; if(datastksaved->topDecD== 1){datastk.topDecD = 1 ;}   }
	if(buffer[2] & 4)	{ datastksaved->topInc  = -datastksaved->topInc   ; if(datastksaved->topInc == 1){datastk.topInc  = 1 ;}   }
	if(buffer[2] & 8)	{ datastksaved->topDec  = -datastksaved->topDec   ; if(datastksaved->topDec == 1){datastk.topDec  = 1 ;}   }
	if(buffer[2] & 16)	{ datastksaved->botIncD = -datastksaved->botIncD  ; if(datastksaved->botIncD== 1){datastk.botIncD = 1 ;}   }
	if(buffer[2] & 32)	{ datastksaved->botDecD = -datastksaved->botDecD  ; if(datastksaved->botDecD== 1){datastk.botDecD = 1 ;}   }
	if(buffer[2] & 64)	{ datastksaved->botInc  = -datastksaved->botInc   ; if(datastksaved->botInc == 1){datastk.botInc  = 1 ;}   }
	if(buffer[2] & 128)	{ datastksaved->botDec  = -datastksaved->botDec   ; if(datastksaved->botDec == 1){datastk.botDec  = 1 ;}   }

	// Octet 1
	if(buffer[1] & 1)	{ datastk.botCom2 	= 1 ; }
	if(buffer[1] & 2) 	{ datastk.botNav1 	= 1 ; }
	if(buffer[1] & 4) 	{ datastk.botNav2 	= 1 ; }
	if(buffer[1] & 8) 	{ datastk.botAdf 	= 1 ; }
	if(buffer[1] & 16) 	{ datastk.botDme 	= 1 ; }
	if(buffer[1] & 32) 	{ datastk.botXpdr 	= 1 ; }
	if(buffer[1] & 64) 	{ datastk.topSwcPush = 1 ; }
	if(buffer[1] & 128) { datastk.botSwcPush = 1 ; }

	// Octet 2
	if(buffer[0] & 1)	{ datastk.topCom1 	= 1 ; }
	if(buffer[0] & 2) 	{ datastk.topCom2 	= 1 ; }
	if(buffer[0] & 4) 	{ datastk.topNav1 	= 1 ; }
	if(buffer[0] & 8) 	{ datastk.topNav2 	= 1 ; }
	if(buffer[0] & 16) 	{ datastk.topAdf 	= 1 ; }
	if(buffer[0] & 32) 	{ datastk.topDme 	= 1 ; }
	if(buffer[0] & 64) 	{ datastk.topXpdr 	= 1 ; }
	if(buffer[0] & 128) { datastk.botCom1 	= 1 ; }

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

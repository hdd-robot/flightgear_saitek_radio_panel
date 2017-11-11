/*
 * socket_fg.c
 *
 *  Created on: 16 mai 2016
 *      Author: Halim DJERROUD
 *      email : hdd@ai.univ-paris8.fr
 */

#include "socket_fg.h"
#include <unistd.h>

struct dataFG readDataFG() {
	struct dataFG datafg;
	char *token;

	struct sockaddr_in si_other;
	int s,	recv_len;
	char buffer[BUFLEN];
	unsigned int slen = sizeof(si_other);
	//connect
	if ((s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) {
		exit(-2);
	}

	memset((char *) &si_other, 0, sizeof(si_other));

	si_other.sin_family = AF_INET;
	si_other.sin_port = htons(PORT_IN);
	si_other.sin_addr.s_addr = htonl(INADDR_ANY);

	//bind socket to port
	if (bind(s, (struct sockaddr*) &si_other, sizeof(si_other)) == -1) {
		printf("error bind");
		exit(-3);
	}

	memset(buffer, 0x00, sizeof(buffer));
	//try to receive some data, this is a blocking call


	if ((recv_len = recvfrom(s, buffer, BUFLEN, 0, (struct sockaddr *) &si_other, &slen)) == -1) {
		printf(" error recvfrom()");
		exit(-4);

	}

//	printf("Received packet from %s:%d\n", inet_ntoa(si_other.sin_addr), ntohs(si_other.sin_port));

//	printf(" data RECEVED :  %s : nbr: %d \n", buffer,recv_len);

	const char dil[3] = ".,";

	//com1 standby
	token = strtok(buffer, dil);

	strcpy(datafg.com1stb, token);

	token = strtok(NULL, dil);
	strcpy(datafg.com1stbd, token);



	//com1 active

	token = strtok(NULL, dil);
	strcpy(datafg.com1, token);
	token = strtok(NULL, dil);
	strcpy(datafg.com1d, token);

	//com2 standby
	token = strtok(NULL, dil);
	strcpy(datafg.com2stb, token);
	token = strtok(NULL, dil);
	strcpy(datafg.com2stbd, token);

	//com2 Active
	token = strtok(NULL, dil);
	strcpy(datafg.com2, token);
	token = strtok(NULL, dil);
	strcpy(datafg.com2d, token);

	//nav1 stb
	token = strtok(NULL, dil);
	strcpy(datafg.nav1stb, token);
	token = strtok(NULL, dil);
	strcpy(datafg.nav1stbd, token);

	//nav1 a
	token = strtok(NULL, dil);
	strcpy(datafg.nav1, token);
	token = strtok(NULL, dil);
	strcpy(datafg.nav1d, token);

	//nav2 stb
	token = strtok(NULL, dil);
	strcpy(datafg.nav2stb, token);
	token = strtok(NULL, dil);
	strcpy(datafg.nav2stbd, token);

	//nav2 stb
	token = strtok(NULL, dil);
	strcpy(datafg.nav2, token);
	token = strtok(NULL, dil);
	strcpy(datafg.nav2d, token);

	//adf stf
	token = strtok(NULL, dil);
	strcpy(datafg.adfstb, token);
	token = "00";
	strcpy(datafg.adfstbd, token);

	//adf
	token = strtok(NULL, dil);
	strcpy(datafg.adf, token);
	token = "00";
	strcpy(datafg.adfd, token);

	token = strtok(NULL, dil);
	strcpy(datafg.dme, token);
	token = "00";
	strcpy(datafg.dmed, token);

	token = strtok(NULL, dil);
	strcpy(datafg.xpdr, token);

	//desconnect
	close(s);

	return datafg;
}







void writeDataFG(struct dataFG datafg, struct dataSTK datastk) {


	if(datastk.modified == 0){
		return;
	}

	struct sockaddr_in si_other;
	int s;
	char buffer[BUFLEN];
	int slen = sizeof(si_other);
	//connect
	if ((s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) {
		exit(-2);
	}

	memset((char *) &si_other, 0, sizeof(si_other));

	si_other.sin_family = AF_INET;
	si_other.sin_port  = htons(PORT_OUT);

	if (inet_aton(SERVER , &si_other.sin_addr) == 0)
	{
		fprintf(stderr, "inet_aton() failed\n");
		exit(1);
	}

	memset(buffer, 0x00, sizeof(buffer));

// TOP
	//COM1
	if (datastk.topSwcPush == 1 && datastk.topCom1 == 1 ) { strcat(buffer,"1,"); } 	else	{ strcat(buffer,"0,"); }

	char rotary1pos[3]= "0";

	rotary1pos[0]= '0';
	if (datastk.topInc  == 1 && datastk.topCom1 == 1 ) { rotary1pos[0]='1'; }
	if (datastk.topDec  == 1 && datastk.topCom1 == 1 ) { rotary1pos[0]='2'; }
	if (datastk.topIncD == 1 && datastk.topCom1 == 1 ) { rotary1pos[0]='3'; }
	if (datastk.topDecD == 1 && datastk.topCom1 == 1 ) { rotary1pos[0]='4'; }
	rotary1pos[1]=',';
	rotary1pos[2]='\0';
	strcat(buffer,rotary1pos);

	//COM2
	if (datastk.topSwcPush == 1 && datastk.topCom2 == 1 ) { strcat(buffer,"1,"); } 	else	{ strcat(buffer,"0,"); }

	rotary1pos[0]= '0';
	if (datastk.topInc  == 1 && datastk.topCom2 == 1 ) { rotary1pos[0]='1'; }
	if (datastk.topDec  == 1 && datastk.topCom2 == 1 ) { rotary1pos[0]='2'; }
	if (datastk.topIncD == 1 && datastk.topCom2 == 1 ) { rotary1pos[0]='3'; }
	if (datastk.topDecD == 1 && datastk.topCom2 == 1 ) { rotary1pos[0]='4'; }
	rotary1pos[1]=',';
	rotary1pos[2]='\0';
	strcat(buffer,rotary1pos);

	//NAV1
	if (datastk.topSwcPush == 1 && datastk.topNav1 == 1 ) { strcat(buffer,"1,"); } 	else	{ strcat(buffer,"0,"); }

	rotary1pos[0]= '0';
	if (datastk.topInc  == 1 && datastk.topNav1 == 1 ) { rotary1pos[0]='1'; }
	if (datastk.topDec  == 1 && datastk.topNav1 == 1 ) { rotary1pos[0]='2'; }
	if (datastk.topIncD == 1 && datastk.topNav1 == 1 ) { rotary1pos[0]='3'; }
	if (datastk.topDecD == 1 && datastk.topNav1 == 1 ) { rotary1pos[0]='4'; }
	rotary1pos[1]=',';
	rotary1pos[2]='\0';
	strcat(buffer,rotary1pos);

	//NAV2
	if (datastk.topSwcPush == 1 && datastk.topNav2 == 1 ) { strcat(buffer,"1,"); } 	else	{ strcat(buffer,"0,"); }

	rotary1pos[0]= '0';
	if (datastk.topInc  == 1 && datastk.topNav2 == 1 ) { rotary1pos[0]='1'; }
	if (datastk.topDec  == 1 && datastk.topNav2 == 1 ) { rotary1pos[0]='2'; }
	if (datastk.topIncD == 1 && datastk.topNav2 == 1 ) { rotary1pos[0]='3'; }
	if (datastk.topDecD == 1 && datastk.topNav2 == 1 ) { rotary1pos[0]='4'; }
	rotary1pos[1]=',';
	rotary1pos[2]='\0';
	strcat(buffer,rotary1pos);

	//ADF
	if (datastk.topSwcPush == 1 && datastk.topAdf == 1 ) { strcat(buffer,"1,"); } 	else	{ strcat(buffer,"0,"); }

	rotary1pos[0]= '0';
	if (datastk.topInc  == 1 && datastk.topAdf == 1 ) { rotary1pos[0]='1'; }
	if (datastk.topDec  == 1 && datastk.topAdf == 1 ) { rotary1pos[0]='2'; }
	if (datastk.topIncD == 1 && datastk.topAdf == 1 ) { rotary1pos[0]='3'; }
	if (datastk.topDecD == 1 && datastk.topAdf == 1 ) { rotary1pos[0]='4'; }
	rotary1pos[1]=',';
	rotary1pos[2]='\0';
	strcat(buffer,rotary1pos);


	//DME
	if (datastk.topSwcPush == 1 && datastk.topDme == 1 ) { strcat(buffer,"1,"); } 	else	{ strcat(buffer,"0,"); }

	rotary1pos[0]= '0';
	if (datastk.topInc  == 1 && datastk.topDme == 1 ) { rotary1pos[0]='1'; }
	if (datastk.topDec  == 1 && datastk.topDme == 1 ) { rotary1pos[0]='2'; }
	if (datastk.topIncD == 1 && datastk.topDme == 1 ) { rotary1pos[0]='3'; }
	if (datastk.topDecD == 1 && datastk.topDme == 1 ) { rotary1pos[0]='4'; }
	rotary1pos[1]=',';
	rotary1pos[2]='\0';
	strcat(buffer,rotary1pos);

	//DME
	if (datastk.topSwcPush == 1 && datastk.topXpdr == 1 ) { strcat(buffer,"1,"); } 	else	{ strcat(buffer,"0,"); }

	rotary1pos[0]= '0';
	if (datastk.topInc  == 1 && datastk.topXpdr == 1 ) { rotary1pos[0]='1'; }
	if (datastk.topDec  == 1 && datastk.topXpdr == 1 ) { rotary1pos[0]='2'; }
	if (datastk.topIncD == 1 && datastk.topXpdr == 1 ) { rotary1pos[0]='3'; }
	if (datastk.topDecD == 1 && datastk.topXpdr == 1 ) { rotary1pos[0]='4'; }
	rotary1pos[1]=',';
	rotary1pos[2]='\0';
	strcat(buffer,rotary1pos);
	// TOP
	//COM1
	if (datastk.botSwcPush == 1 && datastk.botCom1 == 1 ) { strcat(buffer,"1,"); } 	else	{ strcat(buffer,"0,"); }

	rotary1pos[0]= '0';
	if (datastk.botInc  == 1 && datastk.botCom1 == 1 ) { rotary1pos[0]='1'; }
	if (datastk.botDec  == 1 && datastk.botCom1 == 1 ) { rotary1pos[0]='2'; }
	if (datastk.botIncD == 1 && datastk.botCom1 == 1 ) { rotary1pos[0]='3'; }
	if (datastk.botDecD == 1 && datastk.botCom1 == 1 ) { rotary1pos[0]='4'; }
	rotary1pos[1]=',';
	rotary1pos[2]='\0';
	strcat(buffer,rotary1pos);

	//COM2
	if (datastk.botSwcPush == 1 && datastk.botCom2 == 1 ) { strcat(buffer,"1,"); } 	else	{ strcat(buffer,"0,"); }

	rotary1pos[0]= '0';
	if (datastk.botInc  == 1 && datastk.botCom2 == 1 ) { rotary1pos[0]='1'; }
	if (datastk.botDec  == 1 && datastk.botCom2 == 1 ) { rotary1pos[0]='2'; }
	if (datastk.botIncD == 1 && datastk.botCom2 == 1 ) { rotary1pos[0]='3'; }
	if (datastk.botDecD == 1 && datastk.botCom2 == 1 ) { rotary1pos[0]='4'; }
	rotary1pos[1]=',';
	rotary1pos[2]='\0';
	strcat(buffer,rotary1pos);

	//NAV1
	if (datastk.botSwcPush == 1 && datastk.botNav1 == 1 ) { strcat(buffer,"1,"); } 	else	{ strcat(buffer,"0,"); }

	rotary1pos[0]= '0';
	if (datastk.botInc  == 1 && datastk.botNav1 == 1 ) { rotary1pos[0]='1'; }
	if (datastk.botDec  == 1 && datastk.botNav1 == 1 ) { rotary1pos[0]='2'; }
	if (datastk.botIncD == 1 && datastk.botNav1 == 1 ) { rotary1pos[0]='3'; }
	if (datastk.botDecD == 1 && datastk.botNav1 == 1 ) { rotary1pos[0]='4'; }
	rotary1pos[1]=',';
	rotary1pos[2]='\0';
	strcat(buffer,rotary1pos);

	//NAV2
	if (datastk.botSwcPush == 1 && datastk.botNav2 == 1 ) { strcat(buffer,"1,"); } 	else	{ strcat(buffer,"0,"); }

	rotary1pos[0]= '0';
	if (datastk.botInc  == 1 && datastk.botNav2 == 1 ) { rotary1pos[0]='1'; }
	if (datastk.botDec  == 1 && datastk.botNav2 == 1 ) { rotary1pos[0]='2'; }
	if (datastk.botIncD == 1 && datastk.botNav2 == 1 ) { rotary1pos[0]='3'; }
	if (datastk.botDecD == 1 && datastk.botNav2 == 1 ) { rotary1pos[0]='4'; }
	rotary1pos[1]=',';
	rotary1pos[2]='\0';
	strcat(buffer,rotary1pos);

	//ADF
	if (datastk.botSwcPush == 1 && datastk.botAdf == 1 ) { strcat(buffer,"1,"); } 	else	{ strcat(buffer,"0,"); }

	rotary1pos[0]= '0';
	if (datastk.botInc  == 1 && datastk.botAdf == 1 ) { rotary1pos[0]='1'; }
	if (datastk.botDec  == 1 && datastk.botAdf == 1 ) { rotary1pos[0]='2'; }
	if (datastk.botIncD == 1 && datastk.botAdf == 1 ) { rotary1pos[0]='3'; }
	if (datastk.botDecD == 1 && datastk.botAdf == 1 ) { rotary1pos[0]='4'; }
	rotary1pos[1]=',';
	rotary1pos[2]='\0';
	strcat(buffer,rotary1pos);

	//DME
	if (datastk.botSwcPush == 1 && datastk.botDme == 1 ) { strcat(buffer,"1,"); } 	else	{ strcat(buffer,"0,"); }

	rotary1pos[0]= '0';
	if (datastk.botInc  == 1 && datastk.botDme == 1 ) { rotary1pos[0]='1'; }
	if (datastk.botDec  == 1 && datastk.botDme == 1 ) { rotary1pos[0]='2'; }
	if (datastk.botIncD == 1 && datastk.botDme == 1 ) { rotary1pos[0]='3'; }
	if (datastk.botDecD == 1 && datastk.botDme == 1 ) { rotary1pos[0]='4'; }
	rotary1pos[1]=',';
	rotary1pos[2]='\0';
	strcat(buffer,rotary1pos);

	//DME
	if (datastk.botSwcPush == 1 && datastk.botXpdr == 1 ) { strcat(buffer,"1,"); } 	else	{ strcat(buffer,"0,"); }

	rotary1pos[0]= '0';
	if (datastk.botInc  == 1 && datastk.botXpdr == 1 ) { rotary1pos[0]='1'; }
	if (datastk.botDec  == 1 && datastk.botXpdr == 1 ) { rotary1pos[0]='2'; }
	if (datastk.botIncD == 1 && datastk.botXpdr == 1 ) { rotary1pos[0]='3'; }
	if (datastk.botDecD == 1 && datastk.botXpdr == 1 ) { rotary1pos[0]='4'; }
	rotary1pos[1]=',';
	rotary1pos[2]='\0';
	strcat(buffer,rotary1pos);

	strcat(buffer,"\n");
	//printf("BUFFER : %s",buffer);

	if (sendto(s, buffer, strlen(buffer), 0, (struct sockaddr *) &si_other, slen) == -1) {
			perror("PError: ");
			printf(" error sendto()");
			exit(-6);
	}


	//desconnect socket
	close(s);

}
















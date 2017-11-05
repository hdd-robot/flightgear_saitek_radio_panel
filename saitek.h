/*
 * saitek.h
 *
 *  Created on: 16 mai 2016
 *      Author: Halim DJERROUD
 *      email : hdd@ai.univ-paris8.fr
 */

#ifndef SAITEK_H_
#define SAITEK_H_

struct dataSTKsaved{
    char topInc;
    char topDec;
    char topIncD;
    char topDecD;
    char botInc;
	char botDec;
	char botIncD;
	char botDecD;
};


struct dataFG {

    char com1stb[10];
    char com1stbd[10];
    char com1[10];
    char com1d[10];

    char com2stb[10];
    char com2stbd[10];
    char com2[10];
    char com2d[10];

    char nav1stb[10];
    char nav1stbd[10];
    char nav1[10];
    char nav1d[10];

    char nav2stb[10];
    char nav2stbd[10];
    char nav2[10];
    char nav2d[10];

    char adf[10];
    char adfd[10];
    char adfstb[10];
    char adfstbd[10];

    char dme[10];
    char dmed[10];

    char xpdr[10];
};

struct dataSTK{

	char data[3];
	char modified;

	char topCom1;
    char topCom2;
    char topNav1;
    char topNav2;
    char topAdf;
    char topDme;
    char topXpdr;

    char topInc;
    char topDec;
    char topIncD;
    char topDecD;
    char topSwcPush;

    char botCom1;
    char botCom2;
    char botNav1;
    char botNav2;
    char botAdf;
    char botDme;
    char botXpdr;

    char botInc;
	char botDec;
	char botIncD;
	char botDecD;
	char botSwcPush;

};


#endif /* SAITEK_H_ */

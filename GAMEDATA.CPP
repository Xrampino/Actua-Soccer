#include <iostream.h>
#include <stdlib.h>
#include <stdio.h>
#include <graph.h>
#include <i86.h>
#include <dos.h>
#include <conio.h>
#include <float.h>
#include <math.h>
#include <string.h>

#include "defines.h"
#include "data.equ"
#include "3deng.h"
#include "video.h"
#include "menu.h"
#include "unmangle.h"
#include "gamedata.h"


referee_info		referee_data[33]={

		"Angeles",		86,	55,	USA, 
		"Spirin",		50,	35,	RUS, 
		"Vega Diaz",		68,	90,	SPN, 
		"Van Langenhove",	78,	66,	BEL, 
		"Mikkelsen",		92,	44,	DEN, 
		"Snoddy",		75,	49,	NIR, 
		"Jouini",		32,	70,	TUN, 
		"Rothlisberger",    	50,	32,	SWZ, 
		"Duk-hwan",   	 	67,	23,	SKR, 
		"Baldas",    		88,	94,	ITA, 
		"Don",    		79,	56,	ENG, 
		"Mottram",    		25,	77,	SCO, 
		"Burge",    		48,	64,	WAL, 
		"Torres Cadena",   	88,	76,	COL, 
		"Karlsson", 	  	66,	28,	SWE, 
		"Lamolina", 	  	96,	88,	ARG, 

		"Van der Ende",		34,	23,	HOL,
		"Kruger", 		88,	98,	GER,
		"Quiniou",		50,	44,	FRA,
		"Filippi Cavani",	22,	75,	URU,
		"Marsiglia",		78,	89,	BRA,
		"Brizio Carter",	66,	13,	MEX,
		"Krondl",		34,	49,	CZE,
		"Koho",			23,	44,	FIN,
		"Okada",		88,	96,	JAP,
		"Bakas",		78,	45,	GRE,
		"Orumbouio",		56,	89,	ROM,
		"Hrinak",		34,	23,	SLV,
		"Pena",			45,	77,	BOL,
		"Pairetto",    		78,	64,	ITA, 
		"Araujo",		98,	80,	BRA,
		"Matto",		52,	85,	URU,

		"Random", 	  	60,	40,	NULL, 
		};



team_info	game_data[2]={

		{		  
	//ษออออออออออออออออออออออออป 
	//บ                        บ
	//บ  Team statistics done  บ
	//บ			   บ
	//ศออออออออออออออออออออออออผ 

		"DEMO TEAM A", 
		"Bora Milutinovic",
		0 , 0,
		10,6,3,0,0,12,NULL,NULL,
		NULL,
		"USA",
		22,0,		 
		0,0,
		BIN_USA,
		0,0,0,
		"US",		 // Country Code for Samples
		F_4_3_3,

				 //            Pace    Power  Control  Flair  Vision   Accur   Stam   Discip
		"PLAYER 1",		0,    	65,     23,     33,     77,     73,     67,     28,     47,	0,	0,	GK,	0,
		"PLAYER 2",		0,	64,     68,     49,     52,     48,     56,     68,     56,	0,	1,	DF,	0,
		"PLAYER 3",		0,	78,     51,     43,     45,     55,     53,     43,     74,	0,	2,	DF,	0,
		"PLAYER 4",		0,	75,     85,     50,     70,     46,     55,     72,     35,	0,	3,	DF,	0,
		"PLAYER 5",		0,	68,     62,     46,     53,     37,     49,     57,     43,	0,	4,	DF,	0,
		"PLAYER 6",		0,	60,     47,     53,     43,     53,     45,     41,     18,	0,	5,	MD,	0,
		"PLAYER 7",		0,	65,     48,     82,     52,     55,     71,     61,     49,	0,	6,	MD,	0,
		"PLAYER 8",		0,	59,     50,     67,     47,     79,     50,     45,     55,	0,	7,	MD,	0,
		"PLAYER 9",		0,	69,     52,     48,     62,     51,     60,     78,     73,	0,	8,	FD,	1,
		"PLAYER 10",		0,	64,     73,     66,     65,     46,     78,     43,     45,	0,	9,	FD,	0,
		"PLAYER 11",		0,	55,     46,     55,     39,     56,     35,     47,     33,	0,	10,	MD,    	0,
		"PLAYER 12",		0,	23,     14,     31,     20,     42,     24,     39,     52,	0,	11,	GK,	0,
		"PLAYER 13",		0,	75,     53,     42,     49,     58,     36,     45,     44,	0,	12,	DF,	0,
		"PLAYER 14",		0,	33,     35,     43,     40,     50,     57,     36,     45,	0,	13,	MD,	0,
		"PLAYER 15",		0,	42,     50,     49,     51,     45,     55,     12,     10,	0,	14,	MD,	0,
		"PLAYER 16",		0,	29,     42,     50,     42,     51,     26,     55,     9,	0,	15,	DF,	0,
		"PLAYER 17",		0,	85,     47,     47,     65,     46,     46,     70,     30,	0,	16,	MD,	1,
		"PLAYER 18",		0,	40,     36,     49,     38,     45,     56,     74,     48,	0,	17,	FD,	0,
		"PLAYER 19",		5,	24,     46,     30,     53,     36,     51,     56,     64,	0,	18,	FD,	0,
		"PLAYER 20",		0,	36,     49,     52,     43,     44,     70,     36,     45,	0,	19,	MD,	0,
		"PLAYER 21",		0,	40,     39,     44,     86,     49,     58,     64,     67,	0,	20,	FD,	0,
		"PLAYER 22",		0,	29,     26,     30,     33,     36,     46,     58,     54,	0,	21,	GK,	0,
		},																	

		{		  

	//ษออออออออออออออออออออออออป 
	//บ                        บ
	//บ  Team statistics done  บ
	//บ			   บ
	//ศออออออออออออออออออออออออผ 

		"DEMO TEAM B", 
		"Pavel Sadyrin",
		0, 0,
		NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,
		NULL,
		"Russia",
		12,1,		 
		0,0,
		BIN_RUSSIA,
		0,0,0,
		"RU",		 // Country Code for Samples
		F_4_4_2,

				 //            Pace    Power  Control  Flair  Vision   Accur   Stam   Discip
		"PLAYER 1",		0,    	34,     55,     21,     34,     44,     43,     20,     56,	0,	0,	GK,	0,
		"PLAYER 2",		0,   	24,     48,     53,     45,     51,     78,     35,     42,	0,	1,	DF,	0,
		"PLAYER 3",		0,     	41,     49,     47,     57,     63,     52,     63,     62,	0,	2,	DF,	0,
		"PLAYER 4",		0,     	72,     52,     96,     55,     62,     45,     67,     43,	0,	3,	DF,	0,
		"PLAYER 5",		0,     	39,     45,     48,     61,     35,     57,     43,     65,	0,	4,	DF,	0,
		"PLAYER 6",		0,     	69,     62,     58,     65,     58,     67,     56,     58,	0,	5,	MD,	0,
		"PLAYER 7",    		0,    	68,     59,     60,     53,     45,     59,     58,     74,	0,	6,	MD,	0,
		"PLAYER 8",		0,	63,     53,     60,     59,     57,     66,     35,     35,	0,	7,	MD,	0,
		"PLAYER 9",		0,	59,     69,     64,     93,     55,     68,     74,     67,	0,	8,	FD,	0,
		"PLAYER 10",		0,     	54,     86,     59,     68,     59,     70,     45,     75,	0,	9,	FD,	0,
		"PLAYER 11",		0,	66,     66,     55,     59,     68,     63,     26,     56,	0,	10,	MD,	0,
		"PLAYER 12",		0,	24,     33,     21,     34,     47,     35,     56,     46,	0,	11,	GK,	0,
		"PLAYER 13",		0,      67,     66,     56,     49,     28,     71,     37,     58,	0,	12,	MD,	0,
		"PLAYER 14",   		0,   	70,     69,     60,     54,     63,     90,     73,     49,	0,	13,	MD,	0,
		"PLAYER 15",		0,	54,     61,     54,     69,     62,     33,     56,     57,	0,	14,	DF,	0,
		"PLAYER 16",		0,      44,     53,     51,     34,     49,     72,     47,     34,	0,	15,	DF,	0,
		"PLAYER 17",		0,	52,     24,     44,     53,     52,     43,     38,     53,	0,	16,	FD,	0,
		"PLAYER 18", 	  	0,   	57,     64,     68,     58,     38,     46,     73,     57,	0,	17,	MD,	0,
		"PLAYER 19",		0,	19,     45,     46,     60,     37,     67,     67,     7,	0,	18,	DF,	0,
		"PLAYER 20",		0,      36,     57,     67,     42,     27,     56,     10,     38,	0,	19,	FD,	0,
		"PLAYER 21",		0,      44,     46,     57,     61,     41,     69,     29,     56,	0,	20,	MD,	0,
		"PLAYER 22",		0,      26,     43,     58,     34,     47,     67,     55,     56,	0,	21,	DF,	0,
		},																	

		     };


						


// old actuasprite		sprite_table[]={				       	 
// old actua								 
// old actua		{
// old actua		sprite1width,sprite1height,sprite1Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite1awidth,sprite1aheight,sprite1aBitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite1bwidth,sprite1bheight,sprite1bBitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite2width,sprite2height,sprite2Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite3width,sprite3height,sprite3Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite4width,sprite4height,sprite4Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite5width,sprite5height,sprite5Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite6width,sprite6height,sprite6Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite7width,sprite7height,sprite7Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite8width,sprite8height,sprite8Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite9width,sprite9height,sprite9Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite10width,sprite10height,sprite10Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite11width,sprite11height,sprite11Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite12width,sprite12height,sprite12Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite13width,sprite13height,sprite13Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite14width,sprite14height,sprite14Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite15width,sprite15height,sprite15Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite16width,sprite16height,sprite16Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite17width,sprite17height,sprite17Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite18width,sprite18height,sprite18Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite19width,sprite19height,sprite19Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite20width,sprite20height,sprite20Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite21width,sprite21height,sprite21Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite22width,sprite22height,sprite22Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite23width,sprite23height,sprite23Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite24width,sprite24height,sprite24Bitmap,
// old actua		},
// old actua	
// old actua		{
// old actua		sprite25width,sprite25height,sprite25Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite26width,sprite26height,sprite26Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite27width,sprite27height,sprite27Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite28width,sprite28height,sprite28Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite29width,sprite29height,sprite29Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite30width,sprite30height,sprite30Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite31width,sprite31height,sprite31Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite32width,sprite32height,sprite32Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite33width,sprite33height,sprite33Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite34width,sprite34height,sprite34Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite35width,sprite35height,sprite35Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite36width,sprite36height,sprite36Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite37width,sprite37height,sprite37Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite38width,sprite38height,sprite38Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite39width,sprite39height,sprite39Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite40width,sprite40height,sprite40Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite41width,sprite41height,sprite41Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite42width,sprite42height,sprite42Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite43width,sprite43height,sprite43Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite44width,sprite44height,sprite44Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite45width,sprite45height,sprite45Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite46width,sprite46height,sprite46Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite47width,sprite47height,sprite47Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite48width,sprite48height,sprite48Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite49width,sprite49height,sprite49Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite50width,sprite50height,sprite50Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite51width,sprite51height,sprite51Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite52width,sprite52height,sprite52Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite53width,sprite53height,sprite53Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite54width,sprite54height,sprite54Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite55width,sprite55height,sprite55Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite55Bwidth,sprite55Bheight,sprite55BBitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite55Cwidth,sprite55Cheight,sprite55CBitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite56width,sprite56height,sprite56Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite57width,sprite57height,sprite57Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite58width,sprite58height,sprite58Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite59width,sprite59height,sprite59Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite60width,sprite60height,sprite60Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite61width,sprite61height,sprite61Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite62width,sprite62height,sprite62Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite63width,sprite63height,sprite63Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite64width,sprite64height,sprite64Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite65width,sprite65height,sprite65Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite66width,sprite66height,sprite66Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite67width,sprite67height,sprite67Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite68width,sprite68height,sprite68Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite69width,sprite69height,sprite69Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite70width,sprite70height,sprite70Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite71width,sprite71height,sprite71Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite72width,sprite72height,sprite72Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite73width,sprite73height,sprite73Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite74width,sprite74height,sprite74Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite75width,sprite75height,sprite75Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite76width,sprite76height,sprite76Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite77width,sprite77height,sprite77Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite78width,sprite78height,sprite78Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite79width,sprite79height,sprite79Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite80width,sprite80height,sprite80Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite81width,sprite81height,sprite81Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite82width,sprite82height,sprite82Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite83width,sprite83height,sprite83Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite84width,sprite84height,sprite84Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite85width,sprite85height,sprite85Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite86width,sprite86height,sprite86Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite87width,sprite87height,sprite87Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite88width,sprite88height,sprite88Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite89width,sprite89height,sprite89Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite90width,sprite90height,sprite90Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite91width,sprite91height,sprite91Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite92width,sprite92height,sprite92Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite93width,sprite93height,sprite93Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite94width,sprite94height,sprite94Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite95width,sprite95height,sprite95Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite96width,sprite96height,sprite96Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite97width,sprite97height,sprite97Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite98width,sprite98height,sprite98Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite99width,sprite99height,sprite99Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite100width,sprite100height,sprite100Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite101width,sprite101height,sprite101Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite102width,sprite102height,sprite102Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite103width,sprite103height,sprite103Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite104width,sprite104height,sprite104Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite105width,sprite105height,sprite105Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite106width,sprite106height,sprite106Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite107width,sprite107height,sprite107Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite108width,sprite108height,sprite108Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite109width,sprite109height,sprite109Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite110width,sprite110height,sprite110Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite111width,sprite111height,sprite111Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite112width,sprite112height,sprite112Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite113width,sprite113height,sprite113Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite114width,sprite114height,sprite114Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite115width,sprite115height,sprite115Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite116width,sprite116height,sprite116Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite117width,sprite117height,sprite117Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite118width,sprite118height,sprite118Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite119width,sprite119height,sprite119Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite120width,sprite120height,sprite120Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite121width,sprite121height,sprite121Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite122width,sprite122height,sprite122Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite123width,sprite123height,sprite123Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite124width,sprite124height,sprite124Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite125width,sprite125height,sprite125Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite126width,sprite126height,sprite126Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite127width,sprite127height,sprite127Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite128width,sprite128height,sprite128Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite129width,sprite129height,sprite129Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite130width,sprite130height,sprite130Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite131width,sprite131height,sprite131Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite132width,sprite132height,sprite132Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite133width,sprite133height,sprite133Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite134width,sprite134height,sprite134Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite135width,sprite135height,sprite135Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite136width,sprite136height,sprite136Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite137width,sprite137height,sprite137Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite138width,sprite138height,sprite138Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite139width,sprite139height,sprite139Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite140width,sprite140height,sprite140Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite141width,sprite141height,sprite141Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite142width,sprite142height,sprite142Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite143width,sprite143height,sprite143Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite144width,sprite144height,sprite144Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite145width,sprite145height,sprite145Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite146width,sprite146height,sprite146Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite147width,sprite147height,sprite147Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite148width,sprite148height,sprite148Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite149width,sprite149height,sprite149Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite150width,sprite150height,sprite150Bitmap,
// old actua		},
// old actua
// old actua//		{
// old actua//		sprite151width,sprite151height,sprite151Bitmap,
// old actua//		},
// old actua//
// old actua//		{
// old actua//		sprite152width,sprite152height,sprite152Bitmap,
// old actua//		},
// old actua
// old actua
// old actua
// old actua
// old actua
// old actua
// old actua		
// old actua		{
// old actua		sprite_S62width,sprite_S62height,sprite_S62Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S63width,sprite_S63height,sprite_S63Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S64width,sprite_S64height,sprite_S64Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S65width,sprite_S65height,sprite_S65Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S66width,sprite_S66height,sprite_S66Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S67width,sprite_S67height,sprite_S67Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S68width,sprite_S68height,sprite_S68Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S69width,sprite_S69height,sprite_S69Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S70width,sprite_S70height,sprite_S70Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S71width,sprite_S71height,sprite_S71Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S72width,sprite_S72height,sprite_S72Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S73width,sprite_S73height,sprite_S73Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S74width,sprite_S74height,sprite_S74Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S75width,sprite_S75height,sprite_S75Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S76width,sprite_S76height,sprite_S76Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S77width,sprite_S77height,sprite_S77Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S78width,sprite_S78height,sprite_S78Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S79width,sprite_S79height,sprite_S79Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S80width,sprite_S80height,sprite_S80Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S81width,sprite_S81height,sprite_S81Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S82width,sprite_S82height,sprite_S82Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S83width,sprite_S83height,sprite_S83Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S84width,sprite_S84height,sprite_S84Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S85width,sprite_S85height,sprite_S85Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S86width,sprite_S86height,sprite_S86Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S87width,sprite_S87height,sprite_S87Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S88width,sprite_S88height,sprite_S88Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S89width,sprite_S89height,sprite_S89Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S90width,sprite_S90height,sprite_S90Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S91width,sprite_S91height,sprite_S91Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S92width,sprite_S92height,sprite_S92Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S93width,sprite_S93height,sprite_S93Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S94width,sprite_S94height,sprite_S94Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S95width,sprite_S95height,sprite_S95Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S96width,sprite_S96height,sprite_S96Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S97width,sprite_S97height,sprite_S97Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S98width,sprite_S98height,sprite_S98Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S99width,sprite_S99height,sprite_S99Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S100width,sprite_S100height,sprite_S100Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S101width,sprite_S101height,sprite_S101Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S102width,sprite_S102height,sprite_S102Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S103width,sprite_S103height,sprite_S103Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S104width,sprite_S104height,sprite_S104Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S105width,sprite_S105height,sprite_S105Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S106width,sprite_S106height,sprite_S106Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S107width,sprite_S107height,sprite_S107Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S108width,sprite_S108height,sprite_S108Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S109width,sprite_S109height,sprite_S109Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S110width,sprite_S110height,sprite_S110Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S111width,sprite_S111height,sprite_S111Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S112width,sprite_S112height,sprite_S112Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S113width,sprite_S113height,sprite_S113Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S114width,sprite_S114height,sprite_S114Bitmap,
// old actua		},
// old actua 
// old actua		{
// old actua		sprite_S115width,sprite_S115height,sprite_S115Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S116width,sprite_S116height,sprite_S116Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S117width,sprite_S117height,sprite_S117Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S118width,sprite_S118height,sprite_S118Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S119width,sprite_S119height,sprite_S119Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S120width,sprite_S120height,sprite_S120Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S121width,sprite_S121height,sprite_S121Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S122width,sprite_S122height,sprite_S122Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S123width,sprite_S123height,sprite_S123Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S124width,sprite_S124height,sprite_S124Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S125width,sprite_S125height,sprite_S125Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S126width,sprite_S126height,sprite_S126Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S127width,sprite_S127height,sprite_S127Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S128width,sprite_S128height,sprite_S128Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S129width,sprite_S129height,sprite_S129Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S130width,sprite_S130height,sprite_S130Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S131width,sprite_S131height,sprite_S131Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S132width,sprite_S132height,sprite_S132Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S133width,sprite_S133height,sprite_S133Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S134width,sprite_S134height,sprite_S134Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S135width,sprite_S135height,sprite_S135Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S136width,sprite_S136height,sprite_S136Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S137width,sprite_S137height,sprite_S137Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S138width,sprite_S138height,sprite_S138Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S139width,sprite_S139height,sprite_S139Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S140width,sprite_S140height,sprite_S140Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S141width,sprite_S141height,sprite_S141Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S142width,sprite_S142height,sprite_S142Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S143width,sprite_S143height,sprite_S143Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S144width,sprite_S144height,sprite_S144Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S145width,sprite_S145height,sprite_S145Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S146width,sprite_S146height,sprite_S146Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S147width,sprite_S147height,sprite_S147Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S148width,sprite_S148height,sprite_S148Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S149width,sprite_S149height,sprite_S149Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S150width,sprite_S150height,sprite_S150Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S151width,sprite_S151height,sprite_S151Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S152width,sprite_S152height,sprite_S152Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S153width,sprite_S153height,sprite_S153Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S154width,sprite_S154height,sprite_S154Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S155width,sprite_S155height,sprite_S155Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S156width,sprite_S156height,sprite_S156Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S157width,sprite_S157height,sprite_S157Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S158width,sprite_S158height,sprite_S158Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S159width,sprite_S159height,sprite_S159Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S160width,sprite_S160height,sprite_S160Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S161width,sprite_S161height,sprite_S161Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S162width,sprite_S162height,sprite_S162Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S163width,sprite_S163height,sprite_S163Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S164width,sprite_S164height,sprite_S164Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S165width,sprite_S165height,sprite_S165Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S166width,sprite_S166height,sprite_S166Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S167width,sprite_S167height,sprite_S167Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S168width,sprite_S168height,sprite_S168Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S169width,sprite_S169height,sprite_S169Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S170width,sprite_S170height,sprite_S170Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S171width,sprite_S171height,sprite_S171Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S172width,sprite_S172height,sprite_S172Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S173width,sprite_S173height,sprite_S173Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S174width,sprite_S174height,sprite_S174Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S175width,sprite_S175height,sprite_S175Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S176width,sprite_S176height,sprite_S176Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S177width,sprite_S177height,sprite_S177Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S178width,sprite_S178height,sprite_S178Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S179width,sprite_S179height,sprite_S179Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S180width,sprite_S180height,sprite_S180Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S181width,sprite_S181height,sprite_S181Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S182width,sprite_S182height,sprite_S182Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S183width,sprite_S183height,sprite_S183Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S184width,sprite_S184height,sprite_S184Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S185width,sprite_S185height,sprite_S185Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S186width,sprite_S186height,sprite_S186Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S187width,sprite_S187height,sprite_S187Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S188width,sprite_S188height,sprite_S188Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S189width,sprite_S189height,sprite_S189Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S190width,sprite_S190height,sprite_S190Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S191width,sprite_S191height,sprite_S191Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S192width,sprite_S192height,sprite_S192Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S193width,sprite_S193height,sprite_S193Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S194width,sprite_S194height,sprite_S194Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S195width,sprite_S195height,sprite_S195Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S196width,sprite_S196height,sprite_S196Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S197width,sprite_S197height,sprite_S197Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S198width,sprite_S198height,sprite_S198Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S199width,sprite_S199height,sprite_S199Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S200width,sprite_S200height,sprite_S200Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S201width,sprite_S201height,sprite_S201Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S202width,sprite_S202height,sprite_S202Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S203width,sprite_S203height,sprite_S203Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S204width,sprite_S204height,sprite_S204Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S205width,sprite_S205height,sprite_S205Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S206width,sprite_S206height,sprite_S206Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S207width,sprite_S207height,sprite_S207Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S208width,sprite_S208height,sprite_S208Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S209width,sprite_S209height,sprite_S209Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S210width,sprite_S210height,sprite_S210Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S211width,sprite_S211height,sprite_S211Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S212width,sprite_S212height,sprite_S212Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S213width,sprite_S213height,sprite_S213Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S214width,sprite_S214height,sprite_S214Bitmap,
// old actua		},
// old actua 
// old actua		{
// old actua		sprite_S215width,sprite_S215height,sprite_S215Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S216width,sprite_S216height,sprite_S216Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S217width,sprite_S217height,sprite_S217Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S218width,sprite_S218height,sprite_S218Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S219width,sprite_S219height,sprite_S219Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S220width,sprite_S220height,sprite_S220Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S221width,sprite_S221height,sprite_S221Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S222width,sprite_S222height,sprite_S222Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S223width,sprite_S223height,sprite_S223Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S224width,sprite_S224height,sprite_S224Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S225width,sprite_S225height,sprite_S225Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S226width,sprite_S226height,sprite_S226Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S227width,sprite_S227height,sprite_S227Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S228width,sprite_S228height,sprite_S228Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S229width,sprite_S229height,sprite_S229Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S230width,sprite_S230height,sprite_S230Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S231width,sprite_S231height,sprite_S231Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S232width,sprite_S232height,sprite_S232Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S233width,sprite_S233height,sprite_S233Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S234width,sprite_S234height,sprite_S234Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S235width,sprite_S235height,sprite_S235Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S236width,sprite_S236height,sprite_S236Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S237width,sprite_S237height,sprite_S237Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S238width,sprite_S238height,sprite_S238Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S239width,sprite_S239height,sprite_S239Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S240width,sprite_S240height,sprite_S240Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S241width,sprite_S241height,sprite_S241Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S242width,sprite_S242height,sprite_S242Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S243width,sprite_S243height,sprite_S243Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S244width,sprite_S244height,sprite_S244Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S245width,sprite_S245height,sprite_S245Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S246width,sprite_S246height,sprite_S246Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S247width,sprite_S247height,sprite_S247Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S248width,sprite_S248height,sprite_S248Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S249width,sprite_S249height,sprite_S249Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S250width,sprite_S250height,sprite_S250Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S251width,sprite_S251height,sprite_S251Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S252width,sprite_S252height,sprite_S252Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S253width,sprite_S253height,sprite_S253Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S254width,sprite_S254height,sprite_S254Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S255width,sprite_S255height,sprite_S255Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S256width,sprite_S256height,sprite_S256Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S257width,sprite_S257height,sprite_S257Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S258width,sprite_S258height,sprite_S258Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S259width,sprite_S259height,sprite_S259Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S260width,sprite_S260height,sprite_S260Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S261width,sprite_S261height,sprite_S261Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S262width,sprite_S262height,sprite_S262Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S263width,sprite_S263height,sprite_S263Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S264width,sprite_S264height,sprite_S264Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S265width,sprite_S265height,sprite_S265Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S266width,sprite_S266height,sprite_S266Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S267width,sprite_S267height,sprite_S267Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S268width,sprite_S268height,sprite_S268Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S269width,sprite_S269height,sprite_S269Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S270width,sprite_S270height,sprite_S270Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S271width,sprite_S271height,sprite_S271Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S272width,sprite_S272height,sprite_S272Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S273width,sprite_S273height,sprite_S273Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S274width,sprite_S274height,sprite_S274Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S275width,sprite_S275height,sprite_S275Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S276width,sprite_S276height,sprite_S276Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S277width,sprite_S277height,sprite_S277Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S278width,sprite_S278height,sprite_S278Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S279width,sprite_S279height,sprite_S279Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S280width,sprite_S280height,sprite_S280Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S281width,sprite_S281height,sprite_S281Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S282width,sprite_S282height,sprite_S282Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S283width,sprite_S283height,sprite_S283Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S284width,sprite_S284height,sprite_S284Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S285width,sprite_S285height,sprite_S285Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S286width,sprite_S286height,sprite_S286Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S287width,sprite_S287height,sprite_S287Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S288width,sprite_S288height,sprite_S288Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S289width,sprite_S289height,sprite_S289Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S290width,sprite_S290height,sprite_S290Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S291width,sprite_S291height,sprite_S291Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S292width,sprite_S292height,sprite_S292Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S293width,sprite_S293height,sprite_S293Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S294width,sprite_S294height,sprite_S294Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S295width,sprite_S295height,sprite_S295Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S296width,sprite_S296height,sprite_S296Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S297width,sprite_S297height,sprite_S297Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S298width,sprite_S298height,sprite_S298Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S299width,sprite_S299height,sprite_S299Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S300width,sprite_S300height,sprite_S300Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S301width,sprite_S301height,sprite_S301Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S302width,sprite_S302height,sprite_S302Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S303width,sprite_S303height,sprite_S303Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S304width,sprite_S304height,sprite_S304Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S305width,sprite_S305height,sprite_S305Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S306width,sprite_S306height,sprite_S306Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S307width,sprite_S307height,sprite_S307Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S308width,sprite_S308height,sprite_S308Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S309width,sprite_S309height,sprite_S309Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S310width,sprite_S310height,sprite_S310Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S311width,sprite_S311height,sprite_S311Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S312width,sprite_S312height,sprite_S312Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S313width,sprite_S313height,sprite_S313Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S314width,sprite_S314height,sprite_S314Bitmap,
// old actua		},
// old actua 
// old actua		{
// old actua		sprite_S315width,sprite_S315height,sprite_S315Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S316width,sprite_S316height,sprite_S316Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S317width,sprite_S317height,sprite_S317Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S318width,sprite_S318height,sprite_S318Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S319width,sprite_S319height,sprite_S319Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S320width,sprite_S320height,sprite_S320Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S321width,sprite_S321height,sprite_S321Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S322width,sprite_S322height,sprite_S322Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S323width,sprite_S323height,sprite_S323Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S324width,sprite_S324height,sprite_S324Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S325width,sprite_S325height,sprite_S325Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S326width,sprite_S326height,sprite_S326Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S327width,sprite_S327height,sprite_S327Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S328width,sprite_S328height,sprite_S328Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S329width,sprite_S329height,sprite_S329Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S330width,sprite_S330height,sprite_S330Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S331width,sprite_S331height,sprite_S331Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S332width,sprite_S332height,sprite_S332Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S333width,sprite_S333height,sprite_S333Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S333width,sprite_S333height,sprite_S333Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S334width,sprite_S334height,sprite_S334Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S335width,sprite_S335height,sprite_S335Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S336width,sprite_S336height,sprite_S336Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S337width,sprite_S337height,sprite_S337Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S338width,sprite_S338height,sprite_S338Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S339width,sprite_S339height,sprite_S339Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S340width,sprite_S340height,sprite_S340Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S341width,sprite_S341height,sprite_S341Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S342width,sprite_S342height,sprite_S342Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S343width,sprite_S343height,sprite_S343Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S344width,sprite_S344height,sprite_S344Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S345width,sprite_S345height,sprite_S345Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S346width,sprite_S346height,sprite_S346Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S347width,sprite_S347height,sprite_S347Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S348width,sprite_S348height,sprite_S348Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S349width,sprite_S349height,sprite_S349Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S350width,sprite_S350height,sprite_S350Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S351width,sprite_S351height,sprite_S351Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S352width,sprite_S352height,sprite_S352Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S353width,sprite_S353height,sprite_S353Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S354width,sprite_S354height,sprite_S354Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S355width,sprite_S355height,sprite_S355Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S356width,sprite_S356height,sprite_S356Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S357width,sprite_S357height,sprite_S357Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S358width,sprite_S358height,sprite_S358Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S359width,sprite_S359height,sprite_S359Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S360width,sprite_S360height,sprite_S360Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S361width,sprite_S361height,sprite_S361Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S362width,sprite_S362height,sprite_S362Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S363width,sprite_S363height,sprite_S363Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S364width,sprite_S364height,sprite_S364Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S365width,sprite_S365height,sprite_S365Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S366width,sprite_S366height,sprite_S366Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S367width,sprite_S367height,sprite_S367Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S368width,sprite_S368height,sprite_S368Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S369width,sprite_S369height,sprite_S369Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S370width,sprite_S370height,sprite_S370Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S371width,sprite_S371height,sprite_S371Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S372width,sprite_S372height,sprite_S372Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S373width,sprite_S373height,sprite_S373Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S374width,sprite_S374height,sprite_S374Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S375width,sprite_S375height,sprite_S375Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S376width,sprite_S376height,sprite_S376Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S377width,sprite_S377height,sprite_S377Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S378width,sprite_S378height,sprite_S378Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S379width,sprite_S379height,sprite_S379Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S380width,sprite_S380height,sprite_S380Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S381width,sprite_S381height,sprite_S381Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S382width,sprite_S382height,sprite_S382Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S383width,sprite_S383height,sprite_S383Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S384width,sprite_S384height,sprite_S384Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S385width,sprite_S385height,sprite_S385Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S386width,sprite_S386height,sprite_S386Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S387width,sprite_S387height,sprite_S387Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S388width,sprite_S388height,sprite_S388Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S389width,sprite_S389height,sprite_S389Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S390width,sprite_S390height,sprite_S390Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S391width,sprite_S391height,sprite_S391Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S392width,sprite_S392height,sprite_S392Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S393width,sprite_S393height,sprite_S393Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S394width,sprite_S394height,sprite_S394Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S395width,sprite_S395height,sprite_S395Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S396width,sprite_S396height,sprite_S396Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S397width,sprite_S397height,sprite_S397Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S398width,sprite_S398height,sprite_S398Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S399width,sprite_S399height,sprite_S399Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S400width,sprite_S400height,sprite_S400Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S401width,sprite_S401height,sprite_S401Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S402width,sprite_S402height,sprite_S402Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S403width,sprite_S403height,sprite_S403Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S404width,sprite_S404height,sprite_S404Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S405width,sprite_S405height,sprite_S405Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S406width,sprite_S406height,sprite_S406Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S407width,sprite_S407height,sprite_S407Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S408width,sprite_S408height,sprite_S408Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S409width,sprite_S409height,sprite_S409Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S410width,sprite_S410height,sprite_S410Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S411width,sprite_S411height,sprite_S411Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S412width,sprite_S412height,sprite_S412Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S413width,sprite_S413height,sprite_S413Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S414width,sprite_S414height,sprite_S414Bitmap,
// old actua		},
// old actua 
// old actua		{
// old actua		sprite_S415width,sprite_S415height,sprite_S415Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S416width,sprite_S416height,sprite_S416Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S417width,sprite_S417height,sprite_S417Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S418width,sprite_S418height,sprite_S418Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S419width,sprite_S419height,sprite_S419Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S420width,sprite_S420height,sprite_S420Bitmap,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_999width,sprite_999height,sprite_999Bitmap,
// old actua		},
// old actua
// old actua				};
// old actua
// old actua	long	spool_index[]={
// old actua
// old actua	spool_index1,spool_index1,spool_index1,spool_index1,spool_index1,spool_index1,spool_index1,spool_index1,
// old actua	spool_index2,spool_index2,spool_index2,spool_index2,spool_index2,spool_index2,spool_index2,spool_index2,
// old actua	spool_index3,spool_index3,spool_index3,spool_index3,spool_index3,spool_index3,spool_index3,spool_index3,
// old actua	spool_index4,spool_index4,spool_index4,spool_index4,spool_index4,spool_index4,spool_index4,spool_index4,
// old actua	spool_index5,spool_index5,spool_index5,spool_index5,spool_index5,spool_index5,spool_index5,spool_index5,
// old actua	spool_index6,spool_index6,spool_index6,spool_index6,spool_index6,spool_index6,spool_index6,spool_index6,
// old actua	spool_index7,spool_index7,spool_index7,spool_index7,spool_index7,spool_index7,spool_index7,spool_index7,
// old actua	spool_index8,spool_index8,spool_index8,spool_index8,spool_index8,spool_index8,spool_index8,spool_index8,
// old actua	spool_index9,spool_index9,spool_index9,spool_index9,spool_index9,spool_index9,spool_index9,spool_index9,
// old actua	spool_index10,spool_index10,spool_index10,spool_index10,spool_index10,spool_index10,spool_index10,spool_index10,
// old actua	spool_index11,spool_index11,spool_index11,spool_index11,spool_index11,spool_index11,spool_index11,spool_index11,
// old actua	spool_index12,spool_index12,spool_index12,spool_index12,spool_index12,spool_index12,spool_index12,spool_index12,
// old actua	spool_index13,spool_index13,spool_index13,spool_index13,spool_index13,spool_index13,spool_index13,spool_index13,
// old actua	spool_index14,spool_index14,spool_index14,spool_index14,spool_index14,spool_index14,spool_index14,spool_index14,
// old actua	spool_index15,spool_index15,spool_index15,spool_index15,spool_index15,spool_index15,spool_index15,spool_index15,
// old actua	spool_index16,spool_index16,spool_index16,spool_index16,spool_index16,spool_index16,spool_index16,spool_index16,
// old actua	spool_index17,spool_index17,spool_index17,spool_index17,spool_index17,spool_index17,spool_index17,spool_index17,
// old actua	spool_index18,spool_index18,spool_index18,spool_index18,spool_index18,spool_index18,spool_index18,spool_index18,
// old actua	spool_index19,spool_index19,spool_index19,spool_index19,spool_index19,spool_index19,spool_index19,spool_index19,
// old actua	spool_index20,spool_index20,spool_index20,spool_index20,spool_index20,spool_index20,spool_index20,spool_index20,
// old actua	spool_index21,spool_index21,spool_index21,spool_index21,spool_index21,spool_index21,spool_index21,spool_index21,
// old actua	spool_index22,spool_index22,spool_index22,spool_index22,spool_index22,spool_index22,spool_index22,spool_index22,
// old actua	spool_index23,spool_index23,spool_index23,spool_index23,spool_index23,spool_index23,spool_index23,spool_index23,
// old actua	spool_index24,spool_index24,spool_index24,spool_index24,spool_index24,spool_index24,spool_index24,spool_index24,
// old actua	spool_index25,spool_index25,spool_index25,spool_index25,spool_index25,spool_index25,spool_index25,spool_index25,
// old actua	spool_index26,spool_index26,spool_index26,spool_index26,spool_index26,spool_index26,spool_index26,spool_index26,
// old actua	spool_index27,spool_index27,spool_index27,spool_index27,spool_index27,spool_index27,spool_index27,spool_index27,
// old actua	spool_index28,spool_index28,spool_index28,spool_index28,spool_index28,spool_index28,spool_index28,spool_index28,
// old actua	spool_index29,spool_index29,spool_index29,spool_index29,spool_index29,spool_index29,spool_index29,spool_index29,
// old actua	spool_index30,spool_index30,spool_index30,spool_index30,spool_index30,spool_index30,spool_index30,spool_index30,
// old actua	spool_index31,spool_index31,spool_index31,spool_index31,spool_index31,spool_index31,spool_index31,spool_index31,
// old actua	spool_index32,spool_index32,spool_index32,spool_index32,spool_index32,spool_index32,spool_index32,spool_index32,
// old actua	spool_index33,spool_index33,spool_index33,spool_index33,spool_index33,spool_index33,spool_index33,spool_index33,
// old actua	spool_index34,spool_index34,spool_index34,spool_index34,spool_index34,spool_index34,spool_index34,spool_index34,
// old actua	spool_index35,spool_index35,spool_index35,spool_index35,spool_index35,spool_index35,spool_index35,spool_index35,
// old actua	spool_index36,spool_index36,spool_index36,spool_index36,spool_index36,spool_index36,spool_index36,spool_index36,
// old actua	spool_index37,spool_index37,spool_index37,spool_index37,spool_index37,spool_index37,spool_index37,spool_index37,
// old actua	spool_index38,spool_index38,spool_index38,spool_index38,spool_index38,spool_index38,spool_index38,spool_index38,
// old actua	spool_index39,spool_index39,spool_index39,spool_index39,spool_index39,spool_index39,spool_index39,spool_index39,
// old actua	spool_index40,spool_index40,spool_index40,spool_index40,spool_index40,spool_index40,spool_index40,spool_index40,
// old actua	spool_index41,spool_index41,spool_index41,spool_index41,spool_index41,spool_index41,spool_index41,spool_index41,
// old actua	spool_index42,spool_index42,spool_index42,spool_index42,spool_index42,spool_index42,spool_index42,spool_index42,
// old actua	spool_index43,spool_index43,spool_index43,spool_index43,spool_index43,spool_index43,spool_index43,spool_index43,
// old actua	spool_index44,spool_index44,spool_index44,spool_index44,spool_index44,spool_index44,spool_index44,spool_index44,
// old actua	spool_index45,spool_index45,spool_index45,spool_index45,spool_index45,spool_index45,spool_index45,spool_index45,
// old actua	
// old actua			      };
// old actua
// old actua
// old actua	long	spool_index_small[]={
// old actua
// old actua	spool_index1s,spool_index1s,spool_index1s,spool_index1s,spool_index1s,spool_index1s,spool_index1s,spool_index1s,
// old actua	spool_index2s,spool_index2s,spool_index2s,spool_index2s,spool_index2s,spool_index2s,spool_index2s,spool_index2s,
// old actua	spool_index3s,spool_index3s,spool_index3s,spool_index3s,spool_index3s,spool_index3s,spool_index3s,spool_index3s,
// old actua	spool_index4s,spool_index4s,spool_index4s,spool_index4s,spool_index4s,spool_index4s,spool_index4s,spool_index4s,
// old actua	spool_index5s,spool_index5s,spool_index5s,spool_index5s,spool_index5s,spool_index5s,spool_index5s,spool_index5s,
// old actua	spool_index6s,spool_index6s,spool_index6s,spool_index6s,spool_index6s,spool_index6s,spool_index6s,spool_index6s,
// old actua	spool_index7s,spool_index7s,spool_index7s,spool_index7s,spool_index7s,spool_index7s,spool_index7s,spool_index7s,
// old actua	spool_index8s,spool_index8s,spool_index8s,spool_index8s,spool_index8s,spool_index8s,spool_index8s,spool_index8s,
// old actua	spool_index9s,spool_index9s,spool_index9s,spool_index9s,spool_index9s,spool_index9s,spool_index9s,spool_index9s,
// old actua	spool_index10s,spool_index10s,spool_index10s,spool_index10s,spool_index10s,spool_index10s,spool_index10s,spool_index10s,
// old actua	spool_index11s,spool_index11s,spool_index11s,spool_index11s,spool_index11s,spool_index11s,spool_index11s,spool_index11s,
// old actua	spool_index12s,spool_index12s,spool_index12s,spool_index12s,spool_index12s,spool_index12s,spool_index12s,spool_index12s,
// old actua	spool_index13s,spool_index13s,spool_index13s,spool_index13s,spool_index13s,spool_index13s,spool_index13s,spool_index13s,
// old actua	spool_index14s,spool_index14s,spool_index14s,spool_index14s,spool_index14s,spool_index14s,spool_index14s,spool_index14s,
// old actua	spool_index15s,spool_index15s,spool_index15s,spool_index15s,spool_index15s,spool_index15s,spool_index15s,spool_index15s,
// old actua	spool_index16s,spool_index16s,spool_index16s,spool_index16s,spool_index16s,spool_index16s,spool_index16s,spool_index16s,
// old actua	spool_index17s,spool_index17s,spool_index17s,spool_index17s,spool_index17s,spool_index17s,spool_index17s,spool_index17s,
// old actua	spool_index18s,spool_index18s,spool_index18s,spool_index18s,spool_index18s,spool_index18s,spool_index18s,spool_index18s,
// old actua	spool_index19s,spool_index19s,spool_index19s,spool_index19s,spool_index19s,spool_index19s,spool_index19s,spool_index19s,
// old actua	spool_index20s,spool_index20s,spool_index20s,spool_index20s,spool_index20s,spool_index20s,spool_index20s,spool_index20s,
// old actua	spool_index21s,spool_index21s,spool_index21s,spool_index21s,spool_index21s,spool_index21s,spool_index21s,spool_index21s,
// old actua	spool_index22s,spool_index22s,spool_index22s,spool_index22s,spool_index22s,spool_index22s,spool_index22s,spool_index22s,
// old actua	spool_index23s,spool_index23s,spool_index23s,spool_index23s,spool_index23s,spool_index23s,spool_index23s,spool_index23s,
// old actua	spool_index24s,spool_index24s,spool_index24s,spool_index24s,spool_index24s,spool_index24s,spool_index24s,spool_index24s,
// old actua	spool_index25s,spool_index25s,spool_index25s,spool_index25s,spool_index25s,spool_index25s,spool_index25s,spool_index25s,
// old actua	spool_index26s,spool_index26s,spool_index26s,spool_index26s,spool_index26s,spool_index26s,spool_index26s,spool_index26s,
// old actua	spool_index27s,spool_index27s,spool_index27s,spool_index27s,spool_index27s,spool_index27s,spool_index27s,spool_index27s,
// old actua	spool_index28s,spool_index28s,spool_index28s,spool_index28s,spool_index28s,spool_index28s,spool_index28s,spool_index28s,
// old actua	spool_index29s,spool_index29s,spool_index29s,spool_index29s,spool_index29s,spool_index29s,spool_index29s,spool_index29s,
// old actua	spool_index30s,spool_index30s,spool_index30s,spool_index30s,spool_index30s,spool_index30s,spool_index30s,spool_index30s,
// old actua	spool_index31s,spool_index31s,spool_index31s,spool_index31s,spool_index31s,spool_index31s,spool_index31s,spool_index31s,
// old actua	spool_index32s,spool_index32s,spool_index32s,spool_index32s,spool_index32s,spool_index32s,spool_index32s,spool_index32s,
// old actua	spool_index33s,spool_index33s,spool_index33s,spool_index33s,spool_index33s,spool_index33s,spool_index33s,spool_index33s,
// old actua	spool_index34s,spool_index34s,spool_index34s,spool_index34s,spool_index34s,spool_index34s,spool_index34s,spool_index34s,
// old actua	spool_index35s,spool_index35s,spool_index35s,spool_index35s,spool_index35s,spool_index35s,spool_index35s,spool_index35s,
// old actua	spool_index36s,spool_index36s,spool_index36s,spool_index36s,spool_index36s,spool_index36s,spool_index36s,spool_index36s,
// old actua	spool_index37s,spool_index37s,spool_index37s,spool_index37s,spool_index37s,spool_index37s,spool_index37s,spool_index37s,
// old actua	spool_index38s,spool_index38s,spool_index38s,spool_index38s,spool_index38s,spool_index38s,spool_index38s,spool_index38s,
// old actua	spool_index39s,spool_index39s,spool_index39s,spool_index39s,spool_index39s,spool_index39s,spool_index39s,spool_index39s,
// old actua	spool_index40s,spool_index40s,spool_index40s,spool_index40s,spool_index40s,spool_index40s,spool_index40s,spool_index40s,
// old actua	spool_index41s,spool_index41s,spool_index41s,spool_index41s,spool_index41s,spool_index41s,spool_index41s,spool_index41s,
// old actua	spool_index42s,spool_index42s,spool_index42s,spool_index42s,spool_index42s,spool_index42s,spool_index42s,spool_index42s,
// old actua	spool_index43s,spool_index43s,spool_index43s,spool_index43s,spool_index43s,spool_index43s,spool_index43s,spool_index43s,
// old actua	spool_index44s,spool_index44s,spool_index44s,spool_index44s,spool_index44s,spool_index44s,spool_index44s,spool_index44s,
// old actua	spool_index45s,spool_index45s,spool_index45s,spool_index45s,spool_index45s,spool_index45s,spool_index45s,spool_index45s,
// old actua	
// old actua			      };
// old actua
// old actua
// old actua
// old actua
// old actua
// old actua
// old actua
// old actua
// old actua
// old actua
// old actua
// old actua
// old actua
// old actua
// old actua
// old actuasprite		sprite_table_small[]={				       	 
// old actua								 
// old actua		{
// old actua		sprite1width_s,sprite1height_s,sprite1Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite1awidth_s,sprite1aheight_s,sprite1aBitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite1bwidth_s,sprite1bheight_s,sprite1bBitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite2width_s,sprite2height_s,sprite2Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite3width_s,sprite3height_s,sprite3Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite4width_s,sprite4height_s,sprite4Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite5width_s,sprite5height_s,sprite5Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite6width_s,sprite6height_s,sprite6Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite7width_s,sprite7height_s,sprite7Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite8width_s,sprite8height_s,sprite8Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite9width_s,sprite9height_s,sprite9Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite10width_s,sprite10height_s,sprite10Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite11width_s,sprite11height_s,sprite11Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite12width_s,sprite12height_s,sprite12Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite13width_s,sprite13height_s,sprite13Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite14width_s,sprite14height_s,sprite14Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite15width_s,sprite15height_s,sprite15Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite16width_s,sprite16height_s,sprite16Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite17width_s,sprite17height_s,sprite17Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite18width_s,sprite18height_s,sprite18Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite19width_s,sprite19height_s,sprite19Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite20width_s,sprite20height_s,sprite20Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite21width_s,sprite21height_s,sprite21Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite22width_s,sprite22height_s,sprite22Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite23width_s,sprite23height_s,sprite23Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite24width_s,sprite24height_s,sprite24Bitmap_s,
// old actua		},
// old actua	
// old actua		{
// old actua		sprite25width_s,sprite25height_s,sprite25Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite26width_s,sprite26height_s,sprite26Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite27width_s,sprite27height_s,sprite27Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite28width_s,sprite28height_s,sprite28Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite29width_s,sprite29height_s,sprite29Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite30width_s,sprite30height_s,sprite30Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite31width_s,sprite31height_s,sprite31Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite32width_s,sprite32height_s,sprite32Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite33width_s,sprite33height_s,sprite33Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite34width_s,sprite34height_s,sprite34Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite35width_s,sprite35height_s,sprite35Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite36width_s,sprite36height_s,sprite36Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite37width_s,sprite37height_s,sprite37Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite38width_s,sprite38height_s,sprite38Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite39width_s,sprite39height_s,sprite39Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite40width_s,sprite40height_s,sprite40Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite41width_s,sprite41height_s,sprite41Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite42width_s,sprite42height_s,sprite42Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite43width_s,sprite43height_s,sprite43Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite44width_s,sprite44height_s,sprite44Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite45width_s,sprite45height_s,sprite45Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite46width_s,sprite46height_s,sprite46Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite47width_s,sprite47height_s,sprite47Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite48width_s,sprite48height_s,sprite48Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite49width_s,sprite49height_s,sprite49Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite50width_s,sprite50height_s,sprite50Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite51width_s,sprite51height_s,sprite51Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite52width_s,sprite52height_s,sprite52Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite53width_s,sprite53height_s,sprite53Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite54width_s,sprite54height_s,sprite54Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite55width_s,sprite55height_s,sprite55Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite55Bwidth_s,sprite55Bheight_s,sprite55BBitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite55Cwidth_s,sprite55Cheight_s,sprite55CBitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite56width_s,sprite56height_s,sprite56Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite57width_s,sprite57height_s,sprite57Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite58width_s,sprite58height_s,sprite58Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite59width_s,sprite59height_s,sprite59Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite60width_s,sprite60height_s,sprite60Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite61width_s,sprite61height_s,sprite61Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite62width_s,sprite62height_s,sprite62Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite63width_s,sprite63height_s,sprite63Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite64width_s,sprite64height_s,sprite64Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite65width_s,sprite65height_s,sprite65Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite66width_s,sprite66height_s,sprite66Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite67width_s,sprite67height_s,sprite67Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite68width_s,sprite68height_s,sprite68Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite69width_s,sprite69height_s,sprite69Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite70width_s,sprite70height_s,sprite70Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite71width_s,sprite71height_s,sprite71Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite72width_s,sprite72height_s,sprite72Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite73width_s,sprite73height_s,sprite73Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite74width_s,sprite74height_s,sprite74Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite75width_s,sprite75height_s,sprite75Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite76width_s,sprite76height_s,sprite76Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite77width_s,sprite77height_s,sprite77Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite78width_s,sprite78height_s,sprite78Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite79width_s,sprite79height_s,sprite79Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite80width_s,sprite80height_s,sprite80Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite81width_s,sprite81height_s,sprite81Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite82width_s,sprite82height_s,sprite82Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite83width_s,sprite83height_s,sprite83Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite84width_s,sprite84height_s,sprite84Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite85width_s,sprite85height_s,sprite85Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite86width_s,sprite86height_s,sprite86Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite87width_s,sprite87height_s,sprite87Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite88width_s,sprite88height_s,sprite88Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite89width_s,sprite89height_s,sprite89Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite90width_s,sprite90height_s,sprite90Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite91width_s,sprite91height_s,sprite91Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite92width_s,sprite92height_s,sprite92Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite93width_s,sprite93height_s,sprite93Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite94width_s,sprite94height_s,sprite94Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite95width_s,sprite95height_s,sprite95Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite96width_s,sprite96height_s,sprite96Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite97width_s,sprite97height_s,sprite97Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite98width_s,sprite98height_s,sprite98Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite99width_s,sprite99height_s,sprite99Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite100width_s,sprite100height_s,sprite100Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite101width_s,sprite101height_s,sprite101Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite102width_s,sprite102height_s,sprite102Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite103width_s,sprite103height_s,sprite103Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite104width_s,sprite104height_s,sprite104Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite105width_s,sprite105height_s,sprite105Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite106width_s,sprite106height_s,sprite106Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite107width_s,sprite107height_s,sprite107Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite108width_s,sprite108height_s,sprite108Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite109width_s,sprite109height_s,sprite109Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite110width_s,sprite110height_s,sprite110Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite111width_s,sprite111height_s,sprite111Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite112width_s,sprite112height_s,sprite112Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite113width_s,sprite113height_s,sprite113Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite114width_s,sprite114height_s,sprite114Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite115width_s,sprite115height_s,sprite115Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite116width_s,sprite116height_s,sprite116Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite117width_s,sprite117height_s,sprite117Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite118width_s,sprite118height_s,sprite118Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite119width_s,sprite119height_s,sprite119Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite120width_s,sprite120height_s,sprite120Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite121width_s,sprite121height_s,sprite121Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite122width_s,sprite122height_s,sprite122Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite123width_s,sprite123height_s,sprite123Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite124width_s,sprite124height_s,sprite124Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite125width_s,sprite125height_s,sprite125Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite126width_s,sprite126height_s,sprite126Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite127width_s,sprite127height_s,sprite127Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite128width_s,sprite128height_s,sprite128Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite129width_s,sprite129height_s,sprite129Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite130width_s,sprite130height_s,sprite130Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite131width_s,sprite131height_s,sprite131Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite132width_s,sprite132height_s,sprite132Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite133width_s,sprite133height_s,sprite133Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite134width_s,sprite134height_s,sprite134Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite135width_s,sprite135height_s,sprite135Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite136width_s,sprite136height_s,sprite136Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite137width_s,sprite137height_s,sprite137Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite138width_s,sprite138height_s,sprite138Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite139width_s,sprite139height_s,sprite139Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite140width_s,sprite140height_s,sprite140Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite141width_s,sprite141height_s,sprite141Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite142width_s,sprite142height_s,sprite142Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite143width_s,sprite143height_s,sprite143Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite144width_s,sprite144height_s,sprite144Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite145width_s,sprite145height_s,sprite145Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite146width_s,sprite146height_s,sprite146Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite147width_s,sprite147height_s,sprite147Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite148width_s,sprite148height_s,sprite148Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite149width_s,sprite149height_s,sprite149Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite150width_s,sprite150height_s,sprite150Bitmap_s,
// old actua		},
// old actua
// old actua//		{
// old actua//		sprite151width_s,sprite151height_s,sprite151Bitmap_s,
// old actua//		},
// old actua//
// old actua//		{
// old actua//		sprite152width_s,sprite152height_s,sprite152Bitmap_s,
// old actua//		},
// old actua
// old actua		{
// old actua		sprite_S62width_s,sprite_S62height_s,sprite_S62Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S63width_s,sprite_S63height_s,sprite_S63Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S64width_s,sprite_S64height_s,sprite_S64Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S65width_s,sprite_S65height_s,sprite_S65Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S66width_s,sprite_S66height_s,sprite_S66Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S67width_s,sprite_S67height_s,sprite_S67Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S68width_s,sprite_S68height_s,sprite_S68Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S69width_s,sprite_S69height_s,sprite_S69Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S70width_s,sprite_S70height_s,sprite_S70Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S71width_s,sprite_S71height_s,sprite_S71Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S72width_s,sprite_S72height_s,sprite_S72Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S73width_s,sprite_S73height_s,sprite_S73Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S74width_s,sprite_S74height_s,sprite_S74Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S75width_s,sprite_S75height_s,sprite_S75Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S76width_s,sprite_S76height_s,sprite_S76Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S77width_s,sprite_S77height_s,sprite_S77Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S78width_s,sprite_S78height_s,sprite_S78Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S79width_s,sprite_S79height_s,sprite_S79Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S80width_s,sprite_S80height_s,sprite_S80Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S81width_s,sprite_S81height_s,sprite_S81Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S82width_s,sprite_S82height_s,sprite_S82Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S83width_s,sprite_S83height_s,sprite_S83Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S84width_s,sprite_S84height_s,sprite_S84Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S85width_s,sprite_S85height_s,sprite_S85Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S86width_s,sprite_S86height_s,sprite_S86Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S87width_s,sprite_S87height_s,sprite_S87Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S88width_s,sprite_S88height_s,sprite_S88Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S89width_s,sprite_S89height_s,sprite_S89Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S90width_s,sprite_S90height_s,sprite_S90Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S91width_s,sprite_S91height_s,sprite_S91Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S92width_s,sprite_S92height_s,sprite_S92Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S93width_s,sprite_S93height_s,sprite_S93Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S94width_s,sprite_S94height_s,sprite_S94Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S95width_s,sprite_S95height_s,sprite_S95Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S96width_s,sprite_S96height_s,sprite_S96Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S97width_s,sprite_S97height_s,sprite_S97Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S98width_s,sprite_S98height_s,sprite_S98Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S99width_s,sprite_S99height_s,sprite_S99Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S100width_s,sprite_S100height_s,sprite_S100Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S101width_s,sprite_S101height_s,sprite_S101Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S102width_s,sprite_S102height_s,sprite_S102Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S103width_s,sprite_S103height_s,sprite_S103Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S104width_s,sprite_S104height_s,sprite_S104Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S105width_s,sprite_S105height_s,sprite_S105Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S106width_s,sprite_S106height_s,sprite_S106Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S107width_s,sprite_S107height_s,sprite_S107Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S108width_s,sprite_S108height_s,sprite_S108Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S109width_s,sprite_S109height_s,sprite_S109Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S110width_s,sprite_S110height_s,sprite_S110Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S111width_s,sprite_S111height_s,sprite_S111Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S112width_s,sprite_S112height_s,sprite_S112Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S113width_s,sprite_S113height_s,sprite_S113Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S114width_s,sprite_S114height_s,sprite_S114Bitmap_s,
// old actua		},
// old actua 
// old actua		{
// old actua		sprite_S115width_s,sprite_S115height_s,sprite_S115Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S116width_s,sprite_S116height_s,sprite_S116Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S117width_s,sprite_S117height_s,sprite_S117Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S118width_s,sprite_S118height_s,sprite_S118Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S119width_s,sprite_S119height_s,sprite_S119Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S120width_s,sprite_S120height_s,sprite_S120Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S121width_s,sprite_S121height_s,sprite_S121Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S122width_s,sprite_S122height_s,sprite_S122Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S123width_s,sprite_S123height_s,sprite_S123Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S124width_s,sprite_S124height_s,sprite_S124Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S125width_s,sprite_S125height_s,sprite_S125Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S126width_s,sprite_S126height_s,sprite_S126Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S127width_s,sprite_S127height_s,sprite_S127Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S128width_s,sprite_S128height_s,sprite_S128Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S129width_s,sprite_S129height_s,sprite_S129Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S130width_s,sprite_S130height_s,sprite_S130Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S131width_s,sprite_S131height_s,sprite_S131Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S132width_s,sprite_S132height_s,sprite_S132Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S133width_s,sprite_S133height_s,sprite_S133Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S134width_s,sprite_S134height_s,sprite_S134Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S135width_s,sprite_S135height_s,sprite_S135Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S136width_s,sprite_S136height_s,sprite_S136Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S137width_s,sprite_S137height_s,sprite_S137Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S138width_s,sprite_S138height_s,sprite_S138Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S139width_s,sprite_S139height_s,sprite_S139Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S140width_s,sprite_S140height_s,sprite_S140Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S141width_s,sprite_S141height_s,sprite_S141Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S142width_s,sprite_S142height_s,sprite_S142Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S143width_s,sprite_S143height_s,sprite_S143Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S144width_s,sprite_S144height_s,sprite_S144Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S145width_s,sprite_S145height_s,sprite_S145Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S146width_s,sprite_S146height_s,sprite_S146Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S147width_s,sprite_S147height_s,sprite_S147Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S148width_s,sprite_S148height_s,sprite_S148Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S149width_s,sprite_S149height_s,sprite_S149Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S150width_s,sprite_S150height_s,sprite_S150Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S151width_s,sprite_S151height_s,sprite_S151Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S152width_s,sprite_S152height_s,sprite_S152Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S153width_s,sprite_S153height_s,sprite_S153Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S154width_s,sprite_S154height_s,sprite_S154Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S155width_s,sprite_S155height_s,sprite_S155Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S156width_s,sprite_S156height_s,sprite_S156Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S157width_s,sprite_S157height_s,sprite_S157Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S158width_s,sprite_S158height_s,sprite_S158Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S159width_s,sprite_S159height_s,sprite_S159Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S160width_s,sprite_S160height_s,sprite_S160Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S161width_s,sprite_S161height_s,sprite_S161Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S162width_s,sprite_S162height_s,sprite_S162Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S163width_s,sprite_S163height_s,sprite_S163Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S164width_s,sprite_S164height_s,sprite_S164Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S165width_s,sprite_S165height_s,sprite_S165Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S166width_s,sprite_S166height_s,sprite_S166Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S167width_s,sprite_S167height_s,sprite_S167Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S168width_s,sprite_S168height_s,sprite_S168Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S169width_s,sprite_S169height_s,sprite_S169Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S170width_s,sprite_S170height_s,sprite_S170Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S171width_s,sprite_S171height_s,sprite_S171Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S172width_s,sprite_S172height_s,sprite_S172Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S173width_s,sprite_S173height_s,sprite_S173Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S174width_s,sprite_S174height_s,sprite_S174Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S175width_s,sprite_S175height_s,sprite_S175Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S176width_s,sprite_S176height_s,sprite_S176Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S177width_s,sprite_S177height_s,sprite_S177Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S178width_s,sprite_S178height_s,sprite_S178Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S179width_s,sprite_S179height_s,sprite_S179Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S180width_s,sprite_S180height_s,sprite_S180Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S181width_s,sprite_S181height_s,sprite_S181Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S182width_s,sprite_S182height_s,sprite_S182Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S183width_s,sprite_S183height_s,sprite_S183Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S184width_s,sprite_S184height_s,sprite_S184Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S185width_s,sprite_S185height_s,sprite_S185Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S186width_s,sprite_S186height_s,sprite_S186Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S187width_s,sprite_S187height_s,sprite_S187Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S188width_s,sprite_S188height_s,sprite_S188Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S189width_s,sprite_S189height_s,sprite_S189Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S190width_s,sprite_S190height_s,sprite_S190Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S191width_s,sprite_S191height_s,sprite_S191Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S192width_s,sprite_S192height_s,sprite_S192Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S193width_s,sprite_S193height_s,sprite_S193Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S194width_s,sprite_S194height_s,sprite_S194Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S195width_s,sprite_S195height_s,sprite_S195Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S196width_s,sprite_S196height_s,sprite_S196Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S197width_s,sprite_S197height_s,sprite_S197Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S198width_s,sprite_S198height_s,sprite_S198Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S199width_s,sprite_S199height_s,sprite_S199Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S200width_s,sprite_S200height_s,sprite_S200Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S201width_s,sprite_S201height_s,sprite_S201Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S202width_s,sprite_S202height_s,sprite_S202Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S203width_s,sprite_S203height_s,sprite_S203Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S204width_s,sprite_S204height_s,sprite_S204Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S205width_s,sprite_S205height_s,sprite_S205Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S206width_s,sprite_S206height_s,sprite_S206Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S207width_s,sprite_S207height_s,sprite_S207Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S208width_s,sprite_S208height_s,sprite_S208Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S209width_s,sprite_S209height_s,sprite_S209Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S210width_s,sprite_S210height_s,sprite_S210Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S211width_s,sprite_S211height_s,sprite_S211Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S212width_s,sprite_S212height_s,sprite_S212Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S213width_s,sprite_S213height_s,sprite_S213Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S214width_s,sprite_S214height_s,sprite_S214Bitmap_s,
// old actua		},
// old actua 
// old actua		{
// old actua		sprite_S215width_s,sprite_S215height_s,sprite_S215Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S216width_s,sprite_S216height_s,sprite_S216Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S217width_s,sprite_S217height_s,sprite_S217Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S218width_s,sprite_S218height_s,sprite_S218Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S219width_s,sprite_S219height_s,sprite_S219Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S220width_s,sprite_S220height_s,sprite_S220Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S221width_s,sprite_S221height_s,sprite_S221Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S222width_s,sprite_S222height_s,sprite_S222Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S223width_s,sprite_S223height_s,sprite_S223Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S224width_s,sprite_S224height_s,sprite_S224Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S225width_s,sprite_S225height_s,sprite_S225Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S226width_s,sprite_S226height_s,sprite_S226Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S227width_s,sprite_S227height_s,sprite_S227Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S228width_s,sprite_S228height_s,sprite_S228Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S229width_s,sprite_S229height_s,sprite_S229Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S230width_s,sprite_S230height_s,sprite_S230Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S231width_s,sprite_S231height_s,sprite_S231Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S232width_s,sprite_S232height_s,sprite_S232Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S233width_s,sprite_S233height_s,sprite_S233Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S234width_s,sprite_S234height_s,sprite_S234Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S235width_s,sprite_S235height_s,sprite_S235Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S236width_s,sprite_S236height_s,sprite_S236Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S237width_s,sprite_S237height_s,sprite_S237Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S238width_s,sprite_S238height_s,sprite_S238Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S239width_s,sprite_S239height_s,sprite_S239Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S240width_s,sprite_S240height_s,sprite_S240Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S241width_s,sprite_S241height_s,sprite_S241Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S242width_s,sprite_S242height_s,sprite_S242Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S243width_s,sprite_S243height_s,sprite_S243Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S244width_s,sprite_S244height_s,sprite_S244Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S245width_s,sprite_S245height_s,sprite_S245Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S246width_s,sprite_S246height_s,sprite_S246Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S247width_s,sprite_S247height_s,sprite_S247Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S248width_s,sprite_S248height_s,sprite_S248Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S249width_s,sprite_S249height_s,sprite_S249Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S250width_s,sprite_S250height_s,sprite_S250Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S251width_s,sprite_S251height_s,sprite_S251Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S252width_s,sprite_S252height_s,sprite_S252Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S253width_s,sprite_S253height_s,sprite_S253Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S254width_s,sprite_S254height_s,sprite_S254Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S255width_s,sprite_S255height_s,sprite_S255Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S256width_s,sprite_S256height_s,sprite_S256Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S257width_s,sprite_S257height_s,sprite_S257Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S258width_s,sprite_S258height_s,sprite_S258Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S259width_s,sprite_S259height_s,sprite_S259Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S260width_s,sprite_S260height_s,sprite_S260Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S261width_s,sprite_S261height_s,sprite_S261Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S262width_s,sprite_S262height_s,sprite_S262Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S263width_s,sprite_S263height_s,sprite_S263Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S264width_s,sprite_S264height_s,sprite_S264Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S265width_s,sprite_S265height_s,sprite_S265Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S266width_s,sprite_S266height_s,sprite_S266Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S267width_s,sprite_S267height_s,sprite_S267Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S268width_s,sprite_S268height_s,sprite_S268Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S269width_s,sprite_S269height_s,sprite_S269Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S270width_s,sprite_S270height_s,sprite_S270Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S271width_s,sprite_S271height_s,sprite_S271Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S272width_s,sprite_S272height_s,sprite_S272Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S273width_s,sprite_S273height_s,sprite_S273Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S274width_s,sprite_S274height_s,sprite_S274Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S275width_s,sprite_S275height_s,sprite_S275Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S276width_s,sprite_S276height_s,sprite_S276Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S277width_s,sprite_S277height_s,sprite_S277Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S278width_s,sprite_S278height_s,sprite_S278Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S279width_s,sprite_S279height_s,sprite_S279Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S280width_s,sprite_S280height_s,sprite_S280Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S281width_s,sprite_S281height_s,sprite_S281Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S282width_s,sprite_S282height_s,sprite_S282Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S283width_s,sprite_S283height_s,sprite_S283Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S284width_s,sprite_S284height_s,sprite_S284Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S285width_s,sprite_S285height_s,sprite_S285Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S286width_s,sprite_S286height_s,sprite_S286Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S287width_s,sprite_S287height_s,sprite_S287Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S288width_s,sprite_S288height_s,sprite_S288Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S289width_s,sprite_S289height_s,sprite_S289Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S290width_s,sprite_S290height_s,sprite_S290Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S291width_s,sprite_S291height_s,sprite_S291Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S292width_s,sprite_S292height_s,sprite_S292Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S293width_s,sprite_S293height_s,sprite_S293Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S294width_s,sprite_S294height_s,sprite_S294Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S295width_s,sprite_S295height_s,sprite_S295Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S296width_s,sprite_S296height_s,sprite_S296Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S297width_s,sprite_S297height_s,sprite_S297Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S298width_s,sprite_S298height_s,sprite_S298Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S299width_s,sprite_S299height_s,sprite_S299Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S300width_s,sprite_S300height_s,sprite_S300Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S301width_s,sprite_S301height_s,sprite_S301Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S302width_s,sprite_S302height_s,sprite_S302Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S303width_s,sprite_S303height_s,sprite_S303Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S304width_s,sprite_S304height_s,sprite_S304Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S305width_s,sprite_S305height_s,sprite_S305Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S306width_s,sprite_S306height_s,sprite_S306Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S307width_s,sprite_S307height_s,sprite_S307Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S308width_s,sprite_S308height_s,sprite_S308Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S309width_s,sprite_S309height_s,sprite_S309Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S310width_s,sprite_S310height_s,sprite_S310Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S311width_s,sprite_S311height_s,sprite_S311Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S312width_s,sprite_S312height_s,sprite_S312Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S313width_s,sprite_S313height_s,sprite_S313Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S314width_s,sprite_S314height_s,sprite_S314Bitmap_s,
// old actua		},
// old actua 
// old actua		{
// old actua		sprite_S315width_s,sprite_S315height_s,sprite_S315Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S316width_s,sprite_S316height_s,sprite_S316Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S317width_s,sprite_S317height_s,sprite_S317Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S318width_s,sprite_S318height_s,sprite_S318Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S319width_s,sprite_S319height_s,sprite_S319Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S320width_s,sprite_S320height_s,sprite_S320Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S321width_s,sprite_S321height_s,sprite_S321Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S322width_s,sprite_S322height_s,sprite_S322Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S323width_s,sprite_S323height_s,sprite_S323Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S324width_s,sprite_S324height_s,sprite_S324Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S325width_s,sprite_S325height_s,sprite_S325Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S326width_s,sprite_S326height_s,sprite_S326Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S327width_s,sprite_S327height_s,sprite_S327Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S328width_s,sprite_S328height_s,sprite_S328Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S329width_s,sprite_S329height_s,sprite_S329Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S330width_s,sprite_S330height_s,sprite_S330Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S331width_s,sprite_S331height_s,sprite_S331Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S332width_s,sprite_S332height_s,sprite_S332Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S333width_s,sprite_S333height_s,sprite_S333Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S333width_s,sprite_S333height_s,sprite_S333Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S334width_s,sprite_S334height_s,sprite_S334Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S335width_s,sprite_S335height_s,sprite_S335Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S336width_s,sprite_S336height_s,sprite_S336Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S337width_s,sprite_S337height_s,sprite_S337Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S338width_s,sprite_S338height_s,sprite_S338Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S339width_s,sprite_S339height_s,sprite_S339Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S340width_s,sprite_S340height_s,sprite_S340Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S341width_s,sprite_S341height_s,sprite_S341Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S342width_s,sprite_S342height_s,sprite_S342Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S343width_s,sprite_S343height_s,sprite_S343Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S344width_s,sprite_S344height_s,sprite_S344Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S345width_s,sprite_S345height_s,sprite_S345Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S346width_s,sprite_S346height_s,sprite_S346Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S347width_s,sprite_S347height_s,sprite_S347Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S348width_s,sprite_S348height_s,sprite_S348Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S349width_s,sprite_S349height_s,sprite_S349Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S350width_s,sprite_S350height_s,sprite_S350Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S351width_s,sprite_S351height_s,sprite_S351Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S352width_s,sprite_S352height_s,sprite_S352Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S353width_s,sprite_S353height_s,sprite_S353Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S354width_s,sprite_S354height_s,sprite_S354Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S355width_s,sprite_S355height_s,sprite_S355Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S356width_s,sprite_S356height_s,sprite_S356Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S357width_s,sprite_S357height_s,sprite_S357Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S358width_s,sprite_S358height_s,sprite_S358Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S359width_s,sprite_S359height_s,sprite_S359Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S360width_s,sprite_S360height_s,sprite_S360Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S361width_s,sprite_S361height_s,sprite_S361Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S362width_s,sprite_S362height_s,sprite_S362Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S363width_s,sprite_S363height_s,sprite_S363Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S364width_s,sprite_S364height_s,sprite_S364Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S365width_s,sprite_S365height_s,sprite_S365Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S366width_s,sprite_S366height_s,sprite_S366Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S367width_s,sprite_S367height_s,sprite_S367Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S368width_s,sprite_S368height_s,sprite_S368Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S369width_s,sprite_S369height_s,sprite_S369Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S370width_s,sprite_S370height_s,sprite_S370Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S371width_s,sprite_S371height_s,sprite_S371Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S372width_s,sprite_S372height_s,sprite_S372Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S373width_s,sprite_S373height_s,sprite_S373Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S374width_s,sprite_S374height_s,sprite_S374Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S375width_s,sprite_S375height_s,sprite_S375Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S376width_s,sprite_S376height_s,sprite_S376Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S377width_s,sprite_S377height_s,sprite_S377Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S378width_s,sprite_S378height_s,sprite_S378Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S379width_s,sprite_S379height_s,sprite_S379Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S380width_s,sprite_S380height_s,sprite_S380Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S381width_s,sprite_S381height_s,sprite_S381Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S382width_s,sprite_S382height_s,sprite_S382Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S383width_s,sprite_S383height_s,sprite_S383Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S384width_s,sprite_S384height_s,sprite_S384Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S385width_s,sprite_S385height_s,sprite_S385Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S386width_s,sprite_S386height_s,sprite_S386Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S387width_s,sprite_S387height_s,sprite_S387Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S388width_s,sprite_S388height_s,sprite_S388Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S389width_s,sprite_S389height_s,sprite_S389Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S390width_s,sprite_S390height_s,sprite_S390Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S391width_s,sprite_S391height_s,sprite_S391Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S392width_s,sprite_S392height_s,sprite_S392Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S393width_s,sprite_S393height_s,sprite_S393Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S394width_s,sprite_S394height_s,sprite_S394Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S395width_s,sprite_S395height_s,sprite_S395Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S396width_s,sprite_S396height_s,sprite_S396Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S397width_s,sprite_S397height_s,sprite_S397Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S398width_s,sprite_S398height_s,sprite_S398Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S399width_s,sprite_S399height_s,sprite_S399Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S400width_s,sprite_S400height_s,sprite_S400Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S401width_s,sprite_S401height_s,sprite_S401Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S402width_s,sprite_S402height_s,sprite_S402Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S403width_s,sprite_S403height_s,sprite_S403Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S404width_s,sprite_S404height_s,sprite_S404Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S405width_s,sprite_S405height_s,sprite_S405Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S406width_s,sprite_S406height_s,sprite_S406Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S407width_s,sprite_S407height_s,sprite_S407Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S408width_s,sprite_S408height_s,sprite_S408Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S409width_s,sprite_S409height_s,sprite_S409Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S410width_s,sprite_S410height_s,sprite_S410Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S411width_s,sprite_S411height_s,sprite_S411Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S412width_s,sprite_S412height_s,sprite_S412Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S413width_s,sprite_S413height_s,sprite_S413Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S414width_s,sprite_S414height_s,sprite_S414Bitmap_s,
// old actua		},
// old actua 
// old actua		{
// old actua		sprite_S415width_s,sprite_S415height_s,sprite_S415Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S416width_s,sprite_S416height_s,sprite_S416Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S417width_s,sprite_S417height_s,sprite_S417Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S418width_s,sprite_S418height_s,sprite_S418Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S419width_s,sprite_S419height_s,sprite_S419Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_S420width_s,sprite_S420height_s,sprite_S420Bitmap_s,
// old actua		},
// old actua
// old actua		{
// old actua		sprite_999width_s,sprite_999height_s,sprite_999Bitmap_s,
// old actua		},
// old actua
// old actua		};
// old actua
// old actua		
// old actua
// old actua
// old actua
// old actua
#define		Scr100		0
#define		Scr85		1
#define		Scr85w		2
#define		Scr75		3
#define		Scr75w		4
#define		Scr65		5
#define		Scr65w		6
#define		Scr50		7
#define		Scr50w		8
#define		Scr40w		9

#define		SKY_OFF		0
#define		SKY_ON		1
#define		STADIA_OFF	0
#define		STADIA_ON	1
#define		PITCH_OFF	0
#define		PITCH_MED	1
#define		PITCH_ON	2
#define		PLAYERS_OFF	0
#define		PLAYERS_ON	1
#define		LINES_OFF	0
#define		LINES_ON	1
#define		SHADOWS_OFF	0
#define		SHADOWS_ON	1

detail_info 	detail_defaults[]=								// PC_speed
		{
		{SKY_ON , STADIA_OFF, PITCH_MED, PLAYERS_ON , LINES_OFF, SHADOWS_ON },		// 0
		{SKY_ON , STADIA_OFF, PITCH_MED, PLAYERS_ON , LINES_OFF, SHADOWS_ON },		// 1
		{SKY_ON , STADIA_OFF, PITCH_MED, PLAYERS_ON , LINES_OFF, SHADOWS_ON },		// 2
		{SKY_ON , STADIA_OFF, PITCH_MED, PLAYERS_ON , LINES_OFF, SHADOWS_ON },		// 3
		{SKY_ON , STADIA_OFF, PITCH_MED, PLAYERS_ON , LINES_OFF, SHADOWS_ON },		// 4
		{SKY_ON , STADIA_OFF, PITCH_MED, PLAYERS_ON , LINES_OFF, SHADOWS_ON },		// 5
		{SKY_ON , STADIA_OFF, PITCH_MED, PLAYERS_ON , LINES_OFF, SHADOWS_ON },		// 6
		{SKY_ON , STADIA_OFF, PITCH_MED, PLAYERS_ON , LINES_OFF, SHADOWS_ON },		// 7
		{SKY_ON , STADIA_OFF, PITCH_MED, PLAYERS_ON , LINES_OFF, SHADOWS_ON },		// 8
		{SKY_ON , STADIA_OFF, PITCH_MED, PLAYERS_ON , LINES_OFF, SHADOWS_ON },		// 9
		{SKY_ON , STADIA_OFF, PITCH_MED, PLAYERS_ON , LINES_OFF, SHADOWS_ON },		// 10
		{SKY_ON , STADIA_OFF, PITCH_MED, PLAYERS_ON , LINES_OFF, SHADOWS_ON },		// 11
		{SKY_ON , STADIA_ON , PITCH_MED, PLAYERS_OFF, LINES_OFF, SHADOWS_ON },		// 12
		{SKY_ON , STADIA_ON , PITCH_MED, PLAYERS_OFF, LINES_OFF, SHADOWS_ON },		// 13
		{SKY_ON , STADIA_ON , PITCH_MED, PLAYERS_OFF, LINES_OFF, SHADOWS_ON },		// 14
		{SKY_ON , STADIA_ON , PITCH_MED, PLAYERS_OFF, LINES_OFF, SHADOWS_ON },		// 15
		{SKY_ON , STADIA_ON , PITCH_MED, PLAYERS_OFF, LINES_OFF, SHADOWS_ON },		// 16
		{SKY_ON , STADIA_ON , PITCH_MED, PLAYERS_OFF, LINES_OFF, SHADOWS_ON },		// 17
		{SKY_ON , STADIA_ON , PITCH_MED, PLAYERS_ON , LINES_ON , SHADOWS_ON },		// 18
		{SKY_ON , STADIA_ON , PITCH_MED, PLAYERS_ON , LINES_ON , SHADOWS_ON },		// 19
		{SKY_ON , STADIA_ON , PITCH_MED, PLAYERS_ON , LINES_ON , SHADOWS_ON },		// 20
		{SKY_ON , STADIA_ON , PITCH_MED, PLAYERS_ON , LINES_ON , SHADOWS_ON },		// 21
		{SKY_ON , STADIA_ON , PITCH_MED, PLAYERS_ON , LINES_ON , SHADOWS_ON },		// 22
		{SKY_ON , STADIA_ON , PITCH_MED, PLAYERS_ON , LINES_ON , SHADOWS_ON },		// 23
		{SKY_ON , STADIA_ON , PITCH_MED, PLAYERS_ON , LINES_ON , SHADOWS_ON },		// 24
		{SKY_ON , STADIA_ON , PITCH_MED, PLAYERS_ON , LINES_ON , SHADOWS_ON },		// 25
		{SKY_ON , STADIA_ON , PITCH_MED, PLAYERS_ON , LINES_ON , SHADOWS_ON },		// 26
		{SKY_ON , STADIA_ON , PITCH_MED, PLAYERS_ON , LINES_ON , SHADOWS_ON },		// 27
		{SKY_ON , STADIA_ON , PITCH_MED, PLAYERS_ON , LINES_ON , SHADOWS_ON },		// 28
		{SKY_ON , STADIA_ON , PITCH_MED, PLAYERS_ON , LINES_ON , SHADOWS_ON },		// 29
		{SKY_ON , STADIA_ON , PITCH_MED, PLAYERS_ON , LINES_ON , SHADOWS_ON },		// 30
		{SKY_ON , STADIA_ON , PITCH_MED, PLAYERS_ON , LINES_ON , SHADOWS_ON },		// 31
		{SKY_ON , STADIA_ON , PITCH_MED, PLAYERS_ON , LINES_ON , SHADOWS_ON },		// 32
		};												  

short screen_defaults[]=
		{	

		{ Scr65w },									// 0
		{ Scr65w },									// 1
		{ Scr65w },									// 2
		{ Scr65w },									// 3
		{ Scr65w },									// 4
		{ Scr65w },									// 5
		{ Scr65w },									// 6
		{ Scr65w },									// 7
		{ Scr65w },									// 8
		{ Scr65w },									// 9
		{ Scr65w },									// 10
		{ Scr65w },									// 11
		{ Scr75	 },									// 12
		{ Scr75	 },									// 13
		{ Scr75	 },									// 14
		{ Scr75	 },									// 15
		{ Scr75	 },									// 16
		{ Scr75	 },									// 17
		{ Scr100 },									// 18
		{ Scr100 },									// 19
		{ Scr100 },									// 20
		{ Scr100 },									// 21
		{ Scr100 },									// 22
		{ Scr100 },									// 23
		{ Scr100 },									// 24
		{ Scr100 },									// 25
		{ Scr100 },									// 26
		{ Scr100 },									// 27
		{ Scr100 },									// 28
		{ Scr100 },									// 29
		{ Scr100 },									// 30
		{ Scr100 },									// 31
		{ Scr100 },									// 32
		};


	int	spin_y_offsets[]={
		15,17,20,23,25,28,30,33,10,10,9,9,10,11,12,
		};

// old actua		char	*formation_types[]={
// old actua			"4-3-3",
// old actua			"5-3-2",
// old actua			"6-3-1",
// old actua			"4-2-4",
// old actua			"5-1-4",
// old actua			"4-0-6",
// old actua			"3-1-6",
// old actua			"4-1-5",
// old actua			"5-2-3",
// old actua			"4-4-2",     };
// old actua					
// old actua		char	*sky_types[]={
// old actua			"OFF",
// old actua			"ON",	     
// old actua	
// old actua			  "OFF",
// old actua			  "ON",	     
// old actua			
// old actua			    "AUS",
// old actua			    "AN",
// old actua	
// old actua			      "OFF",
// old actua	        	      "ON",	     
// old actua	
// old actua			        "OFF",
// old actua			        "ON",	     
// old actua	
// old actua				  "AV",
// old actua				  "P|",	     
// old actua					};
// old actua					
// old actua		char	*sub_types[]={
// old actua			"OFF",
// old actua			"ON",	     
// old actua	
// old actua			  "OFF",
// old actua			  "ON",	     
// old actua			
// old actua			    "AUS",
// old actua			    "AN",
// old actua	
// old actua			      "OFF",
// old actua			      "ON",	     
// old actua	
// old actua			        "OFF",
// old actua			        "ON",	     
// old actua	
// old actua				  "AV",
// old actua				  "P|",	     
// old actua					};
// old actua					
// old actua		char	*stadium_types[]={
// old actua			"LOW",
// old actua			"HIGH",	     
// old actua	
// old actua			  "FAIBLE",
// old actua			  "ELEVE",
// old actua			    
// old actua			    "MIN",
// old actua			    "MAX",
// old actua	
// old actua			      "LOW",
// old actua			      "HIGH",	     
// old actua	
// old actua			        "FAIBLE",
// old actua			        "ELEVE",
// old actua	
// old actua				  "LOW",
// old actua				  "GROV",
// old actua	  			  "HIGH",
// old actua				  "FIN",	     
// old actua	
// old actua					};
// old actua		
// old actua		char	*pitch_types[]={
// old actua			"LOW",
// old actua			"MED",
// old actua			"HIGH",	     
// old actua	
// old actua			  "FAIBLE",
// old actua			  "MOYEN",
// old actua			  "ELEVE",
// old actua	
// old actua			    "MIN",
// old actua			    "MED",
// old actua			    "MAX",
// old actua	
// old actua			      "LOW",
// old actua			      "MED",
// old actua			      "HIGH",	     
// old actua	
// old actua			        "FAIBLE",
// old actua			        "MOYEN",
// old actua			        "ELEVE",
// old actua	
// old actua				  "LAV",
// old actua				  "MED",
// old actua				  "H{Y",	     
// old actua					};
// old actua	
// old actua					
// old actua		char	*wind_types[]={
// old actua			"OFF",
// old actua			"LOW",
// old actua			"MED",
// old actua			"HIGH",	     
// old actua	
// old actua		 	  "OFF",
// old actua			  "FAIBLE",
// old actua			  "MOYEN",
// old actua			  "ELEVE",
// old actua	
// old actua			    "AUS",
// old actua			    "MIN",
// old actua			    "MED",
// old actua			    "MAX",
// old actua	
// old actua			      "OFF",
// old actua			      "LOW",
// old actua			      "MED",
// old actua			      "HIGH",	     
// old actua	
// old actua		 	        "OFF",
// old actua			        "FAIBLE",
// old actua			        "MOYEN",
// old actua			        "ELEVE",
// old actua	
// old actua				  "AV",
// old actua				  "SVAK",
// old actua				  "MED",
// old actua				  "STERK",	     
// old actua	
// old actua					};
// old actua					
// old actua		char	*camera_types[]={
// old actua	
// old actua			"WIRE",
// old actua			"FAR",
// old actua			"PLAN",
// old actua			"G.LINE",
// old actua			"ISO.",
// old actua			"PLYR",
// old actua			"REF",
// old actua	
// old actua		 	  "MAN.",  
// old actua			  "ELO.",  
// old actua			  "AERIEN",
// old actua			  "LIGNE", 
// old actua			  "ISO.",
// old actua			  "JOU.",
// old actua			  "ARB",
// old actua			
// old actua			    "FREI",
// old actua			    "WEIT",
// old actua			    "PLAN",
// old actua			    "TOR L.",
// old actua			    "ISO.",
// old actua			    "PLYR",
// old actua			    "SCHI.",
// old actua	
// old actua			      "WIRE",
// old actua			      "FAR",
// old actua			      "PLAN",
// old actua			      "G.LINE",
// old actua			      "ISO.",
// old actua			      "PLYR",
// old actua			      "REF",
// old actua	
// old actua		 	        "MAN.",  
// old actua			        "ELO.",  
// old actua			        "AERIEN",
// old actua			        "LIGNE", 
// old actua			        "ISO.",
// old actua			        "JOU.",
// old actua			        "ARB",
// old actua	
// old actua				  "WIRE",
// old actua				  "VIDV.",
// old actua				  "PLAN",
// old actua				  "M|L-L",
// old actua				  "ISO.",
// old actua				  "SPLR",
// old actua				  "DOMR",
// old actua					};
// old actua		
// old actua		char	*player_labels[]={
// old actua	
// old actua			"PLAYER 1",
// old actua			"PLAYER 2",
// old actua			"PLAYER 3",
// old actua			"PLAYER 4",
// old actua	
// old actua			  "JOUEUR 1",
// old actua			  "JOUEUR 2",
// old actua			  "JOUEUR 3",
// old actua			  "JOUEUR 4",
// old actua	
// old actua			    "SPIELER 1",
// old actua			    "SPIELER 2",
// old actua			    "SPIELER 3",
// old actua			    "SPIELER 4",
// old actua	
// old actua			      "PLAYER 1",
// old actua			      "PLAYER 2",
// old actua			      "PLAYER 3",
// old actua			      "PLAYER 4",
// old actua	
// old actua			        "JOUEUR 1",
// old actua			        "JOUEUR 2",
// old actua			        "JOUEUR 3",
// old actua			        "JOUEUR 4",
// old actua	
// old actua				  "SPILLER 1",
// old actua				  "SPILLER 2",
// old actua				  "SPILLER 3",
// old actua				  "SPILLER 4",
// old actua	
// old actua					};
// old actua				
// old actua		char	*control_labels[]={
// old actua	
// old actua			"KEYBOARD 1",
// old actua			"KEYBOARD 2",
// old actua			"JOYSTICK 1",
// old actua			"JOYSTICK 2",
// old actua	
// old actua			  "CLAVIER 1",
// old actua			  "CLAVIER 2",
// old actua			  "JOYSTICK 1",
// old actua			  "JOYSTICK 2",
// old actua	
// old actua			    "TASTATUR 1",
// old actua			    "TASTATUR 2",
// old actua			    "JOYSTICK 1",		
// old actua			    "JOYSTICK 2",		
// old actua	
// old actua			      "KEYBOARD 1",
// old actua			      "KEYBOARD 2",
// old actua			      "JOYSTICK 1",
// old actua			      "JOYSTICK 2",
// old actua			    
// old actua			        "CLAVIER 1",
// old actua			        "CLAVIER 2",
// old actua			        "JOYSTICK 1",
// old actua			        "JOYSTICK 2",
// old actua			    
// old actua				  "TASTATUR 1",
// old actua				  "TASTATUR 2",
// old actua				  "JOYSTICK 1",
// old actua				  "JOYSTICK 2",
// old actua	
// old actua					};
// old actua	
// old actua		char	*calibrate_message[]={
// old actua			
// old actua			"PLAYER 1, Circle joystick 1 then press fire...",
// old actua			"PLAYER 2, Circle joystick 1 then press fire...",
// old actua			"PLAYER 3, Circle joystick 1 then press fire...",
// old actua			"PLAYER 4, Circle joystick 1 then press fire...",
// old actua			"PLAYER 1, Circle joystick 2 then press fire...",
// old actua			"PLAYER 2, Circle joystick 2 then press fire...",
// old actua			"PLAYER 3, Circle joystick 2 then press fire...",
// old actua			"PLAYER 4, Circle joystick 2 then press fire...",
// old actua	
// old actua			  "J1, Cercle avec joystick 1, puis Feu...",
// old actua			  "J2, Cercle avec joystick 1, puis Feu...",
// old actua			  "J3, Cercle avec joystick 1, puis Feu...",
// old actua			  "J4, Cercle avec joystick 1, puis Feu...",
// old actua			  "J1, Cercle avec joystick 2, puis Feu...",
// old actua			  "J2, Cercle avec joystick 2, puis Feu...",
// old actua			  "J3, Cercle avec joystick 2, puis Feu...",
// old actua			  "J4, Cercle avec joystick 2, puis Feu...",
// old actua			    
// old actua			    "SPIELER 1, bitte Joystick 1 drehen, dann Feuer",
// old actua			    "SPIELER 2, bitte Joystick 1 drehen, dann Feuer",
// old actua			    "SPIELER 3, bitte Joystick 1 drehen, dann Feuer",
// old actua			    "SPIELER 4, bitte Joystick 1 drehen, dann Feuer",
// old actua			    "SPIELER 1, bitte Joystick 2 drehen, dann Feuer",
// old actua			    "SPIELER 2, bitte Joystick 2 drehen, dann Feuer",
// old actua			    "SPIELER 3, bitte Joystick 2 drehen, dann Feuer",
// old actua			    "SPIELER 4, bitte Joystick 2 drehen, dann Feuer",
// old actua			
// old actua			      "PLAYER 1, Circle joystick 1 then press fire...",
// old actua			      "PLAYER 2, Circle joystick 1 then press fire...",
// old actua			      "PLAYER 3, Circle joystick 1 then press fire...",
// old actua			      "PLAYER 4, Circle joystick 1 then press fire...",
// old actua			      "PLAYER 1, Circle joystick 2 then press fire...",
// old actua			      "PLAYER 2, Circle joystick 2 then press fire...",
// old actua			      "PLAYER 3, Circle joystick 2 then press fire...",
// old actua			      "PLAYER 4, Circle joystick 2 then press fire...",
// old actua	
// old actua			        "J1, Cercle avec joystick 1, puis Feu...",
// old actua			        "J2, Cercle avec joystick 1, puis Feu...",
// old actua			        "J3, Cercle avec joystick 1, puis Feu...",
// old actua			        "J4, Cercle avec joystick 1, puis Feu...",
// old actua			        "J1, Cercle avec joystick 2, puis Feu...",
// old actua			        "J2, Cercle avec joystick 2, puis Feu...",
// old actua			        "J3, Cercle avec joystick 2, puis Feu...",
// old actua			        "J4, Cercle avec joystick 2, puis Feu...",
// old actua			    
// old actua				  "SPILLER 1, Vri joystick 1, deretter fyr...",
// old actua				  "SPILLER 2, Vri joystick 1, deretter fyr...",
// old actua				  "SPILLER 3, Vri joystick 1, deretter fyr...",
// old actua				  "SPILLER 4, Vri joystick 1, deretter fyr...",
// old actua				  "SPILLER 1, Vri joystick 2, deretter fyr...",
// old actua				  "SPILLER 2, Vri joystick 2, deretter fyr...",
// old actua				  "SPILLER 3, Vri joystick 2, deretter fyr...",
// old actua				  "SPILLER 4, Vri joystick 2, deretter fyr...",
// old actua	
// old actua					};
// old actua	
// old actua				 	
// old actua		char	*redefine_message[]={
// old actua			
// old actua			"PLAYER 1, Redefine Keyboard 1...",
// old actua			"PLAYER 2, Redefine Keyboard 1...",
// old actua			"PLAYER 3, Redefine Keyboard 1...",
// old actua			"PLAYER 4, Redefine Keyboard 1...",
// old actua			"PLAYER 1, Redefine Keyboard 2...",
// old actua			"PLAYER 2, Redefine Keyboard 2...",
// old actua			"PLAYER 3, Redefine Keyboard 2...",
// old actua			"PLAYER 4, Redefine Keyboard 2...",
// old actua			
// old actua			  "JOUEUR NUMERO 1, Redefinissez le clavier 1...",
// old actua			  "JOUEUR NUMERO 2, Redefinissez le clavier 1...",
// old actua			  "JOUEUR NUMERO 3, Redefinissez le clavier 1...",
// old actua			  "JOUEUR NUMERO 4, Redefinissez le clavier 1...",
// old actua			  "JOUEUR NUMERO 1, Redefinissez le clavier 2...",
// old actua			  "JOUEUR NUMERO 2, Redefinissez le clavier 2...",
// old actua			  "JOUEUR NUMERO 3, Redefinissez le clavier 2...",
// old actua			  "JOUEUR NUMERO 4, Redefinissez le clavier 2...",
// old actua	
// old actua			    "SPIELER 1, Testatur umdefinieren 1...",
// old actua			    "SPIELER 2, Testatur umdefinieren 1...",
// old actua			    "SPIELER 3, Testatur umdefinieren 1...",
// old actua			    "SPIELER 4, Testatur umdefinieren 1...",
// old actua			    "SPIELER 1, Testatur umdefinieren 2...",
// old actua			    "SPIELER 2, Testatur umdefinieren 2...",
// old actua			    "SPIELER 3, Testatur umdefinieren 2...",
// old actua			    "SPIELER 4, Testatur umdefinieren 2...",
// old actua			
// old actua			      "PLAYER 1, Redefine Keyboard 1...",
// old actua			      "PLAYER 2, Redefine Keyboard 1...",
// old actua			      "PLAYER 3, Redefine Keyboard 1...",
// old actua			      "PLAYER 4, Redefine Keyboard 1...",
// old actua			      "PLAYER 1, Redefine Keyboard 2...",
// old actua			      "PLAYER 2, Redefine Keyboard 2...",
// old actua			      "PLAYER 3, Redefine Keyboard 2...",
// old actua			      "PLAYER 4, Redefine Keyboard 2...",
// old actua			
// old actua			        "JOUEUR NUMERO 1, Redefinissez le clavier 1...",
// old actua			        "JOUEUR NUMERO 2, Redefinissez le clavier 1...",
// old actua			        "JOUEUR NUMERO 3, Redefinissez le clavier 1...",
// old actua			        "JOUEUR NUMERO 4, Redefinissez le clavier 1...",
// old actua			        "JOUEUR NUMERO 1, Redefinissez le clavier 2...",
// old actua			        "JOUEUR NUMERO 2, Redefinissez le clavier 2...",
// old actua			        "JOUEUR NUMERO 3, Redefinissez le clavier 2...",
// old actua			        "JOUEUR NUMERO 4, Redefinissez le clavier 2...",
// old actua	
// old actua				  "SPILLER 1, definer tastatur 1...",
// old actua				  "SPILLER 2, definer tastatur 1...",
// old actua				  "SPILLER 3, definer tastatur 1...",
// old actua				  "SPILLER 4, definer tastatur 1...",
// old actua				  "SPILLER 1, definer tastatur 2...",
// old actua				  "SPILLER 2, definer tastatur 2...",
// old actua				  "SPILLER 3, definer tastatur 2...",
// old actua			 	  "SPILLER 4, definer tastatur 2...",
// old actua	
// old actua					};
// old actua	
// old actua		char	*size_types[]={
// old actua			"100%",
// old actua			"85%",
// old actua			"85%W",
// old actua			"75%",
// old actua			"75%W",
// old actua			"65%",
// old actua			"65%W",
// old actua			"50%",
// old actua			"50%W",
// old actua			"40%W",
// old actua	
// old actua		// SAME IN FRENCH
// old actua					};
// old actua					
// old actua		char	*time_types[]={
// old actua			"5",
// old actua			"10",
// old actua			"20",
// old actua			"40",
// old actua			"90",
// old actua	
// old actua		// SAME IN FRENCH
// old actua					};
// old actua					
// old actua					
// old actua		char	*audio_types[]={
// old actua			"OFF",
// old actua			"MONO",
// old actua			"3D",	 	
// old actua	
// old actua			  "OFF",
// old actua			  "MONO",
// old actua			  "3D",
// old actua	
// old actua			    "AUS",
// old actua			    "MONO",
// old actua			    "3D",
// old actua	
// old actua			      "OFF",
// old actua			      "MONO",
// old actua			      "3D",	 	
// old actua	
// old actua			        "OFF",
// old actua			        "MONO",
// old actua			        "3D",
// old actua	
// old actua				  "AV",
// old actua				  "MONO",
// old actua		 		  "3D",
// old actua					};
// old actua	
// old actua		char	*NoOfPLAYERS_types[]={
// old actua	
// old actua			"PLAYERS: 1",
// old actua			"PLAYERS: 2",
// old actua			"PLAYERS: 3",
// old actua			"PLAYERS: 4",	
// old actua			"GAME: 0",
// old actua			"GAME: 1",
// old actua			"GAME: 2",
// old actua			"GAME: 3",
// old actua			"GAME: 4",
// old actua			"GAME: 5",
// old actua			"GAME: 6",
// old actua			"GAME: 7",
// old actua	
// old actua			  "JOUEURS: 1",
// old actua			  "JOUEURS: 2",
// old actua			  "JOUEURS: 3",
// old actua			  "JOUEURS: 4",
// old actua			  "JEU: 0",
// old actua			  "JEU: 1",
// old actua			  "JEU: 2",
// old actua			  "JEU: 3",
// old actua			  "JEU: 4",
// old actua			  "JEU: 5",
// old actua			  "JEU: 6",
// old actua			  "JEU: 7",
// old actua	
// old actua			    "SPIELER: 1",
// old actua			    "SPIELER: 2",
// old actua			    "SPIELER: 3",
// old actua			    "SPIELER: 4",	
// old actua			    "SPIEL: 0",
// old actua			    "SPIEL: 1",
// old actua			    "SPIEL: 2",
// old actua			    "SPIEL: 3",
// old actua			    "SPIEL: 4",
// old actua			    "SPIEL: 5",
// old actua			    "SPIEL: 6",
// old actua			    "SPIEL: 7",
// old actua	
// old actua			      "PLAYERS: 1",
// old actua			      "PLAYERS: 2",
// old actua			      "PLAYERS: 3",
// old actua			      "PLAYERS: 4",	
// old actua			      "GAME: 0",
// old actua			      "GAME: 1",
// old actua			      "GAME: 2",
// old actua			      "GAME: 3",
// old actua			      "GAME: 4",
// old actua			      "GAME: 5",
// old actua			      "GAME: 6",
// old actua			      "GAME: 7",
// old actua			      
// old actua			        "JOUEURS: 1",
// old actua			        "JOUEURS: 2",
// old actua			        "JOUEURS: 3",
// old actua			        "JOUEURS: 4",
// old actua			        "JEU: 0",
// old actua			        "JEU: 1",
// old actua			        "JEU: 2",
// old actua			        "JEU: 3",
// old actua			        "JEU: 4",
// old actua			        "JEU: 5",
// old actua			        "JEU: 6",
// old actua			        "JEU: 7",
// old actua	
// old actua				  "SPILLERE: 1",
// old actua				  "SPILLERE: 2",
// old actua				  "SPILLERE: 3",
// old actua				  "SPILLERE: 4",
// old actua				  "KAMP: 0",
// old actua				  "KAMP: 1",
// old actua				  "KAMP: 2",
// old actua				  "KAMP: 3",
// old actua				  "KAMP: 4",
// old actua				  "KAMP: 5",
// old actua				  "KAMP: 6",
// old actua				  "KAMP: 7",
// old actua	
// old actua					};
// old actua					
// old actua		char	*Game_types[]={
// old actua			"ARCADE",
// old actua			"SIMULATION",
// old actua	
// old actua			  "ARCADE",
// old actua			  "SIMULATION",
// old actua	
// old actua			    "ARCADE",
// old actua			    "SIMULATION",
// old actua	
// old actua			      "ARCADE",
// old actua			      "SIMULATION",
// old actua	
// old actua			        "ARCADE",
// old actua			        "SIMULATION",
// old actua	
// old actua				  "ARKADE",
// old actua		 		  "SIMULERING",
// old actua	
// old actua					};
// old actua	
// old actua		char	*COMPETITION_types[]={
// old actua	
// old actua			"FRIENDLY",
// old actua			"LEAGUE",
// old actua			"CUP",
// old actua			"PRACTICE",
// old actua			"NETWORK",
// old actua			
// old actua			  "AMICAL",
// old actua			  "LIGUE",
// old actua			  "COUPE",
// old actua			  "PRACTIQUE",
// old actua			  "RESEAU",
// old actua	
// old actua			    "FREUNDSCHA.",
// old actua			    "LIGA",
// old actua			    "POKAL",
// old actua			    "TRAINING",
// old actua			    "NETZWERK",
// old actua	
// old actua			      "FRIENDLY",
// old actua			      "LEAGUE",
// old actua			      "CUP",
// old actua			      "PRACTICE",
// old actua			      "NETWORK",
// old actua			      
// old actua			        "AMICAL",
// old actua			        "LIGUE",
// old actua			        "COUPE",
// old actua			        "PRACTIQUE",
// old actua			        "RESEAU",
// old actua	
// old actua				  "VENNSKAP",
// old actua				  "LIGA",
// old actua				  "CUP",
// old actua				  "TRENING",
// old actua				  "NETTVERK",
// old actua	
// old actua					};
// old actua	
// old actua		char	*NETWORK_types[]={
// old actua			"DONE",
// old actua			"WAITING",
// old actua	
// old actua			  "FAIT",
// old actua			  "EN ATTENTE",
// old actua	
// old actua			    "FERTIG",
// old actua			    "BITTE WARTEN",
// old actua	
// old actua			      "DONE",
// old actua			      "WAITING",
// old actua			      
// old actua			        "FAIT",
// old actua			        "EN ATTENTE",
// old actua	
// old actua				  "FERDIG",
// old actua		  		  "VENTER",
// old actua	
// old actua			 		};
// old actua	
// old actua		char	*slot_names[]={
// old actua			"SLOT 1",
// old actua			"SLOT 2",
// old actua			"SLOT 3",	     
// old actua			"SLOT 4",	     
// old actua			"SLOT 5",	     
// old actua			"SLOT 6",	     
// old actua			"SLOT 7",	     
// old actua			"SLOT 8",	     
// old actua	
// old actua			  "EMPL. 1",
// old actua			  "EMPL. 2",
// old actua			  "EMPL. 3",	     
// old actua			  "EMPL. 4",	     
// old actua			  "EMPL. 5",	     
// old actua			  "EMPL. 6",	     
// old actua			  "EMPL. 7",	     
// old actua			  "EMPL. 8",	     
// old actua	
// old actua			    "SPIEL 1",
// old actua			    "SPIEL 2",
// old actua			    "SPIEL 3",	     
// old actua			    "SPIEL 4",	     
// old actua			    "SPIEL 5",	     
// old actua			    "SPIEL 6",	     
// old actua			    "SPIEL 7",	     
// old actua			    "SPIEL 8",	     
// old actua	
// old actua			      "SLOT 1",
// old actua			      "SLOT 2",
// old actua			      "SLOT 3",	     
// old actua			      "SLOT 4",	     
// old actua			      "SLOT 5",	     
// old actua			      "SLOT 6",	     
// old actua			      "SLOT 7",	     
// old actua			      "SLOT 8",	     
// old actua			      
// old actua			        "EMPL. 1",
// old actua			        "EMPL. 2",
// old actua			        "EMPL. 3",	     
// old actua			        "EMPL. 4",	     
// old actua			        "EMPL. 5",	     
// old actua			        "EMPL. 6",	     
// old actua			        "EMPL. 7",	     
// old actua			        "EMPL. 8",	     
// old actua	
// old actua				  "SPILL 1",
// old actua				  "SPILL 2",
// old actua				  "SPILL 3",
// old actua				  "SPILL 4",
// old actua				  "SPILL 5",
// old actua				  "SPILL 6",
// old actua				  "SPILL 7",
// old actua				  "SPILL 8",
// old actua	
// old actua					};
// old actua					


match_data	match_info;

batch_data	batch_info;



// old actua		char	*ROUNDS[]={
// old actua	
// old actua			"1st Round",   			// 32
// old actua			"2nd Round",			// 16 
// old actua			"Quarter Final", 		// 8
// old actua			"Semi-Final",			// 4
// old actua			"Final",			// 2
// old actua			
// old actua			"1st Round",   			// 16
// old actua			"Quarter Final",		// 8
// old actua			"Semi-Final",			// 4
// old actua			"Final",			// 2
// old actua	
// old actua			  "1are manche",   
// old actua			  "2ame manche",   
// old actua			  "Quart de finale",
// old actua			  "Demi-finale",
// old actua			  "Finale",
// old actua	
// old actua			  "1are manche",   
// old actua			  "Quart de finale",
// old actua			  "Demi-finale",
// old actua			  "Finale",
// old actua	
// old actua			    "1. Runde",
// old actua			    "2. Runde",
// old actua			    "Viertelfinale",
// old actua			    "Halbfinale",
// old actua			    "Finale",
// old actua	
// old actua			    "1. Runde",
// old actua			    "Viertelfinale",
// old actua			    "Halbfinale",
// old actua			    "Finale",
// old actua	
// old actua			      "1st Round",   			// 32
// old actua			      "2nd Round",			// 16 
// old actua			      "Quarter Final", 		// 8
// old actua			      "Semi-Final",			// 4
// old actua			      "Final",			// 2
// old actua			
// old actua			      "1st Round",   			// 16
// old actua			      "Quarter Final",		// 8
// old actua			      "Semi-Final",			// 4
// old actua			      "Final",			// 2
// old actua	
// old actua			        "1are manche", 
// old actua			        "2ame manche", 
// old actua			        "Quart de finale",
// old actua			        "Demi-finale",
// old actua			        "Finale",
// old actua			      
// old actua			        "1are manche", 
// old actua			        "Quart de finale",
// old actua			        "Demi-finale",
// old actua			        "Finale",
// old actua	
// old actua				   "1. runde",
// old actua				   "2. runde",
// old actua				   "Kvartfinale",
// old actua				   "Semifinale",
// old actua				   "Finale",
// old actua	
// old actua				   "1. runde",
// old actua				   "Kvartfinale",
// old actua				   "Semifinale",
// old actua				   "Finale",
// old actua	
// old actua	
// old actua			      
// old actua				};
// old actua	

			
// old actua	char	*VENUES[]={
// old actua
// old actua		"New York",
// old actua		"Moscow",
// old actua		"Madrid",
// old actua		"Sofia",
// old actua		"Brussels",
// old actua		"Copenhagen",
// old actua		"Belfast",
// old actua		"Tunis",
// old actua		"Lusaka",
// old actua		"Zurich",
// old actua		"Yaoynde",
// old actua		"Seoul",
// old actua		"Rome",
// old actua		"Rabat",
// old actua		"London",
// old actua		"Glasgow",
// old actua		"Cardiff",
// old actua		"Cairo",
// old actua		"Bogota",
// old actua		"Stockholm",
// old actua		"Buenos Aires",
// old actua		"Dublin",
// old actua		"Amsterdam",
// old actua		"Helsinki",
// old actua		"Bratislava",
// old actua		"Abidjan",
// old actua		"Accra",
// old actua		"Bucharest",
// old actua		"Berlin",
// old actua		"Athens",
// old actua		"Oslo",
// old actua		"Riyadh",
// old actua		"Paris",
// old actua		"Warsaw",
// old actua		"Tokyo",
// old actua		"Montevideo",
// old actua		"Rio De Janeiro",
// old actua		"Lagos",
// old actua		"Guadalajara",	
// old actua		"Prague",
// old actua		"Reykjavik",
// old actua		"Lisbon",
// old actua		"Peking",
// old actua		"La Paz",
// old actua		"Sheffield",
// old actua
// old actua			"New York",
// old actua			"Moscou",	// ok
// old actua			"Madrid",	// ok
// old actua			"Sofia",
// old actua			"Bruxelles",
// old actua			"Copenhagen",	// ok
// old actua			"Belfast",
// old actua			"Tunis",	// ok
// old actua			"Lusaka",
// old actua			"Zurich",
// old actua			"Yaoynde",
// old actua			"Seoul",
// old actua			"Rome",
// old actua			"Rabat",
// old actua			"Londres",	// ok
// old actua			"Glasgow",
// old actua			"Cardiff",
// old actua			"Caire",	// ok
// old actua			"Bogota",
// old actua			"Stockholm",
// old actua			"Buenos Aires",
// old actua			"Dublin",
// old actua			"Amsterdam",
// old actua			"Helsinki",
// old actua			"Bratislava",
// old actua			"Abidjan",
// old actua			"Accra",
// old actua			"Bucharest",
// old actua			"Berlin",
// old actua			"Athenes",	// ok
// old actua			"Oslo",
// old actua			"Riyadh",
// old actua			"Paris",        // ok
// old actua			"Varsovie",	// ok
// old actua			"Tokyo",
// old actua			"Montevideo",
// old actua			"Rio De Janeiro",
// old actua			"Lagos",
// old actua			"Guadalajara",	
// old actua			"Prague",
// old actua			"Reykjavik",
// old actua			"Lisbon",
// old actua			"Pekin",
// old actua			"La Paz",
// old actua			"Sheffield",
// old actua
// old actua				"New York", 	
// old actua				"Moskau",	//ok 1
// old actua				"Madrid",
// old actua				"Sofia",
// old actua				"Bruessel",	//ok 2
// old actua				"Kopenhagen",	//ok 3
// old actua				"Belfast",
// old actua				"Tunis",
// old actua				"Lusaka",
// old actua				"Zuerich",	//ok 4
// old actua				"Jaunde",	//ok 5
// old actua				"Seoul",
// old actua				"Rom",		//ok 6
// old actua				"Rabat",
// old actua				"London",
// old actua				"Glasgow",
// old actua				"Cardiff",
// old actua				"Kairo",	//ok 7
// old actua				"Bogota",
// old actua				"Stockholm",
// old actua				"Buenos Aires",
// old actua				"Dublin",
// old actua				"Amsterdam",
// old actua				"Helsinki",
// old actua				"Bratyslawa",	//ok 8
// old actua				"Abidzan",	//ok 9
// old actua				"Akra",		//ok 10
// old actua				"Bukarest",	//ok 11
// old actua				"Berlin",
// old actua				"Athen",	//ok 12
// old actua				"Oslo",
// old actua				"Riad",		//ok 13
// old actua				"Paris",
// old actua				"Warschau",	//ok 14
// old actua				"Tokio", 	//ok 15
// old actua				"Montevideo",
// old actua				"Rio De Janeiro",
// old actua				"Lagos",
// old actua				"Guadalajara",	
// old actua				"Prag",		//ok 16
// old actua				"Reykjavik",
// old actua				"Lissabon",	//ok 17
// old actua				"Peking",
// old actua				"La Paz",
// old actua				"Sheffield",
// old actua
// old actua					"New York",
// old actua					"Moscow",
// old actua					"Madrid",
// old actua					"Sofia",
// old actua					"Brussels",
// old actua					"Copenhagen",
// old actua					"Belfast",
// old actua					"Tunis",
// old actua					"Lusaka",
// old actua					"Zurich",
// old actua					"Yaoynde",
// old actua					"Seoul",
// old actua					"Rome",
// old actua					"Rabat",
// old actua					"London",
// old actua					"Glasgow",
// old actua					"Cardiff",
// old actua					"Cairo",
// old actua					"Bogota",
// old actua					"Stockholm",
// old actua					"Buenos Aires",
// old actua					"Dublin",
// old actua					"Amsterdam",
// old actua					"Helsinki",
// old actua					"Bratislava",
// old actua					"Abidjan",
// old actua					"Accra",
// old actua					"Bucharest",
// old actua					"Berlin",
// old actua					"Athens",
// old actua					"Oslo",
// old actua					"Riyadh",
// old actua					"Paris",
// old actua					"Warsaw",
// old actua					"Tokyo",
// old actua					"Montevideo",
// old actua					"Rio De Janeiro",
// old actua					"Lagos",
// old actua					"Guadalajara",	
// old actua					"Prague",
// old actua					"Reykjavik",
// old actua					"Lisbon",
// old actua					"Peking",
// old actua					"La Paz",
// old actua					"Sheffield",
// old actua			
// old actua						"New York",
// old actua						"Moscou",	// ok
// old actua						"Madrid",	// ok
// old actua						"Sofia",
// old actua						"Bruxelles",
// old actua						"Copenhagen",	// ok
// old actua						"Belfast",
// old actua						"Tunis",	// ok
// old actua						"Lusaka",
// old actua						"Zurich",
// old actua						"Yaoynde",
// old actua						"Seoul",
// old actua						"Rome",
// old actua						"Rabat",
// old actua						"Londres",	// ok
// old actua						"Glasgow",
// old actua						"Cardiff",
// old actua						"Caire",	// ok
// old actua						"Bogota",
// old actua						"Stockholm",
// old actua						"Buenos Aires",
// old actua						"Dublin",
// old actua						"Amsterdam",
// old actua						"Helsinki",
// old actua						"Bratislava",
// old actua						"Abidjan",
// old actua						"Accra",
// old actua						"Bucharest",
// old actua						"Berlin",
// old actua						"Athenes",	// ok
// old actua						"Oslo",
// old actua						"Riyadh",
// old actua						"Paris",        // ok
// old actua						"Varsovie",	// ok
// old actua						"Tokyo",
// old actua						"Montevideo",
// old actua						"Rio De Janeiro",
// old actua						"Lagos",
// old actua						"Guadalajara",	
// old actua						"Prague",
// old actua						"Reykjavik",
// old actua						"Lisbon",
// old actua						"Pekin",
// old actua						"La Paz",
// old actua						"Sheffield",
// old actua
// old actua							"New York",
// old actua							"Moskva",
// old actua							"Madrid",
// old actua							"Sofia",
// old actua							"Brussel",
// old actua							"Kbenhavn",
// old actua							"Belfast",
// old actua							"Tunis",
// old actua							"Lusaka",
// old actua							"Zurich",
// old actua							"Yaoynde",
// old actua							"Seoul",
// old actua							"Roma",
// old actua							"Rabat",
// old actua							"London",
// old actua							"Glasgow",
// old actua							"Cardiff",
// old actua							"Kairo",
// old actua							"Bogota",
// old actua							"Stockholm",
// old actua							"Buenos Aires",
// old actua							"Dublin",
// old actua							"Amsterdam",
// old actua							"Helsinki",
// old actua							"Bratislava",
// old actua							"Abidjan",
// old actua							"Accra",
// old actua							"Bucharest",
// old actua							"Berlin",
// old actua							"Athen",
// old actua							"Oslo",
// old actua							"Riyadh",
// old actua							"Paris",
// old actua							"Warsawa",
// old actua							"Tokyo",
// old actua							"Montevideo",
// old actua							"Rio de Janeiro",
// old actua							"Lagos",
// old actua							"Guadalajara",
// old actua							"Praha",
// old actua							"Reykjavik",
// old actua							"Lisboa",
// old actua							"Peking",
// old actua							"La Paz",
// old actua							"Sheffield",	
// old actua				};
// old actua						
// old actua
// old actua	
// old actuaint		allocation_flags[]={
// old actua		NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,
// old actua				};
// old actua
// old actuachoose_info	choose_data[5]={
// old actua
// old actua		{
// old actua		-14,6,
// old actua		-14,22,		
// old actua		-14,38,
// old actua// 4 TEAMS
// old actua		SHADOWtextON|SFONT|CENTREjustifyTEXT, LARGE|SHADOW, CHOOSE_TEAM_NAME, 
// old actua		TABx16TEAMS+(sprite_S62width/2),                             A03yPOS-2+(3*A03yOFFSET)+76, 
// old actua                TABx16TEAMS,                                                 A03yPOS-2+(3*A03yOFFSET)+16,
// old actua                TABx16TEAMS,                                                 A03yPOS-2+(3*A03yOFFSET)+16,
// old actua		TABx16TEAMS+sprite_S62width,				     A03yPOS-2+(3*A03yOFFSET)+16+sprite_S62height+24,
// old actua                TABx16TEAMS-16,                                              A03yPOS-2+(3*A03yOFFSET)+76,
// old actua		sprite_S62width+28,				             24,
// old actua
// old actua		SHADOWtextON|SFONT|CENTREjustifyTEXT, LARGE|SHADOW, CHOOSE_TEAM_NAME,
// old actua		(2*TABx16TEAMS)+(sprite_S62width)+(sprite_S62width/2),       A03yPOS-2+(3*A03yOFFSET)+76, 
// old actua                (2*TABx16TEAMS)+(sprite_S62width),                           A03yPOS-2+(3*A03yOFFSET)+16,
// old actua                (2*TABx16TEAMS)+(sprite_S62width),                           A03yPOS-2+(3*A03yOFFSET)+16,
// old actua		(2*TABx16TEAMS)+(sprite_S62width)+sprite_S62width,	     A03yPOS-2+(3*A03yOFFSET)+16+sprite_S62height+24,
// old actua                (2*TABx16TEAMS)+(sprite_S62width)-16,                        A03yPOS-2+(3*A03yOFFSET)+76,
// old actua		sprite_S62width+28,				             24,
// old actua
// old actua		SHADOWtextON|SFONT|CENTREjustifyTEXT, LARGE|SHADOW, CHOOSE_TEAM_NAME,
// old actua		(3*TABx16TEAMS)+(2*sprite_S62width)+(sprite_S62width/2),     A03yPOS-2+(3*A03yOFFSET)+76, 
// old actua                (3*TABx16TEAMS)+(2*sprite_S62width),                         A03yPOS-2+(3*A03yOFFSET)+16,
// old actua                (3*TABx16TEAMS)+(2*sprite_S62width),                         A03yPOS-2+(3*A03yOFFSET)+16,
// old actua		(3*TABx16TEAMS)+(2*sprite_S62width)+sprite_S62width,	     A03yPOS-2+(3*A03yOFFSET)+16+sprite_S62height+24,
// old actua                (3*TABx16TEAMS)+(2*sprite_S62width)-16,                      A03yPOS-2+(3*A03yOFFSET)+76,
// old actua		sprite_S62width+28,				             24,
// old actua
// old actua		SHADOWtextON|SFONT|CENTREjustifyTEXT, LARGE|SHADOW, CHOOSE_TEAM_NAME,
// old actua		(4*TABx16TEAMS)+(3*sprite_S62width)+(sprite_S62width/2),     A03yPOS-2+(3*A03yOFFSET)+76, 
// old actua                (4*TABx16TEAMS)+(3*sprite_S62width),                         A03yPOS-2+(3*A03yOFFSET)+16,
// old actua                (4*TABx16TEAMS)+(3*sprite_S62width),                         A03yPOS-2+(3*A03yOFFSET)+16,
// old actua		(4*TABx16TEAMS)+(3*sprite_S62width)+sprite_S62width,	     A03yPOS-2+(3*A03yOFFSET)+16+sprite_S62height+24,
// old actua                (4*TABx16TEAMS)+(3*sprite_S62width)-16,                      A03yPOS-2+(3*A03yOFFSET)+76,
// old actua		sprite_S62width+28,				             24,
// old actua
// old actua		NULL,NULL,NULL,NULL,NULL,NULL,NULL,
// old actua		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
// old actua		NULL,NULL,NULL,NULL,NULL,NULL,NULL,
// old actua		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
// old actua		NULL,NULL,NULL,NULL,NULL,NULL,NULL,
// old actua		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
// old actua		NULL,NULL,NULL,NULL,NULL,NULL,NULL,
// old actua		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
// old actua		NULL,NULL,NULL,NULL,NULL,NULL,NULL,
// old actua		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
// old actua		NULL,NULL,NULL,NULL,NULL,NULL,NULL,
// old actua		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
// old actua		NULL,NULL,NULL,NULL,NULL,NULL,NULL,
// old actua		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
// old actua		NULL,NULL,NULL,NULL,NULL,NULL,NULL,
// old actua		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
// old actua		NULL,NULL,NULL,NULL,NULL,NULL,NULL,
// old actua		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
// old actua		NULL,NULL,NULL,NULL,NULL,NULL,NULL,
// old actua		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
// old actua		NULL,NULL,NULL,NULL,NULL,NULL,NULL,
// old actua		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
// old actua		NULL,NULL,NULL,NULL,NULL,NULL,NULL,
// old actua		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
// old actua		NULL,NULL,NULL,NULL,NULL,NULL,NULL,
// old actua		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
// old actua		NULL,NULL,NULL,NULL,NULL,NULL,NULL,
// old actua		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
// old actua		NULL,NULL,NULL,NULL,NULL,NULL,NULL,
// old actua		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
// old actua		NULL,NULL,NULL,NULL,NULL,NULL,NULL,
// old actua		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
// old actua		NULL,NULL,NULL,NULL,NULL,NULL,NULL,
// old actua		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
// old actua		NULL,NULL,NULL,NULL,NULL,NULL,NULL,
// old actua		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
// old actua		NULL,NULL,NULL,NULL,NULL,NULL,NULL,
// old actua		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
// old actua		NULL,NULL,NULL,NULL,NULL,NULL,NULL,
// old actua		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
// old actua		NULL,NULL,NULL,NULL,NULL,NULL,NULL,
// old actua		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
// old actua		NULL,NULL,NULL,NULL,NULL,NULL,NULL,
// old actua		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
// old actua		NULL,NULL,NULL,NULL,NULL,NULL,NULL,
// old actua		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
// old actua		NULL,NULL,NULL,NULL,NULL,NULL,NULL,
// old actua		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
// old actua		NULL,NULL,NULL,NULL,NULL,NULL,NULL,
// old actua		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
// old actua		NULL,NULL,NULL,NULL,NULL,NULL,NULL,
// old actua		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
// old actua		NULL,NULL,NULL,NULL,NULL,NULL,NULL,
// old actua		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
// old actua		NULL,NULL,NULL,NULL,NULL,NULL,NULL,
// old actua		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
// old actua		NULL,NULL,NULL,NULL,NULL,NULL,NULL,
// old actua		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
// old actua		NULL,NULL,NULL,NULL,NULL,NULL,NULL,
// old actua		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
// old actua		NULL,NULL,NULL,NULL,NULL,NULL,NULL,
// old actua		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
// old actua		NULL,NULL,NULL,NULL,NULL,NULL,NULL,
// old actua		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
// old actua		NULL,NULL,NULL,NULL,NULL,NULL,NULL,
// old actua		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
// old actua		NULL,NULL,NULL,NULL,NULL,NULL,NULL,
// old actua		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
// old actua		NULL,NULL,NULL,NULL,NULL,NULL,NULL,
// old actua		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
// old actua		NULL,NULL,NULL,NULL,NULL,NULL,NULL,
// old actua		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
// old actua		NULL,NULL,NULL,NULL,NULL,NULL,NULL,
// old actua		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
// old actua		NULL,NULL,NULL,NULL,NULL,NULL,NULL,
// old actua		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
// old actua		NULL,NULL,NULL,NULL,NULL,NULL,NULL,
// old actua		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
// old actua		NULL,NULL,NULL,NULL,NULL,NULL,NULL,
// old actua		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
// old actua		},
// old actua
// old actua		{
// old actua		-14,6,
// old actua		-14,22,		
// old actua		-14,38,
// old actua// 8 TEAMS
// old actua		SHADOWtextON|SFONT|CENTREjustifyTEXT, LARGE|SHADOW, CHOOSE_TEAM_NAME, 
// old actua		TABx16TEAMS+(sprite_S62width/2),                             A03yPOS-2+(1*A03yOFFSET)+76, 
// old actua                TABx16TEAMS,                                                 A03yPOS-2+(1*A03yOFFSET)+16,
// old actua                TABx16TEAMS,                                                 A03yPOS-2+(1*A03yOFFSET)+16,
// old actua		TABx16TEAMS+sprite_S62width,				     A03yPOS-2+(1*A03yOFFSET)+16+sprite_S62height+24,
// old actua                TABx16TEAMS-16,                                              A03yPOS-2+(1*A03yOFFSET)+76,
// old actua		sprite_S62width+28,				             24,
// old actua
// old actua		SHADOWtextON|SFONT|CENTREjustifyTEXT, LARGE|SHADOW, CHOOSE_TEAM_NAME,
// old actua		(2*TABx16TEAMS)+(sprite_S62width)+(sprite_S62width/2),       A03yPOS-2+(1*A03yOFFSET)+76, 
// old actua                (2*TABx16TEAMS)+(sprite_S62width),                           A03yPOS-2+(1*A03yOFFSET)+16,
// old actua                (2*TABx16TEAMS)+(sprite_S62width),                           A03yPOS-2+(1*A03yOFFSET)+16,
// old actua		(2*TABx16TEAMS)+(sprite_S62width)+sprite_S62width,	     A03yPOS-2+(1*A03yOFFSET)+16+sprite_S62height+24,
// old actua                (2*TABx16TEAMS)+(sprite_S62width)-16,                        A03yPOS-2+(1*A03yOFFSET)+76,
// old actua		sprite_S62width+28,				             24,
// old actua
// old actua		SHADOWtextON|SFONT|CENTREjustifyTEXT, LARGE|SHADOW, CHOOSE_TEAM_NAME,
// old actua		(3*TABx16TEAMS)+(2*sprite_S62width)+(sprite_S62width/2),     A03yPOS-2+(1*A03yOFFSET)+76, 
// old actua                (3*TABx16TEAMS)+(2*sprite_S62width),                         A03yPOS-2+(1*A03yOFFSET)+16,
// old actua                (3*TABx16TEAMS)+(2*sprite_S62width),                         A03yPOS-2+(1*A03yOFFSET)+16,
// old actua		(3*TABx16TEAMS)+(2*sprite_S62width)+sprite_S62width,	     A03yPOS-2+(1*A03yOFFSET)+16+sprite_S62height+24,
// old actua                (3*TABx16TEAMS)+(2*sprite_S62width)-16,                      A03yPOS-2+(1*A03yOFFSET)+76,
// old actua		sprite_S62width+28,				             24,
// old actua
// old actua		SHADOWtextON|SFONT|CENTREjustifyTEXT, LARGE|SHADOW, CHOOSE_TEAM_NAME,
// old actua		(4*TABx16TEAMS)+(3*sprite_S62width)+(sprite_S62width/2),     A03yPOS-2+(1*A03yOFFSET)+76, 
// old actua                (4*TABx16TEAMS)+(3*sprite_S62width),                         A03yPOS-2+(1*A03yOFFSET)+16,
// old actua                (4*TABx16TEAMS)+(3*sprite_S62width),                         A03yPOS-2+(1*A03yOFFSET)+16,
// old actua		(4*TABx16TEAMS)+(3*sprite_S62width)+sprite_S62width,	     A03yPOS-2+(1*A03yOFFSET)+16+sprite_S62height+24,
// old actua                (4*TABx16TEAMS)+(3*sprite_S62width)-16,                      A03yPOS-2+(1*A03yOFFSET)+76,
// old actua		sprite_S62width+28,				             24,
// old actua
// old actua
// old actua		SHADOWtextON|SFONT|CENTREjustifyTEXT, LARGE|SHADOW, CHOOSE_TEAM_NAME,
// old actua		TABx16TEAMS+(sprite_S62width/2),                             A03yPOS-2+(6*A03yOFFSET)+76-8, 
// old actua                TABx16TEAMS,                                                 A03yPOS-2+(6*A03yOFFSET)+16-8,
// old actua                TABx16TEAMS,                                                 A03yPOS-2+(6*A03yOFFSET)+16-8,
// old actua		TABx16TEAMS+sprite_S62width,				     A03yPOS-2+(6*A03yOFFSET)+16-8+sprite_S62height+24,
// old actua                TABx16TEAMS-16,                                              A03yPOS-2+(6*A03yOFFSET)+76-8,
// old actua		sprite_S62width+28,				             24,
// old actua
// old actua		SHADOWtextON|SFONT|CENTREjustifyTEXT, LARGE|SHADOW, CHOOSE_TEAM_NAME,
// old actua		(2*TABx16TEAMS)+(sprite_S62width)+(sprite_S62width/2),       A03yPOS-2+(6*A03yOFFSET)+76-8, 
// old actua                (2*TABx16TEAMS)+(sprite_S62width),                           A03yPOS-2+(6*A03yOFFSET)+16-8,
// old actua                (2*TABx16TEAMS)+(sprite_S62width),                           A03yPOS-2+(6*A03yOFFSET)+16-8,
// old actua		(2*TABx16TEAMS)+(sprite_S62width)+sprite_S62width,	     A03yPOS-2+(6*A03yOFFSET)+16-8+sprite_S62height+24,
// old actua                (2*TABx16TEAMS)+(sprite_S62width)-16,                        A03yPOS-2+(6*A03yOFFSET)+76-8,
// old actua		sprite_S62width+28,				             24,
// old actua
// old actua		SHADOWtextON|SFONT|CENTREjustifyTEXT, LARGE|SHADOW, CHOOSE_TEAM_NAME,
// old actua		(3*TABx16TEAMS)+(2*sprite_S62width)+(sprite_S62width/2),     A03yPOS-2+(6*A03yOFFSET)+76-8, 
// old actua                (3*TABx16TEAMS)+(2*sprite_S62width),                         A03yPOS-2+(6*A03yOFFSET)+16-8,
// old actua                (3*TABx16TEAMS)+(2*sprite_S62width),                         A03yPOS-2+(6*A03yOFFSET)+16-8,
// old actua		(3*TABx16TEAMS)+(2*sprite_S62width)+sprite_S62width,	     A03yPOS-2+(6*A03yOFFSET)+16-8+sprite_S62height+24,
// old actua                (3*TABx16TEAMS)+(2*sprite_S62width)-16,                      A03yPOS-2+(6*A03yOFFSET)+76-8,
// old actua		sprite_S62width+28,				             24,
// old actua
// old actua		SHADOWtextON|SFONT|CENTREjustifyTEXT, LARGE|SHADOW, CHOOSE_TEAM_NAME,
// old actua		(4*TABx16TEAMS)+(3*sprite_S62width)+(sprite_S62width/2),     A03yPOS-2+(6*A03yOFFSET)+76-8, 
// old actua                (4*TABx16TEAMS)+(3*sprite_S62width),                         A03yPOS-2+(6*A03yOFFSET)+16-8,
// old actua                (4*TABx16TEAMS)+(3*sprite_S62width),                         A03yPOS-2+(6*A03yOFFSET)+16-8,
// old actua		(4*TABx16TEAMS)+(3*sprite_S62width)+sprite_S62width,	     A03yPOS-2+(6*A03yOFFSET)+16-8+sprite_S62height+24,
// old actua                (4*TABx16TEAMS)+(3*sprite_S62width)-16,                      A03yPOS-2+(6*A03yOFFSET)+76-8,
// old actua		sprite_S62width+28,				             24,
// old actua
// old actua
// old actua		NULL,NULL,NULL,NULL,NULL,NULL,NULL,
// old actua		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
// old actua		NULL,NULL,NULL,NULL,NULL,NULL,NULL,
// old actua		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
// old actua		NULL,NULL,NULL,NULL,NULL,NULL,NULL,
// old actua		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
// old actua		NULL,NULL,NULL,NULL,NULL,NULL,NULL,
// old actua		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
// old actua		NULL,NULL,NULL,NULL,NULL,NULL,NULL,
// old actua		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
// old actua		NULL,NULL,NULL,NULL,NULL,NULL,NULL,
// old actua		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
// old actua		NULL,NULL,NULL,NULL,NULL,NULL,NULL,
// old actua		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
// old actua		NULL,NULL,NULL,NULL,NULL,NULL,NULL,
// old actua		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
// old actua		NULL,NULL,NULL,NULL,NULL,NULL,NULL,
// old actua		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
// old actua		NULL,NULL,NULL,NULL,NULL,NULL,NULL,
// old actua		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
// old actua		NULL,NULL,NULL,NULL,NULL,NULL,NULL,
// old actua		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
// old actua		NULL,NULL,NULL,NULL,NULL,NULL,NULL,
// old actua		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
// old actua		NULL,NULL,NULL,NULL,NULL,NULL,NULL,
// old actua		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
// old actua		NULL,NULL,NULL,NULL,NULL,NULL,NULL,
// old actua		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
// old actua		NULL,NULL,NULL,NULL,NULL,NULL,NULL,
// old actua		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
// old actua		NULL,NULL,NULL,NULL,NULL,NULL,NULL,
// old actua		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
// old actua		NULL,NULL,NULL,NULL,NULL,NULL,NULL,
// old actua		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
// old actua		NULL,NULL,NULL,NULL,NULL,NULL,NULL,
// old actua		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
// old actua		NULL,NULL,NULL,NULL,NULL,NULL,NULL,
// old actua		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
// old actua		NULL,NULL,NULL,NULL,NULL,NULL,NULL,
// old actua		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
// old actua		NULL,NULL,NULL,NULL,NULL,NULL,NULL,
// old actua		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
// old actua		NULL,NULL,NULL,NULL,NULL,NULL,NULL,
// old actua		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
// old actua		NULL,NULL,NULL,NULL,NULL,NULL,NULL,
// old actua		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
// old actua		NULL,NULL,NULL,NULL,NULL,NULL,NULL,
// old actua		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
// old actua		NULL,NULL,NULL,NULL,NULL,NULL,NULL,
// old actua		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
// old actua		NULL,NULL,NULL,NULL,NULL,NULL,NULL,
// old actua		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
// old actua		NULL,NULL,NULL,NULL,NULL,NULL,NULL,
// old actua		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
// old actua		NULL,NULL,NULL,NULL,NULL,NULL,NULL,
// old actua		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
// old actua		NULL,NULL,NULL,NULL,NULL,NULL,NULL,
// old actua		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
// old actua		NULL,NULL,NULL,NULL,NULL,NULL,NULL,
// old actua		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
// old actua		NULL,NULL,NULL,NULL,NULL,NULL,NULL,
// old actua		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
// old actua		NULL,NULL,NULL,NULL,NULL,NULL,NULL,
// old actua		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
// old actua		NULL,NULL,NULL,NULL,NULL,NULL,NULL,
// old actua		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
// old actua		NULL,NULL,NULL,NULL,NULL,NULL,NULL,
// old actua		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
// old actua		NULL,NULL,NULL,NULL,NULL,NULL,NULL,
// old actua		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
// old actua		NULL,NULL,NULL,NULL,NULL,NULL,NULL,
// old actua		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
// old actua		},
// old actua
// old actua		{
// old actua		-14,6,
// old actua		-14,22,		
// old actua		-14,38,
// old actua// 16 TEAMS
// old actua		SHADOWtextON|SFONT|CENTREjustifyTEXT, LARGE|SHADOW, CHOOSE_TEAM_NAME, 
// old actua		TABx16TEAMS+(sprite_S62width/2),                             A03yPOS-2+(0*A03yOFFSET)+76, 
// old actua                TABx16TEAMS,                                                 A03yPOS-2+(0*A03yOFFSET)+16,
// old actua                TABx16TEAMS,                                                 A03yPOS-2+(0*A03yOFFSET)+16,
// old actua		TABx16TEAMS+sprite_S62width,				     A03yPOS-2+(0*A03yOFFSET)+16+sprite_S62height+24,
// old actua                TABx16TEAMS-16,                                              A03yPOS-2+(0*A03yOFFSET)+76,
// old actua		sprite_S62width+28,				             24,
// old actua
// old actua		SHADOWtextON|SFONT|CENTREjustifyTEXT, LARGE|SHADOW, CHOOSE_TEAM_NAME,
// old actua		(2*TABx16TEAMS)+(sprite_S62width)+(sprite_S62width/2),       A03yPOS-2+(0*A03yOFFSET)+76, 
// old actua                (2*TABx16TEAMS)+(sprite_S62width),                           A03yPOS-2+(0*A03yOFFSET)+16,
// old actua                (2*TABx16TEAMS)+(sprite_S62width),                           A03yPOS-2+(0*A03yOFFSET)+16,
// old actua		(2*TABx16TEAMS)+(sprite_S62width)+sprite_S62width,	     A03yPOS-2+(0*A03yOFFSET)+16+sprite_S62height+24,
// old actua                (2*TABx16TEAMS)+(sprite_S62width)-16,                        A03yPOS-2+(0*A03yOFFSET)+76,
// old actua		sprite_S62width+28,				             24,
// old actua
// old actua		SHADOWtextON|SFONT|CENTREjustifyTEXT, LARGE|SHADOW, CHOOSE_TEAM_NAME,
// old actua		(3*TABx16TEAMS)+(2*sprite_S62width)+(sprite_S62width/2),     A03yPOS-2+(0*A03yOFFSET)+76, 
// old actua                (3*TABx16TEAMS)+(2*sprite_S62width),                         A03yPOS-2+(0*A03yOFFSET)+16,
// old actua                (3*TABx16TEAMS)+(2*sprite_S62width),                         A03yPOS-2+(0*A03yOFFSET)+16,
// old actua		(3*TABx16TEAMS)+(2*sprite_S62width)+sprite_S62width,	     A03yPOS-2+(0*A03yOFFSET)+16+sprite_S62height+24,
// old actua                (3*TABx16TEAMS)+(2*sprite_S62width)-16,                      A03yPOS-2+(0*A03yOFFSET)+76,
// old actua		sprite_S62width+28,				             24,
// old actua
// old actua		SHADOWtextON|SFONT|CENTREjustifyTEXT, LARGE|SHADOW, CHOOSE_TEAM_NAME,
// old actua		(4*TABx16TEAMS)+(3*sprite_S62width)+(sprite_S62width/2),     A03yPOS-2+(0*A03yOFFSET)+76, 
// old actua                (4*TABx16TEAMS)+(3*sprite_S62width),                         A03yPOS-2+(0*A03yOFFSET)+16,
// old actua                (4*TABx16TEAMS)+(3*sprite_S62width),                         A03yPOS-2+(0*A03yOFFSET)+16,
// old actua		(4*TABx16TEAMS)+(3*sprite_S62width)+sprite_S62width,	     A03yPOS-2+(0*A03yOFFSET)+16+sprite_S62height+24,
// old actua                (4*TABx16TEAMS)+(3*sprite_S62width)-16,                      A03yPOS-2+(0*A03yOFFSET)+76,
// old actua		sprite_S62width+28,				             24,
// old actua
// old actua
// old actua		SHADOWtextON|SFONT|CENTREjustifyTEXT, LARGE|SHADOW, CHOOSE_TEAM_NAME,
// old actua		TABx16TEAMS+(sprite_S62width/2),                             A03yPOS-2+(3*A03yOFFSET)+76-8, 
// old actua                TABx16TEAMS,                                                 A03yPOS-2+(3*A03yOFFSET)+16-8,
// old actua                TABx16TEAMS,                                                 A03yPOS-2+(3*A03yOFFSET)+16-8,
// old actua		TABx16TEAMS+sprite_S62width,				     A03yPOS-2+(3*A03yOFFSET)+16-8+sprite_S62height+24,
// old actua                TABx16TEAMS-16,                                              A03yPOS-2+(3*A03yOFFSET)+76-8,
// old actua		sprite_S62width+28,				             24,
// old actua
// old actua		SHADOWtextON|SFONT|CENTREjustifyTEXT, LARGE|SHADOW, CHOOSE_TEAM_NAME,
// old actua		(2*TABx16TEAMS)+(sprite_S62width)+(sprite_S62width/2),       A03yPOS-2+(3*A03yOFFSET)+76-8, 
// old actua                (2*TABx16TEAMS)+(sprite_S62width),                           A03yPOS-2+(3*A03yOFFSET)+16-8,
// old actua                (2*TABx16TEAMS)+(sprite_S62width),                           A03yPOS-2+(3*A03yOFFSET)+16-8,
// old actua		(2*TABx16TEAMS)+(sprite_S62width)+sprite_S62width,	     A03yPOS-2+(3*A03yOFFSET)+16-8+sprite_S62height+24,
// old actua                (2*TABx16TEAMS)+(sprite_S62width)-16,                        A03yPOS-2+(3*A03yOFFSET)+76-8,
// old actua		sprite_S62width+28,				             24,
// old actua
// old actua		SHADOWtextON|SFONT|CENTREjustifyTEXT, LARGE|SHADOW, CHOOSE_TEAM_NAME,
// old actua		(3*TABx16TEAMS)+(2*sprite_S62width)+(sprite_S62width/2),     A03yPOS-2+(3*A03yOFFSET)+76-8, 
// old actua                (3*TABx16TEAMS)+(2*sprite_S62width),                         A03yPOS-2+(3*A03yOFFSET)+16-8,
// old actua                (3*TABx16TEAMS)+(2*sprite_S62width),                         A03yPOS-2+(3*A03yOFFSET)+16-8,
// old actua		(3*TABx16TEAMS)+(2*sprite_S62width)+sprite_S62width,	     A03yPOS-2+(3*A03yOFFSET)+16-8+sprite_S62height+24,
// old actua                (3*TABx16TEAMS)+(2*sprite_S62width)-16,                      A03yPOS-2+(3*A03yOFFSET)+76-8,
// old actua		sprite_S62width+28,				             24,
// old actua
// old actua		SHADOWtextON|SFONT|CENTREjustifyTEXT, LARGE|SHADOW, CHOOSE_TEAM_NAME,
// old actua		(4*TABx16TEAMS)+(3*sprite_S62width)+(sprite_S62width/2),     A03yPOS-2+(3*A03yOFFSET)+76-8, 
// old actua                (4*TABx16TEAMS)+(3*sprite_S62width),                         A03yPOS-2+(3*A03yOFFSET)+16-8,
// old actua                (4*TABx16TEAMS)+(3*sprite_S62width),                         A03yPOS-2+(3*A03yOFFSET)+16-8,
// old actua		(4*TABx16TEAMS)+(3*sprite_S62width)+sprite_S62width,	     A03yPOS-2+(3*A03yOFFSET)+16-8+sprite_S62height+24,
// old actua                (4*TABx16TEAMS)+(3*sprite_S62width)-16,                      A03yPOS-2+(3*A03yOFFSET)+76-8,
// old actua		sprite_S62width+28,				             24,
// old actua
// old actua
// old actua		SHADOWtextON|SFONT|CENTREjustifyTEXT, LARGE|SHADOW, CHOOSE_TEAM_NAME,
// old actua		TABx16TEAMS+(sprite_S62width/2),                             A03yPOS-2+(6*A03yOFFSET)+76-16, 
// old actua                TABx16TEAMS,                                                 A03yPOS-2+(6*A03yOFFSET)+16-16,
// old actua                TABx16TEAMS,                                                 A03yPOS-2+(6*A03yOFFSET)+16-16,
// old actua		TABx16TEAMS+sprite_S62width,				     A03yPOS-2+(6*A03yOFFSET)+16-16+sprite_S62height+24,
// old actua                TABx16TEAMS-16,                                              A03yPOS-2+(6*A03yOFFSET)+76-16,
// old actua		sprite_S62width+28,				             24,
// old actua
// old actua		SHADOWtextON|SFONT|CENTREjustifyTEXT, LARGE|SHADOW, CHOOSE_TEAM_NAME,
// old actua		(2*TABx16TEAMS)+(sprite_S62width)+(sprite_S62width/2),       A03yPOS-2+(6*A03yOFFSET)+76-16, 
// old actua                (2*TABx16TEAMS)+(sprite_S62width),                           A03yPOS-2+(6*A03yOFFSET)+16-16,
// old actua                (2*TABx16TEAMS)+(sprite_S62width),                           A03yPOS-2+(6*A03yOFFSET)+16-16,
// old actua		(2*TABx16TEAMS)+(sprite_S62width)+sprite_S62width,	     A03yPOS-2+(6*A03yOFFSET)+16-16+sprite_S62height+24,
// old actua                (2*TABx16TEAMS)+(sprite_S62width)-16,                        A03yPOS-2+(6*A03yOFFSET)+76-16,
// old actua		sprite_S62width+28,				             24,
// old actua
// old actua		SHADOWtextON|SFONT|CENTREjustifyTEXT, LARGE|SHADOW, CHOOSE_TEAM_NAME,
// old actua		(3*TABx16TEAMS)+(2*sprite_S62width)+(sprite_S62width/2),     A03yPOS-2+(6*A03yOFFSET)+76-16, 
// old actua                (3*TABx16TEAMS)+(2*sprite_S62width),                         A03yPOS-2+(6*A03yOFFSET)+16-16,
// old actua                (3*TABx16TEAMS)+(2*sprite_S62width),                         A03yPOS-2+(6*A03yOFFSET)+16-16,
// old actua		(3*TABx16TEAMS)+(2*sprite_S62width)+sprite_S62width,	     A03yPOS-2+(6*A03yOFFSET)+16-16+sprite_S62height+24,
// old actua                (3*TABx16TEAMS)+(2*sprite_S62width)-16,                      A03yPOS-2+(6*A03yOFFSET)+76-16,
// old actua		sprite_S62width+28,				             24,
// old actua
// old actua		SHADOWtextON|SFONT|CENTREjustifyTEXT, LARGE|SHADOW, CHOOSE_TEAM_NAME,
// old actua		(4*TABx16TEAMS)+(3*sprite_S62width)+(sprite_S62width/2),     A03yPOS-2+(6*A03yOFFSET)+76-16, 
// old actua                (4*TABx16TEAMS)+(3*sprite_S62width),                         A03yPOS-2+(6*A03yOFFSET)+16-16,
// old actua                (4*TABx16TEAMS)+(3*sprite_S62width),                         A03yPOS-2+(6*A03yOFFSET)+16-16,
// old actua		(4*TABx16TEAMS)+(3*sprite_S62width)+sprite_S62width,	     A03yPOS-2+(6*A03yOFFSET)+16-16+sprite_S62height+24,
// old actua                (4*TABx16TEAMS)+(3*sprite_S62width)-16,                      A03yPOS-2+(6*A03yOFFSET)+76-16,
// old actua		sprite_S62width+28,				             24,
// old actua
// old actua
// old actua		SHADOWtextON|SFONT|CENTREjustifyTEXT, LARGE|SHADOW, CHOOSE_TEAM_NAME,
// old actua		TABx16TEAMS+(sprite_S62width/2),                             A03yPOS-2+(9*A03yOFFSET)+76-24, 
// old actua                TABx16TEAMS,                                                 A03yPOS-2+(9*A03yOFFSET)+16-24,
// old actua                TABx16TEAMS,                                                 A03yPOS-2+(9*A03yOFFSET)+16-24,
// old actua		TABx16TEAMS+sprite_S62width,				     A03yPOS-2+(9*A03yOFFSET)+16-24+sprite_S62height+24,
// old actua                TABx16TEAMS-16,                                              A03yPOS-2+(9*A03yOFFSET)+76-24,
// old actua		sprite_S62width+28,				             24,
// old actua
// old actua		SHADOWtextON|SFONT|CENTREjustifyTEXT, LARGE|SHADOW, CHOOSE_TEAM_NAME,
// old actua		(2*TABx16TEAMS)+(sprite_S62width)+(sprite_S62width/2),       A03yPOS-2+(9*A03yOFFSET)+76-24, 
// old actua                (2*TABx16TEAMS)+(sprite_S62width),                           A03yPOS-2+(9*A03yOFFSET)+16-24,
// old actua                (2*TABx16TEAMS)+(sprite_S62width),                           A03yPOS-2+(9*A03yOFFSET)+16-24,
// old actua		(2*TABx16TEAMS)+(sprite_S62width)+sprite_S62width,	     A03yPOS-2+(9*A03yOFFSET)+16-24+sprite_S62height+24,
// old actua                (2*TABx16TEAMS)+(sprite_S62width)-16,                        A03yPOS-2+(9*A03yOFFSET)+76-24,
// old actua		sprite_S62width+28,				             24,
// old actua
// old actua		SHADOWtextON|SFONT|CENTREjustifyTEXT, LARGE|SHADOW, CHOOSE_TEAM_NAME,
// old actua		(3*TABx16TEAMS)+(2*sprite_S62width)+(sprite_S62width/2),     A03yPOS-2+(9*A03yOFFSET)+76-24, 
// old actua                (3*TABx16TEAMS)+(2*sprite_S62width),                         A03yPOS-2+(9*A03yOFFSET)+16-24,
// old actua                (3*TABx16TEAMS)+(2*sprite_S62width),                         A03yPOS-2+(9*A03yOFFSET)+16-24,
// old actua		(3*TABx16TEAMS)+(2*sprite_S62width)+sprite_S62width,	     A03yPOS-2+(9*A03yOFFSET)+16-24+sprite_S62height+24,
// old actua                (3*TABx16TEAMS)+(2*sprite_S62width)-16,                      A03yPOS-2+(9*A03yOFFSET)+76-24,
// old actua		sprite_S62width+28,				             24,
// old actua
// old actua		SHADOWtextON|SFONT|CENTREjustifyTEXT, LARGE|SHADOW, CHOOSE_TEAM_NAME,
// old actua		(4*TABx16TEAMS)+(3*sprite_S62width)+(sprite_S62width/2),     A03yPOS-2+(9*A03yOFFSET)+76-24, 
// old actua                (4*TABx16TEAMS)+(3*sprite_S62width),                         A03yPOS-2+(9*A03yOFFSET)+16-24,
// old actua                (4*TABx16TEAMS)+(3*sprite_S62width),                         A03yPOS-2+(9*A03yOFFSET)+16-24,
// old actua		(4*TABx16TEAMS)+(3*sprite_S62width)+sprite_S62width,	     A03yPOS-2+(9*A03yOFFSET)+16-24+sprite_S62height+24,
// old actua                (4*TABx16TEAMS)+(3*sprite_S62width)-16,                      A03yPOS-2+(9*A03yOFFSET)+76-24,
// old actua		sprite_S62width+28,				             24,
// old actua
// old actua
// old actua		NULL,NULL,NULL,NULL,NULL,NULL,NULL,
// old actua		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
// old actua		NULL,NULL,NULL,NULL,NULL,NULL,NULL,
// old actua		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
// old actua		NULL,NULL,NULL,NULL,NULL,NULL,NULL,
// old actua		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
// old actua		NULL,NULL,NULL,NULL,NULL,NULL,NULL,
// old actua		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
// old actua		NULL,NULL,NULL,NULL,NULL,NULL,NULL,
// old actua		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
// old actua		NULL,NULL,NULL,NULL,NULL,NULL,NULL,
// old actua		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
// old actua		NULL,NULL,NULL,NULL,NULL,NULL,NULL,
// old actua		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
// old actua		NULL,NULL,NULL,NULL,NULL,NULL,NULL,
// old actua		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
// old actua		NULL,NULL,NULL,NULL,NULL,NULL,NULL,
// old actua		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
// old actua		NULL,NULL,NULL,NULL,NULL,NULL,NULL,
// old actua		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
// old actua		NULL,NULL,NULL,NULL,NULL,NULL,NULL,
// old actua		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
// old actua		NULL,NULL,NULL,NULL,NULL,NULL,NULL,
// old actua		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
// old actua		NULL,NULL,NULL,NULL,NULL,NULL,NULL,
// old actua		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
// old actua		NULL,NULL,NULL,NULL,NULL,NULL,NULL,
// old actua		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
// old actua		NULL,NULL,NULL,NULL,NULL,NULL,NULL,
// old actua		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
// old actua		NULL,NULL,NULL,NULL,NULL,NULL,NULL,
// old actua		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
// old actua		NULL,NULL,NULL,NULL,NULL,NULL,NULL,
// old actua		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
// old actua		NULL,NULL,NULL,NULL,NULL,NULL,NULL,
// old actua		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
// old actua		NULL,NULL,NULL,NULL,NULL,NULL,NULL,
// old actua		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
// old actua		NULL,NULL,NULL,NULL,NULL,NULL,NULL,
// old actua		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
// old actua		NULL,NULL,NULL,NULL,NULL,NULL,NULL,
// old actua		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
// old actua		NULL,NULL,NULL,NULL,NULL,NULL,NULL,
// old actua		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
// old actua		NULL,NULL,NULL,NULL,NULL,NULL,NULL,
// old actua		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
// old actua		NULL,NULL,NULL,NULL,NULL,NULL,NULL,
// old actua		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
// old actua		NULL,NULL,NULL,NULL,NULL,NULL,NULL,
// old actua		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
// old actua		NULL,NULL,NULL,NULL,NULL,NULL,NULL,
// old actua		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
// old actua		NULL,NULL,NULL,NULL,NULL,NULL,NULL,
// old actua		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
// old actua		NULL,NULL,NULL,NULL,NULL,NULL,NULL,
// old actua		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
// old actua		},
// old actua
// old actua
// old actua
// old actua
// old actua		{
// old actua		50,4,
// old actua		66,4,		
// old actua		82,4,
// old actua// 32 TEAMS
// old actua		SHADOWtextON|SFONT|CENTREjustifyTEXT, SMALL|SHADOW, CHOOSE_TEAM_NAME, 
// old actua		(1*TABx32TEAMS)+(sprite_S62width/4),                          A03yPOS-14+(0*A03yOFFSET)+54, 
// old actua		(1*TABx32TEAMS),                          	              A03yPOS-14+(0*A03yOFFSET)+24,
// old actua		(1*TABx32TEAMS),                          	              A03yPOS-14+(0*A03yOFFSET)+24,
// old actua		(1*TABx32TEAMS)+(sprite_S62width/2),                          A03yPOS-14+(0*A03yOFFSET)+24+(sprite_S62height/2)+20, 
// old actua		(1*TABx32TEAMS)-36,                          		      A03yPOS-14+(0*A03yOFFSET)+54, 
// old actua		(sprite_S62width/2)+74,                                       24, 
// old actua				
// old actua		SHADOWtextON|SFONT|CENTREjustifyTEXT, SMALL|SHADOW, CHOOSE_TEAM_NAME, 
// old actua		(3*TABx32TEAMS)+(1*(sprite_S62width/2))+(sprite_S62width/4),  A03yPOS-14+(0*A03yOFFSET)+54, 
// old actua		(3*TABx32TEAMS)+(1*(sprite_S62width/2)), 		      A03yPOS-14+(0*A03yOFFSET)+24,
// old actua		(3*TABx32TEAMS)+(1*(sprite_S62width/2)),                      A03yPOS-14+(0*A03yOFFSET)+24,
// old actua		(3*TABx32TEAMS)+(1*(sprite_S62width/2))+(sprite_S62width/2),  A03yPOS-14+(0*A03yOFFSET)+24+(sprite_S62height/2)+20, 
// old actua		(3*TABx32TEAMS)+(1*(sprite_S62width/2))-36,                   A03yPOS-14+(0*A03yOFFSET)+54, 
// old actua		(sprite_S62width/2)+74,                                       24, 
// old actua
// old actua		SHADOWtextON|SFONT|CENTREjustifyTEXT, SMALL|SHADOW, CHOOSE_TEAM_NAME, 
// old actua                (5*TABx32TEAMS)+(2*(sprite_S62width/2))+(sprite_S62width/4),  A03yPOS-14+(0*A03yOFFSET)+54, 
// old actua                (5*TABx32TEAMS)+(2*(sprite_S62width/2)),                      A03yPOS-14+(0*A03yOFFSET)+24,
// old actua		(5*TABx32TEAMS)+(2*(sprite_S62width/2)),                      A03yPOS-14+(0*A03yOFFSET)+24,
// old actua		(5*TABx32TEAMS)+(2*(sprite_S62width/2))+(sprite_S62width/2),  A03yPOS-14+(0*A03yOFFSET)+24+(sprite_S62height/2)+20, 
// old actua		(5*TABx32TEAMS)+(2*(sprite_S62width/2))-36,                   A03yPOS-14+(0*A03yOFFSET)+54, 
// old actua		(sprite_S62width/2)+74,                                       24, 
// old actua
// old actua		SHADOWtextON|SFONT|CENTREjustifyTEXT, SMALL|SHADOW, CHOOSE_TEAM_NAME, 
// old actua                (7*TABx32TEAMS)+(3*(sprite_S62width/2))+(sprite_S62width/4),  A03yPOS-14+(0*A03yOFFSET)+54, 
// old actua                (7*TABx32TEAMS)+(3*(sprite_S62width/2)),                      A03yPOS-14+(0*A03yOFFSET)+24,
// old actua		(7*TABx32TEAMS)+(3*(sprite_S62width/2)),                      A03yPOS-14+(0*A03yOFFSET)+24,
// old actua		(7*TABx32TEAMS)+(3*(sprite_S62width/2))+(sprite_S62width/2),  A03yPOS-14+(0*A03yOFFSET)+24+(sprite_S62height/2)+20, 
// old actua		(7*TABx32TEAMS)+(3*(sprite_S62width/2))-36,                   A03yPOS-14+(0*A03yOFFSET)+54, 
// old actua		(sprite_S62width/2)+74,                                       24, 
// old actua
// old actua		SHADOWtextON|SFONT|CENTREjustifyTEXT, SMALL|SHADOW, CHOOSE_TEAM_NAME, 
// old actua                (9*TABx32TEAMS)+(4*(sprite_S62width/2))+(sprite_S62width/4),  A03yPOS-14+(0*A03yOFFSET)+54, 
// old actua		(9*TABx32TEAMS)+(4*(sprite_S62width/2)),                      A03yPOS-14+(0*A03yOFFSET)+24,
// old actua		(9*TABx32TEAMS)+(4*(sprite_S62width/2)),                      A03yPOS-14+(0*A03yOFFSET)+24,
// old actua		(9*TABx32TEAMS)+(4*(sprite_S62width/2))+(sprite_S62width/2),  A03yPOS-14+(0*A03yOFFSET)+24+(sprite_S62height/2)+20, 
// old actua		(9*TABx32TEAMS)+(4*(sprite_S62width/2))-36,                   A03yPOS-14+(0*A03yOFFSET)+54, 
// old actua		(sprite_S62width/2)+74,                                       24, 
// old actua
// old actua		SHADOWtextON|SFONT|CENTREjustifyTEXT, SMALL|SHADOW, CHOOSE_TEAM_NAME, 
// old actua                (1*TABx32TEAMS)+(sprite_S62width/4),                          A03yPOS-14+(2*A03yOFFSET)+54-8, 
// old actua		(1*TABx32TEAMS),                                              A03yPOS-14+(2*A03yOFFSET)+24-8,
// old actua		(1*TABx32TEAMS),                          	              A03yPOS-14+(2*A03yOFFSET)+24-8,
// old actua		(1*TABx32TEAMS)+(sprite_S62width/2),                          A03yPOS-14+(2*A03yOFFSET)+24-8+(sprite_S62height/2)+20, 
// old actua		(1*TABx32TEAMS)-36,                          		      A03yPOS-14+(2*A03yOFFSET)+54-8, 
// old actua		(sprite_S62width/2)+74,                                       24, 
// old actua
// old actua		SHADOWtextON|SFONT|CENTREjustifyTEXT, SMALL|SHADOW, CHOOSE_TEAM_NAME, 
// old actua                (3*TABx32TEAMS)+(1*(sprite_S62width/2))+(sprite_S62width/4),  A03yPOS-14+(2*A03yOFFSET)+54-8, 
// old actua                (3*TABx32TEAMS)+(1*(sprite_S62width/2)),                      A03yPOS-14+(2*A03yOFFSET)+24-8,
// old actua		(3*TABx32TEAMS)+(1*(sprite_S62width/2)),                      A03yPOS-14+(2*A03yOFFSET)+24-8,
// old actua		(3*TABx32TEAMS)+(1*(sprite_S62width/2))+(sprite_S62width/2),  A03yPOS-14+(2*A03yOFFSET)+24-8+(sprite_S62height/2)+20, 
// old actua		(3*TABx32TEAMS)+(1*(sprite_S62width/2))-36,                   A03yPOS-14+(2*A03yOFFSET)+54-8, 
// old actua		(sprite_S62width/2)+74,                                       24, 
// old actua
// old actua		SHADOWtextON|SFONT|CENTREjustifyTEXT, SMALL|SHADOW, CHOOSE_TEAM_NAME, 
// old actua                (5*TABx32TEAMS)+(2*(sprite_S62width/2))+(sprite_S62width/4),  A03yPOS-14+(2*A03yOFFSET)+54-8, 
// old actua                (5*TABx32TEAMS)+(2*(sprite_S62width/2)),                      A03yPOS-14+(2*A03yOFFSET)+24-8,
// old actua		(5*TABx32TEAMS)+(2*(sprite_S62width/2)),                      A03yPOS-14+(2*A03yOFFSET)+24-8,
// old actua		(5*TABx32TEAMS)+(2*(sprite_S62width/2))+(sprite_S62width/2),  A03yPOS-14+(2*A03yOFFSET)+24-8+(sprite_S62height/2)+20, 
// old actua		(5*TABx32TEAMS)+(2*(sprite_S62width/2))-36,                   A03yPOS-14+(2*A03yOFFSET)+54-8, 
// old actua		(sprite_S62width/2)+74,                                       24, 
// old actua				
// old actua		SHADOWtextON|SFONT|CENTREjustifyTEXT, SMALL|SHADOW, CHOOSE_TEAM_NAME, 
// old actua                (7*TABx32TEAMS)+(3*(sprite_S62width/2))+(sprite_S62width/4),  A03yPOS-14+(2*A03yOFFSET)+54-8, 
// old actua                (7*TABx32TEAMS)+(3*(sprite_S62width/2)),                      A03yPOS-14+(2*A03yOFFSET)+24-8,
// old actua		(7*TABx32TEAMS)+(3*(sprite_S62width/2)),                      A03yPOS-14+(2*A03yOFFSET)+24-8,
// old actua		(7*TABx32TEAMS)+(3*(sprite_S62width/2))+(sprite_S62width/2),  A03yPOS-14+(2*A03yOFFSET)+24-8+(sprite_S62height/2)+20, 
// old actua		(7*TABx32TEAMS)+(3*(sprite_S62width/2))-36,                   A03yPOS-14+(2*A03yOFFSET)+54-8, 
// old actua		(sprite_S62width/2)+74,                                       24, 
// old actua
// old actua		SHADOWtextON|SFONT|CENTREjustifyTEXT, SMALL|SHADOW, CHOOSE_TEAM_NAME, 
// old actua                (9*TABx32TEAMS)+(4*(sprite_S62width/2))+(sprite_S62width/4),  A03yPOS-14+(2*A03yOFFSET)+54-8, 
// old actua                (9*TABx32TEAMS)+(4*(sprite_S62width/2)),                      A03yPOS-14+(2*A03yOFFSET)+24-8,
// old actua		(9*TABx32TEAMS)+(4*(sprite_S62width/2)),                      A03yPOS-14+(2*A03yOFFSET)+24-8,
// old actua		(9*TABx32TEAMS)+(4*(sprite_S62width/2))+(sprite_S62width/2),  A03yPOS-14+(2*A03yOFFSET)+24-8+(sprite_S62height/2)+20, 
// old actua		(9*TABx32TEAMS)+(4*(sprite_S62width/2))-36,                   A03yPOS-14+(2*A03yOFFSET)+54-8, 
// old actua		(sprite_S62width/2)+74,                                       24, 
// old actua
// old actua		SHADOWtextON|SFONT|CENTREjustifyTEXT, SMALL|SHADOW, CHOOSE_TEAM_NAME, 
// old actua                (1*TABx32TEAMS)+(sprite_S62width/4),                          A03yPOS-14+(4*A03yOFFSET)+54-16, 
// old actua                (1*TABx32TEAMS),                                              A03yPOS-14+(4*A03yOFFSET)+24-16,
// old actua		(1*TABx32TEAMS),                          	              A03yPOS-14+(4*A03yOFFSET)+24-16,
// old actua		(1*TABx32TEAMS)+(sprite_S62width/2),                          A03yPOS-14+(4*A03yOFFSET)+24-16+(sprite_S62height/2)+20, 
// old actua		(1*TABx32TEAMS)-36,                          		      A03yPOS-14+(4*A03yOFFSET)+54-16, 
// old actua		(sprite_S62width/2)+74,                                       24, 
// old actua
// old actua		SHADOWtextON|SFONT|CENTREjustifyTEXT, SMALL|SHADOW, CHOOSE_TEAM_NAME, 
// old actua                (3*TABx32TEAMS)+(1*(sprite_S62width/2))+(sprite_S62width/4),  A03yPOS-14+(4*A03yOFFSET)+54-16, 
// old actua                (3*TABx32TEAMS)+(1*(sprite_S62width/2)),                      A03yPOS-14+(4*A03yOFFSET)+24-16,
// old actua		(3*TABx32TEAMS)+(1*(sprite_S62width/2)),                      A03yPOS-14+(4*A03yOFFSET)+24-16,
// old actua		(3*TABx32TEAMS)+(1*(sprite_S62width/2))+(sprite_S62width/2),  A03yPOS-14+(4*A03yOFFSET)+24-16+(sprite_S62height/2)+20, 
// old actua		(3*TABx32TEAMS)+(1*(sprite_S62width/2))-36,                   A03yPOS-14+(4*A03yOFFSET)+54-16, 
// old actua		(sprite_S62width/2)+74,                                       24, 
// old actua
// old actua		SHADOWtextON|SFONT|CENTREjustifyTEXT, SMALL|SHADOW, CHOOSE_TEAM_NAME, 
// old actua                (5*TABx32TEAMS)+(2*(sprite_S62width/2))+(sprite_S62width/4),  A03yPOS-14+(4*A03yOFFSET)+54-16, 
// old actua                (5*TABx32TEAMS)+(2*(sprite_S62width/2)),                      A03yPOS-14+(4*A03yOFFSET)+24-16,
// old actua		(5*TABx32TEAMS)+(2*(sprite_S62width/2)),                      A03yPOS-14+(4*A03yOFFSET)+24-16,
// old actua		(5*TABx32TEAMS)+(2*(sprite_S62width/2))+(sprite_S62width/2),  A03yPOS-14+(4*A03yOFFSET)+24-16+(sprite_S62height/2)+20, 
// old actua		(5*TABx32TEAMS)+(2*(sprite_S62width/2))-36,                   A03yPOS-14+(4*A03yOFFSET)+54-16, 
// old actua		(sprite_S62width/2)+74,                                       24, 
// old actua				
// old actua		SHADOWtextON|SFONT|CENTREjustifyTEXT, SMALL|SHADOW, CHOOSE_TEAM_NAME, 
// old actua                (7*TABx32TEAMS)+(3*(sprite_S62width/2))+(sprite_S62width/4),  A03yPOS-14+(4*A03yOFFSET)+54-16, 
// old actua                (7*TABx32TEAMS)+(3*(sprite_S62width/2)),                      A03yPOS-14+(4*A03yOFFSET)+24-16,
// old actua		(7*TABx32TEAMS)+(3*(sprite_S62width/2)),                      A03yPOS-14+(4*A03yOFFSET)+24-16,
// old actua		(7*TABx32TEAMS)+(3*(sprite_S62width/2))+(sprite_S62width/2),  A03yPOS-14+(4*A03yOFFSET)+24-16+(sprite_S62height/2)+20, 
// old actua		(7*TABx32TEAMS)+(3*(sprite_S62width/2))-36,                   A03yPOS-14+(4*A03yOFFSET)+54-16, 
// old actua		(sprite_S62width/2)+74,                                       24, 
// old actua				
// old actua		SHADOWtextON|SFONT|CENTREjustifyTEXT, SMALL|SHADOW, CHOOSE_TEAM_NAME, 
// old actua                (9*TABx32TEAMS)+(4*(sprite_S62width/2))+(sprite_S62width/4),  A03yPOS-14+(4*A03yOFFSET)+54-16, 
// old actua                (9*TABx32TEAMS)+(4*(sprite_S62width/2)),                      A03yPOS-14+(4*A03yOFFSET)+24-16,
// old actua		(9*TABx32TEAMS)+(4*(sprite_S62width/2)),                      A03yPOS-14+(4*A03yOFFSET)+24-16,
// old actua		(9*TABx32TEAMS)+(4*(sprite_S62width/2))+(sprite_S62width/2),  A03yPOS-14+(4*A03yOFFSET)+24-16+(sprite_S62height/2)+20, 
// old actua		(9*TABx32TEAMS)+(4*(sprite_S62width/2))-36,                   A03yPOS-14+(4*A03yOFFSET)+54-16, 
// old actua		(sprite_S62width/2)+74,                                       24, 
// old actua
// old actua		SHADOWtextON|SFONT|CENTREjustifyTEXT, SMALL|SHADOW, CHOOSE_TEAM_NAME, 
// old actua                (1*TABx32TEAMS)+(sprite_S62width/4),                          A03yPOS-14+(6*A03yOFFSET)+54-24, 
// old actua                (1*TABx32TEAMS),                                              A03yPOS-14+(6*A03yOFFSET)+24-24,
// old actua		(1*TABx32TEAMS),                          	              A03yPOS-14+(6*A03yOFFSET)+24-24,
// old actua		(1*TABx32TEAMS)+(sprite_S62width/2),                          A03yPOS-14+(6*A03yOFFSET)+24-24+(sprite_S62height/2)+20, 
// old actua		(1*TABx32TEAMS)-36,                          		      A03yPOS-14+(6*A03yOFFSET)+54-24, 
// old actua		(sprite_S62width/2)+74,                                       24, 
// old actua
// old actua		SHADOWtextON|SFONT|CENTREjustifyTEXT, SMALL|SHADOW, CHOOSE_TEAM_NAME, 
// old actua                (3*TABx32TEAMS)+(1*(sprite_S62width/2))+(sprite_S62width/4),  A03yPOS-14+(6*A03yOFFSET)+54-24, 
// old actua                (3*TABx32TEAMS)+(1*(sprite_S62width/2)),                      A03yPOS-14+(6*A03yOFFSET)+24-24,
// old actua		(3*TABx32TEAMS)+(1*(sprite_S62width/2)),                      A03yPOS-14+(6*A03yOFFSET)+24-24,
// old actua		(3*TABx32TEAMS)+(1*(sprite_S62width/2))+(sprite_S62width/2),  A03yPOS-14+(6*A03yOFFSET)+24-24+(sprite_S62height/2)+20, 
// old actua		(3*TABx32TEAMS)+(1*(sprite_S62width/2))-36,                   A03yPOS-14+(6*A03yOFFSET)+54-24, 
// old actua		(sprite_S62width/2)+74,                                       24, 
// old actua				
// old actua		SHADOWtextON|SFONT|CENTREjustifyTEXT, SMALL|SHADOW, CHOOSE_TEAM_NAME, 
// old actua                (5*TABx32TEAMS)+(2*(sprite_S62width/2))+(sprite_S62width/4),  A03yPOS-14+(6*A03yOFFSET)+54-24, 
// old actua	        (5*TABx32TEAMS)+(2*(sprite_S62width/2)),                      A03yPOS-14+(6*A03yOFFSET)+24-24,
// old actua		(5*TABx32TEAMS)+(2*(sprite_S62width/2)),                      A03yPOS-14+(6*A03yOFFSET)+24-24,
// old actua		(5*TABx32TEAMS)+(2*(sprite_S62width/2))+(sprite_S62width/2),  A03yPOS-14+(6*A03yOFFSET)+24-24+(sprite_S62height/2)+20, 
// old actua		(5*TABx32TEAMS)+(2*(sprite_S62width/2))-36,                   A03yPOS-14+(6*A03yOFFSET)+54-24, 
// old actua		(sprite_S62width/2)+74,                                       24, 
// old actua				
// old actua		SHADOWtextON|SFONT|CENTREjustifyTEXT, SMALL|SHADOW, CHOOSE_TEAM_NAME, 
// old actua                (7*TABx32TEAMS)+(3*(sprite_S62width/2))+(sprite_S62width/4),  A03yPOS-14+(6*A03yOFFSET)+54-24, 
// old actua                (7*TABx32TEAMS)+(3*(sprite_S62width/2)),                      A03yPOS-14+(6*A03yOFFSET)+24-24,
// old actua		(7*TABx32TEAMS)+(3*(sprite_S62width/2)),                      A03yPOS-14+(6*A03yOFFSET)+24-24,
// old actua		(7*TABx32TEAMS)+(3*(sprite_S62width/2))+(sprite_S62width/2),  A03yPOS-14+(6*A03yOFFSET)+24-24+(sprite_S62height/2)+20, 
// old actua		(7*TABx32TEAMS)+(3*(sprite_S62width/2))-36,                   A03yPOS-14+(6*A03yOFFSET)+54-24, 
// old actua		(sprite_S62width/2)+74,                                       24, 
// old actua				
// old actua		SHADOWtextON|SFONT|CENTREjustifyTEXT, SMALL|SHADOW, CHOOSE_TEAM_NAME, 
// old actua                (9*TABx32TEAMS)+(4*(sprite_S62width/2))+(sprite_S62width/4),  A03yPOS-14+(6*A03yOFFSET)+54-24, 
// old actua                (9*TABx32TEAMS)+(4*(sprite_S62width/2)),                      A03yPOS-14+(6*A03yOFFSET)+24-24,
// old actua		(9*TABx32TEAMS)+(4*(sprite_S62width/2)),                      A03yPOS-14+(6*A03yOFFSET)+24-24,
// old actua		(9*TABx32TEAMS)+(4*(sprite_S62width/2))+(sprite_S62width/2),  A03yPOS-14+(6*A03yOFFSET)+24-24+(sprite_S62height/2)+20, 
// old actua		(9*TABx32TEAMS)+(4*(sprite_S62width/2))-36,                   A03yPOS-14+(6*A03yOFFSET)+54-24, 
// old actua		(sprite_S62width/2)+74,                                       24, 
// old actua
// old actua		SHADOWtextON|SFONT|CENTREjustifyTEXT, SMALL|SHADOW, CHOOSE_TEAM_NAME, 
// old actua		(1*TABx32TEAMS)+(sprite_S62width/4),                          A03yPOS-14+(8*A03yOFFSET)+54-32, 
// old actua                (1*TABx32TEAMS),                                              A03yPOS-14+(8*A03yOFFSET)+24-32,
// old actua		(1*TABx32TEAMS),                          	              A03yPOS-14+(8*A03yOFFSET)+24-32,
// old actua		(1*TABx32TEAMS)+(sprite_S62width/2),                          A03yPOS-14+(8*A03yOFFSET)+24-32+(sprite_S62height/2)+20, 
// old actua		(1*TABx32TEAMS)-36,                          		      A03yPOS-14+(8*A03yOFFSET)+54-32, 
// old actua		(sprite_S62width/2)+74,                                       24, 
// old actua
// old actua		SHADOWtextON|SFONT|CENTREjustifyTEXT, SMALL|SHADOW, CHOOSE_TEAM_NAME, 
// old actua		(3*TABx32TEAMS)+(1*(sprite_S62width/2))+(sprite_S62width/4),  A03yPOS-14+(8*A03yOFFSET)+54-32, 
// old actua		(3*TABx32TEAMS)+(1*(sprite_S62width/2)), 		      A03yPOS-14+(8*A03yOFFSET)+24-32,
// old actua		(3*TABx32TEAMS)+(1*(sprite_S62width/2)),                      A03yPOS-14+(8*A03yOFFSET)+24-32,
// old actua		(3*TABx32TEAMS)+(1*(sprite_S62width/2))+(sprite_S62width/2),  A03yPOS-14+(8*A03yOFFSET)+24-32+(sprite_S62height/2)+20, 
// old actua		(3*TABx32TEAMS)+(1*(sprite_S62width/2))-36,                   A03yPOS-14+(8*A03yOFFSET)+54-32, 
// old actua		(sprite_S62width/2)+74,                                       24, 
// old actua				
// old actua		SHADOWtextON|SFONT|CENTREjustifyTEXT, SMALL|SHADOW, CHOOSE_TEAM_NAME, 
// old actua		(5*TABx32TEAMS)+(2*(sprite_S62width/2))+(sprite_S62width/4),  A03yPOS-14+(8*A03yOFFSET)+54-32, 
// old actua		(5*TABx32TEAMS)+(2*(sprite_S62width/2)), 		      A03yPOS-14+(8*A03yOFFSET)+24-32,
// old actua		(5*TABx32TEAMS)+(2*(sprite_S62width/2)),                      A03yPOS-14+(8*A03yOFFSET)+24-32,
// old actua		(5*TABx32TEAMS)+(2*(sprite_S62width/2))+(sprite_S62width/2),  A03yPOS-14+(8*A03yOFFSET)+24-32+(sprite_S62height/2)+20, 
// old actua		(5*TABx32TEAMS)+(2*(sprite_S62width/2))-36,                   A03yPOS-14+(8*A03yOFFSET)+54-32, 
// old actua		(sprite_S62width/2)+74,                                       24, 
// old actua				
// old actua		SHADOWtextON|SFONT|CENTREjustifyTEXT, SMALL|SHADOW, CHOOSE_TEAM_NAME, 
// old actua		(7*TABx32TEAMS)+(3*(sprite_S62width/2))+(sprite_S62width/4),  A03yPOS-14+(8*A03yOFFSET)+54-32, 
// old actua		(7*TABx32TEAMS)+(3*(sprite_S62width/2)), 		      A03yPOS-14+(8*A03yOFFSET)+24-32,
// old actua		(7*TABx32TEAMS)+(3*(sprite_S62width/2)),                      A03yPOS-14+(8*A03yOFFSET)+24-32,
// old actua		(7*TABx32TEAMS)+(3*(sprite_S62width/2))+(sprite_S62width/2),  A03yPOS-14+(8*A03yOFFSET)+24-32+(sprite_S62height/2)+20, 
// old actua		(7*TABx32TEAMS)+(3*(sprite_S62width/2))-36,                   A03yPOS-14+(8*A03yOFFSET)+54-32, 
// old actua		(sprite_S62width/2)+74,                                       24, 
// old actua				
// old actua		SHADOWtextON|SFONT|CENTREjustifyTEXT, SMALL|SHADOW, CHOOSE_TEAM_NAME, 
// old actua		(9*TABx32TEAMS)+(4*(sprite_S62width/2))+(sprite_S62width/4),  A03yPOS-14+(8*A03yOFFSET)+54-32, 
// old actua		(9*TABx32TEAMS)+(4*(sprite_S62width/2)), 		      A03yPOS-14+(8*A03yOFFSET)+24-32,
// old actua		(9*TABx32TEAMS)+(4*(sprite_S62width/2)),                      A03yPOS-14+(8*A03yOFFSET)+24-32,
// old actua		(9*TABx32TEAMS)+(4*(sprite_S62width/2))+(sprite_S62width/2),  A03yPOS-14+(8*A03yOFFSET)+24-32+(sprite_S62height/2)+20, 
// old actua		(9*TABx32TEAMS)+(4*(sprite_S62width/2))-36,                   A03yPOS-14+(8*A03yOFFSET)+54-32, 
// old actua		(sprite_S62width/2)+74,                                       24, 
// old actua
// old actua		SHADOWtextON|SFONT|CENTREjustifyTEXT, SMALL|SHADOW, CHOOSE_TEAM_NAME, 
// old actua		(1*TABx32TEAMS)+(sprite_S62width/4),                          A03yPOS-14+(10*A03yOFFSET)+54-40, 
// old actua		(1*TABx32TEAMS),                             		      A03yPOS-14+(10*A03yOFFSET)+24-40,
// old actua		(1*TABx32TEAMS),                          	              A03yPOS-14+(10*A03yOFFSET)+24-40,
// old actua		(1*TABx32TEAMS)+(sprite_S62width/2),                          A03yPOS-14+(10*A03yOFFSET)+24-40+(sprite_S62height/2)+20, 
// old actua		(1*TABx32TEAMS)-36,                          		      A03yPOS-14+(10*A03yOFFSET)+54-40, 
// old actua		(sprite_S62width/2)+74,                                       24, 
// old actua
// old actua		SHADOWtextON|SFONT|CENTREjustifyTEXT, SMALL|SHADOW, CHOOSE_TEAM_NAME, 
// old actua		(3*TABx32TEAMS)+(1*(sprite_S62width/2))+(sprite_S62width/4),  A03yPOS-14+(10*A03yOFFSET)+54-40, 
// old actua		(3*TABx32TEAMS)+(1*(sprite_S62width/2)),                      A03yPOS-14+(10*A03yOFFSET)+24-40,
// old actua		(3*TABx32TEAMS)+(1*(sprite_S62width/2)),                      A03yPOS-14+(10*A03yOFFSET)+24-40,
// old actua		(3*TABx32TEAMS)+(1*(sprite_S62width/2))+(sprite_S62width/2),  A03yPOS-14+(10*A03yOFFSET)+24-40+(sprite_S62height/2)+20, 
// old actua		(3*TABx32TEAMS)+(1*(sprite_S62width/2))-36,                   A03yPOS-14+(10*A03yOFFSET)+54-40, 
// old actua		(sprite_S62width/2)+74,                                       24, 
// old actua				
// old actua		SHADOWtextON|SFONT|CENTREjustifyTEXT, SMALL|SHADOW, CHOOSE_TEAM_NAME, 
// old actua                (5*TABx32TEAMS)+(2*(sprite_S62width/2))+(sprite_S62width/4),  A03yPOS-14+(10*A03yOFFSET)+54-40, 
// old actua                (5*TABx32TEAMS)+(2*(sprite_S62width/2)),                      A03yPOS-14+(10*A03yOFFSET)+24-40,
// old actua		(5*TABx32TEAMS)+(2*(sprite_S62width/2)),                      A03yPOS-14+(10*A03yOFFSET)+24-40,
// old actua		(5*TABx32TEAMS)+(2*(sprite_S62width/2))+(sprite_S62width/2),  A03yPOS-14+(10*A03yOFFSET)+24-40+(sprite_S62height/2)+20, 
// old actua		(5*TABx32TEAMS)+(2*(sprite_S62width/2))-36,                   A03yPOS-14+(10*A03yOFFSET)+54-40, 
// old actua		(sprite_S62width/2)+74,                                       24, 
// old actua				
// old actua		SHADOWtextON|SFONT|CENTREjustifyTEXT, SMALL|SHADOW, CHOOSE_TEAM_NAME, 
// old actua                (7*TABx32TEAMS)+(3*(sprite_S62width/2))+(sprite_S62width/4),  A03yPOS-14+(10*A03yOFFSET)+54-40, 
// old actua                (7*TABx32TEAMS)+(3*(sprite_S62width/2)),                      A03yPOS-14+(10*A03yOFFSET)+24-40,
// old actua		(7*TABx32TEAMS)+(3*(sprite_S62width/2)),                      A03yPOS-14+(10*A03yOFFSET)+24-40,
// old actua		(7*TABx32TEAMS)+(3*(sprite_S62width/2))+(sprite_S62width/2),  A03yPOS-14+(10*A03yOFFSET)+24-40+(sprite_S62height/2)+20, 
// old actua		(7*TABx32TEAMS)+(3*(sprite_S62width/2))-36,                   A03yPOS-14+(10*A03yOFFSET)+54-40, 
// old actua		(sprite_S62width/2)+74,                                       24, 
// old actua				
// old actua		SHADOWtextON|SFONT|CENTREjustifyTEXT, SMALL|SHADOW, CHOOSE_TEAM_NAME, 
// old actua                (9*TABx32TEAMS)+(4*(sprite_S62width/2))+(sprite_S62width/4),  A03yPOS-14+(10*A03yOFFSET)+54-40, 
// old actua		(9*TABx32TEAMS)+(4*(sprite_S62width/2)), 		      A03yPOS-14+(10*A03yOFFSET)+24-40,
// old actua		(9*TABx32TEAMS)+(4*(sprite_S62width/2)),                      A03yPOS-14+(10*A03yOFFSET)+24-40,
// old actua		(9*TABx32TEAMS)+(4*(sprite_S62width/2))+(sprite_S62width/2),  A03yPOS-14+(10*A03yOFFSET)+24-40+(sprite_S62height/2)+20, 
// old actua		(9*TABx32TEAMS)+(4*(sprite_S62width/2))-36,                   A03yPOS-14+(10*A03yOFFSET)+54-40, 
// old actua		(sprite_S62width/2)+74,                                       24, 
// old actua
// old actua		SHADOWtextON|SFONT|CENTREjustifyTEXT, SMALL|SHADOW, CHOOSE_TEAM_NAME, 
// old actua		(1*TABx32TEAMS)+(sprite_S62width/4),                          A03yPOS-14+(12*A03yOFFSET)+54-48, 
// old actua		(1*TABx32TEAMS),                             		      A03yPOS-14+(12*A03yOFFSET)+24-48,
// old actua		(1*TABx32TEAMS),                          	              A03yPOS-14+(12*A03yOFFSET)+24-48,
// old actua		(1*TABx32TEAMS)+(sprite_S62width/2),                          A03yPOS-14+(12*A03yOFFSET)+24-48+(sprite_S62height/2)+20, 
// old actua		(1*TABx32TEAMS)-36,                          		      A03yPOS-14+(12*A03yOFFSET)+54-48, 
// old actua		(sprite_S62width/2)+74,                                       24, 
// old actua
// old actua		SHADOWtextON|SFONT|CENTREjustifyTEXT, SMALL|SHADOW, CHOOSE_TEAM_NAME, 
// old actua                (9*TABx32TEAMS)+(4*(sprite_S62width/2))+(sprite_S62width/4),  A03yPOS-14+(12*A03yOFFSET)+54-48, 
// old actua                (9*TABx32TEAMS)+(4*(sprite_S62width/2)),                      A03yPOS-14+(12*A03yOFFSET)+24-48,
// old actua		(9*TABx32TEAMS)+(4*(sprite_S62width/2)),                      A03yPOS-14+(12*A03yOFFSET)+24-48,
// old actua		(9*TABx32TEAMS)+(4*(sprite_S62width/2))+(sprite_S62width/2),  A03yPOS-14+(12*A03yOFFSET)+24-48+(sprite_S62height/2)+20, 
// old actua		(9*TABx32TEAMS)+(4*(sprite_S62width/2))-36,                   A03yPOS-14+(12*A03yOFFSET)+54-48, 
// old actua		(sprite_S62width/2)+74,                                       24, 
// old actua
// old actua		NULL, NULL, NULL, NULL, NULL, NULL, NULL,
// old actua		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
// old actua		NULL, NULL, NULL, NULL, NULL, NULL, NULL,
// old actua		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
// old actua		NULL, NULL, NULL, NULL, NULL, NULL, NULL,
// old actua		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
// old actua		NULL, NULL, NULL, NULL, NULL, NULL, NULL,
// old actua		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
// old actua		NULL, NULL, NULL, NULL, NULL, NULL, NULL,
// old actua		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
// old actua		NULL, NULL, NULL, NULL, NULL, NULL, NULL,
// old actua		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
// old actua		NULL, NULL, NULL, NULL, NULL, NULL, NULL,
// old actua		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
// old actua		NULL, NULL, NULL, NULL, NULL, NULL, NULL,
// old actua		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
// old actua		NULL, NULL, NULL, NULL, NULL, NULL, NULL,
// old actua		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
// old actua		NULL, NULL, NULL, NULL, NULL, NULL, NULL,
// old actua		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
// old actua		NULL, NULL, NULL, NULL, NULL, NULL, NULL,
// old actua		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
// old actua		NULL, NULL, NULL, NULL, NULL, NULL, NULL,
// old actua		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
// old actua		},
// old actua
// old actua		{
// old actua		50, 15,
// old actua		66, 15,		
// old actua		82, 15,
// old actua// 44 TEAMS
// old actua		SHADOWtextON|TIGHTEN|SFONT, SMALL|SHADOW, CHOOSE_TEAM_NAME, 
// old actua		A03xTAB+A03xINDENT, 		A15yPOS+A15yINDENT, 
// old actua		A03xTAB, 			A15yPOS,
// old actua
// old actua		A03xTAB, A15yPOS,
// old actua		A03xTAB+A03xOFFSET,A03yOFFSET+A15yPOS,
// old actua		A03xTAB+A03xINDENT,A15yPOS+A15yINDENT,
// old actua		(A03xTAB+(1*A03xOFFSET))-(A03xTAB+A03xINDENT),32,
// old actua
// old actua		SHADOWtextON|TIGHTEN|SFONT,SMALL|SHADOW,CHOOSE_TEAM_NAME,A03xTAB+A03xINDENT,A15yPOS+(1*A03yOFFSET)+A15yINDENT,A03xTAB, A15yPOS+(1*A03yOFFSET),
// old actua		A03xTAB, A15yPOS+(1*A03yOFFSET),
// old actua		A03xTAB+A03xOFFSET,A03yOFFSET+A15yPOS+(1*A03yOFFSET),
// old actua		A03xTAB+A03xINDENT,A15yPOS+(1*A03yOFFSET)+A15yINDENT,
// old actua		(A03xTAB+(1*A03xOFFSET))-(A03xTAB+A03xINDENT),32,
// old actua
// old actua		SHADOWtextON|TIGHTEN|SFONT,SMALL|SHADOW,CHOOSE_TEAM_NAME,A03xTAB+A03xINDENT,A15yPOS+(2*A03yOFFSET)+A15yINDENT,A03xTAB, A15yPOS+(2*A03yOFFSET),
// old actua		A03xTAB, A15yPOS+(2*A03yOFFSET),
// old actua		A03xTAB+A03xOFFSET,A03yOFFSET+A15yPOS+(2*A03yOFFSET),
// old actua		A03xTAB+A03xINDENT,A15yPOS+(2*A03yOFFSET)+A15yINDENT,
// old actua		(A03xTAB+(1*A03xOFFSET))-(A03xTAB+A03xINDENT),32,
// old actua
// old actua		SHADOWtextON|TIGHTEN|SFONT,SMALL|SHADOW,CHOOSE_TEAM_NAME,A03xTAB+A03xINDENT,A15yPOS+(3*A03yOFFSET)+A15yINDENT,A03xTAB, A15yPOS+(3*A03yOFFSET),
// old actua		A03xTAB, A15yPOS+(3*A03yOFFSET),
// old actua		A03xTAB+A03xOFFSET,A03yOFFSET+A15yPOS+(3*A03yOFFSET),
// old actua		A03xTAB+A03xINDENT,A15yPOS+(3*A03yOFFSET)+A15yINDENT,
// old actua		(A03xTAB+(1*A03xOFFSET))-(A03xTAB+A03xINDENT),32,
// old actua
// old actua		SHADOWtextON|TIGHTEN|SFONT,SMALL|SHADOW,CHOOSE_TEAM_NAME,A03xTAB+A03xINDENT,A15yPOS+(4*A03yOFFSET)+A15yINDENT,A03xTAB, A15yPOS+(4*A03yOFFSET),
// old actua		A03xTAB, A15yPOS+(4*A03yOFFSET),
// old actua		A03xTAB+A03xOFFSET,A03yOFFSET+A15yPOS+(4*A03yOFFSET),
// old actua		A03xTAB+A03xINDENT,A15yPOS+(4*A03yOFFSET)+A15yINDENT,
// old actua		(A03xTAB+(1*A03xOFFSET))-(A03xTAB+A03xINDENT),32,
// old actua
// old actua		SHADOWtextON|TIGHTEN|SFONT,SMALL|SHADOW,CHOOSE_TEAM_NAME,A03xTAB+A03xINDENT,A15yPOS+(5*A03yOFFSET)+A15yINDENT,A03xTAB, A15yPOS+(5*A03yOFFSET),
// old actua		A03xTAB, A15yPOS+(5*A03yOFFSET),
// old actua		A03xTAB+A03xOFFSET,A03yOFFSET+A15yPOS+(5*A03yOFFSET),
// old actua		A03xTAB+A03xINDENT,A15yPOS+(5*A03yOFFSET)+A15yINDENT,
// old actua		(A03xTAB+(1*A03xOFFSET))-(A03xTAB+A03xINDENT),32,
// old actua
// old actua		SHADOWtextON|TIGHTEN|SFONT,SMALL|SHADOW,CHOOSE_TEAM_NAME,A03xTAB+A03xINDENT,A15yPOS+(6*A03yOFFSET)+A15yINDENT,A03xTAB, A15yPOS+(6*A03yOFFSET),
// old actua		A03xTAB, A15yPOS+(6*A03yOFFSET),
// old actua		A03xTAB+A03xOFFSET,A03yOFFSET+A15yPOS+(6*A03yOFFSET),
// old actua		A03xTAB+A03xINDENT,A15yPOS+(6*A03yOFFSET)+A15yINDENT,
// old actua		(A03xTAB+(1*A03xOFFSET))-(A03xTAB+A03xINDENT),32,
// old actua
// old actua		SHADOWtextON|TIGHTEN|SFONT,SMALL|SHADOW,CHOOSE_TEAM_NAME,A03xTAB+A03xINDENT,A15yPOS+(7*A03yOFFSET)+A15yINDENT,A03xTAB, A15yPOS+(7*A03yOFFSET),
// old actua		A03xTAB, A15yPOS+(7*A03yOFFSET),
// old actua		A03xTAB+A03xOFFSET,A03yOFFSET+A15yPOS+(7*A03yOFFSET),
// old actua		A03xTAB+A03xINDENT,A15yPOS+(7*A03yOFFSET)+A15yINDENT,
// old actua		(A03xTAB+(1*A03xOFFSET))-(A03xTAB+A03xINDENT),32,
// old actua
// old actua		SHADOWtextON|TIGHTEN|SFONT,SMALL|SHADOW,CHOOSE_TEAM_NAME,A03xTAB+A03xINDENT,A15yPOS+(8*A03yOFFSET)+A15yINDENT,A03xTAB, A15yPOS+(8*A03yOFFSET),
// old actua		A03xTAB, A15yPOS+(8*A03yOFFSET),
// old actua		A03xTAB+A03xOFFSET,A03yOFFSET+A15yPOS+(8*A03yOFFSET),
// old actua		A03xTAB+A03xINDENT,A15yPOS+(8*A03yOFFSET)+A15yINDENT,
// old actua		(A03xTAB+(1*A03xOFFSET))-(A03xTAB+A03xINDENT),32,
// old actua
// old actua		SHADOWtextON|TIGHTEN|SFONT,SMALL|SHADOW,CHOOSE_TEAM_NAME,A03xTAB+A03xINDENT,A15yPOS+(9*A03yOFFSET)+A15yINDENT,A03xTAB, A15yPOS+(9*A03yOFFSET),
// old actua		A03xTAB, A15yPOS+(9*A03yOFFSET),
// old actua		A03xTAB+A03xOFFSET,A03yOFFSET+A15yPOS+(9*A03yOFFSET),
// old actua		A03xTAB+A03xINDENT,A15yPOS+(9*A03yOFFSET)+A15yINDENT,
// old actua		(A03xTAB+(1*A03xOFFSET))-(A03xTAB+A03xINDENT),32,
// old actua
// old actua		SHADOWtextON|TIGHTEN|SFONT,SMALL|SHADOW,CHOOSE_TEAM_NAME,A03xTAB+A03xINDENT,A15yPOS+(10*A03yOFFSET)+A15yINDENT,A03xTAB, A15yPOS+(10*A03yOFFSET),
// old actua		A03xTAB, A15yPOS+(10*A03yOFFSET),
// old actua		A03xTAB+A03xOFFSET,A03yOFFSET+A15yPOS+(10*A03yOFFSET),
// old actua		A03xTAB+A03xINDENT,A15yPOS+(10*A03yOFFSET)+A15yINDENT,
// old actua		(A03xTAB+(1*A03xOFFSET))-(A03xTAB+A03xINDENT),32,
// old actua
// old actua		SHADOWtextON|TIGHTEN|SFONT,SMALL|SHADOW,CHOOSE_TEAM_NAME,A03xTAB+(1*A03xOFFSET)+A03xINDENT,A15yPOS+A15yINDENT,A03xTAB+(1*A03xOFFSET), A15yPOS,
// old actua		A03xTAB+(1*A03xOFFSET), A15yPOS,
// old actua		A03xTAB+(2*A03xOFFSET) ,A03yOFFSET+A15yPOS,
// old actua		A03xTAB+(1*A03xOFFSET)+A03xINDENT,A15yPOS+A15yINDENT,
// old actua		(A03xTAB+(1*A03xOFFSET))-(A03xTAB+A03xINDENT),32,
// old actua
// old actua		SHADOWtextON|TIGHTEN|SFONT,SMALL|SHADOW,CHOOSE_TEAM_NAME,A03xTAB+(1*A03xOFFSET)+A03xINDENT,A15yPOS+(1*A03yOFFSET)+A15yINDENT,A03xTAB+(1*A03xOFFSET), A15yPOS+(1*A03yOFFSET),
// old actua		A03xTAB+(1*A03xOFFSET), A15yPOS+(1*A03yOFFSET),
// old actua		A03xTAB+(2*A03xOFFSET) ,A03yOFFSET+A15yPOS+(1*A03yOFFSET),
// old actua		A03xTAB+(1*A03xOFFSET)+A03xINDENT,A15yPOS+(1*A03yOFFSET)+A15yINDENT,
// old actua		(A03xTAB+(1*A03xOFFSET))-(A03xTAB+A03xINDENT),32,
// old actua
// old actua		SHADOWtextON|TIGHTEN|SFONT,SMALL|SHADOW,CHOOSE_TEAM_NAME,A03xTAB+(1*A03xOFFSET)+A03xINDENT,A15yPOS+(2*A03yOFFSET)+A15yINDENT,A03xTAB+(1*A03xOFFSET), A15yPOS+(2*A03yOFFSET),
// old actua		A03xTAB+(1*A03xOFFSET), A15yPOS+(2*A03yOFFSET),
// old actua		A03xTAB+(2*A03xOFFSET) ,A03yOFFSET+A15yPOS+(2*A03yOFFSET),
// old actua		A03xTAB+(1*A03xOFFSET)+A03xINDENT,A15yPOS+(2*A03yOFFSET)+A15yINDENT,
// old actua		(A03xTAB+(1*A03xOFFSET))-(A03xTAB+A03xINDENT),32,
// old actua
// old actua		SHADOWtextON|TIGHTEN|SFONT,SMALL|SHADOW,CHOOSE_TEAM_NAME,A03xTAB+(1*A03xOFFSET)+A03xINDENT,A15yPOS+(3*A03yOFFSET)+A15yINDENT,A03xTAB+(1*A03xOFFSET), A15yPOS+(3*A03yOFFSET),
// old actua		A03xTAB+(1*A03xOFFSET), A15yPOS+(3*A03yOFFSET),
// old actua		A03xTAB+(2*A03xOFFSET) ,A03yOFFSET+A15yPOS+(3*A03yOFFSET),
// old actua		A03xTAB+(1*A03xOFFSET)+A03xINDENT,A15yPOS+(3*A03yOFFSET)+A15yINDENT,
// old actua		(A03xTAB+(1*A03xOFFSET))-(A03xTAB+A03xINDENT),32,
// old actua
// old actua		SHADOWtextON|TIGHTEN|SFONT,SMALL|SHADOW,CHOOSE_TEAM_NAME,A03xTAB+(1*A03xOFFSET)+A03xINDENT,A15yPOS+(4*A03yOFFSET)+A15yINDENT,A03xTAB+(1*A03xOFFSET), A15yPOS+(4*A03yOFFSET),
// old actua		A03xTAB+(1*A03xOFFSET), A15yPOS+(4*A03yOFFSET),
// old actua		A03xTAB+(2*A03xOFFSET) ,A03yOFFSET+A15yPOS+(4*A03yOFFSET),
// old actua		A03xTAB+(1*A03xOFFSET)+A03xINDENT,A15yPOS+(4*A03yOFFSET)+A15yINDENT,
// old actua		(A03xTAB+(1*A03xOFFSET))-(A03xTAB+A03xINDENT),32,
// old actua
// old actua		SHADOWtextON|TIGHTEN|SFONT,SMALL|SHADOW,CHOOSE_TEAM_NAME,A03xTAB+(1*A03xOFFSET)+A03xINDENT,A15yPOS+(5*A03yOFFSET)+A15yINDENT,A03xTAB+(1*A03xOFFSET), A15yPOS+(5*A03yOFFSET),
// old actua		A03xTAB+(1*A03xOFFSET), A15yPOS+(5*A03yOFFSET),
// old actua		A03xTAB+(2*A03xOFFSET) ,A03yOFFSET+A15yPOS+(5*A03yOFFSET),
// old actua		A03xTAB+(1*A03xOFFSET)+A03xINDENT,A15yPOS+(5*A03yOFFSET)+A15yINDENT,
// old actua		(A03xTAB+(1*A03xOFFSET))-(A03xTAB+A03xINDENT),32,
// old actua
// old actua		SHADOWtextON|TIGHTEN|SFONT,SMALL|SHADOW,CHOOSE_TEAM_NAME,A03xTAB+(1*A03xOFFSET)+A03xINDENT,A15yPOS+(6*A03yOFFSET)+A15yINDENT,A03xTAB+(1*A03xOFFSET), A15yPOS+(6*A03yOFFSET),
// old actua		A03xTAB+(1*A03xOFFSET), A15yPOS+(6*A03yOFFSET),
// old actua		A03xTAB+(2*A03xOFFSET) ,A03yOFFSET+A15yPOS+(6*A03yOFFSET),
// old actua		A03xTAB+(1*A03xOFFSET)+A03xINDENT,A15yPOS+(6*A03yOFFSET)+A15yINDENT,
// old actua		(A03xTAB+(1*A03xOFFSET))-(A03xTAB+A03xINDENT),32,
// old actua
// old actua		SHADOWtextON|TIGHTEN|SFONT,SMALL|SHADOW,CHOOSE_TEAM_NAME,A03xTAB+(1*A03xOFFSET)+A03xINDENT,A15yPOS+(7*A03yOFFSET)+A15yINDENT,A03xTAB+(1*A03xOFFSET), A15yPOS+(7*A03yOFFSET),
// old actua		A03xTAB+(1*A03xOFFSET), A15yPOS+(7*A03yOFFSET),
// old actua		A03xTAB+(2*A03xOFFSET) ,A03yOFFSET+A15yPOS+(7*A03yOFFSET),
// old actua		A03xTAB+(1*A03xOFFSET)+A03xINDENT,A15yPOS+(7*A03yOFFSET)+A15yINDENT,
// old actua		(A03xTAB+(1*A03xOFFSET))-(A03xTAB+A03xINDENT),32,
// old actua
// old actua		SHADOWtextON|TIGHTEN|SFONT,SMALL|SHADOW,CHOOSE_TEAM_NAME,A03xTAB+(1*A03xOFFSET)+A03xINDENT,A15yPOS+(8*A03yOFFSET)+A15yINDENT,A03xTAB+(1*A03xOFFSET), A15yPOS+(8*A03yOFFSET),
// old actua		A03xTAB+(1*A03xOFFSET), A15yPOS+(8*A03yOFFSET),
// old actua		A03xTAB+(2*A03xOFFSET) ,A03yOFFSET+A15yPOS+(8*A03yOFFSET),
// old actua		A03xTAB+(1*A03xOFFSET)+A03xINDENT,A15yPOS+(8*A03yOFFSET)+A15yINDENT,
// old actua		(A03xTAB+(1*A03xOFFSET))-(A03xTAB+A03xINDENT),32,
// old actua
// old actua		SHADOWtextON|TIGHTEN|SFONT,SMALL|SHADOW,CHOOSE_TEAM_NAME,A03xTAB+(1*A03xOFFSET)+A03xINDENT,A15yPOS+(9*A03yOFFSET)+A15yINDENT,A03xTAB+(1*A03xOFFSET), A15yPOS+(9*A03yOFFSET),
// old actua		A03xTAB+(1*A03xOFFSET), A15yPOS+(9*A03yOFFSET),
// old actua		A03xTAB+(2*A03xOFFSET) ,A03yOFFSET+A15yPOS+(9*A03yOFFSET),
// old actua		A03xTAB+(1*A03xOFFSET)+A03xINDENT,A15yPOS+(9*A03yOFFSET)+A15yINDENT,
// old actua		(A03xTAB+(1*A03xOFFSET))-(A03xTAB+A03xINDENT),32,
// old actua
// old actua		SHADOWtextON|TIGHTEN|SFONT,SMALL|SHADOW,CHOOSE_TEAM_NAME,A03xTAB+(1*A03xOFFSET)+A03xINDENT,A15yPOS+(10*A03yOFFSET)+A15yINDENT,A03xTAB+(1*A03xOFFSET), A15yPOS+(10*A03yOFFSET),
// old actua		A03xTAB+(1*A03xOFFSET), A15yPOS+(10*A03yOFFSET),
// old actua		A03xTAB+(2*A03xOFFSET) ,A03yOFFSET+A15yPOS+(10*A03yOFFSET),
// old actua		A03xTAB+(1*A03xOFFSET)+A03xINDENT,A15yPOS+(10*A03yOFFSET)+A15yINDENT,
// old actua		(A03xTAB+(1*A03xOFFSET))-(A03xTAB+A03xINDENT)+3,32,
// old actua
// old actua		SHADOWtextON|TIGHTEN|SFONT,SMALL|SHADOW,CHOOSE_TEAM_NAME,A03xTAB+(2*A03xOFFSET)+A03xINDENT,A15yPOS+A15yINDENT,A03xTAB+(2*A03xOFFSET), A15yPOS,
// old actua		A03xTAB+(2*A03xOFFSET), A15yPOS,
// old actua		A03xTAB+(3*A03xOFFSET) ,A03yOFFSET+A15yPOS,
// old actua		A03xTAB+(2*A03xOFFSET)+A03xINDENT,A15yPOS+A15yINDENT,
// old actua		(A03xTAB+(1*A03xOFFSET))-(A03xTAB+A03xINDENT),32,
// old actua
// old actua		SHADOWtextON|TIGHTEN|SFONT,SMALL|SHADOW,CHOOSE_TEAM_NAME,A03xTAB+(2*A03xOFFSET)+A03xINDENT,A15yPOS+(1*A03yOFFSET)+A15yINDENT,A03xTAB+(2*A03xOFFSET), A15yPOS+(1*A03yOFFSET),
// old actua		A03xTAB+(2*A03xOFFSET), A15yPOS+(1*A03yOFFSET),
// old actua		A03xTAB+(3*A03xOFFSET) ,A03yOFFSET+A15yPOS+(1*A03yOFFSET),
// old actua		A03xTAB+(2*A03xOFFSET)+A03xINDENT,A15yPOS+(1*A03yOFFSET)+A15yINDENT,
// old actua		(A03xTAB+(1*A03xOFFSET))-(A03xTAB+A03xINDENT),32,
// old actua
// old actua		SHADOWtextON|TIGHTEN|SFONT,SMALL|SHADOW,CHOOSE_TEAM_NAME,A03xTAB+(2*A03xOFFSET)+A03xINDENT,A15yPOS+(2*A03yOFFSET)+A15yINDENT,A03xTAB+(2*A03xOFFSET), A15yPOS+(2*A03yOFFSET),
// old actua		A03xTAB+(2*A03xOFFSET), A15yPOS+(2*A03yOFFSET),
// old actua		A03xTAB+(3*A03xOFFSET) ,A03yOFFSET+A15yPOS+(2*A03yOFFSET),
// old actua		A03xTAB+(2*A03xOFFSET)+A03xINDENT,A15yPOS+(2*A03yOFFSET)+A15yINDENT,
// old actua		(A03xTAB+(1*A03xOFFSET))-(A03xTAB+A03xINDENT),32,
// old actua
// old actua		SHADOWtextON|TIGHTEN|SFONT,SMALL|SHADOW,CHOOSE_TEAM_NAME,A03xTAB+(2*A03xOFFSET)+A03xINDENT,A15yPOS+(3*A03yOFFSET)+A15yINDENT,A03xTAB+(2*A03xOFFSET), A15yPOS+(3*A03yOFFSET),
// old actua		A03xTAB+(2*A03xOFFSET), A15yPOS+(3*A03yOFFSET),
// old actua		A03xTAB+(3*A03xOFFSET) ,A03yOFFSET+A15yPOS+(3*A03yOFFSET),
// old actua		A03xTAB+(2*A03xOFFSET)+A03xINDENT,A15yPOS+(3*A03yOFFSET)+A15yINDENT,
// old actua		(A03xTAB+(1*A03xOFFSET))-(A03xTAB+A03xINDENT),32,
// old actua
// old actua		SHADOWtextON|TIGHTEN|SFONT,SMALL|SHADOW,CHOOSE_TEAM_NAME,A03xTAB+(2*A03xOFFSET)+A03xINDENT,A15yPOS+(4*A03yOFFSET)+A15yINDENT,A03xTAB+(2*A03xOFFSET), A15yPOS+(4*A03yOFFSET),
// old actua		A03xTAB+(2*A03xOFFSET), A15yPOS+(4*A03yOFFSET),
// old actua		A03xTAB+(3*A03xOFFSET) ,A03yOFFSET+A15yPOS+(4*A03yOFFSET),
// old actua		A03xTAB+(2*A03xOFFSET)+A03xINDENT,A15yPOS+(4*A03yOFFSET)+A15yINDENT,
// old actua		(A03xTAB+(1*A03xOFFSET))-(A03xTAB+A03xINDENT),32,
// old actua
// old actua		SHADOWtextON|TIGHTEN|SFONT,SMALL|SHADOW,CHOOSE_TEAM_NAME,A03xTAB+(2*A03xOFFSET)+A03xINDENT,A15yPOS+(5*A03yOFFSET)+A15yINDENT,A03xTAB+(2*A03xOFFSET), A15yPOS+(5*A03yOFFSET),
// old actua		A03xTAB+(2*A03xOFFSET), A15yPOS+(5*A03yOFFSET),
// old actua		A03xTAB+(3*A03xOFFSET) ,A03yOFFSET+A15yPOS+(5*A03yOFFSET),
// old actua		A03xTAB+(2*A03xOFFSET)+A03xINDENT,A15yPOS+(5*A03yOFFSET)+A15yINDENT,
// old actua		(A03xTAB+(1*A03xOFFSET))-(A03xTAB+A03xINDENT),32,
// old actua
// old actua		SHADOWtextON|TIGHTEN|SFONT,SMALL|SHADOW,CHOOSE_TEAM_NAME,A03xTAB+(2*A03xOFFSET)+A03xINDENT,A15yPOS+(6*A03yOFFSET)+A15yINDENT,A03xTAB+(2*A03xOFFSET), A15yPOS+(6*A03yOFFSET),
// old actua		A03xTAB+(2*A03xOFFSET), A15yPOS+(6*A03yOFFSET),
// old actua		A03xTAB+(3*A03xOFFSET) ,A03yOFFSET+A15yPOS+(6*A03yOFFSET),
// old actua		A03xTAB+(2*A03xOFFSET)+A03xINDENT,A15yPOS+(6*A03yOFFSET)+A15yINDENT,
// old actua		(A03xTAB+(1*A03xOFFSET))-(A03xTAB+A03xINDENT),32,
// old actua
// old actua		SHADOWtextON|TIGHTEN|SFONT,SMALL|SHADOW,CHOOSE_TEAM_NAME,A03xTAB+(2*A03xOFFSET)+A03xINDENT,A15yPOS+(7*A03yOFFSET)+A15yINDENT,A03xTAB+(2*A03xOFFSET), A15yPOS+(7*A03yOFFSET),
// old actua		A03xTAB+(2*A03xOFFSET), A15yPOS+(7*A03yOFFSET),
// old actua		A03xTAB+(3*A03xOFFSET) ,A03yOFFSET+A15yPOS+(7*A03yOFFSET),
// old actua		A03xTAB+(2*A03xOFFSET)+A03xINDENT,A15yPOS+(7*A03yOFFSET)+A15yINDENT,
// old actua		(A03xTAB+(1*A03xOFFSET))-(A03xTAB+A03xINDENT),32,
// old actua
// old actua		SHADOWtextON|TIGHTEN|SFONT,SMALL|SHADOW,CHOOSE_TEAM_NAME,A03xTAB+(2*A03xOFFSET)+A03xINDENT,A15yPOS+(8*A03yOFFSET)+A15yINDENT,A03xTAB+(2*A03xOFFSET), A15yPOS+(8*A03yOFFSET),
// old actua		A03xTAB+(2*A03xOFFSET), A15yPOS+(8*A03yOFFSET),
// old actua		A03xTAB+(3*A03xOFFSET) ,A03yOFFSET+A15yPOS+(8*A03yOFFSET),
// old actua		A03xTAB+(2*A03xOFFSET)+A03xINDENT,A15yPOS+(8*A03yOFFSET)+A15yINDENT,
// old actua		(A03xTAB+(1*A03xOFFSET))-(A03xTAB+A03xINDENT),32,
// old actua
// old actua		SHADOWtextON|TIGHTEN|SFONT,SMALL|SHADOW,CHOOSE_TEAM_NAME,A03xTAB+(2*A03xOFFSET)+A03xINDENT,A15yPOS+(9*A03yOFFSET)+A15yINDENT,A03xTAB+(2*A03xOFFSET), A15yPOS+(9*A03yOFFSET),
// old actua		A03xTAB+(2*A03xOFFSET), A15yPOS+(9*A03yOFFSET),
// old actua		A03xTAB+(3*A03xOFFSET) ,A03yOFFSET+A15yPOS+(9*A03yOFFSET),
// old actua		A03xTAB+(2*A03xOFFSET)+A03xINDENT,A15yPOS+(9*A03yOFFSET)+A15yINDENT,
// old actua		(A03xTAB+(1*A03xOFFSET))-(A03xTAB+A03xINDENT),32,
// old actua
// old actua		SHADOWtextON|TIGHTEN|SFONT,SMALL|SHADOW,CHOOSE_TEAM_NAME,A03xTAB+(2*A03xOFFSET)+A03xINDENT,A15yPOS+(10*A03yOFFSET)+A15yINDENT,A03xTAB+(2*A03xOFFSET), A15yPOS+(10*A03yOFFSET),
// old actua		A03xTAB+(2*A03xOFFSET), A15yPOS+(10*A03yOFFSET),
// old actua		A03xTAB+(3*A03xOFFSET) ,A03yOFFSET+A15yPOS+(10*A03yOFFSET),
// old actua		A03xTAB+(2*A03xOFFSET)+A03xINDENT,A15yPOS+(10*A03yOFFSET)+A15yINDENT,
// old actua		(A03xTAB+(1*A03xOFFSET))-(A03xTAB+A03xINDENT),32,
// old actua
// old actua		SHADOWtextON|TIGHTEN|SFONT,SMALL|SHADOW,CHOOSE_TEAM_NAME,A03xTAB+(3*A03xOFFSET)+A03xINDENT,A15yPOS+A15yINDENT,A03xTAB+(3*A03xOFFSET), A15yPOS,
// old actua		A03xTAB+(3*A03xOFFSET), A15yPOS,
// old actua		A03xTAB+(4*A03xOFFSET) ,A03yOFFSET+A15yPOS,
// old actua		A03xTAB+(3*A03xOFFSET)+A03xINDENT,A15yPOS+A15yINDENT,
// old actua		(A03xTAB+(1*A03xOFFSET))-(A03xTAB+A03xINDENT),32,
// old actua
// old actua		SHADOWtextON|TIGHTEN|SFONT,SMALL|SHADOW,CHOOSE_TEAM_NAME,A03xTAB+(3*A03xOFFSET)+A03xINDENT,A15yPOS+(1*A03yOFFSET)+A15yINDENT,A03xTAB+(3*A03xOFFSET), A15yPOS+(1*A03yOFFSET),
// old actua		A03xTAB+(3*A03xOFFSET), A15yPOS+(1*A03yOFFSET),
// old actua		A03xTAB+(4*A03xOFFSET) ,A03yOFFSET+A15yPOS+(1*A03yOFFSET),
// old actua		A03xTAB+(3*A03xOFFSET)+A03xINDENT,A15yPOS+(1*A03yOFFSET)+A15yINDENT,
// old actua		(A03xTAB+(1*A03xOFFSET))-(A03xTAB+A03xINDENT),32,
// old actua
// old actua		SHADOWtextON|TIGHTEN|SFONT,SMALL|SHADOW,CHOOSE_TEAM_NAME,A03xTAB+(3*A03xOFFSET)+A03xINDENT,A15yPOS+(2*A03yOFFSET)+A15yINDENT,A03xTAB+(3*A03xOFFSET), A15yPOS+(2*A03yOFFSET),
// old actua		A03xTAB+(3*A03xOFFSET), A15yPOS+(2*A03yOFFSET),
// old actua		A03xTAB+(4*A03xOFFSET) ,A03yOFFSET+A15yPOS+(2*A03yOFFSET),
// old actua		A03xTAB+(3*A03xOFFSET)+A03xINDENT,A15yPOS+(2*A03yOFFSET)+A15yINDENT,
// old actua		(A03xTAB+(1*A03xOFFSET))-(A03xTAB+A03xINDENT),32,
// old actua
// old actua		SHADOWtextON|TIGHTEN|SFONT,SMALL|SHADOW,CHOOSE_TEAM_NAME,A03xTAB+(3*A03xOFFSET)+A03xINDENT,A15yPOS+(3*A03yOFFSET)+A15yINDENT,A03xTAB+(3*A03xOFFSET), A15yPOS+(3*A03yOFFSET),
// old actua		A03xTAB+(3*A03xOFFSET), A15yPOS+(3*A03yOFFSET),
// old actua		A03xTAB+(4*A03xOFFSET) ,A03yOFFSET+A15yPOS+(3*A03yOFFSET),
// old actua		A03xTAB+(3*A03xOFFSET)+A03xINDENT,A15yPOS+(3*A03yOFFSET)+A15yINDENT,
// old actua		(A03xTAB+(1*A03xOFFSET))-(A03xTAB+A03xINDENT),32,
// old actua
// old actua		SHADOWtextON|TIGHTEN|SFONT,SMALL|SHADOW,CHOOSE_TEAM_NAME,A03xTAB+(3*A03xOFFSET)+A03xINDENT,A15yPOS+(4*A03yOFFSET)+A15yINDENT,A03xTAB+(3*A03xOFFSET), A15yPOS+(4*A03yOFFSET),
// old actua		A03xTAB+(3*A03xOFFSET), A15yPOS+(4*A03yOFFSET),
// old actua		A03xTAB+(4*A03xOFFSET) ,A03yOFFSET+A15yPOS+(4*A03yOFFSET),
// old actua		A03xTAB+(3*A03xOFFSET)+A03xINDENT,A15yPOS+(4*A03yOFFSET)+A15yINDENT,
// old actua		(A03xTAB+(1*A03xOFFSET))-(A03xTAB+A03xINDENT),32,
// old actua
// old actua		SHADOWtextON|TIGHTEN|SFONT,SMALL|SHADOW,CHOOSE_TEAM_NAME,A03xTAB+(3*A03xOFFSET)+A03xINDENT,A15yPOS+(5*A03yOFFSET)+A15yINDENT,A03xTAB+(3*A03xOFFSET), A15yPOS+(5*A03yOFFSET),
// old actua		A03xTAB+(3*A03xOFFSET), A15yPOS+(5*A03yOFFSET),
// old actua		A03xTAB+(4*A03xOFFSET) ,A03yOFFSET+A15yPOS+(5*A03yOFFSET),
// old actua		A03xTAB+(3*A03xOFFSET)+A03xINDENT,A15yPOS+(5*A03yOFFSET)+A15yINDENT,
// old actua		(A03xTAB+(1*A03xOFFSET))-(A03xTAB+A03xINDENT),32,
// old actua
// old actua		SHADOWtextON|TIGHTEN|SFONT,SMALL|SHADOW,CHOOSE_TEAM_NAME,A03xTAB+(3*A03xOFFSET)+A03xINDENT,A15yPOS+(6*A03yOFFSET)+A15yINDENT,A03xTAB+(3*A03xOFFSET), A15yPOS+(6*A03yOFFSET),
// old actua		A03xTAB+(3*A03xOFFSET), A15yPOS+(6*A03yOFFSET),
// old actua		A03xTAB+(4*A03xOFFSET) ,A03yOFFSET+A15yPOS+(6*A03yOFFSET),
// old actua		A03xTAB+(3*A03xOFFSET)+A03xINDENT,A15yPOS+(6*A03yOFFSET)+A15yINDENT,
// old actua		(A03xTAB+(1*A03xOFFSET))-(A03xTAB+A03xINDENT),32,
// old actua
// old actua		SHADOWtextON|TIGHTEN|SFONT,SMALL|SHADOW,CHOOSE_TEAM_NAME,A03xTAB+(3*A03xOFFSET)+A03xINDENT,A15yPOS+(7*A03yOFFSET)+A15yINDENT,A03xTAB+(3*A03xOFFSET), A15yPOS+(7*A03yOFFSET),
// old actua		A03xTAB+(3*A03xOFFSET),                        A15yPOS+(7*A03yOFFSET),
// old actua		A03xTAB+(4*A03xOFFSET),                        A03yOFFSET+A15yPOS+(7*A03yOFFSET),
// old actua		A03xTAB+(3*A03xOFFSET)+A03xINDENT,             A15yPOS+(7*A03yOFFSET)+A15yINDENT,
// old actua		(A03xTAB+(1*A03xOFFSET))-(A03xTAB+A03xINDENT), 32,
// old actua
// old actua		SHADOWtextON|TIGHTEN|SFONT,SMALL|SHADOW,CHOOSE_TEAM_NAME,A03xTAB+(3*A03xOFFSET)+A03xINDENT,A15yPOS+(8*A03yOFFSET)+A15yINDENT,A03xTAB+(3*A03xOFFSET), A15yPOS+(8*A03yOFFSET),
// old actua		A03xTAB+(3*A03xOFFSET),                        A15yPOS+(8*A03yOFFSET),
// old actua		A03xTAB+(4*A03xOFFSET),                        A03yOFFSET+A15yPOS+(8*A03yOFFSET),
// old actua		A03xTAB+(3*A03xOFFSET)+A03xINDENT,             A15yPOS+(8*A03yOFFSET)+A15yINDENT,
// old actua		(A03xTAB+(1*A03xOFFSET))-(A03xTAB+A03xINDENT), 32,
// old actua
// old actua		SHADOWtextON|TIGHTEN|SFONT,SMALL|SHADOW,CHOOSE_TEAM_NAME,A03xTAB+(3*A03xOFFSET)+A03xINDENT,A15yPOS+(9*A03yOFFSET)+A15yINDENT,A03xTAB+(3*A03xOFFSET), A15yPOS+(9*A03yOFFSET),
// old actua		A03xTAB+(3*A03xOFFSET),                        A15yPOS+(9*A03yOFFSET),
// old actua		A03xTAB+(4*A03xOFFSET),                        A03yOFFSET+A15yPOS+(9*A03yOFFSET),
// old actua		A03xTAB+(3*A03xOFFSET)+A03xINDENT,             A15yPOS+(9*A03yOFFSET)+A15yINDENT,
// old actua		(A03xTAB+(1*A03xOFFSET))-(A03xTAB+A03xINDENT), 32,
// old actua
// old actua		SHADOWtextON|TIGHTEN|SFONT,SMALL|SHADOW,CHOOSE_TEAM_NAME,A03xTAB+(3*A03xOFFSET)+A03xINDENT,A15yPOS+(10*A03yOFFSET)+A15yINDENT,A03xTAB+(3*A03xOFFSET), A15yPOS+(10*A03yOFFSET),
// old actua		A03xTAB+(3*A03xOFFSET),                        A15yPOS+(10*A03yOFFSET),
// old actua		A03xTAB+(4*A03xOFFSET),                        A03yOFFSET+A15yPOS+(10*A03yOFFSET),
// old actua		A03xTAB+(3*A03xOFFSET)+A03xINDENT,             A15yPOS+(10*A03yOFFSET)+A15yINDENT,
// old actua		(A03xTAB+(1*A03xOFFSET))-(A03xTAB+A03xINDENT), 32,
// old actua
// old actua		},
// old actua
// old actua					};
// old actua
// old actuacontrols   	control_table[16]={
// old actua
// old actua
// old actua	       	COMPUTER_TEXT, 0, NULL,
// old actua		NULL, NULL, NULL, 
// old actua		NULL, NULL, NULL, 
// old actua		NULL, NULL, NULL, 
// old actua
// old actua		PLAYER_ONE_TEXT, 0, PLAYER1,
// old actua		NULL, NULL, NULL,
// old actua		NULL, NULL, NULL,
// old actua		NULL, NULL, NULL,
// old actua
// old actua		PLAYER_TWO_TEXT, 0, PLAYER2,
// old actua		NULL, NULL, NULL,
// old actua		NULL, NULL, NULL,
// old actua		NULL, NULL, NULL,
// old actua
// old actua		PLAYER_ONE_TEXT, 0,  PLAYER1,
// old actua		PLAYER_TWO_TEXT, 22, PLAYER2,
// old actua		NULL, NULL, NULL,
// old actua		NULL, NULL, NULL,
// old actua
// old actua		PLAYER_THREE_TEXT, 0, PLAYER3,
// old actua		NULL, NULL, NULL,
// old actua		NULL, NULL, NULL,
// old actua		NULL, NULL, NULL,
// old actua
// old actua		PLAYER_ONE_TEXT, 0,    PLAYER1,
// old actua		PLAYER_THREE_TEXT, 22, PLAYER3,
// old actua		NULL, NULL, NULL, 
// old actua		NULL, NULL, NULL, 
// old actua
// old actua		PLAYER_TWO_TEXT, 0,    PLAYER2,
// old actua		PLAYER_THREE_TEXT, 22, PLAYER3,
// old actua		NULL, NULL, NULL, 
// old actua		NULL, NULL, NULL, 
// old actua
// old actua		PLAYER_ONE_TEXT, 0,    PLAYER1,
// old actua		PLAYER_TWO_TEXT, 22,   PLAYER2,
// old actua		PLAYER_THREE_TEXT, 44, PLAYER3,
// old actua		NULL, NULL, NULL, 
// old actua
// old actua		PLAYER_FOUR_TEXT, 0,   PLAYER4,
// old actua		NULL, NULL, NULL, 
// old actua		NULL, NULL, NULL, 
// old actua		NULL, NULL, NULL, 
// old actua
// old actua		PLAYER_ONE_TEXT, 0,    PLAYER1,
// old actua		PLAYER_FOUR_TEXT, 22,  PLAYER4,
// old actua		NULL, NULL, NULL, 
// old actua		NULL, NULL, NULL, 
// old actua
// old actua		PLAYER_TWO_TEXT, 0,   PLAYER2,
// old actua		PLAYER_FOUR_TEXT, 22, PLAYER4,
// old actua		NULL, NULL, NULL,
// old actua		NULL, NULL, NULL,
// old actua				
// old actua		PLAYER_ONE_TEXT, 0,   PLAYER1,
// old actua		PLAYER_TWO_TEXT, 22,  PLAYER2,
// old actua		PLAYER_FOUR_TEXT, 44, PLAYER4,
// old actua		NULL, NULL, NULL,
// old actua
// old actua		PLAYER_THREE_TEXT, 0, PLAYER3,
// old actua		PLAYER_FOUR_TEXT, 22, PLAYER4,
// old actua		NULL, NULL, NULL,
// old actua		NULL, NULL, NULL,
// old actua
// old actua		PLAYER_ONE_TEXT, 0,     PLAYER1,
// old actua		PLAYER_THREE_TEXT,  22, PLAYER3,
// old actua		PLAYER_FOUR_TEXT, 44,   PLAYER4,
// old actua		NULL, NULL, NULL,
// old actua
// old actua		PLAYER_TWO_TEXT, 0,    PLAYER2,
// old actua		PLAYER_THREE_TEXT, 22, PLAYER3,
// old actua		PLAYER_FOUR_TEXT, 44,  PLAYER4,
// old actua		NULL, NULL, NULL,
// old actua
// old actua		PLAYER_ONE_TEXT, 0,    PLAYER1,
// old actua		PLAYER_TWO_TEXT, 22,   PLAYER2,
// old actua		PLAYER_THREE_TEXT, 44, PLAYER3,
// old actua		PLAYER_FOUR_TEXT, 66,  PLAYER4,
// old actua
// old actua				};
// old actua







	char	friendly_controls[]={
		PLAYER1,PLAYER1,PLAYER1+PLAYER2,PLAYER1+PLAYER2,
		NULL,PLAYER2,PLAYER3,PLAYER3+PLAYER4,
				};

	int	cup_games[]={
		NULL,	NULL,
		NULL,	NULL,
		NULL,	NULL,
		NULL,	NULL,
		NULL,	NULL,
		NULL,	NULL,
		NULL,	NULL,
		NULL,	NULL,
		NULL,	NULL,
		NULL,	NULL,
		NULL,	NULL,
		NULL,	NULL,
		NULL,	NULL,
		NULL,	NULL,
		NULL,	NULL,
		NULL,	NULL,
		NULL,	NULL
				};

result_table	results[650]={
		0,0,0,0,
			     };


// old actua	fixture_table	fixtures[]={
// old actua										       	// 600 matches
// old actua			(DIV1*16)+POS11,	(DIV1*16)+POS13,	DIV1,		
// old actua			(DIV3*16)+POS11,	(DIV3*16)+POS13,	DIV3,		
// old actua	
// old actua			(DIV2*16)+POS11,	(DIV2*16)+POS14,	DIV2,		
// old actua			(DIV1*16)+POS01,	(DIV1*16)+POS02,	DIV1,		
// old actua			(DIV3*16)+POS01,	(DIV3*16)+POS02,	DIV3,		
// old actua			(DIV2*16)+POS01,	(DIV2*16)+POS02,	DIV2,		
// old actua	
// old actua			(DIV1*16)+POS03,	(DIV1*16)+POS04,	DIV1,		//1
// old actua			(DIV3*16)+POS03,	(DIV3*16)+POS04,	DIV3,		//1
// old actua			(DIV2*16)+POS03,	(DIV2*16)+POS04,	DIV2,		
// old actua			(DIV1*16)+POS05,	(DIV1*16)+POS06,	DIV1,		
// old actua			(DIV3*16)+POS05,	(DIV3*16)+POS06,	DIV3,		
// old actua	
// old actua			(DIV2*16)+POS05,	(DIV2*16)+POS06,	DIV2,		
// old actua	
// old actua			(DIV2*16)+POS09,	(DIV2*16)+POS12,	DIV2,		
// old actua			(DIV1*16)+POS07,	(DIV1*16)+POS08,	DIV1,		
// old actua			(DIV3*16)+POS07,	(DIV3*16)+POS08,	DIV3,		
// old actua			(DIV2*16)+POS07,	(DIV2*16)+POS08,	DIV2,		
// old actua	
// old actua			(DIV1*16)+POS09,	(DIV1*16)+POS10,	DIV1,		
// old actua			(DIV3*16)+POS09,	(DIV3*16)+POS10,	DIV3,		
// old actua			(DIV2*16)+POS09,	(DIV2*16)+POS10,	DIV2,		
// old actua	
// old actua			(DIV1*16)+POS11,	(DIV1*16)+POS12,	DIV1,		
// old actua			(DIV3*16)+POS11,	(DIV3*16)+POS12,	DIV3,		
// old actua			(DIV2*16)+POS11,	(DIV2*16)+POS12,	DIV2,		
// old actua	
// old actua			(DIV2*16)+POS02,	(DIV2*16)+POS16,	DIV2,		
// old actua			(DIV1*16)+POS13,	(DIV1*16)+POS14,	DIV1,		
// old actua			(DIV3*16)+POS13,	(DIV3*16)+POS14,	DIV3,		
// old actua			(DIV2*16)+POS13,	(DIV2*16)+POS14,	DIV2,		
// old actua	
// old actua			(DIV1*16)+POS02,	(DIV1*16)+POS03,	DIV1,		
// old actua			(DIV3*16)+POS02,	(DIV3*16)+POS03,	DIV3,		
// old actua			(DIV2*16)+POS15,	(DIV2*16)+POS16,	DIV2,		
// old actua	
// old actua			(DIV1*16)+POS06,	(DIV1*16)+POS07,	DIV1,		
// old actua			(DIV3*16)+POS06,	(DIV3*16)+POS07,	DIV3,		
// old actua			(DIV2*16)+POS02,	(DIV2*16)+POS03,	DIV2,		
// old actua	
// old actua			(DIV2*16)+POS13,	(DIV2*16)+POS15,	DIV2,		
// old actua			(DIV1*16)+POS04,	(DIV1*16)+POS05,	DIV1,		//2
// old actua			(DIV3*16)+POS04,	(DIV3*16)+POS05,	DIV3,		//2
// old actua			(DIV2*16)+POS06,	(DIV2*16)+POS07,	DIV2,		
// old actua	
// old actua			(DIV1*16)+POS08,	(DIV1*16)+POS09,	DIV1,		
// old actua			(DIV3*16)+POS08,	(DIV3*16)+POS09,	DIV3,		
// old actua			(DIV2*16)+POS04,	(DIV2*16)+POS05,	DIV2,		
// old actua	
// old actua			(DIV1*16)+POS10,	(DIV1*16)+POS11,	DIV1,		
// old actua			(DIV3*16)+POS10,	(DIV3*16)+POS11,	DIV3,		
// old actua			(DIV2*16)+POS08,	(DIV2*16)+POS09,	DIV2,		
// old actua	
// old actua			(DIV2*16)+POS07,	(DIV2*16)+POS10,	DIV2,		
// old actua			(DIV1*16)+POS12,	(DIV1*16)+POS13,	DIV1,		
// old actua			(DIV3*16)+POS12,	(DIV3*16)+POS13,	DIV3,		
// old actua			(DIV2*16)+POS10,	(DIV2*16)+POS11,	DIV2,		
// old actua	
// old actua			(DIV1*16)+POS14,	(DIV1*16)+POS01,	DIV1,		
// old actua			(DIV3*16)+POS14,	(DIV3*16)+POS01,	DIV3,		
// old actua			(DIV2*16)+POS12,	(DIV2*16)+POS13,	DIV2,		
// old actua	
// old actua			(DIV1*16)+POS05,	(DIV1*16)+POS02,	DIV1,		
// old actua			(DIV3*16)+POS05,	(DIV3*16)+POS02,	DIV3,		
// old actua			(DIV2*16)+POS14,	(DIV2*16)+POS15,	DIV2,		
// old actua	
// old actua			(DIV2*16)+POS05,	(DIV2*16)+POS08,	DIV2,		
// old actua			(DIV1*16)+POS03,	(DIV1*16)+POS01,	DIV1,		
// old actua			(DIV3*16)+POS03,	(DIV3*16)+POS01,	DIV3,		
// old actua			(DIV2*16)+POS16,	(DIV2*16)+POS01,	DIV2,		
// old actua	
// old actua			(DIV1*16)+POS07,	(DIV1*16)+POS04,	DIV1,		//3
// old actua			(DIV3*16)+POS07,	(DIV3*16)+POS04,	DIV3,		//3
// old actua			(DIV2*16)+POS05,	(DIV2*16)+POS02,	DIV2,		
// old actua	
// old actua			(DIV1*16)+POS09,	(DIV1*16)+POS06,	DIV1,		
// old actua			(DIV3*16)+POS09,	(DIV3*16)+POS06,	DIV3,		
// old actua			(DIV2*16)+POS03,	(DIV2*16)+POS01,	DIV2,		
// old actua	
// old actua			(DIV2*16)+POS03,	(DIV2*16)+POS06,	DIV2,		
// old actua			(DIV1*16)+POS11,	(DIV1*16)+POS08,	DIV1,		
// old actua			(DIV3*16)+POS11,	(DIV3*16)+POS08,	DIV3,		
// old actua			(DIV2*16)+POS07,	(DIV2*16)+POS04,	DIV2,		
// old actua	
// old actua			(DIV1*16)+POS13,	(DIV1*16)+POS10,	DIV1,		
// old actua			(DIV3*16)+POS13,	(DIV3*16)+POS10,	DIV3,		
// old actua			(DIV2*16)+POS09,	(DIV2*16)+POS06,	DIV2,		
// old actua	
// old actua			(DIV1*16)+POS12,	(DIV1*16)+POS14,	DIV1,		
// old actua			(DIV3*16)+POS12,	(DIV3*16)+POS14,	DIV3,		
// old actua			(DIV2*16)+POS11,	(DIV2*16)+POS08,	DIV2,		
// old actua	
// old actua			(DIV2*16)+POS01,	(DIV2*16)+POS04,	DIV2,		
// old actua			(DIV1*16)+POS02,	(DIV1*16)+POS07,	DIV1,		
// old actua			(DIV3*16)+POS02,	(DIV3*16)+POS07,	DIV3,		
// old actua			(DIV2*16)+POS13,	(DIV2*16)+POS10,	DIV2,		
// old actua	
// old actua			(DIV1*16)+POS01,	(DIV1*16)+POS05,	DIV1,		
// old actua			(DIV3*16)+POS01,	(DIV3*16)+POS05,	DIV3,		
// old actua			(DIV2*16)+POS15,	(DIV2*16)+POS12,	DIV2,		
// old actua	
// old actua			(DIV1*16)+POS04,	(DIV1*16)+POS09,	DIV1,		//4
// old actua			(DIV3*16)+POS04,	(DIV3*16)+POS09,	DIV3,		//4
// old actua			(DIV2*16)+POS14,	(DIV2*16)+POS16,	DIV2,		
// old actua	
// old actua			(DIV2*16)+POS13,	(DIV2*16)+POS16,	DIV2,		
// old actua			(DIV1*16)+POS06,	(DIV1*16)+POS11,	DIV1,		
// old actua			(DIV3*16)+POS06,	(DIV3*16)+POS11,	DIV3,		
// old actua			(DIV2*16)+POS02,	(DIV2*16)+POS07,	DIV2,		
// old actua	
// old actua			(DIV1*16)+POS08,	(DIV1*16)+POS13,	DIV1,		
// old actua			(DIV3*16)+POS08,	(DIV3*16)+POS13,	DIV3,		
// old actua			(DIV2*16)+POS01,	(DIV2*16)+POS05,	DIV2,		
// old actua	
// old actua			(DIV1*16)+POS10,	(DIV1*16)+POS12,	DIV1,		
// old actua			(DIV3*16)+POS10,	(DIV3*16)+POS12,	DIV3,		
// old actua			(DIV2*16)+POS04,	(DIV2*16)+POS09,	DIV2,		
// old actua	
// old actua			(DIV2*16)+POS14,	(DIV2*16)+POS09,	DIV2,		
// old actua			(DIV1*16)+POS14,	(DIV1*16)+POS03,	DIV1,		
// old actua			(DIV3*16)+POS14,	(DIV3*16)+POS03,	DIV3,		
// old actua			(DIV2*16)+POS06,	(DIV2*16)+POS11,	DIV2,		
// old actua	
// old actua			(DIV1*16)+POS09,	(DIV1*16)+POS02,	DIV1,		
// old actua			(DIV3*16)+POS09,	(DIV3*16)+POS02,	DIV3,		
// old actua			(DIV2*16)+POS08,	(DIV2*16)+POS13,	DIV2,		
// old actua	
// old actua			(DIV1*16)+POS07,	(DIV1*16)+POS01,	DIV1,		
// old actua			(DIV3*16)+POS07,	(DIV3*16)+POS01,	DIV3,		
// old actua			(DIV2*16)+POS10,	(DIV2*16)+POS15,	DIV2,		
// old actua	
// old actua			(DIV2*16)+POS12,	(DIV2*16)+POS07,	DIV2,		
// old actua			(DIV1*16)+POS05,	(DIV1*16)+POS03,	DIV1,		
// old actua			(DIV3*16)+POS05,	(DIV3*16)+POS03,	DIV3,		
// old actua			(DIV2*16)+POS12,	(DIV2*16)+POS14,	DIV2,		
// old actua	
// old actua			(DIV1*16)+POS11,	(DIV1*16)+POS04,	DIV1,		//5
// old actua			(DIV3*16)+POS11,	(DIV3*16)+POS04,	DIV3,		//5
// old actua			(DIV2*16)+POS16,	(DIV2*16)+POS03,	DIV2,		
// old actua	
// old actua			(DIV1*16)+POS13,	(DIV1*16)+POS06,	DIV1,		
// old actua			(DIV3*16)+POS13,	(DIV3*16)+POS06,	DIV3,		
// old actua			(DIV2*16)+POS09,	(DIV2*16)+POS02,	DIV2,		
// old actua	
// old actua			(DIV2*16)+POS15,	(DIV2*16)+POS11,	DIV2,		
// old actua			(DIV1*16)+POS12,	(DIV1*16)+POS08,	DIV1,		
// old actua			(DIV3*16)+POS12,	(DIV3*16)+POS08,	DIV3,		
// old actua			(DIV2*16)+POS07,	(DIV2*16)+POS01,	DIV2,		
// old actua	
// old actua			(DIV1*16)+POS10,	(DIV1*16)+POS14,	DIV1,		
// old actua			(DIV3*16)+POS10,	(DIV3*16)+POS14,	DIV3,		
// old actua			(DIV2*16)+POS05,	(DIV2*16)+POS03,	DIV2,		
// old actua	
// old actua			(DIV1*16)+POS02,	(DIV1*16)+POS11,	DIV1,		
// old actua			(DIV3*16)+POS02,	(DIV3*16)+POS11,	DIV3,		
// old actua			(DIV2*16)+POS11,	(DIV2*16)+POS04,	DIV2,		
// old actua	
// old actua			(DIV2*16)+POS10,	(DIV2*16)+POS05,	DIV2,		
// old actua			(DIV1*16)+POS01,	(DIV1*16)+POS09,	DIV1,		
// old actua			(DIV3*16)+POS01,	(DIV3*16)+POS09,	DIV3,		
// old actua			(DIV2*16)+POS13,	(DIV2*16)+POS06,	DIV2,		
// old actua	
// old actua			(DIV1*16)+POS03,	(DIV1*16)+POS07,	DIV1,		
// old actua			(DIV3*16)+POS03,	(DIV3*16)+POS07,	DIV3,		
// old actua			(DIV2*16)+POS12,	(DIV2*16)+POS16,	DIV2,		
// old actua	
// old actua			(DIV1*16)+POS04,	(DIV1*16)+POS13,	DIV1,		//6
// old actua			(DIV3*16)+POS04,	(DIV3*16)+POS13,	DIV3,		//6
// old actua			(DIV2*16)+POS14,	(DIV2*16)+POS10,	DIV2,		
// old actua	
// old actua			(DIV2*16)+POS08,	(DIV2*16)+POS03,	DIV2,		
// old actua			(DIV1*16)+POS06,	(DIV1*16)+POS12,	DIV1,		
// old actua			(DIV3*16)+POS06,	(DIV3*16)+POS12,	DIV3,		
// old actua			(DIV2*16)+POS15,	(DIV2*16)+POS08,	DIV2,		
// old actua	
// old actua			(DIV1*16)+POS08,	(DIV1*16)+POS10,	DIV1,		
// old actua			(DIV3*16)+POS08,	(DIV3*16)+POS10,	DIV3,		
// old actua			(DIV2*16)+POS02,	(DIV2*16)+POS11,	DIV2,		
// old actua	
// old actua			(DIV1*16)+POS14,	(DIV1*16)+POS05,	DIV1,		
// old actua			(DIV3*16)+POS14,	(DIV3*16)+POS05,	DIV3,		
// old actua			(DIV2*16)+POS01,	(DIV2*16)+POS09,	DIV2,		
// old actua	
// old actua			(DIV2*16)+POS06,	(DIV2*16)+POS01,	DIV2,		
// old actua			(DIV1*16)+POS13,	(DIV1*16)+POS02,	DIV1,		
// old actua			(DIV3*16)+POS13,	(DIV3*16)+POS02,	DIV3,		
// old actua			(DIV2*16)+POS03,	(DIV2*16)+POS07,	DIV2,		
// old actua	
// old actua			(DIV1*16)+POS11,	(DIV1*16)+POS01,	DIV1,		
// old actua			(DIV3*16)+POS11,	(DIV3*16)+POS01,	DIV3,		
// old actua			(DIV2*16)+POS04,	(DIV2*16)+POS13,	DIV2,		
// old actua	
// old actua			(DIV1*16)+POS09,	(DIV1*16)+POS03,	DIV1,		
// old actua			(DIV3*16)+POS09,	(DIV3*16)+POS03,	DIV3,		
// old actua			(DIV2*16)+POS06,	(DIV2*16)+POS15,	DIV2,		
// old actua	
// old actua			(DIV2*16)+POS04,	(DIV2*16)+POS02,	DIV2,		
// old actua			(DIV1*16)+POS07,	(DIV1*16)+POS05,	DIV1,		
// old actua			(DIV3*16)+POS07,	(DIV3*16)+POS05,	DIV3,		
// old actua			(DIV2*16)+POS08,	(DIV2*16)+POS14,	DIV2,		
// old actua	
// old actua			(DIV1*16)+POS12,	(DIV1*16)+POS04,	DIV1,		//7
// old actua			(DIV3*16)+POS12,	(DIV3*16)+POS04,	DIV3,		//7
// old actua			(DIV2*16)+POS16,	(DIV2*16)+POS05,	DIV2,		
// old actua	
// old actua			(DIV1*16)+POS10,	(DIV1*16)+POS06,	DIV1,		
// old actua			(DIV3*16)+POS10,	(DIV3*16)+POS06,	DIV3,		
// old actua			(DIV2*16)+POS10,	(DIV2*16)+POS12,	DIV2,		
// old actua	
// old actua			(DIV2*16)+POS09,	(DIV2*16)+POS15,	DIV2,		
// old actua			(DIV1*16)+POS08,	(DIV1*16)+POS14,	DIV1,		
// old actua			(DIV3*16)+POS08,	(DIV3*16)+POS14,	DIV3,		
// old actua			(DIV2*16)+POS13,	(DIV2*16)+POS02,	DIV2,		
// old actua	
// old actua			(DIV1*16)+POS02,	(DIV1*16)+POS12,	DIV1,		
// old actua			(DIV3*16)+POS02,	(DIV3*16)+POS12,	DIV3,		
// old actua			(DIV2*16)+POS11,	(DIV2*16)+POS01,	DIV2,		
// old actua	
// old actua			(DIV1*16)+POS01,	(DIV1*16)+POS13,	DIV1,		
// old actua			(DIV3*16)+POS01,	(DIV3*16)+POS13,	DIV3,		
// old actua			(DIV2*16)+POS09,	(DIV2*16)+POS03,	DIV2,		
// old actua	
// old actua			(DIV2*16)+POS07,	(DIV2*16)+POS14,	DIV2,		
// old actua			(DIV1*16)+POS03,	(DIV1*16)+POS11,	DIV1,		
// old actua			(DIV3*16)+POS03,	(DIV3*16)+POS11,	DIV3,		
// old actua			(DIV2*16)+POS07,	(DIV2*16)+POS05,	DIV2,		
// old actua	
// old actua			(DIV1*16)+POS05,	(DIV1*16)+POS09,	DIV1,		
// old actua			(DIV3*16)+POS05,	(DIV3*16)+POS09,	DIV3,		
// old actua			(DIV2*16)+POS12,	(DIV2*16)+POS08,	DIV2,		
// old actua	
// old actua			(DIV1*16)+POS04,	(DIV1*16)+POS10,	DIV1,		//8
// old actua			(DIV3*16)+POS04,	(DIV3*16)+POS10,	DIV3,		//8
// old actua			(DIV2*16)+POS10,	(DIV2*16)+POS16,	DIV2,		
// old actua	
// old actua			(DIV2*16)+POS11,	(DIV2*16)+POS13,	DIV2,		
// old actua			(DIV1*16)+POS06,	(DIV1*16)+POS08,	DIV1,		
// old actua			(DIV3*16)+POS06,	(DIV3*16)+POS08,	DIV3,		
// old actua			(DIV2*16)+POS14,	(DIV2*16)+POS06,	DIV2,		
// old actua	
// old actua			(DIV1*16)+POS14,	(DIV1*16)+POS07,	DIV1,		
// old actua			(DIV3*16)+POS14,	(DIV3*16)+POS07,	DIV3,		
// old actua			(DIV2*16)+POS15,	(DIV2*16)+POS04,	DIV2,		
// old actua	
// old actua			(DIV1*16)+POS10,	(DIV1*16)+POS02,	DIV1,		
// old actua			(DIV3*16)+POS10,	(DIV3*16)+POS02,	DIV3,		
// old actua			(DIV2*16)+POS02,	(DIV2*16)+POS15,	DIV2,		
// old actua	
// old actua			(DIV2*16)+POS05,	(DIV2*16)+POS12,	DIV2,		
// old actua			(DIV1*16)+POS12,	(DIV1*16)+POS01,	DIV1,		
// old actua			(DIV3*16)+POS12,	(DIV3*16)+POS01,	DIV3,		
// old actua			(DIV2*16)+POS01,	(DIV2*16)+POS13,	DIV2,		
// old actua	
// old actua			(DIV1*16)+POS13,	(DIV1*16)+POS03,	DIV1,		
// old actua			(DIV3*16)+POS13,	(DIV3*16)+POS03,	DIV3,		
// old actua			(DIV2*16)+POS03,	(DIV2*16)+POS11,	DIV2,		
// old actua	
// old actua			(DIV1*16)+POS11,	(DIV1*16)+POS05,	DIV1,		
// old actua			(DIV3*16)+POS11,	(DIV3*16)+POS05,	DIV3,		
// old actua			(DIV2*16)+POS05,	(DIV2*16)+POS09,	DIV2,		
// old actua	
// old actua									      
// old actua			(DIV2*16)+POS03,	(DIV2*16)+POS10,	DIV2,		
// old actua			(DIV1*16)+POS09,	(DIV1*16)+POS07,	DIV1,		
// old actua			(DIV3*16)+POS09,	(DIV3*16)+POS07,	DIV3,		
// old actua			(DIV2*16)+POS04,	(DIV2*16)+POS14,	DIV2,		
// old actua	
// old actua			(DIV1*16)+POS08,	(DIV1*16)+POS04,	DIV1,		//9
// old actua			(DIV3*16)+POS08,	(DIV3*16)+POS04,	DIV3,		//9
// old actua			(DIV2*16)+POS06,	(DIV2*16)+POS12,	DIV2,		
// old actua	
// old actua			(DIV1*16)+POS06,	(DIV1*16)+POS14,	DIV1,		
// old actua			(DIV3*16)+POS06,	(DIV3*16)+POS14,	DIV3,		
// old actua			(DIV2*16)+POS08,	(DIV2*16)+POS10,	DIV2,		
// old actua	
// old actua			(DIV2*16)+POS01,	(DIV2*16)+POS08,	DIV2,		
// old actua			(DIV1*16)+POS02,	(DIV1*16)+POS08,	DIV1,		
// old actua			(DIV3*16)+POS02,	(DIV3*16)+POS08,	DIV3,		
// old actua			(DIV2*16)+POS16,	(DIV2*16)+POS07,	DIV2,		
// old actua	
// old actua			(DIV1*16)+POS01,	(DIV1*16)+POS10,	DIV1,		
// old actua			(DIV3*16)+POS01,	(DIV3*16)+POS10,	DIV3,		
// old actua			(DIV2*16)+POS10,	(DIV2*16)+POS06,	DIV2,		
// old actua	
// old actua			(DIV1*16)+POS03,	(DIV1*16)+POS12,	DIV1,		
// old actua			(DIV3*16)+POS03,	(DIV3*16)+POS12,	DIV3,		
// old actua			(DIV2*16)+POS12,	(DIV2*16)+POS04,	DIV2,		
// old actua	
// old actua			(DIV2*16)+POS02,	(DIV2*16)+POS06,	DIV2,		
// old actua			(DIV1*16)+POS05,	(DIV1*16)+POS13,	DIV1,		
// old actua			(DIV3*16)+POS05,	(DIV3*16)+POS13,	DIV3,		
// old actua			(DIV2*16)+POS13,	(DIV2*16)+POS03,	DIV2,		
// old actua	
// old actua			(DIV1*16)+POS07,	(DIV1*16)+POS11,	DIV1,		
// old actua			(DIV3*16)+POS07,	(DIV3*16)+POS11,	DIV3,		
// old actua			(DIV2*16)+POS11,	(DIV2*16)+POS05,	DIV2,		
// old actua	
// old actua			(DIV1*16)+POS04,	(DIV1*16)+POS06,	DIV1,		//10
// old actua			(DIV3*16)+POS04,	(DIV3*16)+POS06,	DIV3,		//10
// old actua			(DIV2*16)+POS09,	(DIV2*16)+POS07,	DIV2,		
// old actua	
// old actua			(DIV2*16)+POS16,	(DIV2*16)+POS04,	DIV2,		
// old actua			(DIV1*16)+POS14,	(DIV1*16)+POS09,	DIV1,		
// old actua			(DIV3*16)+POS14,	(DIV3*16)+POS09,	DIV3,		
// old actua			(DIV2*16)+POS08,	(DIV2*16)+POS16,	DIV2,		
// old actua	
// old actua			(DIV1*16)+POS06,	(DIV1*16)+POS02,	DIV1,		
// old actua			(DIV3*16)+POS06,	(DIV3*16)+POS02,	DIV3,		
// old actua			(DIV2*16)+POS15,	(DIV2*16)+POS01,	DIV2,		
// old actua	
// old actua			(DIV1*16)+POS08,	(DIV1*16)+POS01,	DIV1,		
// old actua			(DIV3*16)+POS08,	(DIV3*16)+POS01,	DIV3,		
// old actua			(DIV2*16)+POS14,	(DIV2*16)+POS02,	DIV2,		
// old actua	
// old actua			(DIV2*16)+POS11,	(DIV2*16)+POS16,	DIV2,		
// old actua			(DIV1*16)+POS10,	(DIV1*16)+POS03,	DIV1,		
// old actua			(DIV3*16)+POS10,	(DIV3*16)+POS03,	DIV3,		
// old actua			(DIV2*16)+POS02,	(DIV2*16)+POS12,	DIV2,		
// old actua	
// old actua			(DIV1*16)+POS12,	(DIV1*16)+POS05,	DIV1,		
// old actua			(DIV3*16)+POS12,	(DIV3*16)+POS05,	DIV3,		
// old actua			(DIV2*16)+POS01,	(DIV2*16)+POS14,	DIV2,		
// old actua	
// old actua			(DIV1*16)+POS13,	(DIV1*16)+POS07,	DIV1,		
// old actua			(DIV3*16)+POS13,	(DIV3*16)+POS07,	DIV3,		
// old actua			(DIV2*16)+POS03,	(DIV2*16)+POS15,	DIV2,		
// old actua	
// old actua			(DIV2*16)+POS06,	(DIV2*16)+POS04,	DIV2,		
// old actua			(DIV1*16)+POS11,	(DIV1*16)+POS09,	DIV1,		
// old actua			(DIV3*16)+POS11,	(DIV3*16)+POS09,	DIV3,		
// old actua			(DIV2*16)+POS05,	(DIV2*16)+POS13,	DIV2,		
// old actua	
// old actua			(DIV1*16)+POS04,	(DIV1*16)+POS14,	DIV1,		//11
// old actua			(DIV3*16)+POS04,	(DIV3*16)+POS14,	DIV3,		//11
// old actua			(DIV2*16)+POS07,	(DIV2*16)+POS11,	DIV2,		
// old actua	
// old actua			(DIV1*16)+POS02,	(DIV1*16)+POS04,	DIV1,		//12
// old actua			(DIV3*16)+POS02,	(DIV3*16)+POS04,	DIV3,		//12
// old actua			(DIV2*16)+POS04,	(DIV2*16)+POS10,	DIV2,		
// old actua	
// old actua			(DIV2*16)+POS13,	(DIV2*16)+POS09,	DIV2,		
// old actua			(DIV1*16)+POS01,	(DIV1*16)+POS06,	DIV1,		
// old actua			(DIV3*16)+POS01,	(DIV3*16)+POS06,	DIV3,		
// old actua			(DIV2*16)+POS06,	(DIV2*16)+POS08,	DIV2,		
// old actua	
// old actua			(DIV1*16)+POS03,	(DIV1*16)+POS08,	DIV1,		
// old actua			(DIV3*16)+POS03,	(DIV3*16)+POS08,	DIV3,		
// old actua			(DIV2*16)+POS16,	(DIV2*16)+POS09,	DIV2,		
// old actua	
// old actua			(DIV1*16)+POS05,	(DIV1*16)+POS10,	DIV1,		
// old actua			(DIV3*16)+POS05,	(DIV3*16)+POS10,	DIV3,		
// old actua			(DIV2*16)+POS06,	(DIV2*16)+POS16,	DIV2,		
// old actua	
// old actua			(DIV2*16)+POS15,	(DIV2*16)+POS07,	DIV2,		
// old actua			(DIV1*16)+POS07,	(DIV1*16)+POS12,	DIV1,		
// old actua			(DIV3*16)+POS07,	(DIV3*16)+POS12,	DIV3,		
// old actua			(DIV2*16)+POS08,	(DIV2*16)+POS04,	DIV2,		
// old actua	
// old actua			(DIV1*16)+POS09,	(DIV1*16)+POS13,	DIV1,		
// old actua			(DIV3*16)+POS09,	(DIV3*16)+POS13,	DIV3,		
// old actua			(DIV2*16)+POS10,	(DIV2*16)+POS02,	DIV2,		
// old actua	
// old actua			(DIV1*16)+POS14,	(DIV1*16)+POS11,	DIV1,		
// old actua			(DIV3*16)+POS14,	(DIV3*16)+POS11,	DIV3,		
// old actua			(DIV2*16)+POS12,	(DIV2*16)+POS01,	DIV2,		
// old actua	
// old actua			(DIV2*16)+POS14,	(DIV2*16)+POS05,	DIV2,		
// old actua			(DIV1*16)+POS04,	(DIV1*16)+POS01,	DIV1,		//13
// old actua			(DIV3*16)+POS04,	(DIV3*16)+POS01,	DIV3,		//13
// old actua			(DIV2*16)+POS13,	(DIV2*16)+POS07,	DIV2,		
// old actua	
// old actua			(DIV1*16)+POS06,	(DIV1*16)+POS03,	DIV1,		
// old actua			(DIV3*16)+POS06,	(DIV3*16)+POS03,	DIV3,		
// old actua			(DIV2*16)+POS11,	(DIV2*16)+POS09,	DIV2,		
// old actua	
// old actua			(DIV1*16)+POS08,	(DIV1*16)+POS05,	DIV1,		
// old actua			(DIV3*16)+POS08,	(DIV3*16)+POS05,	DIV3,		
// old actua			(DIV2*16)+POS14,	(DIV2*16)+POS03,	DIV2,		
// old actua	
// old actua			(DIV2*16)+POS12,	(DIV2*16)+POS03,	DIV2,		
// old actua			(DIV1*16)+POS10,	(DIV1*16)+POS07,	DIV1,		
// old actua			(DIV3*16)+POS10,	(DIV3*16)+POS07,	DIV3,		
// old actua			(DIV2*16)+POS15,	(DIV2*16)+POS05,	DIV2,		
// old actua	
// old actua			(DIV1*16)+POS09,	(DIV1*16)+POS12,	DIV1,		//14
// old actua			(DIV3*16)+POS09,	(DIV3*16)+POS12,	DIV3,		//14
// old actua			(DIV2*16)+POS02,	(DIV2*16)+POS08,	DIV2,		
// old actua	
// old actua			(DIV1*16)+POS02,	(DIV1*16)+POS14,	DIV1,		
// old actua			(DIV3*16)+POS02,	(DIV3*16)+POS14,	DIV3,		
// old actua			(DIV2*16)+POS01,	(DIV2*16)+POS10,	DIV2,		
// old actua	
// old actua			(DIV2*16)+POS10,	(DIV2*16)+POS01,	DIV2,		
// old actua			(DIV1*16)+POS02,	(DIV1*16)+POS01,	DIV1,		
// old actua			(DIV3*16)+POS02,	(DIV3*16)+POS01,	DIV3,		
// old actua			(DIV2*16)+POS03,	(DIV2*16)+POS12,	DIV2,		
// old actua	
// old actua			(DIV1*16)+POS04,	(DIV1*16)+POS03,	DIV1,		//15
// old actua			(DIV3*16)+POS04,	(DIV3*16)+POS03,	DIV3,		//15
// old actua			(DIV2*16)+POS05,	(DIV2*16)+POS14,	DIV2,		
// old actua	
// old actua			(DIV1*16)+POS06,	(DIV1*16)+POS05,	DIV1,		
// old actua			(DIV3*16)+POS06,	(DIV3*16)+POS05,	DIV3,		
// old actua			(DIV2*16)+POS07,	(DIV2*16)+POS15,	DIV2,		
// old actua	
// old actua			(DIV2*16)+POS08,	(DIV2*16)+POS02,	DIV2,		
// old actua			(DIV1*16)+POS08,	(DIV1*16)+POS07,	DIV1,		
// old actua			(DIV3*16)+POS08,	(DIV3*16)+POS07,	DIV3,		
// old actua			(DIV2*16)+POS09,	(DIV2*16)+POS13,	DIV2,		
// old actua	
// old actua			(DIV1*16)+POS10,	(DIV1*16)+POS09,	DIV1,		
// old actua			(DIV3*16)+POS10,	(DIV3*16)+POS09,	DIV3,		
// old actua			(DIV2*16)+POS04,	(DIV2*16)+POS06,	DIV2,		
// old actua	
// old actua			(DIV1*16)+POS12,	(DIV1*16)+POS11,	DIV1,		
// old actua			(DIV3*16)+POS12,	(DIV3*16)+POS11,	DIV3,		
// old actua			(DIV2*16)+POS16,	(DIV2*16)+POS11,	DIV2,		
// old actua	
// old actua			(DIV2*16)+POS05,	(DIV2*16)+POS15,	DIV2,		
// old actua			(DIV1*16)+POS14,	(DIV1*16)+POS13,	DIV1,		
// old actua			(DIV3*16)+POS14,	(DIV3*16)+POS13,	DIV3,		
// old actua			(DIV2*16)+POS04,	(DIV2*16)+POS16,	DIV2,		
// old actua	
// old actua			(DIV1*16)+POS03,	(DIV1*16)+POS02,	DIV1,		
// old actua			(DIV3*16)+POS03,	(DIV3*16)+POS02,	DIV3,		
// old actua			(DIV2*16)+POS06,	(DIV2*16)+POS02,	DIV2,		
// old actua	
// old actua			(DIV1*16)+POS07,	(DIV1*16)+POS06,	DIV1,		
// old actua			(DIV3*16)+POS07,	(DIV3*16)+POS06,	DIV3,		
// old actua			(DIV2*16)+POS08,	(DIV2*16)+POS01,	DIV2,		
// old actua	
// old actua			(DIV2*16)+POS03,	(DIV2*16)+POS14,	DIV2,		
// old actua			(DIV1*16)+POS05,	(DIV1*16)+POS04,	DIV1,		//16
// old actua			(DIV3*16)+POS05,	(DIV3*16)+POS04,	DIV3,		//16
// old actua			(DIV2*16)+POS10,	(DIV2*16)+POS03,	DIV2,		
// old actua	
// old actua			(DIV1*16)+POS09,	(DIV1*16)+POS08,	DIV1,		
// old actua			(DIV3*16)+POS09,	(DIV3*16)+POS08,	DIV3,		
// old actua			(DIV2*16)+POS12,	(DIV2*16)+POS05,	DIV2,		
// old actua	
// old actua			(DIV1*16)+POS11,	(DIV1*16)+POS10,	DIV1,		
// old actua			(DIV3*16)+POS11,	(DIV3*16)+POS10,	DIV3,		
// old actua			(DIV2*16)+POS13,	(DIV2*16)+POS11,	DIV2,		
// old actua	
// old actua			(DIV2*16)+POS09,	(DIV2*16)+POS11,	DIV2,		
// old actua			(DIV1*16)+POS13,	(DIV1*16)+POS12,	DIV1,		
// old actua			(DIV3*16)+POS13,	(DIV3*16)+POS12,	DIV3,		
// old actua			(DIV2*16)+POS14,	(DIV2*16)+POS07,	DIV2,		
// old actua	
// old actua			(DIV1*16)+POS01,	(DIV1*16)+POS14,	DIV1,		
// old actua			(DIV3*16)+POS01,	(DIV3*16)+POS14,	DIV3,		
// old actua			(DIV2*16)+POS15,	(DIV2*16)+POS09,	DIV2,		
// old actua	
// old actua			(DIV1*16)+POS02,	(DIV1*16)+POS05,	DIV1,		
// old actua			(DIV3*16)+POS02,	(DIV3*16)+POS05,	DIV3,		
// old actua			(DIV2*16)+POS02,	(DIV2*16)+POS04,	DIV2,		
// old actua	
// old actua			(DIV2*16)+POS07,	(DIV2*16)+POS13,	DIV2,		
// old actua			(DIV1*16)+POS01,	(DIV1*16)+POS03,	DIV1,		
// old actua			(DIV3*16)+POS01,	(DIV3*16)+POS03,	DIV3,		
// old actua			(DIV2*16)+POS01,	(DIV2*16)+POS06,	DIV2,		
// old actua	
// old actua			(DIV1*16)+POS04,	(DIV1*16)+POS07,	DIV1,		//17
// old actua			(DIV3*16)+POS04,	(DIV3*16)+POS07,	DIV3,		//17
// old actua			(DIV2*16)+POS03,	(DIV2*16)+POS08,	DIV2,		
// old actua	
// old actua			(DIV1*16)+POS06,	(DIV1*16)+POS09,	DIV1,		
// old actua			(DIV3*16)+POS06,	(DIV3*16)+POS09,	DIV3,		
// old actua			(DIV2*16)+POS05,	(DIV2*16)+POS10,	DIV2,		
// old actua	
// old actua			(DIV2*16)+POS01,	(DIV2*16)+POS12,	DIV2,		
// old actua			(DIV1*16)+POS08,	(DIV1*16)+POS11,	DIV1,		
// old actua			(DIV3*16)+POS08,	(DIV3*16)+POS11,	DIV3,		
// old actua			(DIV2*16)+POS11,	(DIV2*16)+POS15,	DIV2,		
// old actua	
// old actua			(DIV1*16)+POS10,	(DIV1*16)+POS13,	DIV1,		
// old actua			(DIV3*16)+POS10,	(DIV3*16)+POS13,	DIV3,		
// old actua			(DIV2*16)+POS07,	(DIV2*16)+POS12,	DIV2,		
// old actua	
// old actua			(DIV1*16)+POS14,	(DIV1*16)+POS12,	DIV1,		
// old actua			(DIV3*16)+POS14,	(DIV3*16)+POS12,	DIV3,		
// old actua			(DIV2*16)+POS09,	(DIV2*16)+POS14,	DIV2,		
// old actua	
// old actua			(DIV2*16)+POS02,	(DIV2*16)+POS10,	DIV2,		
// old actua			(DIV1*16)+POS07,	(DIV1*16)+POS02,	DIV1,		
// old actua			(DIV3*16)+POS07,	(DIV3*16)+POS02,	DIV3,		
// old actua			(DIV2*16)+POS16,	(DIV2*16)+POS13,	DIV2,		
// old actua	
// old actua			(DIV1*16)+POS05,	(DIV1*16)+POS01,	DIV1,		
// old actua			(DIV3*16)+POS05,	(DIV3*16)+POS01,	DIV3,		
// old actua			(DIV2*16)+POS04,	(DIV2*16)+POS01,	DIV2,		
// old actua	
// old actua			(DIV1*16)+POS09,	(DIV1*16)+POS04,	DIV1,		//18
// old actua			(DIV3*16)+POS09,	(DIV3*16)+POS04,	DIV3,		//18
// old actua			(DIV2*16)+POS06,	(DIV2*16)+POS03,	DIV2,		
// old actua	
// old actua			(DIV2*16)+POS04,	(DIV2*16)+POS08,	DIV2,		
// old actua			(DIV1*16)+POS11,	(DIV1*16)+POS06,	DIV1,		
// old actua			(DIV3*16)+POS11,	(DIV3*16)+POS06,	DIV3,		
// old actua			(DIV2*16)+POS08,	(DIV2*16)+POS05,	DIV2,		
// old actua	
// old actua			(DIV1*16)+POS13,	(DIV1*16)+POS08,	DIV1,		
// old actua			(DIV3*16)+POS13,	(DIV3*16)+POS08,	DIV3,		
// old actua			(DIV2*16)+POS10,	(DIV2*16)+POS07,	DIV2,		
// old actua	
// old actua			(DIV1*16)+POS12,	(DIV1*16)+POS10,	DIV1,		
// old actua			(DIV3*16)+POS12,	(DIV3*16)+POS10,	DIV3,		
// old actua			(DIV2*16)+POS15,	(DIV2*16)+POS13,	DIV2,		
// old actua	
// old actua			(DIV2*16)+POS16,	(DIV2*16)+POS06,	DIV2,		
// old actua			(DIV1*16)+POS03,	(DIV1*16)+POS14,	DIV1,		
// old actua			(DIV3*16)+POS03,	(DIV3*16)+POS14,	DIV3,		
// old actua			(DIV2*16)+POS16,	(DIV2*16)+POS02,	DIV2,		
// old actua	
// old actua			(DIV1*16)+POS02,	(DIV1*16)+POS09,	DIV1,		
// old actua			(DIV3*16)+POS02,	(DIV3*16)+POS09,	DIV3,		
// old actua			(DIV2*16)+POS12,	(DIV2*16)+POS09,	DIV2,		
// old actua	
// old actua			(DIV1*16)+POS13,	(DIV1*16)+POS11,	DIV1,		
// old actua			(DIV3*16)+POS13,	(DIV3*16)+POS11,	DIV3,		
// old actua	
// old actua			(DIV1*16)+POS01,	(DIV1*16)+POS07,	DIV1,		
// old actua			(DIV3*16)+POS01,	(DIV3*16)+POS07,	DIV3,		
// old actua			(DIV2*16)+POS14,	(DIV2*16)+POS11,	DIV2,		
// old actua	
// old actua			(DIV2*16)+POS09,	(DIV2*16)+POS16,	DIV2,		
// old actua			(DIV1*16)+POS03,	(DIV1*16)+POS05,	DIV1,		
// old actua			(DIV3*16)+POS03,	(DIV3*16)+POS05,	DIV3,		
// old actua			(DIV2*16)+POS02,	(DIV2*16)+POS01,	DIV2,		
// old actua	
// old actua			(DIV1*16)+POS04,	(DIV1*16)+POS11,	DIV1,		//19
// old actua			(DIV3*16)+POS04,	(DIV3*16)+POS11,	DIV3,		//19
// old actua			(DIV2*16)+POS04,	(DIV2*16)+POS03,	DIV2,		
// old actua	
// old actua			(DIV1*16)+POS06,	(DIV1*16)+POS13,	DIV1,		
// old actua			(DIV3*16)+POS06,	(DIV3*16)+POS13,	DIV3,		
// old actua			(DIV2*16)+POS06,	(DIV2*16)+POS05,	DIV2,		
// old actua	
// old actua			(DIV2*16)+POS08,	(DIV2*16)+POS06,	DIV2,		
// old actua			(DIV1*16)+POS08,	(DIV1*16)+POS12,	DIV1,		
// old actua			(DIV3*16)+POS08,	(DIV3*16)+POS12,	DIV3,		
// old actua			(DIV2*16)+POS08,	(DIV2*16)+POS07,	DIV2,		
// old actua	
// old actua			(DIV1*16)+POS14,	(DIV1*16)+POS10,	DIV1,		
// old actua			(DIV3*16)+POS14,	(DIV3*16)+POS10,	DIV3,		
// old actua			(DIV2*16)+POS10,	(DIV2*16)+POS09,	DIV2,		
// old actua	
// old actua			(DIV1*16)+POS11,	(DIV1*16)+POS02,	DIV1,		
// old actua			(DIV3*16)+POS11,	(DIV3*16)+POS02,	DIV3,		
// old actua			(DIV2*16)+POS12,	(DIV2*16)+POS11,	DIV2,		
// old actua	
// old actua			(DIV2*16)+POS10,	(DIV2*16)+POS04,	DIV2,		
// old actua			(DIV1*16)+POS09,	(DIV1*16)+POS01,	DIV1,		
// old actua			(DIV3*16)+POS09,	(DIV3*16)+POS01,	DIV3,		
// old actua			(DIV2*16)+POS14,	(DIV2*16)+POS13,	DIV2,		
// old actua	
// old actua			(DIV1*16)+POS07,	(DIV1*16)+POS03,	DIV1,		
// old actua			(DIV3*16)+POS07,	(DIV3*16)+POS03,	DIV3,		
// old actua			(DIV2*16)+POS16,	(DIV2*16)+POS15,	DIV2,		
// old actua	
// old actua			(DIV1*16)+POS13,	(DIV1*16)+POS04,	DIV1,		//20
// old actua			(DIV3*16)+POS13,	(DIV3*16)+POS04,	DIV3,		//20
// old actua			(DIV2*16)+POS03,	(DIV2*16)+POS02,	DIV2,		
// old actua	
// old actua			(DIV2*16)+POS11,	(DIV2*16)+POS07,	DIV2,		
// old actua			(DIV1*16)+POS12,	(DIV1*16)+POS06,	DIV1,		
// old actua			(DIV3*16)+POS12,	(DIV3*16)+POS06,	DIV3,		
// old actua			(DIV2*16)+POS07,	(DIV2*16)+POS06,	DIV2,		
// old actua	
// old actua			(DIV1*16)+POS10,	(DIV1*16)+POS08,	DIV1,		
// old actua			(DIV3*16)+POS10,	(DIV3*16)+POS08,	DIV3,		
// old actua			(DIV2*16)+POS05,	(DIV2*16)+POS04,	DIV2,		
// old actua	
// old actua			(DIV1*16)+POS05,	(DIV1*16)+POS14,	DIV1,		
// old actua			(DIV3*16)+POS05,	(DIV3*16)+POS14,	DIV3,		
// old actua			(DIV2*16)+POS09,	(DIV2*16)+POS08,	DIV2,		
// old actua	
// old actua			(DIV2*16)+POS13,	(DIV2*16)+POS05,	DIV2,		
// old actua			(DIV1*16)+POS02,	(DIV1*16)+POS13,	DIV1,		
// old actua			(DIV3*16)+POS02,	(DIV3*16)+POS13,	DIV3,		
// old actua			(DIV2*16)+POS11,	(DIV2*16)+POS10,	DIV2,		
// old actua	
// old actua			(DIV1*16)+POS01,	(DIV1*16)+POS11,	DIV1,		
// old actua			(DIV3*16)+POS01,	(DIV3*16)+POS11,	DIV3,		
// old actua			(DIV2*16)+POS13,	(DIV2*16)+POS12,	DIV2,		
// old actua	
// old actua			(DIV1*16)+POS03,	(DIV1*16)+POS09,	DIV1,		
// old actua			(DIV3*16)+POS03,	(DIV3*16)+POS09,	DIV3,		
// old actua			(DIV2*16)+POS15,	(DIV2*16)+POS14,	DIV2,		
// old actua	
// old actua			(DIV2*16)+POS15,	(DIV2*16)+POS03,	DIV2,		
// old actua			(DIV1*16)+POS05,	(DIV1*16)+POS07,	DIV1,		
// old actua			(DIV3*16)+POS05,	(DIV3*16)+POS07,	DIV3,		
// old actua			(DIV2*16)+POS01,	(DIV2*16)+POS16,	DIV2,		
// old actua	
// old actua			(DIV1*16)+POS04,	(DIV1*16)+POS12,	DIV1,		//21
// old actua			(DIV3*16)+POS04,	(DIV3*16)+POS12,	DIV3,		//21
// old actua			(DIV2*16)+POS02,	(DIV2*16)+POS05,	DIV2,		
// old actua	
// old actua			(DIV1*16)+POS06,	(DIV1*16)+POS10,	DIV1,		
// old actua			(DIV3*16)+POS06,	(DIV3*16)+POS10,	DIV3,		
// old actua			(DIV2*16)+POS01,	(DIV2*16)+POS03,	DIV2,		
// old actua	
// old actua			(DIV2*16)+POS14,	(DIV2*16)+POS01,	DIV2,		
// old actua			(DIV1*16)+POS14,	(DIV1*16)+POS08,	DIV1,		
// old actua			(DIV3*16)+POS14,	(DIV3*16)+POS08,	DIV3,		
// old actua			(DIV2*16)+POS04,	(DIV2*16)+POS07,	DIV2,		
// old actua	
// old actua			(DIV1*16)+POS12,	(DIV1*16)+POS02,	DIV1,		
// old actua			(DIV3*16)+POS12,	(DIV3*16)+POS02,	DIV3,		
// old actua			(DIV2*16)+POS06,	(DIV2*16)+POS09,	DIV2,		
// old actua	
// old actua			(DIV1*16)+POS13,	(DIV1*16)+POS01,	DIV1,		
// old actua			(DIV3*16)+POS13,	(DIV3*16)+POS01,	DIV3,		
// old actua			(DIV2*16)+POS08,	(DIV2*16)+POS11,	DIV2,		
// old actua	
// old actua			(DIV2*16)+POS12,	(DIV2*16)+POS02,	DIV2,		
// old actua			(DIV1*16)+POS11,	(DIV1*16)+POS03,	DIV1,		
// old actua			(DIV3*16)+POS11,	(DIV3*16)+POS03,	DIV3,		
// old actua			(DIV2*16)+POS10,	(DIV2*16)+POS13,	DIV2,		
// old actua	
// old actua			(DIV1*16)+POS09,	(DIV1*16)+POS05,	DIV1,		
// old actua			(DIV3*16)+POS09,	(DIV3*16)+POS05,	DIV3,		
// old actua			(DIV2*16)+POS12,	(DIV2*16)+POS15,	DIV2,		
// old actua	
// old actua			(DIV1*16)+POS10,	(DIV1*16)+POS04,	DIV1,		//22
// old actua			(DIV3*16)+POS10,	(DIV3*16)+POS04,	DIV3,		//22
// old actua			(DIV2*16)+POS16,	(DIV2*16)+POS14,	DIV2,		
// old actua	
// old actua			(DIV2*16)+POS02,	(DIV2*16)+POS14,	DIV2,		
// old actua			(DIV1*16)+POS08,	(DIV1*16)+POS06,	DIV1,		
// old actua			(DIV3*16)+POS08,	(DIV3*16)+POS06,	DIV3,		
// old actua			(DIV2*16)+POS07,	(DIV2*16)+POS02,	DIV2,		
// old actua	
// old actua			(DIV1*16)+POS07,	(DIV1*16)+POS14,	DIV1,		
// old actua			(DIV3*16)+POS07,	(DIV3*16)+POS14,	DIV3,		
// old actua			(DIV2*16)+POS05,	(DIV2*16)+POS01,	DIV2,		
// old actua	
// old actua			(DIV1*16)+POS02,	(DIV1*16)+POS10,	DIV1,		
// old actua			(DIV3*16)+POS02,	(DIV3*16)+POS10,	DIV3,		
// old actua			(DIV2*16)+POS09,	(DIV2*16)+POS04,	DIV2,		
// old actua	
// old actua			(DIV2*16)+POS01,	(DIV2*16)+POS15,	DIV2,		
// old actua			(DIV1*16)+POS01,	(DIV1*16)+POS12,	DIV1,		
// old actua			(DIV3*16)+POS01,	(DIV3*16)+POS12,	DIV3,		
// old actua			(DIV2*16)+POS11,	(DIV2*16)+POS06,	DIV2,		
// old actua	
// old actua			(DIV1*16)+POS03,	(DIV1*16)+POS13,	DIV1,		
// old actua			(DIV3*16)+POS03,	(DIV3*16)+POS13,	DIV3,		
// old actua			(DIV2*16)+POS13,	(DIV2*16)+POS08,	DIV2,		
// old actua	
// old actua			(DIV1*16)+POS05,	(DIV1*16)+POS11,	DIV1,		
// old actua			(DIV3*16)+POS05,	(DIV3*16)+POS11,	DIV3,		
// old actua			(DIV2*16)+POS15,	(DIV2*16)+POS10,	DIV2,		
// old actua	
// old actua			(DIV2*16)+POS16,	(DIV2*16)+POS08,	DIV2,		
// old actua			(DIV1*16)+POS07,	(DIV1*16)+POS09,	DIV1,		
// old actua			(DIV3*16)+POS07,	(DIV3*16)+POS09,	DIV3,		
// old actua			(DIV2*16)+POS14,	(DIV2*16)+POS12,	DIV2,		
// old actua	
// old actua			(DIV1*16)+POS04,	(DIV1*16)+POS08,	DIV1,		//23
// old actua			(DIV3*16)+POS04,	(DIV3*16)+POS08,	DIV3,		//23
// old actua			(DIV2*16)+POS03,	(DIV2*16)+POS16,	DIV2,		
// old actua	
// old actua			(DIV1*16)+POS14,	(DIV1*16)+POS06,	DIV1,		
// old actua			(DIV3*16)+POS14,	(DIV3*16)+POS06,	DIV3,		
// old actua			(DIV2*16)+POS02,	(DIV2*16)+POS09,	DIV2,		
// old actua	
// old actua			(DIV2*16)+POS07,	(DIV2*16)+POS09,	DIV2,		
// old actua			(DIV1*16)+POS08,	(DIV1*16)+POS02,	DIV1,		
// old actua			(DIV3*16)+POS08,	(DIV3*16)+POS02,	DIV3,		
// old actua			(DIV2*16)+POS01,	(DIV2*16)+POS07,	DIV2,		
// old actua	
// old actua			(DIV1*16)+POS10,	(DIV1*16)+POS01,	DIV1,		
// old actua			(DIV3*16)+POS10,	(DIV3*16)+POS01,	DIV3,		
// old actua			(DIV2*16)+POS03,	(DIV2*16)+POS05,	DIV2,		
// old actua	
// old actua			(DIV1*16)+POS12,	(DIV1*16)+POS03,	DIV1,		
// old actua			(DIV3*16)+POS12,	(DIV3*16)+POS03,	DIV3,		
// old actua			(DIV2*16)+POS04,	(DIV2*16)+POS11,	DIV2,		
// old actua	
// old actua			(DIV2*16)+POS05,	(DIV2*16)+POS11,	DIV2,		
// old actua			(DIV1*16)+POS13,	(DIV1*16)+POS05,	DIV1,		
// old actua			(DIV3*16)+POS13,	(DIV3*16)+POS05,	DIV3,		
// old actua			(DIV2*16)+POS06,	(DIV2*16)+POS13,	DIV2,		
// old actua	
// old actua			(DIV1*16)+POS11,	(DIV1*16)+POS07,	DIV1,		
// old actua			(DIV3*16)+POS11,	(DIV3*16)+POS07,	DIV3,		
// old actua			(DIV2*16)+POS16,	(DIV2*16)+POS12,	DIV2,		
// old actua	
// old actua			(DIV1*16)+POS06,	(DIV1*16)+POS04,	DIV1,		//24
// old actua			(DIV3*16)+POS06,	(DIV3*16)+POS04,	DIV3,		//24
// old actua			(DIV2*16)+POS10,	(DIV2*16)+POS14,	DIV2,		
// old actua	
// old actua			(DIV2*16)+POS03,	(DIV2*16)+POS13,	DIV2,		
// old actua			(DIV1*16)+POS09,	(DIV1*16)+POS14,	DIV1,		
// old actua			(DIV3*16)+POS09,	(DIV3*16)+POS14,	DIV3,		
// old actua			(DIV2*16)+POS08,	(DIV2*16)+POS15,	DIV2,		
// old actua	
// old actua			(DIV1*16)+POS02,	(DIV1*16)+POS06,	DIV1,		
// old actua			(DIV3*16)+POS02,	(DIV3*16)+POS06,	DIV3,		
// old actua			(DIV2*16)+POS11,	(DIV2*16)+POS02,	DIV2,		
// old actua	
// old actua			(DIV1*16)+POS01,	(DIV1*16)+POS08,	DIV1,		
// old actua			(DIV3*16)+POS01,	(DIV3*16)+POS08,	DIV3,		
// old actua			(DIV2*16)+POS09,	(DIV2*16)+POS01,	DIV2,		
// old actua	
// old actua			(DIV2*16)+POS04,	(DIV2*16)+POS12,	DIV2,		
// old actua			(DIV1*16)+POS03,	(DIV1*16)+POS10,	DIV1,		
// old actua			(DIV3*16)+POS03,	(DIV3*16)+POS10,	DIV3,		
// old actua			(DIV2*16)+POS07,	(DIV2*16)+POS03,	DIV2,		
// old actua	
// old actua			(DIV1*16)+POS05,	(DIV1*16)+POS12,	DIV1,		
// old actua			(DIV3*16)+POS05,	(DIV3*16)+POS12,	DIV3,		
// old actua			(DIV2*16)+POS13,	(DIV2*16)+POS04,	DIV2,		
// old actua	
// old actua			(DIV1*16)+POS07,	(DIV1*16)+POS13,	DIV1,		
// old actua			(DIV3*16)+POS07,	(DIV3*16)+POS13,	DIV3,		
// old actua			(DIV2*16)+POS15,	(DIV2*16)+POS06,	DIV2,		
// old actua	
// old actua			(DIV2*16)+POS06,	(DIV2*16)+POS10,	DIV2,		
// old actua			(DIV1*16)+POS09,	(DIV1*16)+POS11,	DIV1,		
// old actua			(DIV3*16)+POS09,	(DIV3*16)+POS11,	DIV3,		
// old actua			(DIV2*16)+POS14,	(DIV2*16)+POS08,	DIV2,		
// old actua	
// old actua			(DIV1*16)+POS14,	(DIV1*16)+POS04,	DIV1,		//25
// old actua			(DIV3*16)+POS14,	(DIV3*16)+POS04,	DIV3,		//25
// old actua			(DIV2*16)+POS05,	(DIV2*16)+POS16,	DIV2,		
// old actua	
// old actua			(DIV1*16)+POS04,	(DIV1*16)+POS02,	DIV1,		//26
// old actua			(DIV3*16)+POS04,	(DIV3*16)+POS02,	DIV3,		//26
// old actua			(DIV2*16)+POS12,	(DIV2*16)+POS10,	DIV2,		
// old actua	
// old actua			(DIV2*16)+POS07,	(DIV2*16)+POS16,	DIV2,		
// old actua			(DIV1*16)+POS06,	(DIV1*16)+POS01,	DIV1,		
// old actua			(DIV3*16)+POS06,	(DIV3*16)+POS01,	DIV3,		
// old actua			(DIV2*16)+POS02,	(DIV2*16)+POS13,	DIV2,		
// old actua	
// old actua			(DIV1*16)+POS08,	(DIV1*16)+POS03,	DIV1,		
// old actua			(DIV3*16)+POS08,	(DIV3*16)+POS03,	DIV3,		
// old actua			(DIV2*16)+POS01,	(DIV2*16)+POS11,	DIV2,		
// old actua	
// old actua			(DIV1*16)+POS10,	(DIV1*16)+POS05,	DIV1,		
// old actua			(DIV3*16)+POS10,	(DIV3*16)+POS05,	DIV3,		
// old actua			(DIV2*16)+POS03,	(DIV2*16)+POS09,	DIV2,		
// old actua	
// old actua			(DIV2*16)+POS10,	(DIV2*16)+POS08,	DIV2,		
// old actua			(DIV1*16)+POS12,	(DIV1*16)+POS07,	DIV1,		
// old actua			(DIV3*16)+POS12,	(DIV3*16)+POS07,	DIV3,		
// old actua			(DIV2*16)+POS05,	(DIV2*16)+POS07,	DIV2,		
// old actua	
// old actua			(DIV1*16)+POS13,	(DIV1*16)+POS09,	DIV1,		
// old actua			(DIV3*16)+POS13,	(DIV3*16)+POS09,	DIV3,		
// old actua			(DIV2*16)+POS08,	(DIV2*16)+POS12,	DIV2,		
// old actua	
// old actua			(DIV1*16)+POS11,	(DIV1*16)+POS14,	DIV1,		
// old actua			(DIV3*16)+POS11,	(DIV3*16)+POS14,	DIV3,		
// old actua			(DIV2*16)+POS16,	(DIV2*16)+POS10,	DIV2,		
// old actua	
// old actua			(DIV2*16)+POS12,	(DIV2*16)+POS06,	DIV2,		
// old actua			(DIV1*16)+POS01,	(DIV1*16)+POS04,	DIV1,		//27
// old actua			(DIV3*16)+POS01,	(DIV3*16)+POS04,	DIV3,		//27
// old actua			(DIV2*16)+POS06,	(DIV2*16)+POS14,	DIV2,		
// old actua	
// old actua			(DIV1*16)+POS03,	(DIV1*16)+POS06,	DIV1,		
// old actua			(DIV3*16)+POS03,	(DIV3*16)+POS06,	DIV3,		
// old actua			(DIV2*16)+POS04,	(DIV2*16)+POS15,	DIV2,		
// old actua	
// old actua			(DIV1*16)+POS05,	(DIV1*16)+POS08,	DIV1,		
// old actua			(DIV3*16)+POS05,	(DIV3*16)+POS08,	DIV3,		
// old actua			(DIV2*16)+POS15,	(DIV2*16)+POS02,	DIV2,		
// old actua	
// old actua			(DIV2*16)+POS14,	(DIV2*16)+POS04,	DIV2,		
// old actua			(DIV1*16)+POS07,	(DIV1*16)+POS10,	DIV1,		
// old actua			(DIV3*16)+POS07,	(DIV3*16)+POS10,	DIV3,		
// old actua			(DIV2*16)+POS13,	(DIV2*16)+POS01,	DIV2,		
// old actua	
// old actua			(DIV1*16)+POS12,	(DIV1*16)+POS09,	DIV1,		//28
// old actua			(DIV3*16)+POS12,	(DIV3*16)+POS09,	DIV3,		//28
// old actua			(DIV2*16)+POS11,	(DIV2*16)+POS03,	DIV2,		
// old actua	
// old actua			(DIV1*16)+POS14,	(DIV1*16)+POS02,	DIV1,		
// old actua			(DIV3*16)+POS14,	(DIV3*16)+POS02,	DIV3,		
// old actua			(DIV2*16)+POS09,	(DIV2*16)+POS05,	DIV2,		
// old actua	
// old actua			-1,			-1,			-1,		// END OF SEASON
// old actua	
// old actua				}; 
	
	signed int 	restore_cup_data[MAX_TEAMS-1]={
			{-1,},
			{-1,},
			{-1,},
			{-1,},
			{-1,},
			{-1,},
			{-1,},
			{-1,},
			{-1,},
			{-1,},
			{-1,},
		{-1,},
		{-1,},
		{-1,},
		{-1,},
		{-1,},
		{-1,},
		{-1,},
		{-1,},
		{-1,},
		{-1,},
		{-1,},
		{-1,},
		{-1,},
		{-1,},
		{-1,},
		{-1,},
		{-1,},
		{-1,},
		{-1,},
		{-1,},
		{-1,},
		{-1,},
		{-1,},
		{-1,},
		{-1,},
		{-1,},
		{-1,},
		{-1,},
		{-1,},
		{-1,},
		{-1,},
		{-1,},
			};


demo_struct	demo_data[]={

		{ENG,BRA,55745,ENG,4},		// english demo
		{ENG,BRA,55745,ENG,4},		
		{SPN,ITA,2778,CAM,9},
		{SPN,ITA,2778,CAM,9},
		{GER,FRA,9808,BEL,2},
		{GER,FRA,9808,BEL,2},
		{DEN,SCO,9808,NOR,14},
		{DEN,SCO,9808,NOR,14},

		{ENG,BRA,55745,ENG,4},		// french demo
		{ENG,BRA,55745,ENG,4},		
		{SPN,ITA,2778,CAM,9},
		{SPN,ITA,2778,CAM,9},
		{GER,FRA,9808,BEL,2},
		{GER,FRA,9808,BEL,2},
		{DEN,SCO,9808,NOR,14},
		{DEN,SCO,9808,NOR,14},

		{GER,FRA,9808,BEL,2},	     	// german demo
		{GER,FRA,9808,BEL,2},	     	
		{ENG,BRA,55745,ENG,4},
		{ENG,BRA,55745,ENG,4},
		{SPN,ITA,2778,CAM,9},
		{SPN,ITA,2778,CAM,9},
		{DEN,SCO,9808,NOR,14},
		{DEN,SCO,9808,NOR,14},

		{USA,BRA,55745,ENG,4},		// american demo
		{USA,BRA,55745,ENG,4},		
		{SPN,ENG,2778,CAM,9},
		{SPN,ENG,2778,CAM,9},
		{GER,FRA,9808,BEL,2},
		{GER,FRA,9808,BEL,2},
		{DEN,SCO,9808,NOR,14},
		{DEN,SCO,9808,NOR,14},

		{USA,BRA,55745,ENG,4},		// canadian demo
		{USA,BRA,55745,ENG,4},		
		{SPN,ENG,2778,CAM,9},
		{SPN,ENG,2778,CAM,9},
		{GER,FRA,9808,BEL,2},
		{GER,FRA,9808,BEL,2},
		{DEN,SCO,9808,NOR,14},
		{DEN,SCO,9808,NOR,14},

		{NOR,BRA,55745,ENG,4},		// norwegian demo
		{NOR,BRA,55745,ENG,4},		
		{SPN,ENG,2778,CAM,9},
		{SPN,ENG,2778,CAM,9},
		{GER,FRA,9808,BEL,2},
		{GER,FRA,9808,BEL,2},
		{DEN,SCO,9808,NOR,14},
		{DEN,SCO,9808,NOR,14},

				};


goal_table	goals[MAX_GOALS+1]={
		{0,0,0},
		{0,0,0},
		{0,0,0},
		{0,0,0},
		{0,0,0},
		{0,0,0},
		{0,0,0},
		{0,0,0},
		{0,0,0},
		{0,0,0},
		{0,0,0},
		{0,0,0},
		{0,0,0},
		{0,0,0},
		{0,0,0},
		{0,0,0},
		{0,0,0},
		{0,0,0},
		{0,0,0},
		{0,0,0},
		{0,0,0},
		{0,0,0},
					};


// old actuaint	team_b_kit[]={
// old actua	USA, RUS, SPN, BUL, BEL, DEN, NIR, TUN,	ZAM, SWZ, CAM, WHT, WHT, MOR, ENG, WHT,	WAL, EGY, COL, SWE, ARG, EIR, HOL, FIN,	WHT, IVR, GHA, ROM, GER, WHT, NOR, SAU,	WHT, POL, WHT, URU, BRA, NIG, MEX, CZE,	WHT, POR, CHI, BOL, GRM,
// old actua	USA, RUS, SPN, BLU, BEL, DEN, NIR, TUN,	ZAM, SWZ, CAM, SKR, ITA, MOR, BLU, SCO,	WAL, EGY, COL, SWE, ARG, EIR, HOL, BLU,	SLV, IVR, BLU, ROM, BLU, GRE, NOR, BLU,	FRA, POL, JAP, URU, BRA, NIG, MEX, CZE,	ICE, POR, CHI, BOL, GRM,
// old actua	USA, RUS, SPN, BUL, WHT, WHT, NIR, WHT,	ZAM, WHT, CAM, SKR, ITA, WHT, ENG, SCO,	WHT, WHT, COL, SWE, ARG, EIR, HOL, FIN,	SLV, IVR, GHA, ROM, GER, GRE, WHT, SAU,	FRA, WHT, JAP, URU, BRA, NIG, MEX, WHT,	ICE, WHT, WHT, BOL, GRM,
// old actua	USA, BLU, SPN, BUL, BEL, DEN, NIR, TUN,	ZAM, SWZ, CAM, SKR, ITA, MOR, BLU, SCO,	WAL, EGY, COL, SWE, ARG, EIR, HOL, BLU,	SLV, IVR, BLU, ROM, BLU, GRE, NOR, BLU,	FRA, POL, JAP, URU, BRA, NIG, MEX, CZE,	ICE, POR, CHI, BOL, GRM,
// old actua	USA, RUS, WHT, BUL, BEL, WHT, NIR, WHT,	ZAM, WHT, CAM, SKR, ITA, WHT, ENG, SCO,	WHT, WHT, COL, SWE, ARG, EIR, HOL, FIN,	SLV, IVR, GHA, ROM, GER, GRE, WHT, SAU,	FRA, WHT, JAP, URU, BRA, NIG, MEX, WHT,	ICE, WHT, WHT, BOL, GRM,
// old actua	USA, RUS, WHT, BUL, WHT, DEN, NIR, WHT,	ZAM, WHT, CAM, SKR, ITA, WHT, ENG, SCO,	WHT, WHT, COL, SWE, ARG, EIR, HOL, FIN,	SLV, IVR, GHA, ROM, GER, GRE, WHT, SAU,	FRA, WHT, JAP, URU, BRA, NIG, MEX, WHT,	ICE, WHT, WHT, BOL, GRM,
// old actua	USA, RUS, SPN, BUL, BEL, DEN, NIR, TUN,	ZAM, SWZ, CAM, SKR, ITA, MOR, ENG, SCO,	WAL, EGY, COL, SWE, ARG, WHT, HOL, FIN,	SLV, IVR, GHA, ROM, GER, GRE, NOR, SAU,	FRA, POL, JAP, URU, BRA, NIG, MEX, CZE,	ICE, POR, CHI, BOL, GRM,
// old actua	USA, RUS, WHT, BUL, WHT, WHT, NIR, TUN,	ZAM, WHT, CAM, SKR, ITA, WHT, ENG, SCO,	WHT, WHT, COL, SWE, ARG, EIR, HOL, FIN,	SLV, IVR, GHA, ROM, GER, GRE, WHT, SAU,	FRA, WHT, JAP, URU, BRA, NIG, MEX, WHT,	ICE, WHT, WHT, BOL, GRM,
// old actua	USA, RUS, SPN, BUL, BEL, DEN, NIR, TUN,	ZAM, SWZ, WHT, SKR, ITA, MOR, ENG, SCO,	WAL, EGY, COL, SWE, ARG, WHT, HOL, FIN,	SLV, IVR, GHA, ROM, GER, GRE, NOR, SAU,	FRA, POL, JAP, URU, BRA, WHT, WHT, CZE,	ICE, POR, CHI, WHT, GRM,
// old actua	USA, RUS, WHT, BUL, WHT, WHT, NIR, WHT,	ZAM, WHT, CAM, SKR, ITA, WHT, ENG, SCO,	WHT, WHT, COL, SWE, ARG, EIR, HOL, FIN,	SLV, IVR, GHA, ROM, GER, GRE, WHT, SAU,	FRA, WHT, JAP, URU, BRA, NIG, MEX, WHT,	ICE, WHT, WHT, BOL, GRM,
// old actua	USA, RUS, SPN, BUL, BEL, DEN, NIR, TUN,	WHT, SWZ, CAM, SKR, ITA, MOR, ENG, SCO,	WAL, EGY, COL, SWE, ARG, WHT, HOL, FIN,	SLV, IVR, GHA, ROM, GER, GRE, NOR, SAU,	FRA, POL, JAP, URU, BRA, WHT, WHT, CZE,	ICE, POR, CHI, WHT, GRM,
// old actua	WHT, RUS, SPN, BUL, BEL, DEN, NIR, TUN,	ZAM, SWZ, CAM, SKR, WHT, MOR, ENG, WHT,	WAL, EGY, COL, SWE, ARG, EIR, HOL, FIN,	WHT, IVR, GHA, ROM, GER, WHT, NOR, SAU,	WHT, POL, WHT, WHT, BRA, NIG, MEX, CZE,	WHT, POR, CHI, BOL, GRM,
// old actua	WHT, RUS, SPN, BUL, BEL, DEN, NIR, TUN,	ZAM, SWZ, CAM, WHT, ITA, MOR, ENG, WHT,	WAL, EGY, COL, SWE, ARG, EIR, HOL, FIN,	WHT, IVR, GHA, ROM, GER, WHT, NOR, SAU,	WHT, POL, WHT, WHT, BRA, NIG, MEX, CZE,	WHT, POR, CHI, BOL, GRM,
// old actua	USA, RUS, WHT, BUL, WHT, WHT, NIR, WHT,	ZAM, WHT, CAM, SKR, ITA, WHT, ENG, SCO,	WHT, WHT, COL, SWE, ARG, EIR, HOL, FIN,	SLV, IVR, GHA, ROM, GER, GRE, WHT, SAU,	FRA, WHT, JAP, URU, BRA, NIG, MEX, WHT,	ICE, WHT, WHT, BOL, GRM,
// old actua	USA, BLU, SPN, BLU, BEL, DEN, NIR, TUN,	ZAM, SWZ, CAM, SKR, ITA, MOR, ENG, SCO,	WAL, EGY, COL, SWE, ARG, EIR, HOL, BLU,	SLV, IVR, BLU, ROM, BLU, GRE, NOR, BLU,	FRA, POL, JAP, URU, BRA, NIG, MEX, CZE,	ICE, POR, CHI, BOL, GRM,
// old actua	WHT, RUS, SPN, BUL, BEL, DEN, NIR, TUN,	ZAM, SWZ, CAM, WHT, WHT, MOR, ENG, SCO,	WAL, EGY, COL, SWE, ARG, EIR, HOL, FIN,	WHT, IVR, GHA, ROM, GER, WHT, NOR, SAU,	WHT, POL, WHT, URU, BRA, NIG, MEX, CZE,	WHT, POR, CHI, BOL, GRM,
// old actua	USA, RUS, WHT, BUL, WHT, WHT, NIR, WHT,	ZAM, WHT, CAM, SKR, ITA, WHT, ENG, SCO,	WAL, WHT, COL, SWE, ARG, EIR, HOL, FIN,	SLV, IVR, GHA, ROM, GER, GRE, WHT, SAU,	FRA, WHT, JAP, URU, BRA, NIG, MEX, WHT,	ICE, WHT, WHT, BOL, GRM,
// old actua	USA, RUS, WHT, BUL, WHT, WHT, NIR, WHT,	ZAM, WHT, CAM, SKR, ITA, WHT, ENG, SCO,	WHT, EGY, COL, SWE, ARG, EIR, HOL, FIN,	SLV, IVR, GHA, ROM, GER, GRE, WHT, SAU,	FRA, WHT, JAP, URU, BRA, NIG, MEX, WHT,	ICE, WHT, WHT, BOL, GRM,
// old actua	USA, RUS, SPN, BUL, BEL, DEN, NIR, TUN,	ZAM, SWZ, CAM, SKR, ITA, MOR, ENG, SCO,	WAL, EGY, COL, BLU, ARG, EIR, HOL, FIN,	SLV, IVR, GHA, BLU, GER, GRE, NOR, SAU,	FRA, POL, JAP, URU, BLU, NIG, MEX, CZE,	ICE, POR, CHI, BOL, BLU,
// old actua	USA, RUS, SPN, BUL, BEL, DEN, NIR, TUN,	ZAM, SWZ, CAM, SKR, ITA, MOR, ENG, SCO,	WAL, EGY, BLU, SWE, ARG, EIR, HOL, FIN,	SLV, IVR, GHA, BLU, GER, GRE, NOR, SAU,	FRA, POL, JAP, URU, BLU, NIG, MEX, CZE,	ICE, POR, CHI, BOL, BLU,
// old actua	USA, RUS, SPN, BUL, BEL, DEN, NIR, TUN,	ZAM, SWZ, CAM, SKR, ITA, MOR, ENG, SCO,	WAL, EGY, COL, SWE, ARG, EIR, HOL, FIN,	SLV, IVR, GHA, ROM, GER, GRE, NOR, SAU,	FRA, POL, JAP, BLU, BRA, NIG, MEX, CZE,	ICE, POR, CHI, BOL, GRM,
// old actua	USA, RUS, SPN, BUL, BEL, DEN, WHT, TUN,	WHT, SWZ, WHT, SKR, ITA, MOR, ENG, SCO,	WAL, EGY, COL, SWE, ARG, EIR, HOL, FIN,	SLV, IVR, GHA, ROM, GER, GRE, NOR, SAU,	FRA, POL, JAP, URU, BRA, WHT, WHT, CZE,	ICE, POR, CHI, WHT, GRM,
// old actua	USA, RUS, SPN, BUL, BEL, DEN, NIR, TUN,	ZAM, SWZ, CAM, SKR, ITA, MOR, ENG, SCO,	WAL, EGY, COL, SWE, ARG, EIR, HOL, FIN,	SLV, WHT, GHA, ROM, GER, GRE, NOR, SAU,	FRA, POL, JAP, URU, BRA, NIG, MEX, CZE,	ICE, POR, CHI, BOL, GRM,
// old actua	USA, BLU, SPN, BLU, BEL, DEN, NIR, TUN,	ZAM, SWZ, CAM, SKR, ITA, MOR, BLU, SCO,	WAL, EGY, COL, SWE, ARG, EIR, HOL, FIN,	SLV, IVR, BLU, ROM, BLU, GRE, NOR, BLU,	FRA, POL, JAP, URU, BRA, NIG, MEX, CZE,	ICE, POR, CHI, BOL, GRM,
// old actua	WHT, RUS, SPN, BUL, BEL, DEN, NIR, TUN,	ZAM, SWZ, CAM, WHT, WHT, MOR, ENG, WHT,	WAL, EGY, COL, SWE, ARG, EIR, HOL, FIN,	SLV, IVR, GHA, ROM, GER, WHT, NOR, SAU,	WHT, POL, WHT, URU, BRA, NIG, MEX, CZE,	WHT, POR, CHI, BOL, GRM,
// old actua	USA, RUS, SPN, BUL, BEL, DEN, NIR, TUN,	ZAM, SWZ, CAM, SKR, ITA, MOR, ENG, SCO,	WAL, EGY, COL, SWE, ARG, EIR, WHT, FIN,	SLV, IVR, GHA, ROM, GER, GRE, NOR, SAU,	FRA, POL, JAP, URU, BRA, NIG, MEX, CZE,	ICE, POR, CHI, BOL, GRM,
// old actua	USA, BLU, SPN, BLU, BEL, DEN, NIR, TUN,	ZAM, SWZ, CAM, SKR, ITA, MOR, BLU, SCO,	WAL, EGY, COL, SWE, ARG, EIR, HOL, BLU,	SLV, IVR, GHA, ROM, BLU, GRE, NOR, BLU,	FRA, POL, JAP, URU, BRA, NIG, MEX, CZE,	ICE, POR, CHI, BOL, GRM,
// old actua	USA, RUS, SPN, BUL, BEL, DEN, NIR, TUN,	ZAM, SWZ, CAM, SKR, ITA, MOR, ENG, SCO,	WAL, EGY, BLU, BLU, ARG, EIR, HOL, FIN,	SLV, IVR, GHA, ROM, GER, GRE, NOR, SAU,	FRA, POL, JAP, URU, BLU, NIG, MEX, CZE,	ICE, POR, CHI, BOL, BLU,
// old actua	USA, BLU, SPN, BLU, BEL, DEN, NIR, TUN,	ZAM, SWZ, CAM, SKR, ITA, MOR, BLU, SCO,	WAL, EGY, COL, SWE, ARG, EIR, HOL, BLU,	SLV, IVR, BLU, ROM, GER, GRE, NOR, BLU,	FRA, POL, JAP, URU, BRA, NIG, MEX, CZE,	ICE, POR, CHI, BOL, GRM,
// old actua	WHT, RUS, SPN, BUL, BEL, DEN, NIR, TUN,	ZAM, SWZ, CAM, WHT, WHT, MOR, ENG, WHT,	WAL, EGY, COL, SWE, ARG, EIR, HOL, FIN,	WHT, IVR, GHA, ROM, GER, GRE, NOR, SAU,	WHT, POL, WHT, URU, BRA, NIG, MEX, CZE,	WHT, POR, CHI, BOL, GRM,
// old actua	USA, RUS, WHT, BUL, BLU, BLU, NIR, BLU,	ZAM, BLU, CAM, SKR, ITA, BLU, ENG, SCO,	BLU, BLU, COL, SWE, ARG, EIR, HOL, FIN,	SLV, IVR, GHA, ROM, GER, GRE, NOR, SAU,	FRA, BLU, JAP, URU, BRA, NIG, MEX, BLU,	ICE, BLU, BLU, BOL, GRM,
// old actua	USA, BLU, SPN, BLU, BEL, DEN, NIR, TUN,	ZAM, SWZ, CAM, SKR, ITA, MOR, BLU, SCO,	WAL, EGY, COL, SWE, ARG, EIR, HOL, BLU,	SLV, IVR, BLU, ROM, GER, BLU, NOR, SAU,	FRA, POL, JAP, URU, BRA, NIG, MEX, CZE,	ICE, POR, CHI, BOL, GRM,
// old actua	WHT, RUS, SPN, BUL, BEL, DEN, NIR, TUN,	ZAM, SWZ, CAM, WHT, WHT, MOR, ENG, WHT,	WAL, EGY, COL, SWE, ARG, EIR, HOL, FIN,	WHT, IVR, GHA, ROM, GER, WHT, NOR, SAU,	WHT, POL, WHT, WHT, BRA, NIG, MEX, CZE,	WHT, POR, CHI, BOL, GRM,
// old actua	USA, RUS, WHT, BUL, BLU, BLU, NIR, BLU,	ZAM, BLU, CAM, SKR, ITA, BLU, ENG, SCO,	BLU, BLU, COL, SWE, ARG, EIR, HOL, FIN,	SLV, IVR, GHA, ROM, GER, GRE, WHT, SAU,	FRA, POL, JAP, URU, BRA, NIG, MEX, BLU,	ICE, BLU, BLU, BOL, GRM,
// old actua	WHT, RUS, SPN, BUL, BEL, DEN, NIR, TUN,	ZAM, SWZ, CAM, WHT, WHT, MOR, ENG, WHT,	WAL, EGY, COL, SWE, ARG, EIR, HOL, FIN,	WHT, IVR, GHA, ROM, GER, WHT, NOR, SAU,	WHT, POL, JAP, WHT, BRA, NIG, MEX, CZE,	WHT, POR, CHI, BOL, GRM,
// old actua	WHT, RUS, SPN, BUL, BEL, DEN, NIR, TUN,	ZAM, SWZ, CAM, WHT, WHT, MOR, ENG, WHT,	WAL, EGY, COL, SWE, ARG, EIR, HOL, FIN,	WHT, IVR, GHA, ROM, GER, WHT, NOR, SAU,	WHT, POL, WHT, URU, BRA, NIG, MEX, CZE,	WHT, POR, CHI, BOL, GRM,
// old actua	USA, RUS, SPN, BUL, BEL, DEN, NIR, TUN,	ZAM, SWZ, CAM, SKR, ITA, MOR, ENG, SCO,	WAL, EGY, BLU, BLU, ARG, EIR, HOL, FIN,	SLV, IVR, GHA, BLU, GER, GRE, NOR, SAU,	FRA, POL, JAP, URU, BRA, NIG, MEX, CZE,	ICE, POR, CHI, BOL, BLU,
// old actua	USA, RUS, SPN, BUL, BEL, DEN, NIR, TUN,	WHT, SWZ, WHT, SKR, ITA, MOR, ENG, SCO,	WAL, EGY, COL, SWE, ARG, WHT, HOL, FIN,	SLV, IVR, GHA, ROM, GER, GRE, NOR, SAU,	FRA, POL, JAP, URU, BRA, NIG, WHT, CZE,	ICE, POR, CHI, WHT, GRM,
// old actua	USA, RUS, SPN, BUL, BEL, DEN, NIR, TUN,	WHT, SWZ, WHT, SKR, ITA, MOR, ENG, SCO,	WAL, EGY, COL, SWE, ARG, WHT, HOL, FIN,	SLV, IVR, GHA, ROM, GER, GRE, NOR, SAU,	FRA, POL, JAP, URU, BRA, WHT, MEX, CZE,	ICE, POR, CHI, WHT, GRM,
// old actua	USA, RUS, WHT, BUL, WHT, WHT, NIR, WHT,	ZAM, WHT, CAM, SKR, ITA, WHT, ENG, SCO,	WHT, WHT, COL, SWE, ARG, EIR, HOL, FIN,	SLV, IVR, GHA, ROM, GER, GRE, WHT, SAU,	FRA, WHT, JAP, URU, BRA, NIG, MEX, CZE,	ICE, WHT, WHT, BOL, GRM,
// old actua	WHT, RUS, SPN, BUL, BEL, DEN, NIR, TUN,	ZAM, SWZ, CAM, WHT, WHT, MOR, ENG, WHT,	WAL, EGY, COL, SWE, ARG, EIR, HOL, FIN,	WHT, IVR, GHA, ROM, GER, WHT, NOR, SAU,	WHT, POL, WHT, WHT, BRA, NIG, MEX, CZE,	ICE, POR, CHI, BOL, GRM,
// old actua	USA, RUS, WHT, BUL, WHT, WHT, NIR, WHT,	ZAM, WHT, CAM, SKR, ITA, WHT, ENG, SCO,	WHT, WHT, COL, SWE, ARG, EIR, HOL, FIN,	SLV, IVR, GHA, ROM, GER, GRE, WHT, SAU,	FRA, WHT, JAP, URU, BRA, NIG, MEX, WHT,	ICE, POR, WHT, BOL, GRM,
// old actua	USA, RUS, WHT, BUL, WHT, WHT, NIR, WHT,	ZAM, WHT, CAM, SKR, ITA, WHT, ENG, SCO,	WHT, WHT, COL, SWE, ARG, EIR, HOL, FIN,	SLV, IVR, GHA, ROM, GER, GRE, WHT, SAU,	FRA, WHT, JAP, URU, BRA, NIG, MEX, WHT,	ICE, WHT, WHT, BOL, GRM,
// old actua	USA, RUS, SPN, BUL, BEL, DEN, NIR, TUN,	WHT, SWZ, WHT, SKR, ITA, MOR, ENG, SCO,	WAL, EGY, COL, SWE, ARG, WHT, HOL, FIN,	SLV, IVR, GHA, ROM, GER, GRE, NOR, SAU,	FRA, POL, JAP, URU, BRA, WHT, WHT, CZE,	ICE, POR, CHI, BOL, GRM,
// old actua	USA, RUS, SPN, BUL, BEL, DEN, NIR, TUN,	ZAM, SWZ, CAM, SKR, ITA, MOR, ENG, SCO,	WAL, EGY, BLU, BLU, ARG, EIR, HOL, FIN,	SLV, IVR, GHA, BLU, GER, GRE, NOR, SAU,	FRA, POL, JAP, URU, BLU, NIG, MEX, CZE,	ICE, POR, CHI, BOL, GRM,
// old actua			};
// old actua


redefine_info	redefine_data[]={
		{
	150, 350,
		},
		{
	470, 350,
		},
		{
	150, 370,
		},
		{
	470, 370,
		},
		{
	150, 390,
		},
		{
	470, 390,
		},
				};



// old actuashort	LegalKEY[]={
// old actua
// old actua//	 0   1   2   3   4   5   6   7   8   9   A   B   C   D   E   F
// old actua
// old actua	-1, -1, -1, -1, -1, -1, -1, -1,	-1, -1, -1, -1, -1, -1,  0, -1, 
// old actua	 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  
// old actua	 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  
// old actua	 0,  0,  0,  0,  0,  0,  0, -1,  0,  0, -1, -1, -1, -1, -1, -1,
// old actua	-1, -1, -1, -1, -1, -1, -1,  0, -1,  0,  0, -1, -1, -1,  0,  0,  
// old actua	-1,  0,  0,  0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
// old actua
// old actua	-1, -1, -1, -1, -1, -1, -1, -1,	-1, -1, -1, -1, -1, -1, -1, -1, 
// old actua	-1, -1, -1, -1, -1, -1, -1, -1,	-1, -1, -1, -1, -1, -1, -1, -1, 
// old actua	-1, -1, -1, -1, -1, -1, -1, -1,	-1, -1, -1, -1, -1, -1, -1, -1, 
// old actua	-1, -1, -1, -1, -1, -1, -1, -1,	-1, -1, -1, -1, -1, -1, -1, -1, 
// old actua	-1, -1, -1, -1, -1, -1, -1, -1,	-1, -1, -1, -1, -1, -1, -1, -1, 
// old actua	-1, -1, -1, -1, -1, -1, -1, -1,	-1, -1, -1, -1, -1, -1, -1, -1, 
// old actua	-1, -1, -1, -1, -1, -1, -1, -1,	 0, -1, -1,  0, -1,  0, -1, -1, 
// old actua	 0, -1, -1, -1, -1, -1, -1, -1,	-1, -1, -1, -1, -1, -1, -1, -1, 
// old actua	-1, -1, -1, -1, -1, -1, -1, -1,	-1, -1, -1, -1, -1, -1, -1, -1, 
// old actua	-1, -1, -1, -1, -1, -1, -1, -1,	-1, -1, -1, -1, -1, -1, -1, -1, 
// old actua		};
// old actua
// old actuachar    *KEYtext[]={
// old actua
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"Backspace",
// old actua	"NA",
// old actua
// old actua	"Q",
// old actua	"W",
// old actua	"E",
// old actua	"R",
// old actua	"T",
// old actua	"Y",
// old actua	"U",
// old actua	"I",
// old actua	"O",
// old actua	"P",
// old actua	"LFT Bracket",
// old actua	"RHT Bracket",
// old actua	"Enter",
// old actua	"Left Ctrl",
// old actua	"A",
// old actua	"S",
// old actua
// old actua	"D",
// old actua	"F",
// old actua	"G",
// old actua	"H",
// old actua	"J",
// old actua	"K",
// old actua	"L",
// old actua	";",
// old actua	"'",
// old actua	"`",
// old actua	"Left Shift",
// old actua	"#",
// old actua	"Z",
// old actua	"X",
// old actua	"C",
// old actua	"V",
// old actua
// old actua	"B",
// old actua	"N",
// old actua	"M",
// old actua	",",
// old actua	".",
// old actua	"/",
// old actua	"Right Shift",
// old actua	"NA",
// old actua	"Left Alt",
// old actua	"Space",
// old actua	"Caps Lock",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"Keypad 7",
// old actua	"NA",
// old actua	"Keypad 9",
// old actua	"Keypad -",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"Keypad +",
// old actua	"Keypad 1",
// old actua
// old actua	"NA",
// old actua	"Keypad 3",
// old actua	"Keypad 0",
// old actua	"Keypad .",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua
// old actua	"NA",		// 60
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua
// old actua	"NA",	   	// 70
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua
// old actua	"NA",		// 80
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua
// old actua	"NA",		// 90
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua
// old actua	"NA",		// a0
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua
// old actua	"NA",		// b0
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua
// old actua	"NA",		// c0
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"Up Arrow",
// old actua	"NA",
// old actua	"NA",
// old actua	"Left Arrow",
// old actua	"NA",
// old actua	"Right Arrow",
// old actua	"NA",
// old actua	"NA",
// old actua
// old actua	"Down Arrow",	// d0
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua
// old actua	"NA",		// e0
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua
// old actua	"NA",		// f0
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	"NA",
// old actua	};
// old actua
// old actua	int	copykeys[12]={
// old actua		0,0,0,0,0,0,0,0,0,0,0,0};
// old actua


// old actuachar	CodeWheelNumbers[]={
// old actua	37,  5, 54, 45, 15,		// a
// old actua	49,  8, 40, 59, 21,		// p
// old actua	20, 78, 74,  9, 58,		// o
// old actua	57, 48, 30, 75, 39,		// n
// old actua	73,  7, 65, 19, 76,		// m
// old actua	 2, 77, 56, 29, 10,		// l
// old actua	67, 18, 47, 55, 38,		// k
// old actua	79, 60, 28, 50, 31,		// j
// old actua	17, 68, 46, 11, 22,		// i
// old actua	33, 13, 61, 41, 66,		// h
// old actua	80, 23, 69,  1, 32,		// g
// old actua	34, 45, 62, 42, 51,		// f
// old actua	 4, 63, 16, 12, 70,		// e
// old actua	52, 25, 35, 72, 24,		// d
// old actua	64, 36, 44,  6,  3,		// c
// old actua	14, 71, 26, 53, 27,		// b
// old actua
// old actua	37,  5, 54, 45, 15,		// a
// old actua	49,  8, 40, 59, 21,		// p
// old actua	20, 78, 74,  9, 58,		// o
// old actua	57, 48, 30, 75, 39,		// n
// old actua	73,  7, 65, 19, 76,		// m
// old actua	 2, 77, 56, 29, 10,		// l
// old actua	67, 18, 47, 55, 38,		// k
// old actua	79, 60, 28, 50, 31,		// j
// old actua	17, 68, 46, 11, 22,		// i
// old actua	33, 13, 61, 41, 66,		// h
// old actua	80, 23, 69,  1, 32,		// g
// old actua	34, 45, 62, 42, 51,		// f
// old actua	 4, 63, 16, 12, 70,		// e
// old actua	52, 25, 35, 72, 24,		// d
// old actua	64, 36, 44,  6,  3,		// c
// old actua	14, 71, 26, 53, 27,		// b
// old actua
// old actua	37,  5, 54, 45, 15,		// a
// old actua	49,  8, 40, 59, 21,		// p
// old actua	20, 78, 74,  9, 58,		// o
// old actua	57, 48, 30, 75, 39,		// n
// old actua	73,  7, 65, 19, 76,		// m
// old actua	 2, 77, 56, 29, 10,		// l
// old actua	67, 18, 47, 55, 38,		// k
// old actua	79, 60, 28, 50, 31,		// j
// old actua	17, 68, 46, 11, 22,		// i
// old actua	33, 13, 61, 41, 66,		// h
// old actua	80, 23, 69,  1, 32,		// g
// old actua	34, 45, 62, 42, 51,		// f
// old actua	 4, 63, 16, 12, 70,		// e
// old actua	52, 25, 35, 72, 24,		// d
// old actua	64, 36, 44,  6,  3,		// c
// old actua	14, 71, 26, 53, 27,		// b
// old actua
// old actua	37,  5, 54, 45, 15,		// a
// old actua	49,  8, 40, 59, 21,		// p
// old actua	20, 78, 74,  9, 58,		// o
// old actua	57, 48, 30, 75, 39,		// n
// old actua	73,  7, 65, 19, 76,		// m
// old actua	 2, 77, 56, 29, 10,		// l
// old actua	67, 18, 47, 55, 38,		// k
// old actua	79, 60, 28, 50, 31,		// j
// old actua	17, 68, 46, 11, 22,		// i
// old actua	33, 13, 61, 41, 66,		// h
// old actua	80, 23, 69,  1, 32,		// g
// old actua	34, 45, 62, 42, 51,		// f
// old actua	 4, 63, 16, 12, 70,		// e
// old actua	52, 25, 35, 72, 24,		// d
// old actua	64, 36, 44,  6,  3,		// c
// old actua	14, 71, 26, 53, 27,		// b
// old actua
// old actua	37,  5, 54, 45, 15,		// a
// old actua	49,  8, 40, 59, 21,		// p
// old actua	20, 78, 74,  9, 58,		// o
// old actua	57, 48, 30, 75, 39,		// n
// old actua	73,  7, 65, 19, 76,		// m
// old actua	 2, 77, 56, 29, 10,		// l
// old actua	67, 18, 47, 55, 38,		// k
// old actua	79, 60, 28, 50, 31,		// j
// old actua	17, 68, 46, 11, 22,		// i
// old actua	33, 13, 61, 41, 66,		// h
// old actua	80, 23, 69,  1, 32,		// g
// old actua	34, 45, 62, 42, 51,		// f
// old actua	 4, 63, 16, 12, 70,		// e
// old actua	52, 25, 35, 72, 24,		// d
// old actua	64, 36, 44,  6,  3,		// c
// old actua	14, 71, 26, 53, 27,		// b
// old actua
// old actua	37,  5, 54, 45, 15,		// a
// old actua	49,  8, 40, 59, 21,		// p
// old actua	20, 78, 74,  9, 58,		// o
// old actua	57, 48, 30, 75, 39,		// n
// old actua	73,  7, 65, 19, 76,		// m
// old actua	 2, 77, 56, 29, 10,		// l
// old actua	67, 18, 47, 55, 38,		// k
// old actua	79, 60, 28, 50, 31,		// j
// old actua	17, 68, 46, 11, 22,		// i
// old actua	33, 13, 61, 41, 66,		// h
// old actua	80, 23, 69,  1, 32,		// g
// old actua	34, 45, 62, 42, 51,		// f
// old actua	 4, 63, 16, 12, 70,		// e
// old actua	52, 25, 35, 72, 24,		// d
// old actua	64, 36, 44,  6,  3,		// c
// old actua	14, 71, 26, 53, 27,		// b
// old actua
// old actua	37,  5, 54, 45, 15,		// a
// old actua	49,  8, 40, 59, 21,		// p
// old actua	20, 78, 74,  9, 58,		// o
// old actua	57, 48, 30, 75, 39,		// n
// old actua	73,  7, 65, 19, 76,		// m
// old actua	 2, 77, 56, 29, 10,		// l
// old actua	67, 18, 47, 55, 38,		// k
// old actua	79, 60, 28, 50, 31,		// j
// old actua	17, 68, 46, 11, 22,		// i
// old actua	33, 13, 61, 41, 66,		// h
// old actua	80, 23, 69,  1, 32,		// g
// old actua	34, 45, 62, 42, 51,		// f
// old actua	 4, 63, 16, 12, 70,		// e
// old actua	52, 25, 35, 72, 24,		// d
// old actua	64, 36, 44,  6,  3,		// c
// old actua	14, 71, 26, 53, 27,		// b
// old actua
// old actua	37,  5, 54, 45, 15,		// a
// old actua	49,  8, 40, 59, 21,		// p
// old actua	20, 78, 74,  9, 58,		// o
// old actua	57, 48, 30, 75, 39,		// n
// old actua	73,  7, 65, 19, 76,		// m
// old actua	 2, 77, 56, 29, 10,		// l
// old actua	67, 18, 47, 55, 38,		// k
// old actua	79, 60, 28, 50, 31,		// j
// old actua	17, 68, 46, 11, 22,		// i
// old actua	33, 13, 61, 41, 66,		// h
// old actua	80, 23, 69,  1, 32,		// g
// old actua	34, 45, 62, 42, 51,		// f
// old actua	 4, 63, 16, 12, 70,		// e
// old actua	52, 25, 35, 72, 24,		// d
// old actua	64, 36, 44,  6,  3,		// c
// old actua	14, 71, 26, 53, 27,		// b
// old actua		     };
// old actua
// old actua#define		A	0
// old actua#define		B	1
// old actua#define		C	2
// old actua#define		D	3
// old actua#define		E	4
// old actua#define		F	5
// old actua#define		G	6
// old actua#define		H	7
// old actua#define		I	8
// old actua#define		J	9
// old actua#define		K	10
// old actua#define		L	11
// old actua#define		M	12
// old actua#define		N	13
// old actua#define		O	14
// old actua#define		P	15
// old actua
// old actuachar	CodeWheelWindows[]={
// old actua	A, A, B, B, C, C, D, E,
// old actua	E, F, F, F, G, H, H, H,
// old actua	I, I, J, J, J, K, K, K, 
// old actua	L, M, M, M, N, N, O, O,
// old actua	P, P, 
// old actua	A, A, B, B, C, C, D, E,
// old actua	E, F, F, F, G, H, H, H,
// old actua	I, I, J, J, J, K, K, K, 
// old actua	L, M, M, M, N, N, O, O,
// old actua	P, P, 
// old actua	A, A, B, B, C, C, D, E,
// old actua	E, F, F, F, G, H, H, H,
// old actua	I, I, J, J, J, K, K, K, 
// old actua	L, M, M, M, N, N, O, O,
// old actua	P, P, 
// old actua	A, A, B, B, C, C, D, E,
// old actua	E, F, F, F, G, H, H, H,
// old actua	I, I, J, J, J, K, K, K, 
// old actua	L, M, M, M, N, N, O, O,
// old actua	P, P, 
// old actua	A, A, B, B, C, C, D, E,
// old actua	E, F, F, F, G, H, H, H,
// old actua	I, I, J, J, J, K, K, K, 
// old actua	L, M, M, M, N, N, O, O,
// old actua	P, P, 
// old actua	A, A, B, B, C, C, D, E,
// old actua	E, F, F, F, G, H, H, H,
// old actua	I, I, J, J, J, K, K, K, 
// old actua	L, M, M, M, N, N, O, O,
// old actua	P, P, 
// old actua	A, A, B, B, C, C, D, E,
// old actua	E, F, F, F, G, H, H, H,
// old actua	I, I, J, J, J, K, K, K, 
// old actua	L, M, M, M, N, N, O, O,
// old actua	P, P, 
// old actua	A, A, B, B, C, C, D, E,
// old actua	E, F, F, F, G, H, H, H,
// old actua	I, I, J, J, J, K, K, K, 
// old actua	L, M, M, M, N, N, O, O,
// old actua	P, P, 
// old actua		     };
// old actua
// old actua
// old actua
// old actua	char	CodeWheelWindowsOffs[]={
// old actua		1, 4, 0, 2, 1, 3, 2, 0,
// old actua		4, 0, 2, 3, 1, 0, 3, 4,
// old actua		0, 2, 1, 2, 4, 0, 1, 3,
// old actua		0, 1, 2, 4, 0, 2, 1, 3, 
// old actua		0, 2, 
// old actua		1, 4, 0, 2, 1, 3, 2, 0,
// old actua		4, 0, 2, 3, 1, 0, 3, 4,
// old actua		0, 2, 1, 2, 4, 0, 1, 3,
// old actua		0, 1, 2, 4, 0, 2, 1, 3, 
// old actua		0, 2, 
// old actua		1, 4, 0, 2, 1, 3, 2, 0,
// old actua		4, 0, 2, 3, 1, 0, 3, 4,
// old actua		0, 2, 1, 2, 4, 0, 1, 3,
// old actua		0, 1, 2, 4, 0, 2, 1, 3, 
// old actua		0, 2, 
// old actua		1, 4, 0, 2, 1, 3, 2, 0,
// old actua		4, 0, 2, 3, 1, 0, 3, 4,
// old actua		0, 2, 1, 2, 4, 0, 1, 3,
// old actua		0, 1, 2, 4, 0, 2, 1, 3, 
// old actua		0, 2, 
// old actua		1, 4, 0, 2, 1, 3, 2, 0,
// old actua		4, 0, 2, 3, 1, 0, 3, 4,
// old actua		0, 2, 1, 2, 4, 0, 1, 3,
// old actua		0, 1, 2, 4, 0, 2, 1, 3, 
// old actua		0, 2, 
// old actua		1, 4, 0, 2, 1, 3, 2, 0,
// old actua		4, 0, 2, 3, 1, 0, 3, 4,
// old actua		0, 2, 1, 2, 4, 0, 1, 3,
// old actua		0, 1, 2, 4, 0, 2, 1, 3, 
// old actua		0, 2, 
// old actua		1, 4, 0, 2, 1, 3, 2, 0,
// old actua		4, 0, 2, 3, 1, 0, 3, 4,
// old actua		0, 2, 1, 2, 4, 0, 1, 3,
// old actua		0, 1, 2, 4, 0, 2, 1, 3, 
// old actua		0, 2, 
// old actua		1, 4, 0, 2, 1, 3, 2, 0,
// old actua		4, 0, 2, 3, 1, 0, 3, 4,
// old actua		0, 2, 1, 2, 4, 0, 1, 3,
// old actua		0, 1, 2, 4, 0, 2, 1, 3, 
// old actua		0, 2, 
// old actua			     };
// old actua	
int	GDVvidmode[2]={
	0x0110,
	-1,	  };
	
int	MENUvidmode[2]={
	0x0101,
	-1,	  };
int	RESTOREvidmode[2]={
	0x0003,
	-1,	  };
	

// old actua	char	*FrenchCountryNames[]={
// old actua	
// old actua		"U.S.A.",
// old actua		"Russie",
// old actua		"Espagne",
// old actua		"Bulgarie",
// old actua		"Belgique",
// old actua		"Denemark",
// old actua		"Nord Irlande",
// old actua		"Tunisie",
// old actua		"Zambie",
// old actua		"Suisse",
// old actua		"Cameroun",
// old actua		"Sud Coree",
// old actua		"Italie",
// old actua		"Maroc",
// old actua		"Angleterre",
// old actua		"Ecosse",
// old actua		"Pays de Galles",
// old actua		"Egypte",
// old actua		"Colombia",
// old actua		"Suede",
// old actua		"Argentine",
// old actua		"Irlande",
// old actua		"Hollande",
// old actua		"Finlande",
// old actua		"Slovaque",
// old actua		"Cote d'Ivoire",
// old actua		"Ghana",
// old actua		"Roumanie",
// old actua		"Allemagne",
// old actua		"Grece",
// old actua		"Norvege",
// old actua		"Arabie Saoudite",
// old actua		"France",
// old actua		"Pologne",
// old actua		"Japon",
// old actua		"Uruguay",
// old actua		"Bresil",
// old actua		"Nigeria",
// old actua		"Mexique",
// old actua		"Tchecoslovaquie",
// old actua		"Islande",
// old actua		"Portugal",
// old actua		"Chine",
// old actua		"Bolivia",
// old actua		"Gremlin Showbiz XI",
// old actua		};
// old actua	
// old actua	char	*FrenchNickNames[]={
// old actua	
// old actua		"U.S.A.",
// old actua		"Russie",
// old actua		"Espagne",
// old actua		"Bulgarie",
// old actua		"Belgique",
// old actua		"Denemark",
// old actua		"N. Irlande",
// old actua		"Tunisie",
// old actua		"Zambie",
// old actua		"Suisse",
// old actua		"Cameroun",
// old actua		"Sud Coree",
// old actua		"Italie",
// old actua		"Maroc",
// old actua		"Angleterre",
// old actua		"Ecosse",
// old actua		"P. Galles",
// old actua		"Egypte",
// old actua		"Colombia",
// old actua		"Suede",
// old actua		"Argentine",
// old actua		"Irlande",
// old actua		"Hollande",
// old actua		"Finlande",
// old actua		"Slovaque",
// old actua		"C. d'Ivoire",
// old actua		"Ghana",
// old actua		"Roumanie",
// old actua		"Allemagne",
// old actua		"Grece",
// old actua		"Norvege",
// old actua		"Arabie S.",
// old actua		"France",
// old actua		"Pologne",
// old actua		"Japon",
// old actua		"Uruguay",
// old actua		"Bresil",
// old actua		"Nigeria",
// old actua		"Mexique",
// old actua		"Tchecoslov.",
// old actua		"Islande",
// old actua		"Portugal",
// old actua		"Chine",
// old actua		"Bolivia",
// old actua		"Gremlin Showbiz XI",
// old actua		};
// old actua	
// old actua	char	*GermanTeamNames[]={
// old actua	
// old actua		"Berti Logts",
// old actua		"A. Koppke",	
// old actua		"M. Bubbel",	
// old actua		"C. Neringer",	
// old actua		"T. Hellner",	
// old actua		"L. Matthaeuser",	
// old actua		"H. Herluch",
// old actua		"T. Heffler",	
// old actua		"A. Mueller",	
// old actua		"K-H. Reudle",	
// old actua		"J. Klinkmanns",
// old actua		"M. Sommer",	
// old actua		"O. Kuhn",	
// old actua		"T. Heinrichs",	
// old actua		"M. Freunths",	
// old actua		"U. Karsten",	
// old actua		"D. Eiling",	
// old actua		"C. Ziega",	
// old actua		"M. Schull",	
// old actua		"T. Stranz",	
// old actua		"M. Baller",	
// old actua		"S. Kantz",	
// old actua		"U. Habsch",	
// old actua		};
// old actua			
// old actua	char	*GermanCountryNames[]={
// old actua		"U.S.A.",		 
// old actua		"Russland", 		
// old actua		"Spanien",		
// old actua		"Bulgarien",		
// old actua		"Belgien",	 	
// old actua		"Daenemark",		  
// old actua		"Nord-Irland", 		
// old actua		"Tunesien",	 	
// old actua		"Sambia",  		
// old actua		"Schweiz",		
// old actua		"Kamerun",   		
// old actua		"Korea",		
// old actua		"Italien",	 	
// old actua		"Marokko",		
// old actua		"England",  	    	
// old actua		"Schottland",  		
// old actua		"Wales",     	      	
// old actua		"Aegypten",		     
// old actua		"Kolumbien",		   
// old actua		"Schweden", 		
// old actua		"Argentinien",		
// old actua		"Irland",		
// old actua		"Holland",	   	
// old actua		"Finnland", 		
// old actua		"Slowakei",  		
// old actua		"Elfenbeinkueste",	 
// old actua		"Ghana", 		
// old actua		"Rumaenien", 		
// old actua		"Deutschland",  	
// old actua		"Griechenland",    	
// old actua		"Norwegen",    		
// old actua		"Saudi Arabien",	
// old actua		"Frankreich",      	
// old actua		"Polen",		
// old actua		"Japan",		   
// old actua		"Uruguay", 		
// old actua		"Brasilien",   		
// old actua		"Nigera", 		
// old actua		"Mexiko",		 
// old actua		"Tschechien",		
// old actua		"Island", 		
// old actua		"Portugal",  		
// old actua		"China",		   
// old actua		"Bolivien",		 
// old actua		"SAT.1 Dream Team", 							
// old actua		};
// old actua	
// old actua	char	*GermanNickNames[]={
// old actua		"U.S.A.",		 
// old actua		"Russland", 		
// old actua		"Spanien",		
// old actua		"Bulgarien",		
// old actua		"Belgien",	 	
// old actua		"Daenemark",		  
// old actua		"Nord-Irland", 		
// old actua		"Tunesien",	 	
// old actua		"Sambia",  		
// old actua		"Schweiz",		
// old actua		"Kamerun",   		
// old actua		"Korea",		
// old actua		"Italien",	 	
// old actua		"Marokko",		
// old actua		"England",  	    	
// old actua		"Schottland",  		
// old actua		"Wales",     	      	
// old actua		"Aegypten",		     
// old actua		"Kolumbien",		   
// old actua		"Schweden", 		
// old actua		"Argentinien",		
// old actua		"Irland",		
// old actua		"Holland",	   	
// old actua		"Finnland", 		
// old actua		"Slowakei",  		
// old actua		"Elfenbeink.",	 
// old actua		"Ghana", 		
// old actua		"Rumaenien", 		
// old actua		"Deutschland",  	
// old actua		"Griechen.",    	
// old actua		"Norwegen",    		
// old actua		"S. Arabien",	
// old actua		"Frankreich",      	
// old actua		"Polen",		
// old actua		"Japan",		   
// old actua		"Uruguay", 		
// old actua		"Brasilien",   		
// old actua		"Nigera", 		
// old actua		"Mexiko",		 
// old actua		"Tschechien",		
// old actua		"Island", 		
// old actua		"Portugal",  		
// old actua		"China",		   
// old actua		"Bolivien",		 
// old actua		"SAT.1", 							
// old actua		};
// old actua	
// old actua	char	*NorwegianCountryNames[]={
// old actua	
// old actua		"U.S.A.",
// old actua		"Russland",
// old actua		"Spanian",
// old actua		"Bulgaria",
// old actua		"Belgia",
// old actua		"Danmark",
// old actua		"Nord-Irland",
// old actua		"Tunis",
// old actua		"Zambia",
// old actua		"Sveits",
// old actua		"Kamerun",
// old actua		"Syd-Korea",
// old actua		"Italia",
// old actua		"Marokko",
// old actua		"England",
// old actua		"Skotland",
// old actua		"Wales",
// old actua		"Egypt",
// old actua		"Columbia",	
// old actua		"Sverige",
// old actua		"Argentina",
// old actua		"Irland",
// old actua		"Nederland",
// old actua		"Finland",
// old actua		"Slovakia",
// old actua		"Elfenbenkysten",
// old actua		"Ghana",
// old actua		"Romania",
// old actua		"Tyskland",
// old actua		"Hallas",
// old actua		"Norge",
// old actua		"Saudi Arabia",
// old actua		"Frankrike",
// old actua		"Polen",
// old actua		"Japan",
// old actua		"Uruguay",
// old actua		"Brasil",
// old actua		"Nigeria",
// old actua		"Mexico",
// old actua		"Tsjekkia",
// old actua		"Island",
// old actua		"Portugal",
// old actua		"Kina",
// old actua		"Bolivia",
// old actua		"Gremlin Showbiz XI",
// old actua		};
// old actua	
// old actua	char	*NorwegianNickNames[]={
// old actua	
// old actua		"U.S.A.",
// old actua		"Russland",
// old actua		"Spanian",
// old actua		"Bulgaria",
// old actua		"Belgia",
// old actua		"Danmark",
// old actua		"N. Irland",
// old actua		"Tunis",
// old actua		"Zambia",
// old actua		"Sveits",
// old actua		"Kamerun",
// old actua		"S. Korea",
// old actua		"Italia",
// old actua		"Marokko",
// old actua		"England",
// old actua		"Skotland",
// old actua		"Wales",
// old actua		"Egypt",
// old actua		"Columbia",	
// old actua		"Sverige",
// old actua		"Argentina",
// old actua		"Irland",
// old actua		"Nederland",
// old actua		"Finland",
// old actua		"Slovakia",
// old actua		"Elfenbenk.",
// old actua		"Ghana",
// old actua		"Romania",
// old actua		"Tyskland",
// old actua		"Hallas",
// old actua		"Norge",
// old actua		"S. Arabia",
// old actua		"Frankrike",
// old actua		"Polen",
// old actua		"Japan",
// old actua		"Uruguay",
// old actua		"Brasil",
// old actua		"Nigeria",
// old actua		"Mexico",
// old actua		"Tsjekkia",
// old actua		"Island",
// old actua		"Portugal",
// old actua		"Kina",
// old actua		"Bolivia",
// old actua		"Gremlin XI",
// old actua		};
// old actua	
// old actua	german_manual	manual[50]={
// old actua		{"6",       "3",       "1",       "SOUND",},
// old actua		{"6",       "7",       "2",       "PUNKT",},
// old actua		{"6",       "9",       "5",       "BILDSCHIRM",},
// old actua		{"7",       "2",       "7",       "ZEIT",},
// old actua		{"7",       "9",       "1",       "TEAMAUSWAHL",},
// old actua		{"7",       "11",      "3",       "TEAM",},
// old actua		{"8",       "2",       "5",       "COMPUTER",},
// old actua		{"8",       "5",       "1",       "MAUSTASTE",},
// old actua		{"8",       "12",      "4",       "SPIELER",},
// old actua		{"9",       "1",       "3",       "FORMATION",},
// old actua		{"9",       "6",       "2",       "EINSTELLUNGEN",},
// old actua		{"9",       "9",       "3",       "SPIELES",},
// old actua		{"10",      "1",       "13",      "BUTTON",},
// old actua		{"10",      "4",       "1",       "MANNSCHAFTEN",},
// old actua		{"10",      "7",       "3",       "LIGA",},
// old actua		{"11",      "2",       "5",       "SAISON",},
// old actua		{"11",      "4",       "2",       "SIMULATIONSMODUS",},
// old actua		{"11",      "8",       "1",       "POKAL",},
// old actua		{"12",      "3",       "3",       "NAMEN",},
// old actua		{"12",      "5",       "5",       "TEAMAUSWAHL",},
// old actua		{"12",      "10",      "4",       "SIEGER",},
// old actua		{"13",      "1",       "1",       "NETZWERKSPIEL",},
// old actua		{"13",      "2",       "3",       "FUNKTION",},
// old actua		{"13",      "7",       "3",       "NETZ",},
// old actua		{"14",      "1",       "4",       "FALLE",},
// old actua		{"14",      "4",       "7",       "AUFSTELLUNG",},
// old actua		{"14",      "5",       "7",       "SEITE",},
// old actua		{"15",      "4",       "5",       "STEUERUNG",},
// old actua		{"15",      "6",       "1",       "SPIELART",},
// old actua		{"15",      "7",       "1",       "ARCADE",},
// old actua		{"16",      "1",       "1",       "UMGEBUNG",},
// old actua		{"16",      "7",       "4",       "STATUS",},
// old actua		{"17",      "1",       "2",       "KAMERAWINKEL",},
// old actua		{"17",      "1",       "5",       "RANSOCCER",},
// old actua		{"17",      "2",       "3",       "REGISSEUR",},
// old actua		{"19",      "7",       "1",       "FLUGWEITE",},
// old actua		{"19",      "7",       "3",       "BALLES",},
// old actua		{"19",      "12",      "1",       "CHANCEN",},
// old actua		{"23",      "2",       "6",       "ABWEHR",},
// old actua		{"23",      "4",       "1",       "ANGREIFERS",},
// old actua		{"23",      "7",       "3",       "HILFE",},
// old actua		{"26",      "1",       "1",       "ELFMETER",},
// old actua		{"26",      "3",       "1",       "RICHTUNG",},
// old actua		{"26",      "6",       "3",       "SCHIEDSRICHTER",},
// old actua		{"28",      "1",       "1",       "AUFSTELLUNG",},
// old actua		{"28",      "1",       "9",       "FORMATION",},
// old actua		{"28",      "4",       "4",       "SPIELERNUMMER",},
// old actua		{"30",      "1",       "3",       "TASTE",},
// old actua		{"30",      "1",       "11",      "AUGEN",},
// old actua		{"30",      "2",       "6",       "ZAHLENFELD",},
// old actua				    	 
// old actua		};

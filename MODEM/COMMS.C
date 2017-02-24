#include <time.h>
#include <string.h>
#include <stdio.h>
#include <bios.h>
#include <stdlib.h>
#include <fcntl.h>


#include "3d.h"
#include "frontend.h"
#include "func2.h"
#include "func3.h"
#include "sound.h"
#include "network.h"
#include "c:\netnow\hmistd.h"
#include "c:\netnow\netnow.h"
#include "gsscomms.h"
#include "comms.h"

int	serial_port=2;
int	modem_port=2;
int	no_16550=0;							//set to message number when no 16550 found!
extern	unsigned char *scrbuf;
extern	char	*front_vga[16];
extern	int	head_x;
extern	int	head_y;
extern	volatile	int	game_type;
extern	char	language_buffer[][64];
extern	char	config_buffer[][64];
extern	char	font1_ascii[256];
extern	int	font1_offsets[];
extern	unsigned char *screen;	/*pointer to screen */
extern	volatile	int	frames;
extern	unsigned char	keys[140];						// entries get set to one when key is hit.
extern	int	soundon,musicon;
extern	int	MusicCD;


typedef	struct	
	{
	char	name[51];
	int	inittype;
	}	modeminfo;


typedef	struct
	{
	char	initstring[51];
	}	initinfo;

modeminfo	*modembuffer;
initinfo		*modembuffer2;
int	current_modem=0;
int	modems;
int	modemstrs;


int	select_comport(int type)
	{
	//serial link/modem select com port.
	int	done=FALS;
	int	key;
	int	serials;

//	outp(0x20,0xc0+3-1);				//irq 3= COM 2, irq 4 = COM 1 !!!


	serials=(_bios_equiplist()>>9) & 7;
	if (serials<2) serials=2;				//force at least 2 serial ports!

	if (serials<serial_port) serial_port=2;
	check16550(serial_port);

	while (!done)
		{
		display_picture(scrbuf,front_vga[0]);
		display_block(scrbuf,front_vga[1],3,head_x,head_y,0);
		display_block(scrbuf,front_vga[6],0,36,2,0);
		display_block(scrbuf,front_vga[5],type,-4,247,0);
		display_block(scrbuf,front_vga[5],game_type+5,135,247,0);
		display_block(scrbuf,front_vga[4],4,76,257,-1);
		display_block(scrbuf,front_vga[6],4,62,336,-1);

		scale_text(front_vga[15],&language_buffer[83][0],font1_ascii,font1_offsets,400,75,white,CENTRE_ALIGN,200,640);
		scale_text(front_vga[15],&language_buffer[47][0],font1_ascii,font1_offsets,400,93,white,CENTRE_ALIGN,200,640);


		scale_text(front_vga[15],"COM 1",font1_ascii,font1_offsets,400,135,serial_port==1?orange:white,CENTRE_ALIGN,200,640);
		scale_text(front_vga[15],"COM 2",font1_ascii,font1_offsets,400,153,serial_port==2?orange:white,CENTRE_ALIGN,200,640);
		if (serials>=3) scale_text(front_vga[15],"COM 3",font1_ascii,font1_offsets,400,171,serial_port==3?orange:white,CENTRE_ALIGN,200,640);
		if (serials>=4) scale_text(front_vga[15],"COM 4",font1_ascii,font1_offsets,400,189,serial_port==4?orange:white,CENTRE_ALIGN,200,640);

		if (no_16550) 
			scale_text(front_vga[15],language_buffer[109],font1_ascii,font1_offsets,400,351,red,CENTRE_ALIGN,200,640);

		copypic(scrbuf,screen);

		while (fatkbhit())
			{
			key=fatgetch();
			switch (key)
				{
				case 0:
					key=fatgetch();
					switch (key)
						{
						case 80:	//down arrow
							if (serial_port!=serials) serial_port++;
							check16550(serial_port);
							break;
						case 72:	//up arrow
							if (serial_port!=1) serial_port--;
							check16550(serial_port);
							break;
						}
					break;
				case 13:
				case 27:
					done=TRU;
					break;
				}
			}
		}
	gssCommsSetComPort(serial_port);
	if (key==13)
		return(TRU);
	else
		return(FALS);
	}


char	modem_initstring[51]="ATX";
char	modem_phone[51]="";
int	modem_tone=TRU;						//T = tone, P = pulse
int	modem_call=TRU;					//default to calling!

int		stringwidth(volatile char *c)
	{
	int	w=0;
	int	num;
	int	* off;
	w=0;
	while (*c!=0)
		{
		num=font1_ascii[*c++];
		if (num==255)
			w+=8;
		else
			{
			off=(int *) (front_vga[15]+num*12);
			w+=off[0]+1;
			}
		}		  
	return(w);
	}



int	select_modemstuff(int type)
	{
	int	x;
	int	connecting_time=0;
	int	message=-1;
	int	mode=0;									//0 = normal, 1 = type in, 2 = dialling
//	char	buffer[100];
	int	done=FALS;
	int	key;
	int	serials;
	int	option=5;
	int	len;
	float	wait_ok=0;
	float wait_hangup=0;
	char	* edstring;
	int	modem_initialised=FALS;

	if (modem_call)
		option=5;
	else
		option=6;

	loadmodemnames();
	if (current_modem>=0)	strcpy(modem_initstring,modembuffer2[modembuffer[current_modem].inittype].initstring);

	serials=(_bios_equiplist()>>9) & 7;
	if (modem_port<2) serials=2;				//force at least 2 serial ports!
	if (serials<modem_port) modem_port=2;
	check16550(modem_port);

	while (!done)
		{
		display_essentials(type,option,mode);


		if (message==93 || message==94 || message==95 || message==96 || message==104)
			{
			if ((frames & 0x0f)<8)
				scale_text(front_vga[15],language_buffer[message],font1_ascii,font1_offsets,400,279,white,CENTRE_ALIGN,200,640);
			}
		else
			if (message>=0)	scale_text(front_vga[15],language_buffer[message],font1_ascii,font1_offsets,400,279,red,CENTRE_ALIGN,200,640);

		copypic(scrbuf,screen);
		
		if (connecting_time!=0 && frames>connecting_time+72) done=TRU;
		while (fatkbhit())
			{
			key=fatgetch();

			switch (mode)
				{
				case 0:
					//scrolling through!
					message=-1;
					switch (key)
						{
						case 0:
							key=fatgetch();
							switch (key)
								{
								case 80:	//down arrow
									if (option<6)
										{
										option++;
										}
									break;
								case 72:	//up arrow
									if (option!=0)
										{
										option--;
										}
									break;
								}
							break;
						case 13:
							switch(option)
								{
								case 0:
									select_modem(type);
									break;
								case 1:
									//change port
									modem_port++;
									if (modem_port>serials) modem_port=1;
									check16550(modem_port);
								 	break;
								case 2:
									// pulse/tone dialling
									modem_tone=!modem_tone;
									break;
								case 3:
									//init string
									mode=1;
									break;
								case 4:
									//telephone number
									mode=1;
									break;
								case 5:
								case 6:
									if (option==5)
										modem_call=TRU;
									else
										modem_call=FALS;
									mode=2;
									message=104;
									scale_text(front_vga[15],language_buffer[message],font1_ascii,font1_offsets,400,279,white,CENTRE_ALIGN,200,640);
									copypic(scrbuf,screen);

									gssCommsSetComPort(modem_port);
									Initialise_Network();
									gssModemHangUp();
									wait_hangup=clock();
									break;
								}
							break;
						case 27:
							done=TRU;
							connecting_time=0;
							message=-1;
							wait_ok=0;						//stop non-responding message coz escaped!
							wait_hangup=0;
							modem_initialised=FALS;
							break;
						}
					break;
				case 1:
					//user entry of a line
					if (option==3)
						edstring=modem_initstring;
					else
						edstring=modem_phone;
	
					len=strlen(edstring);
					switch (key)
						{
						case 0:
							key=fatgetch();
							break;
						case 8:
					 		if (len>0)
								{
								edstring[len-1]=0;
								if (option==3 && current_modem>=0)	current_modem=-current_modem-1;		//negative means custom set-up
								}
							break;
						case 13:
						case 27:
							mode=0;
							connecting_time=0;
							message=-1;
							break;
						default:
							if (keys[0x2A] || keys[0x36])
								{
								#ifndef US_Wacky_Version
									switch(key)
										{
										case '1':
											key='!';
											break;
										case '2':
											key='\"';
											break;
										case '3':
											key='œ';
											break;
										case '4':
											key='$';
											break;
										case '5':
											key='%';
											break;
										case '6':
											key='^';
											break;
										case '7':
											key='&';
											break;
										case '8':
											key='*';
											break;
										case '9':
											key='(';
											break;
										case '0':
											key=')';
											break;
										case '-':
											key='_';
											break;
										case '=':
											key='+';
											break;
										case ';':
											key=':';
											break;
										case '\'':
											key='@';
											break;
										case '#':
											key='~';
											break;
										case ',':
											key='<';
											break;
										case '.':
											key='>';
											break;
										case '/':
											key='?';
											break;
										}
								#else
									switch(key)
										{
										case '1':
											key='!';
											break;
										case '2':
											key='@';
											break;
										case '3':
											key='#';
											break;
										case '4':
											key='$';
											break;
										case '5':
											key='%';
											break;
										case '6':
											key='^';
											break;
										case '7':
											key='&';
											break;
										case '8':
											key='*';
											break;
										case '9':
											key='(';
												break;
										case '0':
											key=')';
											break;
										case '-':
											key='_';
											break;
										case '=':
											key='+';
											break;
										case ';':
											key=':';
											break;
										case '\'':
											key='\"';
											break;
										case '#':
											key='|';
											break;
										case '`':
											key='~';
											break;
										case ',':
											key='<';
											break;
										case '.':
											key='>';
											break;
										case '/':
											key='?';
											break;
										}
								#endif
								}

							if (strlen(edstring)<50 && key!=127)
								{
								edstring[len]=key;
								edstring[len+1]=0;
								if (option==3 && current_modem>=0)	current_modem=-current_modem-1;		//negative means custom set-up
								}
							break;
						}
					break;
				case 2:
					//dial/receive mode!
					switch(key)
						{
						case 0:
							key=fatgetch();
							break;
						case 27:
							mode=0;						//jump back to mode 0!
							message=-1;
							connecting_time=0;
							wait_ok=0;					//stop non-responding message!
							wait_hangup=0;
							modem_initialised=FALS;
							display_essentials(type,option,mode);
							scale_text(front_vga[15],&language_buffer[108][0],font1_ascii,				//RESETTING MODEM
								font1_offsets,400,279,white,CENTRE_ALIGN,200,640);
							copypic(scrbuf,screen);
							close_network();
							break;
//						case 32:
//							connecting_time=frames;
//							message=95;
//							break;
						}
					break;
				}
			}

		if (mode==2 && connecting_time==0)
			{
			//keep scanning for responses!
			x=gssModemCheckResponse();
			if (x>=0)
				{
				//modem sent a response!
				switch (x)
					{
//					case 0:
					case	gssOK:
						//OK to some command!
						if (wait_ok!=0)
							{
							// ok from modem - dial as necessary
							if (modem_call)	gssModemDial(modem_phone,modem_tone);
							wait_ok=0;
							if (modem_call)
								message=94;
							else
								message=93;
							modem_initialised=TRU;
							}
						if (wait_hangup!=0)
							{
							//ok from modem when waiting for hangup.
							wait_hangup=0;
							gssModemInit(modem_initstring);
				 			wait_ok=clock();							//wait for OK from modem - time out if not there
							}

						break;
//					case 1:
					case gssCONNECT:
						//connect!
						message=95;
						connecting_time=frames;
						break;
//					case 2:
					case gssRING:
						//phone is ringing - only answer if ok read first? will this work?
						if (modem_initialised && !modem_call)
							{
							gssModemAnswer();
							message=96;
							}
						break;
//					case 3:						
//					case 4:
//					case 5:
//					case 6:
//					case 7:
					case gssNOCARRIER:
					case gssERROR:
					case gssNODIALTONE:
					case gssBUSY:
					case gssNOANSWER:
						message=x+94;					//set error message up
						close_network();
						mode=0;
						break;
					}
				}
			}
		if (wait_ok!=0 && (clock()-wait_ok)/CLOCKS_PER_SEC>5)
			{
			message=105;							//modem is not responding!
			close_network();
			wait_ok=0;
			wait_hangup=0;
			modem_initialised=FALS;
			mode=0;
			}
		if (wait_hangup!=0 && (clock()-wait_hangup)/CLOCKS_PER_SEC>5)
			{
			message=105;							//modem is not responding!
			close_network();
			wait_ok=0;
			wait_hangup=0;
			modem_initialised=FALS;
			mode=0;
			}


		}
	fre((char **) &modembuffer);
	fre((char **) &modembuffer2);
	if (connecting_time)
		{
		return(TRU);
		}
	else
		{
		gssModemHangUp();
		close_network();
		return(FALS);
		}
	}

void	loadmodemnames()
	{
	FILE	*fp=NULL;
	char	buffer[512];
	char	*	delims={" ,\n\t\r"};
	char	*p;
	int	i;

	fp=fopen("MODEM.INI","r");
	fgets(buffer,512,fp);
	p=strtok(buffer,delims);

	modems=strtol(p,NULL,10);

	modembuffer=(modeminfo *) getbuffer(sizeof(modeminfo)*modems);
	if (modembuffer==NULL) modems=0;								//can't load modem names!

	for (i=0;i<modems;i++)
		{
		fgets(buffer,512,fp);
		p=strtok(buffer," ");
		modembuffer[i].inittype=strtol(p,NULL,10)-1;
		p=strtok(NULL,"\r\n");
		strcpy(modembuffer[i].name,p);
		}
	fclose(fp);




	fp=fopen("MODEMSTR.INI","r");
	fgets(buffer,512,fp);
	p=strtok(buffer,delims);

	modemstrs=strtol(p,NULL,10);

	modembuffer2=(initinfo *) getbuffer(sizeof(initinfo)*modemstrs);
	if (modembuffer2==NULL) modemstrs=0;								//can't load modem names!

	for (i=0;i<modemstrs;i++)
		{
		fgets(buffer,512,fp);
		p=strtok(buffer,"\r\n\t");
		strcpy(modembuffer2[i].initstring,p);
		}
	fclose(fp);

	if (current_modem>=modems)	current_modem=modems-1;
	if (current_modem<-modems)	current_modem=-modems;

	}

void	select_modem(int type)
	{
	int	done=FALS;
	int	new_modem=current_modem;
	int	first,last,i;
	int	key;

	if (new_modem<0) new_modem=-new_modem-1;			//covert custom set up to the first modem!
	while (!done)
		{
		display_picture(scrbuf,front_vga[0]);
		display_block(scrbuf,front_vga[1],3,head_x,head_y,0);
		display_block(scrbuf,front_vga[6],0,36,2,0);
		display_block(scrbuf,front_vga[5],type,-4,247,0);
		display_block(scrbuf,front_vga[5],game_type+5,135,247,0);
		display_block(scrbuf,front_vga[4],4,76,257,-1);
		display_block(scrbuf,front_vga[6],4,62,336,-1);

		scale_text(front_vga[15],language_buffer[106],font1_ascii,font1_offsets,400,75,white,CENTRE_ALIGN,200,640);

		first=new_modem-7;
		if (first<0) first=0;
		last=new_modem+7;
		if (last>=modems) last=modems-1;


		for (i=first;i<=last;i++)
			{
			scale_text(front_vga[15],modembuffer[i].name,font1_ascii,font1_offsets,400,237-(new_modem-i)*18,
					i==new_modem?orange:white,CENTRE_ALIGN,200,640);
			}
		copypic(scrbuf,screen);


		while (fatkbhit())
			{
			key=fatgetch();

			switch (key)
				{
				case 0:
					key=fatgetch();
					switch (key)
						{
						case 80:	//down arrow
							if (new_modem<modems-1)
								new_modem++;
							break;
						case 72:	//up arrow
							if (new_modem!=0) new_modem--;
							break;
						case 71:	//home
							new_modem=0;
							break;
						case 79:	//end
							new_modem=modems-1;
							break;
						case 73:
							new_modem-=15;
							if (new_modem<0) new_modem=0;
							break;
						case 81:
							new_modem+=15;
							if (new_modem>modems-1) new_modem=modems-1;
							break;
						}
					break;
				case 13:
					current_modem=new_modem;
					strcpy(modem_initstring,modembuffer2[modembuffer[current_modem].inittype].initstring);
					done=TRU;
					break;
				case 27:
					done=TRU;
					break;
				}
			}
		}
	}


char	* getprintstring(char * string,int	input)
	{
	//given the required string, returns a string with ... added if it doesn't fit in the display.
	int	len;
	static	char	getresult[100];

	strcpy(getresult,string);
	if (!input)
		{
		if (stringwidth(string)>240)
			{
			len=strlen(getresult);
			do
				{
				getresult[len-1]='.';
				getresult[len]='.';
				getresult[len+1]='.';
				getresult[len+2]=0;
				len--;
				 }
			while (stringwidth(getresult)>240);
			}
		}
	else
		{
		len=strlen(getresult);
		getresult[len]='_';
		getresult[len+1]=0;
		if (stringwidth(getresult)>240)
			{
			//doesn't fit - prefix with ...
			getresult[0]='.';
			getresult[1]='.';
			getresult[2]='.';
			strcpy(getresult+3,string);
			getresult[len+3]='_';
			getresult[len+4]=0;
			len++;														//length of string + underline!
			while(stringwidth(getresult)>240)
				{
				memmove(getresult+3,getresult+4,len);
				len--;
				}
			len+=3;														//length including ... prefix
			}
		else
			len++;														//length including cursor!
		if ((frames &0xf)>=8) getresult[len-1]=0;				//no cursor!
	

		}
	return(getresult);
	}


void	display_essentials(int type,int option,int mode)
	{
	char	buffer[100];

	display_picture(scrbuf,front_vga[0]);
	display_block(scrbuf,front_vga[1],3,head_x,head_y,0);
	display_block(scrbuf,front_vga[6],0,36,2,0);
	display_block(scrbuf,front_vga[5],type,-4,247,0);
	display_block(scrbuf,front_vga[5],game_type+5,135,247,0);
	display_block(scrbuf,front_vga[4],4,76,257,-1);
	display_block(scrbuf,front_vga[6],4,62,336,-1);

	scale_text(front_vga[15],language_buffer[84],font1_ascii,font1_offsets,400,75,white,CENTRE_ALIGN,200,640);

	//name
	if (modembuffer!=NULL)
		{
		if (current_modem>=0)
			scale_text(front_vga[15],modembuffer[current_modem].name,font1_ascii,font1_offsets,400,117,option==0?orange:white,CENTRE_ALIGN,200,640);
		else
			scale_text(front_vga[15],language_buffer[107],font1_ascii,font1_offsets,400,117,option==0?orange:white,CENTRE_ALIGN,200,640);	//custom
		}


	//Port
	sprintf(buffer,"COM %d",modem_port);
	scale_text(front_vga[15],language_buffer[85],font1_ascii,font1_offsets,400,135,option==1?orange:white,RIGHT_ALIGN,200,640);
	scale_text(front_vga[15],buffer,font1_ascii,font1_offsets,400,135,option==1?orange:white,LEFT_ALIGN,200,640);

	//Dial
	scale_text(front_vga[15],language_buffer[86],font1_ascii,font1_offsets,400,153,option==2?orange:white,RIGHT_ALIGN,200,640);
	if (modem_tone)
		scale_text(front_vga[15],language_buffer[87],font1_ascii,font1_offsets,400,153,option==2?orange:white,LEFT_ALIGN,200,640);
	else
		scale_text(front_vga[15],language_buffer[88],font1_ascii,font1_offsets,400,153,option==2?orange:white,LEFT_ALIGN,200,640);

	//Init string
	scale_text(front_vga[15],language_buffer[89],font1_ascii,font1_offsets,400,171,option==3?orange:white,RIGHT_ALIGN,200,640);
	scale_text(front_vga[15],getprintstring(modem_initstring,option==3 && mode==1),
				font1_ascii,font1_offsets,400,171,option==3?orange:white,LEFT_ALIGN,200,640);

	//phone
	scale_text(front_vga[15],language_buffer[90],font1_ascii,font1_offsets,400,189,option==4?orange:white,RIGHT_ALIGN,200,640);
	scale_text(front_vga[15],getprintstring(modem_phone,option==4 && mode==1),
				font1_ascii,font1_offsets,400,189,option==4?orange:white,LEFT_ALIGN,200,640);

	//call/answer

	scale_text(front_vga[15],language_buffer[91],font1_ascii,font1_offsets,400,225,option==5?orange:white,CENTRE_ALIGN,200,640);
	scale_text(front_vga[15],language_buffer[92],font1_ascii,font1_offsets,400,243,option==6?orange:white,CENTRE_ALIGN,200,640);

	if (no_16550)	scale_text(front_vga[15],language_buffer[no_16550],font1_ascii,font1_offsets,400,351,red,CENTRE_ALIGN,200,640);

	}


void	check16550(int port)
	{
	if (!gss16550(port))
		{
		//turn off the sounds here!
		if (!MusicCD)
			no_16550=109;				//sound/music
		else
			no_16550=110;				//sound only
		}
	else
		no_16550=0;

	if (no_16550==109)
		{
		musicon=FALS;
		reinitmusic();
		}
	if (no_16550)
		{
		soundon=FALS;
		}
	}

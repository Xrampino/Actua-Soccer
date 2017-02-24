#include "global.h"
#include "mouse.h"

/******************************************************************************
******************************************************************************/

#define TRUE 1
#define FALSE 0

/******************************************************************************
*****************************************************************************/

// EDITOR GLOBAL VARIABLES...

int e_button_lit=0;
int ed_zone=0;
int ed_poss=0;
int ed_last_poss=0;
int ed_last_zone=0;
int picked_up=0;
char tac_buffer[((32*2)+4)*10*2*5];

int temp_tactic[10][2];
int undo_tactic[10][2];
int ed_tactic[(32*2)+6][10][2];		//Current Tactic Buffer.
char tac_name[9]="new_tacs";

struct buttons {
	int x;
	int y;
	int w;
	char s[10];
	char l;
};

buttons ed_buttons[]={{186,12,1,"C",0},{292,12,1,"C",0},
							{186,90,1,"C",0},{292,90,1,"C",0},
							{12,120,4,"LOAD",0},{60,120,4,"SAVE",0},
							{220,98,6,"POSS ",0},{192+12,132,4,"COPY",0},
							{240+12,132,4,"SWAP",0},{192+12,156,4,"UNDO",0},
							{240+12,156,4,"INIT",0},{320-40,200-16,4,"GAME",0},
 							{108,120,4,"NAME",0},{186,42,1,"K",0},{292,42,1,"K",0}};

int max_buttons=(sizeof(ed_buttons)/sizeof(buttons));

/******************************************************************************
*****************************************************************************/

// EDITOR FUNCTIONS...

/******************************************************************************
*****************************************************************************/

float rem(float n,int d)
{
	return((n/d)-((int)n/d));
}

/******************************************************************************
*****************************************************************************/

void e_line_border(int x,int y,int wid,int hgt,int col)
{
	int c=_getcolor();
	_moveto(x,y);
	_setcolor(col);
	_lineto(x+wid-1,y);
	_lineto(x+wid-1,y+hgt-1);
	_lineto(x,y+hgt-1);
	_lineto(x,y);
	_setcolor(c);
}

/******************************************************************************
*****************************************************************************/

void draw_grid()
{
	_setcolor(4);
	float step=(160.2)/7;
	float x=8+(step/2);
	for (int i=1; i<8; i++, x+=step )
	{
		_moveto((int)x,8);
		_lineto((int)x,108);
	}
	step=100/3;
	x=8+(step/2);
	for (i=1; i<4; i++, x+=step )
	{
		_moveto(8,(int)x);
		_lineto(168,(int)x);
	}
}

/******************************************************************************
*****************************************************************************/

void draw_zones()
{
	_setcolor(7);
	float step=(84)/7;
	float x=200+(step/2);
	for (int i=1; i<8; i++, x+=step )
	{
		_moveto((int)x,24);
		_lineto((int)x,68+16);
	}
	step=60/3;
	x=24+(step/2);
	for (i=1; i<4; i++, x+=step )
	{
		_moveto(200,(int)x);
		_lineto(200+84,(int)x);
	}
	e_line_border(200,24,85,61,7);
	_moveto(216,12);
	_outgtext("ZONE 1");
}


/******************************************************************************
*****************************************************************************/

void draw_markings()
{
	_moveto(8,8);
	_setcolor(7);
	_lineto(168,8);
	_lineto(168,108);
	_lineto(8,108);
	_lineto(8,8);
// Left Goal
	_moveto(7,50-5+7);
	_lineto(4,50-5+7);
	_lineto(4,50+5+7);
	_lineto(7,50+5+7);
// Right Goal
	_moveto(161+8,50-5+7);
	_lineto(165+8,50-5+7);
	_lineto(165+8,50+5+7);
	_lineto(161+8,50+5+7);
// Left Six Yard Box
	_moveto(8,50-13+7);
	_lineto(8+8,50-13+7);
	_lineto(8+8,50+13+7);
	_lineto(8,50+13+7);
// Right Six Yard Box
	_moveto(160+8,50-13+7);
	_lineto(160-8+8,50-13+7);
	_lineto(160-8+8,50+13+7);
	_lineto(160+8,50+13+7);
// Left 18 Yard Box
	_moveto(8,50-29+7);
	_lineto(8+24,50-29+7);
	_lineto(8+24,50+29+7);
	_lineto(8,50+29+7);
// Right 18 Yard Box
	_moveto(160+8,50-29+7);
	_lineto(160+8-24,50-29+7);
	_lineto(160+8-24,50+29+7);
	_lineto(160+8,50+29+7);
// Centre circle
	_ellipse(_GBORDER,80+8-13,50+7-13,80+8+13,50+7+13);
	_setcolor(2);
	_moveto(10,54);
	_outgtext("1");
}

/******************************************************************************
*****************************************************************************/

void draw_edteam()
{
	char st[3];
	int x,y;
	int c=_getcolor();
	int p=_getplotaction();
	_setcolor(2);
	_setplotaction(_GXOR);
	for (int i=0; i<10; i++)
	{
		sprintf(st,"%d",i+2);
		x=(ed_tactic[ed_zone+((ed_zone<32*2) ? ed_poss*32:0)][i][0])/8;
		y=(ed_tactic[ed_zone+((ed_zone<32*2) ? ed_poss*32:0)][i][1])/8;
		_moveto(8+x-3,8+y-3);
		HideMouse();
		_outgtext(st);
		ShowMouse();
	}
	_setplotaction(p);
	_setcolor(c);
}

/******************************************************************************
*****************************************************************************/

void e_draw_buttons()
{
	int x,y,w;
	char st[10];
	for (int i=0; i<max_buttons; i++)
	{
		x=ed_buttons[i].x;
		y=ed_buttons[i].y;
		w=ed_buttons[i].w;
		strcpy(st,ed_buttons[i].s);
		_moveto(x,y);
		_outgtext(st);
		e_line_border(x-4,y-4,w*8+8,16,1);
	}
}

/******************************************************************************
*****************************************************************************/

void e_light_button(int b)
{
	int x,y,w,c;
	c=_getcolor();
	char st[10];
	x=ed_buttons[b].x;
	y=ed_buttons[b].y;
	w=ed_buttons[b].w;
	strcpy(st,ed_buttons[b].s);
	_setcolor(7);
	_moveto(x,y);
	HideMouse();
	_outgtext(st);
	_setcolor(c);
	ShowMouse();
	e_button_lit=b+1;
}

/******************************************************************************
*****************************************************************************/

void e_unlight_button(int b)
{
	int x,y,w;
	char st[10];
	x=ed_buttons[b].x;
	y=ed_buttons[b].y;
	w=ed_buttons[b].w;
	strcpy(st,ed_buttons[b].s);
	_moveto(x,y);
	HideMouse();
	_outgtext(st);
	ShowMouse();
	if (e_button_lit==b+1)
		e_button_lit=0;
}
/******************************************************************************
*****************************************************************************/

void e_process_butts()
{
	int x,y,w;
	for (int i=0; i<max_buttons; i++)
	{
		x=ed_buttons[i].x;
		y=ed_buttons[i].y;
		w=ed_buttons[i].w;
		if ((Mouse.x/2>=x-4) && (Mouse.x/2<=x+(w*8)+4)
			&& (Mouse.y>=y-4) && (Mouse.y<=y+12))
		{
			if (!ed_buttons[i].l)
			{
				e_light_button(i);			//Mouse will highlight button.
				ed_buttons[i].l=1;
			}
		}
		else
		{
			if (ed_buttons[i].l)
			{
				e_unlight_button(i);
				ed_buttons[i].l=0;
			}
		}
	}
}		

/******************************************************************************
*****************************************************************************/

void undo_copy()
{
	memcpy(undo_tactic,ed_tactic[ed_zone+((ed_zone<32*2) ? ed_poss*32:0)],10*2*sizeof(int));
}


/******************************************************************************
*****************************************************************************/

void reset_poss()
{
	ed_last_poss=ed_poss;
}

/******************************************************************************
*****************************************************************************/

void init_zgrid()
{
 		_setplotaction(_GXOR);
		ed_zone=0;
		undo_copy();
		_moveto(200-3,24-3);
		HideMouse();
		int c=_getcolor();
		_setcolor(7);
		_outgtext("O");
		ShowMouse();
 		_setplotaction(_GPSET);
		_setcolor(c);
}

/******************************************************************************
*****************************************************************************/

void write_name()
{
	_moveto(8,184);
	int c=_getcolor();
	int g=_getplotaction();
	_setplotaction(_GXOR);
	_setcolor(3);
	_outgtext(tac_name);
	_setcolor(c);
	_setplotaction(g);
}

/******************************************************************************
*****************************************************************************/

void input_keys(char *i,int chars)
{
	char buff[2+41];
	int n=chars;
	if (!n)
		n=8+1;		// filename.
	buff[0]=n;
	cgets(buff);
	strcpy(i,buff+2);
}

/******************************************************************************
*****************************************************************************/

void name_butt()
{
	write_name();
	_settextposition(24,2);
	_outtext("New name: ");
	input_keys(tac_name,0);		//0=filename.
	_settextposition(24,2);
	_outtext("                      ");
	write_name();
}

/******************************************************************************
*****************************************************************************/

void save_butt()
{
	write_name();
	_settextposition(24,2);
	_outtext("Are you sure(Y/N)?");
	char k;
	do
	{
		k=getch();
	} while(k!='y' && k!='n');
	if (k=='y')
	{
		_settextposition(24,2);
		_outtext("                      ");
		_settextposition(24,2);
		_outtext("Saving: ");
		char file_name[13];
		strcpy(file_name,tac_name);
		strcat(file_name,".tac");
		_outtext(file_name);
	 	FILE *fp1=fopen(file_name,"wb");
		if (fp1==0)
		{
			_settextposition(24,2);
			_outtext("Save Failed");
			delay(1200);
		}
		else
		{
			fwrite(ed_tactic,sizeof(int),((32*2)+6)*10*2,fp1);
			fclose(fp1);
			delay(600);
		}
	}
	_settextposition(24,2);
	_outtext("                      ");
	write_name();
}		

/******************************************************************************
*****************************************************************************/

void load_butt()
{
	draw_edteam();
	write_name();
	_settextposition(24,2);
	_outtext("Are you sure(Y/N)?");
	char k;
	do
	{
		k=getch();
	} while(k!='y' && k!='n');
	if (k=='y')
	{
		_settextposition(24,2);
		_outtext("                      ");
		_settextposition(24,2);
		_outtext("Loading: ");
		char file_name[13];
		strcpy(file_name,tac_name);
		strcat(file_name,".tac");
		_outtext(file_name);
	 	FILE *fp1=fopen(file_name,"rb");
		if (fp1==0)
		{
			_settextposition(24,2);
			_outtext("Load Failed");
			delay(1200);
		}
		else
		{
			fread(ed_tactic,sizeof(int),((32*2)+6)*10*2,fp1);
			fclose(fp1);
			delay(600);
		}
	}
	_settextposition(24,2);
	_outtext("                      ");
	write_name();
	draw_edteam();
}		

/******************************************************************************
*****************************************************************************/

void get_zx_zy(int *zx,int *zy)
{
		switch(ed_zone)
		{
			case 32+32:
			{		  		// top left corner.
				*zx=1;
				*zy=-9;
				break;
			}

			case 32+33:
			{		  		// top right corner.
				*zx=84;
				*zy=-9;
				break;
			}

			case 32+34:
			{		  		// bot left corner.
				*zx=1;
				*zy=70-1;
				break;
			}

			case 32+35:
			{		  		// bot right corner.
				*zx=84;
				*zy=70-1;
				break;
			}

			case 32+36:
			{		  		// home centre.
				*zx=-11;
				*zy=35;
				break;
			}

			case 32+37:
			{		  		// away centre.
				*zx=95;
				*zy=35;
				break;
			}


			default:
			{
				*zy=(ed_zone/8)*20;
				*zx=rem(ed_zone,8)*12*8;
			}
		}
}
	
/******************************************************************************
*****************************************************************************/

void zone_grid()
{
	int c=_getcolor();
	_setcolor(7);
	int x=(Mouse.x/2)-200;
	int y=(Mouse.y-24);
	x=((x+6)/12);
	y=((y+10)/20);
	int zone=x+(y*8);
	if (zone!=ed_zone)
	{
		reset_poss();
		_setplotaction(_GXOR);
		char st[5];
		int zx,zy;
		get_zx_zy(&zx,&zy);			
		_moveto(200-3+zx,24-3+zy);
		HideMouse();
		_outgtext("O");
		_moveto(256,12);
		sprintf(st,"%d",ed_zone+1);
		_outgtext(st);
		draw_edteam();

		ed_last_zone=ed_zone;
		ed_zone=zone;
		undo_copy();
		zy=(ed_zone/8)*20;
		zx=rem(ed_zone,8)*12*8;
		_moveto(200-3+zx,24-3+zy);
		_outgtext("O");
		_moveto(256,12);
		sprintf(st,"%d",ed_zone+1);
		_outgtext(st);
 		_setplotaction(_GPSET);
		ShowMouse();
		draw_edteam();
	}
	_setcolor(c);
}



/******************************************************************************
*****************************************************************************/

void top_l_corn()
{
	reset_poss();
	if (ed_zone!=32*2)
	{	int c=_getcolor();
		_setcolor(7);
 		_setplotaction(_GXOR);
		char st[5];
		int zx,zy;
		get_zx_zy(&zx,&zy);
		_moveto(200-3+zx,24-3+zy);
		HideMouse();
		_outgtext("O");

		_moveto(256,12);
		sprintf(st,"%d",ed_zone+1);
		_outgtext(st);
		draw_edteam();

		ed_last_zone=ed_zone;
		ed_zone=32*2;
		_moveto(200-2,16-4);
		_outgtext("O");

		_moveto(256,12);
		sprintf(st,"%d",ed_zone+1);
		_outgtext(st);
 		_setplotaction(_GPSET);
		ShowMouse();
		draw_edteam();
		_setcolor(c);
	}
}		

/******************************************************************************
*****************************************************************************/

void top_r_corn()
{
	reset_poss();
	if (ed_zone!=1+(32*2))
	{	int c=_getcolor();
		_setcolor(7);
 		_setplotaction(_GXOR);
		char st[5];
		int zx,zy;
		get_zx_zy(&zx,&zy);
		_moveto(200-3+zx,24-3+zy);
		HideMouse();
		_outgtext("O");

		_moveto(256,12);
		sprintf(st,"%d",ed_zone+1);
		_outgtext(st);
		draw_edteam();

		ed_last_zone=ed_zone;
		ed_zone=1+(32*2);
		_moveto(284-3,16-4);
		_outgtext("O");

		_moveto(256,12);
		sprintf(st,"%d",ed_zone+1);
		_outgtext(st);
 		_setplotaction(_GPSET);
		ShowMouse();
		draw_edteam();
		_setcolor(c);
	}
}		

/******************************************************************************
*****************************************************************************/

void bot_l_corn()
{
	reset_poss();
	if (ed_zone!=2+(32*2))
	{	int c=_getcolor();
		_setcolor(7);
 		_setplotaction(_GXOR);
		char st[5];
		int zx,zy;
		get_zx_zy(&zx,&zy);
		_moveto(200-3+zx,24-3+zy);
		HideMouse();
		_outgtext("O");

		_moveto(256,12);
		sprintf(st,"%d",ed_zone+1);
		_outgtext(st);
		draw_edteam();

		ed_last_zone=ed_zone;
		ed_zone=2+(32*2);
		_moveto(200-2,94-4);
		_outgtext("O");

		_moveto(256,12);
		sprintf(st,"%d",ed_zone+1);
		_outgtext(st);
 		_setplotaction(_GPSET);
		ShowMouse();
		draw_edteam();
		_setcolor(c);
	}
}		

/******************************************************************************
*****************************************************************************/

void bot_r_corn()
{
	reset_poss();
	if (ed_zone!=3+(32*2))
	{	int c=_getcolor();
		_setcolor(7);
 		_setplotaction(_GXOR);
		char st[5];
		int zx,zy;
		get_zx_zy(&zx,&zy);
		_moveto(200-3+zx,24-3+zy);
		HideMouse();
		_outgtext("O");

		_moveto(256,12);
		sprintf(st,"%d",ed_zone+1);
		_outgtext(st);
		draw_edteam();

		ed_last_zone=ed_zone;
		ed_zone=3+(32*2);
		_moveto(284-3,94-4);
		_outgtext("O");

		_moveto(256,12);
		sprintf(st,"%d",ed_zone+1);
		_outgtext(st);
 		_setplotaction(_GPSET);
		ShowMouse();
		draw_edteam();
		_setcolor(c);
	}
}

/******************************************************************************
*****************************************************************************/

void home_centre()
{
	reset_poss();
	if (ed_zone!=4+(32*2))
	{	int c=_getcolor();
		_setcolor(7);
 		_setplotaction(_GXOR);
		char st[5];
		int zx,zy;
		get_zx_zy(&zx,&zy);
		_moveto(200-3+zx,24-3+zy);
		HideMouse();
		_outgtext("O");

		_moveto(256,12);
		sprintf(st,"%d",ed_zone+1);
		_outgtext(st);
		draw_edteam();

		ed_last_zone=ed_zone;
		ed_zone=4+(32*2);
		_moveto(189-3,60-4);
		_outgtext("O");

		_moveto(256,12);
		sprintf(st,"%d",ed_zone+1);
		_outgtext(st);
 		_setplotaction(_GPSET);
		ShowMouse();
		draw_edteam();
		_setcolor(c);
	}
}

/******************************************************************************
*****************************************************************************/

void away_centre()
{
	reset_poss();
	if (ed_zone!=5+(32*2))
	{	int c=_getcolor();
		_setcolor(7);
 		_setplotaction(_GXOR);
		char st[5];
		int zx,zy;
		get_zx_zy(&zx,&zy);
		_moveto(200-3+zx,24-3+zy);
		HideMouse();
		_outgtext("O");

		_moveto(256,12);
		sprintf(st,"%d",ed_zone+1);
		_outgtext(st);
		draw_edteam();

		ed_last_zone=ed_zone;
		ed_zone=5+(32*2);
		_moveto(295-3,60-4);
		_outgtext("O");

		_moveto(256,12);
		sprintf(st,"%d",ed_zone+1);
		_outgtext(st);
 		_setplotaction(_GPSET);
		ShowMouse();
		draw_edteam();
		_setcolor(c);
	}
}

/******************************************************************************
*****************************************************************************/

void poss_butt()
{
	reset_poss();
	HideMouse();
	if (!ed_poss)
	{
		ed_last_zone=ed_zone;
		int g=_getplotaction();
		int c=_getcolor();
		_setcolor(5);
		_setplotaction(_GXOR);
		_moveto(260,98);
		_outgtext("x");
		_setcolor(7);
		_moveto(260,98);
		_outgtext("O");
		_setplotaction(g);
		_setcolor(c);
		MouseRelease();
		draw_edteam();
		ed_poss=1;
		draw_edteam();
	}
	else
	{
		ed_last_zone=ed_zone;
		int g=_getplotaction();
		int c=_getcolor();
		_setcolor(7);
		_setplotaction(_GXOR);
		_moveto(260,98);
		_outgtext("O");
		_setcolor(5);
		_moveto(260,98);
		_outgtext("x");
		_setplotaction(g);
		_setcolor(c);
		MouseRelease();
		draw_edteam();
		ed_poss=0;
		draw_edteam();
	}	
	ShowMouse();
}

/******************************************************************************
*****************************************************************************/

void undo_butt()
{
	HideMouse();
	draw_edteam();
	memcpy(ed_tactic[ed_zone+((ed_zone<32*2) ? ed_poss*32:0)],undo_tactic,10*2*sizeof(int));
	draw_edteam();
	ShowMouse();
	MouseRelease();
}

/******************************************************************************
*****************************************************************************/

void init_butt()
{
	HideMouse();
	draw_edteam();
	memset(&(ed_tactic[ed_zone+((ed_zone<32*2) ? ed_poss*32:0)]),0,10*2*sizeof(int));
	draw_edteam();
	ShowMouse();
	MouseRelease();
}

/******************************************************************************
*****************************************************************************/

void copy_butt()
{
	HideMouse();
	draw_edteam();
	memcpy(ed_tactic[ed_zone+((ed_zone<32*2) ? ed_poss*32:0)],
			 ed_tactic[ed_last_zone+((ed_last_zone<32*2) ? ed_last_poss*32:0)],10*2*sizeof(int));
	draw_edteam();
	ShowMouse();
	MouseRelease();
}

/******************************************************************************
*****************************************************************************/

void swap_butt()
{
	HideMouse();
	draw_edteam();

// Store last zone.
	memcpy(temp_tactic,ed_tactic[ed_last_zone+((ed_last_zone<32*2) ? ed_last_poss*32:0)],10*2*sizeof(int));
// Last=current.
	memcpy(ed_tactic[ed_last_zone+((ed_last_zone<32*2) ? ed_last_poss*32:0)]
	,ed_tactic[ed_zone+((ed_zone<32*2) ? ed_poss*32:0)],10*2*sizeof(int));
// current=last.
	memcpy(ed_tactic[ed_zone+((ed_zone<32*2) ? ed_poss*32:0)],temp_tactic,10*2*sizeof(int));

	draw_edteam();
	ShowMouse();
	MouseRelease();
}
	
/******************************************************************************
*****************************************************************************/

void e_go_button()
{
	switch(e_button_lit)
	{
		case 1:
		{
			top_l_corn();
			break;
		}

		case 2:
		{
			top_r_corn();
			break;
		}

		case 3:
		{
			bot_l_corn();
			break;
		}

		case 4:
		{
			bot_r_corn();
			break;
		}
		case 5:
		{
			load_butt();
			break;
		}
		case 6:
		{
			save_butt();
			break;
		}
		case 7:
		{
			poss_butt();
			break;
		}
		case 8:
		{
			copy_butt();
			break;
		}
		case 9:
		{
			swap_butt();
			break;
		}
		case 10:
		{
			undo_butt();
			break;
		}
		case 11:
		{
			init_butt();
			break;
		}
		case 12:
		{
			in_game=TRUE;				//return to game.
			break;
		}
		case 13:
		{
			name_butt();
			break;
		}
		case 14:
		{
			home_centre();
			break;
		}
		case 15:
		{
			away_centre();
			break;
		}
	}
}

/******************************************************************************
*****************************************************************************/

void capture_ed()
{
	int nd=5000;
	int mx=((Mouse.x/2)-8)*8;
	int my=(Mouse.y-8)*8;
	int x,y,d;
	for (int i=0; i<10; i++)
	{
		x=ed_tactic[ed_zone+((ed_zone<32*2) ? ed_poss*32:0)][i][0];
		y=ed_tactic[ed_zone+((ed_zone<32*2) ? ed_poss*32:0)][i][1];
		x-=mx;
		y-=my;
		d=calc_dist(x,y);
		if (d<nd)
		{
			nd=d;
			picked_up=i+1;
		}
	}
}

/******************************************************************************
*****************************************************************************/

void move_ed()
{
	int c=_getcolor();
	_setcolor(2);
	int mx=((Mouse.x/2)-8)*8;
	int my=(Mouse.y-8)*8;
	int x=ed_tactic[ed_zone+((ed_zone<32*2) ? ed_poss*32:0)][picked_up-1][0];
	int y=ed_tactic[ed_zone+((ed_zone<32*2) ? ed_poss*32:0)][picked_up-1][1];
	_setplotaction(_GXOR);
	char st[3];
	sprintf(st,"%d",picked_up+1);
	_moveto(8+(x/8)-3,8+(y/8)-3);
	HideMouse();
	_outgtext(st);
	ed_tactic[ed_zone+((ed_zone<32*2) ? ed_poss*32:0)][picked_up-1][0]=mx;
	ed_tactic[ed_zone+((ed_zone<32*2) ? ed_poss*32:0)][picked_up-1][1]=my;
	_moveto(8+(mx/8)-3,8+(my/8)-3);
	_outgtext(st);
	ShowMouse();
	_setplotaction(_GPSET);
	_setcolor(c);
}

/******************************************************************************
*****************************************************************************/

void pitch_grid()
{
	if (picked_up)
		move_ed();
	else
	{
		capture_ed();
		MouseYlim(8,107);
		MouseXlim(8*2,167*2);
	}
}
	
/******************************************************************************
*****************************************************************************/

void e_mouse_fired()
{
	if (e_button_lit)
		e_go_button();
	else
	{
		if ((Mouse.x/2>=200) && (Mouse.x/2<=284)
			&& (Mouse.y>=24) && (Mouse.y<=84))
			zone_grid();
		else
		{
			if ((Mouse.x/2>=8) && (Mouse.x/2<=168)
				&& (Mouse.y>=8) && (Mouse.y<=108))
				pitch_grid();
		}
	}
}

/******************************************************************************
*****************************************************************************/

/******************************************************************************
*****************************************************************************/

// Editor Main...

void editor_main()
{
	
	_clearscreen(_GCLEARSCREEN);
	InitMouse();
	MouseYlim(0,200-4);
	MouseXlim(0,(320-4)*2);
	_setplotaction(_GPSET);
	e_line_border(0,0,320,200,1);	
	draw_grid();
	draw_markings();
	draw_zones();
	_setcolor(5);
	e_draw_buttons();
	_moveto(260,98);
	_outgtext("x");
	init_zgrid();
	write_name();
	draw_edteam();
	ShowMouse();

// Main Loop For Editor...

	while (!in_game)
	{
		ReportMouse();
		e_process_butts();
		if (Mouse.b&&1)
			e_mouse_fired();
		else
		{
			if (picked_up)
			{
				picked_up=0;
				MouseYlim(0,200-4);
				MouseXlim(0,(320-4)*2);
			}
		}
		delay(50);
	}	
	_clearscreen(_GCLEARSCREEN);
	memcpy(match_tactics1,ed_tactic,(((32*2)+6)*10*2)*sizeof(int));
	memcpy(match_tactics2,ed_tactic,(((32*2)+6)*10*2)*sizeof(int));
	MouseRelease();
}


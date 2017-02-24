/******************************************************************************
*******************************************************************************

Display output routines...

******************************************************************************
*****************************************************************************/

#include "global.h"

#include "defines.h"
#include "externs.h"
#include "mouse.h"
#include "time.h"
#include "3deng.h"

extern int scale;
extern char camera;
extern int play_cam;
extern buff_info main_buff,vidi_buff;
extern plyrdat pos[];

/*****************************************************************************
*****************************************************************************/

/*****************************************************************************
*****************************************************************************/

void init_pitch_sprites()
{
	pitch_sprs=0;
	spr_coord_tab[0]=0;
}

/*****************************************************************************
*****************************************************************************/

void add_pitch_sprite(short x,short y,short z,short ref)
{
// Set up real 3d sprite...
	spr_coord_tab[0]+=1;
	spr_coord_tab[3*pitch_sprs+1]=x;
	spr_coord_tab[3*pitch_sprs+2]=z;
	spr_coord_tab[3*pitch_sprs+3]=-y;
	spr_ref_tab[pitch_sprs++]=ref;
}

/******************************************************************************
*****************************************************************************/

void grid_map()
{
	int c=_getcolor();
	int g=_getplotaction();
	_setcolor(2);
	_setplotaction(_GXOR);
	float step=(320.2)/7;
	float step2=step*224/320;
	float x=0+(step/2);
	float x2=48+(step2/2);
	for (int i=1; i<8; i++, x+=step, x2+=step2 )
	{
		_moveto((int)x,131);
		_lineto((int)x2,32);
	}
	step=100/3;
	float lstep=48/3;
	x=32+(step/2);
	float lx=48-(lstep/2);
	for (i=1; i<4; i++, x+=step, lx-=lstep )
	{
		_moveto(lx,(int)x);
		_lineto(272+(47-lx),(int)x);
	}
	_setcolor(c);
	_setplotaction(g);
}

/******************************************************************************
******************************************************************************/

void line_border(int x,int y,int wid,int hgt,int col)
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

void draw_buttons()
{
	int x,y,w;
	char st[10];
	for (int i=0; i<max_butts; i++)
	{
		x=us_buttons[i].x;
		y=us_buttons[i].y;
		w=us_buttons[i].w;
		strcpy(st,us_buttons[i].s);
		_moveto(x,y);
		_outgtext(st);
		line_border(x-4,y-4,w*8+8,16,1);
	}
}

/******************************************************************************
*****************************************************************************/

void light_button(int b)
{
	int x,y,w,c;
	c=_getcolor();
	char st[10];
	x=us_buttons[b].x;
	y=us_buttons[b].y;
	w=us_buttons[b].w;
	strcpy(st,us_buttons[b].s);
	_setcolor(7);
	_moveto(x,y);
	HideMouse();
	_outgtext(st);
	_setcolor(c);
	ShowMouse();
	button_lit=b+1;
}

/******************************************************************************
*****************************************************************************/

void unlight_button(int b)
{
	int x,y,w;
	char st[10];
	x=us_buttons[b].x;
	y=us_buttons[b].y;
	w=us_buttons[b].w;
	strcpy(st,us_buttons[b].s);
	_moveto(x,y);
	HideMouse();
	_outgtext(st);
	ShowMouse();
	if (button_lit==b+1)
		button_lit=0;					//no other button lit!
}

/******************************************************************************
*****************************************************************************/

void conv_xypitch(float x, float y, int *screen_x, int *screen_y)
{
	float x2,xoff;
	x2=x;
	x=-(x-halfway_line);
	xoff=scr_pinch*(((float)pitch_wid-y)/(50.0*16))*x/(40.0*16.0);
	x2=(x2/4)+xoff;
	*screen_x=x2;
	*screen_y=(y/8);
}

/******************************************************************************
****************************************************************************/

void pitch_markings()
{
	int g=_getplotaction();
	int c=_getcolor();
	int x,y;
	_setcolor(7);

// Left Goal
	conv_xypitch(0,357,&x,&y);
	_moveto(x,y+32);
	_lineto(x,y+32-4);
	_moveto(x,y+32);
	conv_xypitch(-28,357,&x,&y);
	_lineto(x,y+32);
	_lineto(x,y+32-4);
	_moveto(x,y+32);
	conv_xypitch(-28,443,&x,&y);
	_lineto(x,y+32);
	_lineto(x,y+32-4);
	_moveto(x,y+32);
	conv_xypitch(0,443,&x,&y);
	_lineto(x,y+32);
	_lineto(x,y+32-4);
	conv_xypitch(0,357,&x,&y);
	_lineto(x,y+32-4);
	conv_xypitch(-28,357,&x,&y);
	_lineto(x,y+32-4);
	conv_xypitch(-28,443,&x,&y);
	_lineto(x,y+32-4);
	conv_xypitch(0,443,&x,&y);
	_lineto(x,y+32-4);

// Right Goal
	conv_xypitch(pitch_len,357,&x,&y);
	_moveto(x,y+32);
	_lineto(x,y+32-4);
	_moveto(x,y+32);
	conv_xypitch(pitch_len+28,357,&x,&y);
	_lineto(x,y+32);
	_lineto(x,y+32-4);
	_moveto(x,y+32);
	conv_xypitch(pitch_len+28,443,&x,&y);
	_lineto(x,y+32);
	_lineto(x,y+32-4);
	_moveto(x,y+32);
	conv_xypitch(pitch_len,443,&x,&y);
	_lineto(x,y+32);
	_lineto(x,y+32-4);
	conv_xypitch(pitch_len,357,&x,&y);
	_lineto(x,y+32-4);
	conv_xypitch(pitch_len+28,357,&x,&y);
	_lineto(x,y+32-4);
	conv_xypitch(pitch_len+28,443,&x,&y);
	_lineto(x,y+32-4);
	conv_xypitch(pitch_len,443,&x,&y);
	_lineto(x,y+32-4);

	_setcolor(1);
// Left Six Yard Box
	conv_xypitch(0,293,&x,&y);
	_moveto(x,y+32);
	conv_xypitch(6.0*prat,293,&x,&y);
	_lineto(x,y+32);
	conv_xypitch(6.0*prat,507,&x,&y);
	_lineto(x,y+32);
	conv_xypitch(0,507,&x,&y);
	_lineto(x,y+32);

// Right Six Yard Box
	conv_xypitch(80*16,293,&x,&y);
	_moveto(x,y+32);
	conv_xypitch(80*16-(6.0*prat),293,&x,&y);
	_lineto(x,y+32);
	conv_xypitch(80*16-(6.0*prat),507,&x,&y);
	_lineto(x,y+32);
	conv_xypitch(80*16,507,&x,&y);
	_lineto(x,y+32);

// Left 18 Yard Box
	conv_xypitch(0,208,&x,&y);
	_moveto(x,y+32);
	conv_xypitch(18.0*prat,208,&x,&y);
	_lineto(x,y+32);
	conv_xypitch(18.0*prat,592,&x,&y);
	_lineto(x,y+32);
	conv_xypitch(0,592,&x,&y);
	_lineto(x,y+32);

// Right 18 Yard Box
	conv_xypitch(80*16,208,&x,&y);
	_moveto(x,y+32);
	conv_xypitch(80*16-(18.0*prat),208,&x,&y);
	_lineto(x,y+32);
	conv_xypitch(80*16-(18.0*prat),592,&x,&y);
	_lineto(x,y+32);
	conv_xypitch(80*16,592,&x,&y);
	_lineto(x,y+32);


// Centre circle
	_ellipse(_GBORDER,160-13,82-13,160+13,82+13);
	_setcolor(c);
	_setplotaction(g);
}

/******************************************************************************
****************************************************************************/

void draw_pitch()
{
	_setcolor(0);
	_lineto(48,32);
	_setcolor(1);
	_lineto(48+112+111,32);
	_lineto(319,131);
	_lineto(0,131);
	_lineto(48,32);
	_lineto(160,32);
	_lineto(160,131);
}

/******************************************************************************
*****************************************************************************/

void pitch_plot(int x,int y,int z,char c,char a)		//Place screen coords on plot buffer.
{
	if (plot_buffer)							//Choose Buffer.
	{
	scr_a[plot_cnta][0]=x;
	scr_a[plot_cnta][1]=y-(z/8);
	scr_a[plot_cnta][2]=c;
	scr_a[plot_cnta++][3]=a;
	}
	else
	{
	scr_b[plot_cntb][0]=x;
	scr_b[plot_cntb][1]=y-(z/8);
	scr_b[plot_cntb][2]=c;
	scr_b[plot_cntb++][3]=a;
	}
}

/******************************************************************************
*****************************************************************************/

void draw_buffer()
{
	char pn[3]="  ";
	for (int coords=1; (plot_buffer) ? coords<plot_cnta : coords<plot_cntb;
				coords++)
	{
		if (plot_buffer)							//Choose Buffer.
		{
			if (scr_a[coords][3]==0)
			{
				_setcolor(scr_a[coords][2]);
				_setpixel(scr_a[coords][0],scr_a[coords][1]);
			}	
			else
			{
				_setcolor(scr_a[coords][2]);
				_moveto(scr_a[coords][0]-3,scr_a[coords][1]-3);
				sprintf(pn,"%d",scr_a[coords][3]);
				_outgtext(pn);
			}
		}
		else
		{
			if (scr_b[coords][3]==0)
			{
				_setcolor(scr_b[coords][2]);
				_setpixel(scr_b[coords][0],scr_b[coords][1]);
			}	
			else
			{
				_setcolor(scr_b[coords][2]);
				_moveto(scr_b[coords][0]-3,scr_b[coords][1]-3);
				sprintf(pn,"%d",scr_b[coords][3]);
				_outgtext(pn);
			}
		}
	}
}

/******************************************************************************
*****************************************************************************/

void draw_ball()
{
	float bx=(pos+25)->x;
	float bz=((pos+25)->y);
	float by=((pos+25)->z);
	conv_xypitch(bx,by,&scr_x,&scr_y);
	pitch_plot(scr_x,scr_y+32,(int)bz,ball_col,0);
	pitch_plot(scr_x,scr_y+31,(int)bz,ball_col,0);
	pitch_plot(scr_x+1,scr_y+32,(int)bz,ball_col,0);
	pitch_plot(scr_x+1,scr_y+31,(int)bz,ball_col,0);
	pitch_plot(scr_x,scr_y+32,0,shadow_col,0);
	pitch_plot(scr_x+1,scr_y+32,0,shadow_col,0);
}

/******************************************************************************
*****************************************************************************/

void draw_team()
{
	float tx,ty,tz;

	for (int i=0; i<(players/2); i++)
	{
		tx=(pos+i)->x;
		tz=(pos+i)->y;
		ty=(pos+i)->z;
		conv_xypitch(tx,ty,&scr_x,&scr_y);
		if (play_nums_on)
		{
			pitch_plot(scr_x,scr_y+32,(int)tz,team_a_col,i+2);
		}
		else
		{
		pitch_plot(scr_x,scr_y+32,(int)tz,team_a_col,0);
		pitch_plot(scr_x,scr_y+33,(int)tz,team_a_col,0);
		if ((teams[i].int_cnt) && (teams[i].int_move==I_INTERCEPT))
			pitch_plot(scr_x,scr_y+31,(int)tz,7,0);
		}
	}

	for (i=11; i<players; i++)
	{
		tx=(pos+i)->x;
		tz=(pos+i)->y;
		ty=(pos+i)->z;
		conv_xypitch(tx,ty,&scr_x,&scr_y);
		if (play_nums_on)
		{
			pitch_plot(scr_x,scr_y+32,(int)tz,team_b_col,i-8);
		}
		else
		{
		pitch_plot(scr_x,scr_y+32,(int)tz,team_b_col,0);
		pitch_plot(scr_x,scr_y+33,(int)tz,team_b_col,0);
		if ((teams[i].int_cnt) && (teams[i].int_move==I_INTERCEPT))
			pitch_plot(scr_x,scr_y+31,(int)tz,7,0);
		}
	}
}

/******************************************************************************
*****************************************************************************/

void panel_data()
{
	char info_str1[40];
	char info_str2[40];
	char info_str3[4];
	char info_str4[12];
/*
//	sprintf(info_str1,"zone =%d  poss =%d     ",ball_zone1,ball_poss);
	sprintf(info_str1,"opps =%d  poss =%d     ",opponents_near_holder,ball_poss);
//	sprintf(info_str1,"a =%d  b =%d     ",interceptor_a+1,interceptor_b+1);
//	sprintf(info_str2,"last =%d  bspd =%d     ",last_touch,ball_speed);
	sprintf(info_str2,"xyspin =%d zspin =%d     ",set_xyspin,set_zspin);
	_settextposition(21,0);
	_outtext(info_str1);
	_settextposition(22,0);
	_outtext(info_str2);
	_settextposition(23,0);
	_outtext(action);
	_outtext("          ");
*/
	sprintf(info_str4,"%d - %d     ",team_a_goals,team_b_goals);
	_settextposition(20,0);
	_outtext(info_str4);

	sprintf(info_str3,"%d ",delay_cnt);
	_settextposition(20,37);
	_outtext(info_str3);
}

/******************************************************************************
******************************************************************************/

void slower()
{
	delay_cnt++;
}

/******************************************************************************
******************************************************************************/

void faster()
{
	if (delay_cnt>0)
		delay_cnt--;
}

/******************************************************************************
******************************************************************************/

void show_nums()
{
	if (play_nums_on)
		play_nums_on=FALSE;
	else
		play_nums_on=TRUE;
}

/******************************************************************************
*****************************************************************************/

int old_time=0;
int prev_count=0;
int times=0;

void frame_count()
{
	updates++;
	frames++;
	times++;

	int cl=count-oldcnt;

	if (count-prev_count>TIMER_SPEED)
	{
		prev_count=count;
		old_time=times;
	}

	if (cl>(TIMER_SPEED/4))			// Re-time interval (1/4 sec)!
	{
		oldcnt=count;
		MF=((float)cl*game_speed)/(frames*TIMER_SPEED);
		if (MF>6 && game_speed==REAL_SPEED)
			MF=6;
		frames=0;
	}
}

void oframe_count()
{
	updates++;
	int cl=clock();
	frames++;
	int c=cl/CLOCKS_PER_SEC;
	if (c!=last_second)
	{
		seconds++;
		frms_per_sec=frames;
		frames=0;
		last_second=c;
		int frame_time=cl-old_clock;
		old_clock=cl;
		MF=((float)(frame_time)*game_speed)/(frms_per_sec*100);
	}
}

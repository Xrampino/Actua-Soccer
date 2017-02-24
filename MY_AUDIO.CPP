#include "global.h"

// Audio includes...
#include "audio.h"	

#include "defines.h"
#include "front.h"	
#include "eurofrnt\euro_int.h"

#include "externs.h"

extern match_data match_info;

extern float camera_x,camera_y,camera_z;

/*********************************/
/*** Sound Fx Control Routines ***/
/*********************************/

void play_fx(int fx,float x,float y)
{
	int pan,vol;
	float d,xd,yd,zd;
	xd=x-camera_x;
	yd=y-camera_x;
	zd=camera_z;

	d=calc_dist(x-camera_x,y-camera_y);
	d=calc_dist(d,zd);
	xd=xd/d;
	yd=yd/d;
	
	if (d<MAX_VOL_DIST)
		vol=0x7fff;
	else
		vol=(MAX_VOL_DIST/d)*0x7fff;

	d=((xd*cth)+(yd*sth));
	pan=0x8000+(d*0x8000);

	if (EUROmatch_info.audio==2)
// 3D Sound...
		PlayPitchSample(fx,vol,pan);
	else
// Mono...
		PlayPitchSample(fx,0x7fff,0x8000);
}

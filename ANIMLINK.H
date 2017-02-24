#ifndef _ANIMLINK_H_INCLUDED
/*
 ษออออออออออออป
 บ AUTOHEADER บ
 ฬออออออออออออสออออออออออออออออออป
 บ Filename     ANIMLINK.H       บ
 วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
 บ Creation     7/8/1995         บ
 ฬอออออออออออออออออออออออออออออออน
 บ                               บ
 บ Updated: Mon 7/8/1995 16:27   บ
 บ                               บ
 บ Version: 1.009                บ
 บ                               บ
 ศอออออออออออออออออออออออออออออออผ
*/
#include "playdam.h"
#include "playcall.h"

/* link function for playdam...
****************************************
playanim {
		 	_PlayAnimBlock pab;

		 	if (! InitAnim	( InitAnimPlay( pab ) ))
				{
				StartAnim( pab );
	 			CloseAnim( pab );
				RestoreAnimPlay( pab )
          	}
****************************************
*/

_PlayAnimBlock * InitAnimPlay (_PlayAnimBlock *);
void RestoreAnimPlay (_PlayAnimBlock *);

#define _ANIMLINK_H_INCLUDED
#endif

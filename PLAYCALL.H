#ifndef _PLAYCALL_H_INCLUDED
/*
 ษออออออออออออป
 บ AUTOHEADER บ
 ฬออออออออออออสออออออออออออออออออป
 บ Filename     PLAYCALL.H       บ
 วฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤถ
 บ Creation     11/5/1995        บ
 ฬอออออออออออออออออออออออออออออออน
 บ                               บ
 บ Updated: Fri 12/5/1995 13:50  บ
 บ                               บ
 บ Version: 1.016                บ
 บ                               บ
 ศอออออออออออออออออออออออออออออออผ
*/

#include "playdam.h"

#ifdef __cplusplus
extern "C" {
#endif

// calls
long int InitAnim	( _PlayAnimBlock * ); 
long int StartAnim( _PlayAnimBlock * ); // should not be called if InitAnim failed
void 		CloseAnim( _PlayAnimBlock * ); // should always be called even if it fails

#define _PLAYCALL_H_INCLUDED
#ifdef __cplusplus
};
#endif
#endif



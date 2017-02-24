#ifndef _VIDEO_H_
#define _VIDEO_H_

#define	VESA_MODE_OK							0x0000
#define	VESA_MODE_NOT_SUPPORTED				0x0001

extern void blank_pallette();
extern void set_pallette( unsigned char *Pallette );
extern void set_pallette_entry( unsigned char color, unsigned char red, unsigned	char blue, unsigned char green );
//	extern int set_vesa_mode( unsigned short mode_no, int checks = 1 );
extern void svgacopy( unsigned char *buffpt, short x, short y, short w, short h, short buff_wid);
extern void svgaread( char *buffpt, short x, short y, short w, short h, short buff_wid);
extern short get_curr_vmode();
extern void draw_line(	short x1, short y1, short x2, short y2, char col, buff_info *buffer );

#endif /* _VIDEO_H_ */


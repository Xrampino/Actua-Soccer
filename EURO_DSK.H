extern	FILE 			*fp2;
extern	signed int 	ReadLine( FILE *, char * );
extern	void			ReadDataOffsetFile( char * );
extern	void			ReadData( int, char *, BYTE * );
extern	void			LoadTexturePage( int, char *, unsigned char, texture_info * );
extern	void			LoadPalette( int, char *, int );
extern	void			LoadTactics( int, char *, int *);

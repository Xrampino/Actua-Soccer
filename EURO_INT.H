extern	void	TempFrontend();
extern	void	ExitFrontend();
extern	void	TransferDataToMatchInfo();
extern	short	NormalisePlayer( char, char );
extern	char	*ToUPPER( char * );
extern	char	*GetTEXT( short );
extern	char	*GetTEAMname( char, char );
extern	void	DisplayString( int, int, char *, int, int, signed char, pseudo_info *, texture_info * );
extern	void 	spriteinccopy( int copyWidth, BYTE *dest, BYTE *srce );
extern	char	*GetPLAYERSname( char, char, char );

extern	BYTE				*Text[];
extern	char 				StringBuffer[];
extern	char		 		svalue;
extern	signed 	char	IsUpper[];
extern	unsigned char	ToLower[];
extern	unsigned char 	ToUpper[];
extern	char				NamePREFIXtbl[];
extern	unsigned char	ASCtoImageTBL[];
extern	int				Image_Xcoords[];
extern	int				Image_Ycoords[];
extern	int				Image_Widths[];
extern	int		  		Image_Heights[];
extern	char				Image_Pages[];
extern	int				NextXposn;

extern	char				Pace[];
extern	char				Power[];
extern	char				Control[];
extern	char				Flair[];
extern	char				Vision[];
extern	char				Accuracy[];
extern	char				Stamina[];
extern	char				Discipline[];
extern	char				Fitness[];
extern	char				SquadInfo[];

		//ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป 
		//บ                                                                                      บ
		//บ EURO 96 INTERFACE MODULE, USED TO PASS DATA FROM FRONTEND TO LAURENT, ANDY AND KEVIN บ
		//บ                                                                                      บ
		//ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ 

typedef struct 
{
	char			pace;
	char			power;
	char			control;
	char			flair;
	char			vision;
	char			accuracy;
	char			stamina;
	char			discipline;
	char			fitness;
		
					}player_data;

typedef struct {

	unsigned char	camera;					// done
	short				audio;					// tbd
	int				crowd;					// tbd
	int				pitch;					// tbd
	int				commentary;				// tbd
	int				music;					// tbd
	int				master;					// tbd
	short				timeit;					// tbd							 	
	short				vidi;						// tbd
	char				tac_1;					// tbd
	char				tac_2;					// tbd
	char				offside;					// done
	char				substitutes;			// done
	char				freekicks;				// done
	char				time;						// done
	char				bookings;				// done
	char				wind;						// done
	unsigned char	referee_vision;		// done
	unsigned	char	referee_discipline;	// done
	char				tga_enable;				// done
	short				return_mins;			// done
	int				rand;						// done
  	char				language;				// done

	char				GameType;
	char				verbose;
	char				EscKey;


	char				Team_A_goals;			// score for team_a
	char				Team_B_goals;			// score for team_b
	char				penalties;			 	// done
	char 				extra;					// done
	char				Team_A_penalties;		// done
	char				Team_B_penalties;		// done
	signed char		CntrlTypes[4];
	signed char		PlyrTypes[4];
	char				TeamA_users;
	char				TeamB_users;
	
	char				TeamAname[20];			// country name copied here (used for easier access).
	char				TeamBname[20];			// country name copied here (used for easier access).
	char				RefsName[20];			// referee's name copied here (used for easier access).
	char				TeamAsquad[20];
	char				TeamBsquad[20];
	player_data		TeamA[20];				// team A squad data.
	player_data		TeamB[20];				// team B squad data.
	char				TeamAplyrNames[20][32];	
	char				TeamBplyrNames[20][32];	


            	}interface_data;

extern	interface_data	EUROmatch_info;
	























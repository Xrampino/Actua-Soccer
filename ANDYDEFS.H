

struct match_player {

// Player General...
	short tm_player;
	float tm_x, tm_xdis, tm_y, tm_ydis, tm_z, tm_zdis;
	float mface_x,mface_y;
	short mface_time;
	char mface;
	float tm_dist;
	char tm_pos;
	short tm_limbo;
	short guy_on;
	char control;
	char tm_srng;
	signed char tm_off;
	char tm_stopped;
	char tm_trap;
	short special;
	short tm_strike;
	float tm_stime;
	short tm_ftime;
	short ball_state;
	short tm_fpass_type;
	short tm_fpass_to;
	char draw_me;
	short shirt;

// Player Attributes...
	unsigned char tm_rate;		//Speed.
	unsigned char tm_pow;		//Physical Power.
	unsigned char tm_cont;		//Ball Control.
	unsigned char tm_flair;		//Flair.
	unsigned char tm_vis;		//Vision.
	unsigned char tm_ac;			//Accuracy.
	unsigned char tm_stam;		//Stamina.
	unsigned char tm_disc;		//Discipline.

// Match Stats...
	unsigned char tm_book; 	//Bookings.
	unsigned char tm_fouls;	//Fouls Committed.
	short tm_tacks;			//Tackles attempted.
	short tm_twon;				//Tackles won.
	short tm_shots;			//Shots attempted.
	short tm_saved;			//Shots saved.
	unsigned char tm_goals;	//Goals scored.
	short tm_pass;				//Passes attempted.
	short tm_pwon;				//Passes completed.
	unsigned short tm_inj;	//Injury type.
	short tm_posst;			//Time in possession.
	int tm_work;				//Distance ran.
	short tm_kpsaves;		  	//Keeper save ratio.
	unsigned char tm_ogs;	//Own goals scored.
	unsigned char tm_time;	//Player on field for mins.
	
// Animation Data...
	short turn_dir, face_dir, dir_mode;
	float tm_frm,tm_fstep;
	unsigned short tm_anim;
	unsigned char tm_hcol,tm_htype;
	float tm_mcspd;
	float ls_anim,ls_frm;
	float contact;
	char tm_newanim;
	char tm_barge;
	char tm_limp;	
// Action Data...
	short tm_act, tm_poss, tm_wall, tm_leave, tm_mark;
	int go_dist;
	int go_cnt;
	float go_txdis,go_tydis,go_tx,go_ty,go_xoff,go_yoff,tm_jump;
	char go_stop;
	char go_step;
	char tm_notme;
	
// Player Intelligence...
	short int_move, int_cnt, mess_num, mess_cnt;
	short tm_comm,tm_ccnt;

};

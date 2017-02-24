/******************************************************************************
******************************************************************************/

// Global Constants

// Sound Fx. flags etc...

extern short int crowd_mood_a;
extern short int crowd_mood_b;
extern float possession;
extern float poss_held;
extern char kickoff;

#include "3deng.h"

extern char debug;

struct butts {
	int x;
	int y;
	int w;
	char s[10];
	char l;
};

extern butts us_buttons[];

extern int max_butts;

// Pixel Colours.

extern char ball_col;
extern char shadow_col;
extern char team_a_col;
extern char team_b_col;

// General Control variables...

extern char demo;

// Ball fx.

extern float newdx,newdy;

extern short wind_on,wind_d_trend,wind_s_trend;
extern float wind_x,wind_y,wind_speed;
extern float init_wind_x,init_wind_y,init_wind_speed;
extern float wind_var_ang;

extern float bounce_dis;
extern float gravity;
extern int cntspot_x;
extern int cntspot_y;

// Pitch sizes.
extern int pitch_len, pitch_wid;
extern int halfway_line, scr_pinch;
extern int right_bounds;
extern int left_bounds;
extern int lower_bounds;
extern int upper_bounds;
extern float zone_wid;
extern float zone_hgt;
extern float prat;
extern int goal_height;	//8 feet
extern int goal_depth;		//8 feet
extern int post_width;					//5 inches approx.
extern int top_post_y;
extern int bot_post_y;

// Players.

extern int players;
extern int avg1_rate,avg1_power,avg1_bcontrol,avg1_flair,
		avg1_vision,avg1_accuracy,avg1_fitness,avg1_disc;
extern int avg2_rate,avg2_power,avg2_bcontrol,avg2_flair,
		avg2_vision,avg2_accuracy,avg2_fitness,avg2_disc;
extern int danger_radius;

extern int visual_range;
extern int tackle_range;
extern int block_range;
extern int steal_range;
extern int min_block_range;

/******************************************************************************
******************************************************************************/

// Major control variables...

extern char audio_version;

/******************************************************************************
******************************************************************************/

// Randomize variables...

extern short int rand1_tab[];
extern short int rand2_tab[];
extern char andys_random;


// Global Match Variables...

// Man to man marking table....

extern int man2man[10][2];
extern char man2man_a,man2man_b;

struct mtime{
		unsigned short min;
		float sec;
		};

extern int seconds;
extern mtime match_time;
extern int time_factor;

extern float MF;
extern float mf_scale;
extern float omf_scale;
extern char mf_fixed;
extern char alarm,watch;
extern int stop_min;
extern int stop_sec;
extern char practice;
extern char team_a_on;
extern char team_b_on;

extern char arrow_on;
extern char arrow_guy;

extern short rand_seed,seed;
extern int logic_cnt;
extern char ball_move;
extern float man_down;

extern int match_tactics1[32*2+6][10][2];
extern int match_tactics2[32*2+6][10][2];

extern int launch_type;
extern float launch_x,launch_y;
extern float ballxdis, ballydis, ballzdis;
extern float eff_ballx,eff_bally,eff_ballz;
extern float ballx, bally, ballz;
extern float b_xoff,b_yoff,b_zoff;
extern float prev_ballx, prev_bally, prev_ballz;
extern float ns_ballx, ns_bally, ns_ballz;
extern float ball_zspin, ball_xyspin;
extern float full_zspin, full_xyspin;
extern float shoot_x,shoot_y;

extern int first_bounce;
extern int swerve, spin_cnt, spin_ball, prediction;
extern float ball_horz_ang,ball_vert_ang;
extern float ball_diam;

extern short keeper_down=FALSE;
extern int keeper_will_save;
extern char keeper_on_grnd;
extern float keeper_contact;
extern int set_xyspin,set_zspin;
extern int throw_cnt;
extern char ball_in_goal;
extern char ball_in_hands;
extern char game_action;
extern int team_a_goals;
extern char last_goal;
extern int team_b_goals;
extern int just_scored;
extern int just_thrown;
extern int goal_scorer;
extern int pass_type;
extern int kick_type;
extern int receiver;
extern char cross_now;
extern char must_shoot;
extern char chip_pass;
extern char must_pass;
extern char must_punt;
extern char keeper_a_in_box;
extern char keeper_b_in_box;
extern int keeper_steps;
extern short save_block;
extern float save_xoff,save_yoff,save_zoff;

extern float shot_speed;

extern int scr_x,scr_y,ball_speed;
extern int interceptor_a;
extern int interceptor_b;
extern int in_cross_area;
extern float close_in_number;

extern int ball_inair, super_shot, opponents_near_holder,opponents_really_close;
extern int ball_poss,sender_1_2,ball_still,last_touch,want_pass;
extern int before,support_me;
extern int cannot_pick_up;

extern int ball_limbo_p;
extern char ball_limbo_on;
extern float ball_limbo_c;
extern int ball_released;
extern short last_user_a;
extern short last_user_b;
extern int want_pass_stat,ball_zone1,ball_zone2,ball_out_of_play;
extern int nearest_a,nearest_b,old_ltouch,old_ball_poss;
extern int near_path_a,near_path_b;
extern int zone1_x,zone1_y,zone2_x,zone2_y;
extern int incident_x,incident_y;
extern int difficulty;
extern int ready_centre;

extern float ball_pred_tab[50][3];
extern float ns_ball_pred_tab[50][3];

extern int shooter;
extern char force_select;
extern char heading_ball;
extern char shot_attempt;
extern char flag;
extern char in_game;
extern char analogue;
extern char match_mode;
extern int dead_ball_cnt;
extern int defense_a,defense_b;

extern int savex,savey,savez;
extern char shot_acknowledged;
extern int shot_pending;
extern char match_mode;
extern int duration;
extern char tweening;

/******************************************************************************
******************************************************************************/

// Screen Buffer Stuff...
extern int scr_a[100][4];
extern int scr_b[100][4];
extern int plot_cnta;
extern int plot_cntb;
extern int plot_buffer;
extern int replay_pos;
extern int replay_cnt;
extern int pitch_sprs;

// Sprite Stuff...

extern float spr_coord_tab[MAX_3D_SPRS*3+1];
extern short spr_ref_tab[MAX_3D_SPRS];

// User Interface...

extern short ball_travel;
extern short select_cnt;

extern int button_lit;
extern int delay_cnt;
extern int play_nums_on;
extern char *action;
extern char frame;
extern int frames;
extern int frms_per_sec;
extern "C" int game_speed;		// Currently declared in network.c
extern int last_second;
extern int old_clock;

#pragma pack (1)

struct user_config{
	short type;
	short control;
	int inp_x;
	int inp_y;
	int inp_ox;
	int inp_oy;
	short inp_fb;
	char chng;
	signed char plr;
	};

extern "C" volatile user_config users[MAX_USERS];	// Declared in network.c

struct user_vectors_i{
	short x_f1;
	short y_f2;
	};

extern "C" volatile user_vectors_i users_dir_i[512][MAX_USERS];	// Declared in network.c

#pragma pack (4)

extern "C" volatile int writeptr;
extern "C" volatile int readptr;

struct user_vectors{
	float x;
	float y;
	char m;
	char f;
	};

extern user_vectors users_dir[MAX_USERS];	// Declared in glob_vars.h, as usual

extern short auto_users_list_a[10];
extern short auto_users_a;
extern short play_ball_a;
extern char new_select;

extern short auto_users_list_b[10];
extern short auto_users_b;
extern short play_ball_b;

extern char user_controlled;
extern char after_touch_on;
extern "C" int num_of_users;	// Currently in network.c

extern short f1_down;
extern short f2_down;

extern char setp_kick_type;
extern float setp_kick_x;
extern float setp_kick_y;

extern short user_taker;

// Input devices

extern float ux,uy;		// User x,y,f1,f2,move
extern char uf1,uf2;
extern char um;

// Joysticks & keyboard, taken to network.c

extern "C" signed char key1[6];
extern "C" signed char key2[6];

extern "C" unsigned short joy1_cnt_x,joy1_cnt_y;
extern "C" unsigned short joy2_cnt_x,joy2_cnt_y;

extern "C" int joy1_max_x,joy1_max_y,joy1_min_x,joy1_min_y;
extern "C" int joy2_max_x,joy2_max_y,joy2_min_x,joy2_min_y;

extern "C" volatile int joy1_x;
extern "C" volatile int joy1_y;
extern "C" volatile int joy1_fire;

extern "C" volatile int joy2_x;
extern "C" volatile int joy2_y;
extern "C" volatile int joy2_fire;

extern "C" volatile char joy1_move;
extern "C" volatile char joy2_move;

extern "C" char joystick1_on;
extern "C" char joystick2_on;

extern "C" char digital_joy1;
extern "C" char digital_joy2;


extern char camera;
extern char old_cam;
extern char already_there;
extern char reselection;
extern float camera_dist;
extern float poss_mode;

/******************************************************************************
******************************************************************************/

// Team Players Data...

// Wall data...
extern float wallx,wally;
extern int men_in_wall;
struct wall {
	int guy;
	float x,y;
};

extern wall wguys[];
extern float keeper_pos_x,keeper_pos_y;

extern char in_range,in_header_rng,in_shot_rng;
extern int taker_x,taker_y;

extern int penalty_taker;
extern int penalty_taker_a;
extern int penalty_taker_b;

extern int player_num;
extern int centre_guy_1;
extern int centre_guy_2;

extern int fkick_taker;
extern int fkick_taker_a;
extern int fkick_taker_b;

extern int gkick_taker;
extern int goal_kicker_a;
extern int goal_kicker_b;

extern int corner_taker;
extern int corn_kicker_a;
extern int corn_kicker_b;
extern int ktaker;
extern int bad_guy;
extern char direct_fk;

extern char play_advantage;

extern char set_piece_on;

extern int throw_in_taker;
extern int main_man;

extern float opp_dir_tab[11][3];
extern int drib_opps;

struct bubbles{int say;int cnt;};
extern bubbles speech_tab[26];

struct match_player {

// Player General...
	int tm_player;
	float tm_x, tm_xdis, tm_y, tm_ydis, tm_z, tm_zdis;
	float tm_dist;
	int tm_pos;
	int tm_limbo;
	short guy_on;
	char control;
	char tm_srng;
	char tm_off;
	char tm_stopped;

// Player Attributes...
	int tm_rate;		//Speed.
	int tm_pow;			//Physical Power.
	int tm_cont;		//Ball Control.
	int tm_flair;		//Flair.
	int tm_vis;			//Vision.
	int tm_ac;			//Accuracy.
	int tm_stam;		//Stamina.
	int tm_disc;		//Discipline.

// Match Stats...
	int tm_book;		//Bookings.
	int tm_fouls;		//Fouls Committed.
	int tm_tacks;		//Tackles attempted.
	int tm_twon;		//Tackles won.
	int tm_shots;		//Shots attempted.
	int tm_saved;		//Shots saved.
	int tm_goals;		//Goals scored.
	int tm_pass;		//Passes attempted.
	int tm_pwon;		//Passes completed.
	int tm_inj;			//Injury type.
	int tm_posst;		//Time in possession.

// Animation Data...
	int tm_spr, turn_dir, face_dir, dir_mode;
	float tm_anim, tm_frm, tm_fstep;
	unsigned char tm_hcol,tm_htype;
	float tm_mcspd;
	float ls_anim,ls_frm;
	float contact;
	char tm_newanim;

// Action Data...
	int tm_act, tm_poss, tm_wall, tm_leave, tm_mark;
	int go_dist, go_cnt;
	float go_txdis,go_tydis,go_tx,go_ty,go_xoff,go_yoff,tm_jump;
	char go_step;

// Player Intelligence...
	int int_move, int_cnt, mess_num, mess_cnt;
	int tm_comm,tm_ccnt;
};

extern match_player teams[22];

struct officials {
	float x,y,z,dir_x,dir_y,anim,frm,fstep,goto_x,goto_y;
	int act,go;
	char newanim;

};

extern officials refs[3];
extern char offside_now;
extern char can_be_offside;
extern char offside_on;

extern int ref_accuracy;
extern int ref_strictness;
extern int ref_wait;

extern int tussle_tab[8];
extern int *tussle_ptr;

/******************************************************************************
******************************************************************************/

// FUNCTIONS

/******************************************************************************
******************************************************************************/

// DISPLAY.CPP

extern void grid_map();
extern void line_border(int x,int y,int wid,int hgt,int col);
extern void draw_buttons();
extern void light_button(int b);
extern void unlight_button(int b);
extern void conv_xypitch(float x, float y, int *screen_x, int *screen_y);
extern void pitch_markings();
extern void draw_pitch();
extern void pitch_plot(int x,int y,int z,char c,char a);		//Place screen coords on plot buffer.
extern void draw_buffer();
extern void draw_ball();
extern void draw_team();
extern void panel_data();
extern void faster();
extern void slower();
extern void show_nums();
extern void frame_count();
extern void frame_count_i();
extern void init_pitch_sprites();
extern void add_pitch_sprite(short x,short y,short z,short ref);


// ACTIONS.CPP

extern void fire_ball_off();
extern float actual_spd(match_player *player);
extern float angle_to_xy(float a,float b,float x,float y);
extern void user_conts(match_player *player);
extern void init_anim(match_player *player,int anim);
extern void init_team();
extern void init_officials();
extern void user_set_piece(match_player *player);
extern void init_stand_act(match_player *player);
extern void init_kick_act(match_player *player,int mc,float pc);
extern void kick_action(match_player *player);
extern void init_steal_act(match_player *player);
extern void init_kphold_act(match_player *player);
extern void init_throw_act(match_player *player);
extern void turn_clock(match_player *player);
extern void turn_anti(match_player *player);
extern void turn_action(match_player *player);
extern void throw_action(match_player *player);
extern void init_turn_act(match_player *player);
extern void init_jump_act(match_player *player,char dir,char ride=FALSE);
extern void init_run_act(match_player *player,float tx,float ty,char s);
extern void init_fall(match_player *player);
extern void init_tackle_act(match_player *player,float tx,float ty);
extern void go_toward_target(match_player *player);
extern void dont_run_off(match_player *player);
extern void stand_action(match_player *player);
extern void steal_action(match_player *player);
extern void kphold_action(match_player *player);
extern void run_action(match_player *player);
extern void tackle_action(match_player *player);
extern void fall_action(match_player *player);
extern void process_teams();
extern void user_init_tackle(match_player *player);
extern void init_save_act(match_player *player,int tx,int ty,int tz,int an,int zone,int bp,int cont);
extern void taker_pass_f(float x,float y);
extern void taker_pass_h(float x,float y);
extern void taker_tee_up(float x,float y);
extern void taker_shoot_d(float x,float y);
extern void taker_shoot(float x,float y);
extern void taker_punt(float x,float y);

// BALL.CPP

extern float get_angle(float x,float y,float d);
extern void get_xydis_from_ang(float a,float d);
extern float get_s_angle(float z,float d);
extern void get_zdis_from_ang(float a,float d);
extern void stop_ball_spin();
extern void add_spin_fx();
extern void move_ball();
extern void grav_ball();
extern void ball_friction();
extern void ball_trajectory();
extern void get_ball_zone();
extern void launch_ball(int p);
extern void reset_ball();
extern void respot_ball();
extern void pitch_bounds();
extern void hit_goal_post();
extern void hit_cross_bar();
extern void hit_high_side_net();
extern void hit_low_side_net();
extern void hit_top_net();
extern void hit_inside_back_net();
extern void hit_inside_back_net_r();
extern void hit_inside_top_net();
extern void hit_inside_high_side();
extern void hit_inside_low_side();
extern void go_left_goal();
extern void go_right_goal();
extern void ball_collision();
extern void get_ball_speed();
extern void ball_limbo(int p,float c);
extern void process_ball();
extern void own_goal();
extern void good_goal();
extern void new_shot(int p);
extern void reset_shot();


// BALLINT.CPP

extern void rebound_off_plr(match_player *player);
extern void hold_ball(match_player *player);
extern void collect_ball(match_player *player);
extern void put_spin_on_ball(int power);
extern void control_difficulty(match_player *player);
extern void control_ball(match_player *player);
extern void ball_interact(match_player *player);
extern void predict_ball();
extern void get_opp_near_ball(int holder);
extern void player_distances();
extern int get_nearest_guy(int p_num);
extern void get_nearest();
extern void holder_lose_ball();


// INTELL.CPP

extern int in_kicking_range(match_player *player,float x,float y);
extern void process_speech();
extern void init_speech(int p,int comm,int t=FALSE);
extern void keeper_boxes();
extern void reset_ideas(match_player *player);
extern void reset_all_ideas();
extern int shall_i_turn(match_player *player,float x,float y,char s);
extern void go_to_path(int p_num,char header_only=FALSE);
extern void get_tack_path(match_player *player);
extern void get_target(char flag,int bz,int zx,int zy,int pn,int &x,int &y,int tac[(32*2)+6][10][2]);
extern void find_zonal_target(match_player *player,float px,float py);
extern int get_near_path(int p_num,int not_busy);
extern void get_face_xy(int d,float &x,float &y);
extern void forward_joystick(match_player *p,float &x,float &y);
extern int get_dir(float x,float y);
extern int angle_of_vis(match_player *player,int x,int y,float d,char cross);
extern void get_opp_dir_tab(int pnum);
extern int opp_around(int x,int y,int pnum);
extern void player_ints(match_player *player);
extern void pass_ball(int ps,char cross);
extern void make_pass(match_player *player,int p,char cross);
extern void dribble_dir(match_player *player,float &x,float &y);
extern void go_dribble(match_player *player,float x,float y);
extern void make_run(match_player *player);
extern int run_decide(match_player *player);
extern int punt_decide(match_player *player);
extern int head_punt_decide(match_player *player);
extern void make_punt(match_player *player);
extern void punt_ball(match_player *player);
extern void make_shoot(match_player *player);
extern void shoot_ball(match_player *player);
extern int shoot_decide(match_player *player);
extern int head_shoot_decide(match_player *player);
extern void set_pos_flags(match_player *player);
extern int pass_decide(match_player *player,char cross);
extern void player_comment(match_player *player);
extern void tackle_decide(match_player *player);
extern void steal_decide(match_player *player);
extern void block_decide(match_player *player);
extern void free_ball(match_player *player);
extern void out_of_vis(match_player *player);
extern void got_ball(match_player *player);
extern void we_have_ball(match_player *player);
extern int in_close(match_player *player);
extern int can_close_down(match_player *player);
extern void close_him_down(match_player *player);
extern void force_error(match_player *player);
extern void forceful_retrieve(match_player *player);
extern int facing_opp_side(match_player *player);
extern void go_to_between(int p_num);
extern int facing_opp_back(match_player *player);
extern void opp_has_ball(match_player *player);
extern void intelligence(match_player *player);
extern void user_intelligence(match_player *player);
extern void override(match_player *player);
extern void process_comments();
extern void rotate_offs(int an,float &x,float &y,float &z,float nx,float ny);


// MATHS.CPP

extern void af_randomize();
extern float calc_dist(float x,float y);
extern int rand_range(int range);


// USER.CPP

extern void reselect();
extern void select_users();
extern void auto_select_a(short u);
extern void auto_select_b(short u);
extern void clear_all_autos();
extern void user_xy(char u);
extern void convert_inputs();
extern void go_button();
extern void mouse_fired();
extern void process_butts();
extern short user_taker_a(short p);
extern short user_taker_b(short p);
extern void reselect_all_users();


// 3D_UPDT.CPP

extern void realtime_coords();
extern void process_replay();
extern void new_update_coords();
extern void update_3d();
extern void init_3d();
extern void info_line();
extern void process_pitch_sprs();

extern float cth,sth;			// Current viewing angle...

// RULES.CPP

extern void retake_foul();
extern void match_rules();
extern void process_offs();
extern void init_match_mode();
extern void init_foul(int fouler,char direct,char see=FALSE);
extern void init_offside(match_player *player);
extern char bounds_rules();

// TEST.CPP
extern void stop_mf_time();

// KEYH.C
extern void	claim_key_int(void);
extern void	release_key_int(void);

// MY_AUDIO.CPP
void play_fx(int fx,float x,float y);

// NETWORK.C
extern "C" void read_joystick(char j,int *x, int *y, int *sw);
extern "C" void read_joy1(int *x, int *y, int *sw);
extern "C" void read_joy2(int *x, int *y, int *sw);
extern "C" void calibrate_joy(char j,unsigned short *x,unsigned short *y);
extern "C" void get_joy_dir1(int *x,int *y,int *f);
extern "C" void get_joy_dir2(int *x,int *y,int *f);
extern "C" void get_user_inputs();
extern "C" void process_user_inputs();

extern "C" volatile int Teams[MAX_USERS],Players[MAX_USERS];
extern "C" volatile int net_quit;
extern "C" volatile char paused;
extern "C" volatile char pause_request;
extern "C" volatile char keys[256];
extern "C" volatile char key_togs[256];

extern "C" void NetTest(void);
extern "C" void Network_Play_Ready();
extern "C" void Quit_Network_Play();
extern "C" void End_Network_Game();

extern "C" void __far nethandler(void);
extern "C" unsigned int NetworkHandle;
extern "C" short wConsoleNode;
extern "C" volatile int network_on;
extern "C" volatile int count;
extern "C" volatile int tick;
extern "C" volatile int ftick;



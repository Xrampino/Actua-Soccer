// Prototypes for ADDEXT.C
void add_extension(char *filename,char *extension);
void strip_extension(char *name);
void extract_filename(char *dest, char *fullname);
void extract_path(char *dest, char *fullname);
int check_exe_name(char *real, char *exp);

// Prototypes for CAL.C
char day_of_week(int d, int m, int y);
int days_until(int d, int m, struct tm tm);
char *curdate(char flag);
char *curtime(char flag);

// Prototypes for DOSMEM.C
unsigned char *DOSalloc(unsigned int size, signed short *selector);
void DOSfree(signed short sel);
void real_mode(int number, struct rminfo *rmi);

// Prototypes for FINDDEF.c
unsigned char find_def(char *def, char *value, FILE *fp);

// Prototypes for FONT.C

// Prototypes for GETENV.C
unsigned char get_env_or_default(char *name, char *storage, char *v_default);

// Prototypes for TIME.C
void reltime(int num, char *dest);

// Prototypes for MOUSE.C
void report_mouse(mouse_struct *info);
short init_mouse(void);
void limit_mouse(short xs, short ys, short xe, short ye);
void set_mouse_position(mouse_struct *info);

// Prototypes for TEXT.C
void up_line(void);
void goxy(int x, int y);
void getxy(int *x, int *y);
void cursor_position_routine(u_char flag);
void bottom_line(void);
void get_row_cols(u_char *cols, u_char *rows);
void scroll_window(u_char flag, u_char x1, u_char y1, u_char x2, u_char y2, u_char lines);
void scroll_up(u_char no_lines);
void scroll_down(u_char no_lines);
void write_string(u_char *string, u_char attrs);
void cls(void);

// Prototypes for VESA.C
int VESAget_mode_list(void);
void VESAclosedown(void);
unsigned char VESAget_mode_info(unsigned short scrmode);
unsigned char VESAinit(void);
int VESAfind_mode(int x, int y, int bits);
void VESAget_granularity(int mode);

// Prototypes for VIDEO.C
unsigned short GetVideoMode(void);

// Prototypes for IEEE.C
# define FloatToUnsigned(f)      ((unsigned long)(((long)(f - 2147483648.0)) + 2147483647L) + 1)
void ConvertToIeeeExtended(double num, char *bytes);

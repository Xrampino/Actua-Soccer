
CGL_VERTEX2D_ST Vertex[1];
CGL_VERTEX2D_ST lVertex[1];
CGL_TEXTURE2D_ST Texture[1];
CGL_COLOR_ST Colour[1];
CGL_COLOR_ST lColour[1];
int MapAddress3DB;

int Init3DB(int *scrmode) {return(-1);};
int Close3DB() {return(-1);};
int ChangeScreenMode3DB(int *scrmode) {return(-1);};
int SetPalette3DB(unsigned char *palette) {return(-1);};
void ClearBuffer3DB() {};
void SwapBuffer3DB() {};
int LoadTexture3DB(char *map,int bwid,int wid,int hgt) {return(-1);};
void SetPerspTextureQuadOutput3DB(int TextureAddr) {};
void SetTextureQuadOutput3DB(int TextureAddr) {};
void SetRectangleOutput3DB(int TextureAddr) {};
void SetRectangleOutput3DBx(int TextureAddr) {};
void SetFlatQuadOutput3DB() {};
void SetLineOutput3DB() {};
void Render3DB(int vertices) {};


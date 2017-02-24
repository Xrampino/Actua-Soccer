BOOL	gssCommsSetType(int type);											//0 = net, 1 = serial, 2 = modem
W32	gssCommsGetType(void);
void	gssCommsSetComPort(int port);										//1,2,3,4
void	gssCommsSetComBaudRate(int baud);
void	gssCommsSetCommandBase(unsigned base);
int	gss16550(int port);


W32	gssCommsInitSystem(W32 maxnodes);
W32	gssCommsUnInitSystem(void);
BOOL	gssCommsGetNetworkAddr(_NETNOW_NODE_ADDR * sNodeAddr);
W32	gssCommsNetAddrToNode(_NETNOW_NODE_ADDR * sNodeAddr);
W32	gssCommsGetActiveNodes(void);
W32	gssCommsGetConsoleNode(void);
W32	gssCommsAddNode(_NETNOW_NODE_ADDR * sNode);
W32	gssCommsDeleteNode(W32 wNode);
void	gssCommsSortNodes(void);
BOOL	gssCommsPostListen(void);
BOOL	gssCommsSendData(PSTR pheader,W32 hsize,PSTR pdata,W32 dsize,W32 wNode);
BOOL	gssCommsGetData(PSTR pHeader,W32 wHSize,PSTR pData, W32 wDSize);
BOOL	gssCommsGetHeader(PSTR	pHeader,W32	wHSize,PSTR * pPacket);
void	gssCommsGetBlock(PSTR pPacket,PSTR pData,W32 wDSize);


extern int	gssreadchar(void);
extern int	gsswritechar(int val);
extern int	gsstxfree(void);
extern int	gssrxused(void);
extern int	gsstxused(void);
extern int	gssrxfree(void);
extern	void	gssclrtx(void);
extern	void	gssclrrx(void);

enum	{gssNORESPONSE=-1,gssOK,gssCONNECT,gssRING,gssNOCARRIER,gssERROR,gssNODIALTONE,gssBUSY,gssNOANSWER};

void	gssModemInit(char * string);
void	gssModemDial(char * string,int tone);						//if (tone) tone dialling else pulse dialling
void	gssModemHangUp(void);
void	gssModemAnswer(void);
int	gssModemCheckResponse(void);
char	*	gssModemGetReturnString(int val);



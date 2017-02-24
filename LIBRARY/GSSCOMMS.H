BOOL	gssCommsSetType(int type);											//0 = net, 1 = serial, 2 = modem
WORD	gssCommsGetType(void);
void	gssCommsSetComPort(int port);										//1,2,3,4
void	gssCommsSetComBaudRate(int baud);
int	gss16550(int port);


WORD	gssCommsInitSystem(WORD maxnodes);
WORD	gssCommsUnInitSystem(void);
BOOL	gssCommsGetNetworkAddr(_NETNOW_NODE_ADDR * sNodeAddr);
WORD	gssCommsNetAddrToNode(_NETNOW_NODE_ADDR * sNodeAddr);
WORD	gssCommsGetActiveNodes(void);
WORD	gssCommsGetConsoleNode(void);
WORD	gssCommsAddNode(_NETNOW_NODE_ADDR * sNode);
WORD	gssCommsDeleteNode(WORD wNode);
void	gssCommsSortNodes(void);
BOOL	gssCommsPostListen(void);
BOOL	gssCommsSendData(PSTR pheader,WORD hsize,PSTR pdata,WORD dsize,WORD wNode);
BOOL	gssCommsGetData(PSTR pHeader,WORD wHSize,PSTR pData, WORD wDSize);
BOOL	gssCommsGetHeader(PSTR	pHeader,WORD	wHSize,PSTR * pPacket);
void	gssCommsGetBlock(PSTR pPacket,PSTR pData,WORD wDSize);


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
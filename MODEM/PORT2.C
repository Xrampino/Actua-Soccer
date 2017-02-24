int	gss16550(int port)
	{
	int	bases[]={0x3F8,0x2F8,0x3E8,0x2E8};
	int	x;

	port=bases[port-1];
	outp(port+2,7);								//enable FIFO buffer
	x=inp(port+2);
	x &=0xC0;
	if (x)
		return(TRUE);
	else
		return(FALSE);
	}



void makefilter(filter filt,byte fr,byte fg,byte fb,float mr,float mg,float mb)
	{
	word r1,g1,b1,r2,g2,b2;
	word x,s,c,l1,l2,d1,d2;
	if ((l1=sqrt(fr*fr+fg*fg+fb*fb))==0) l1=1;
	for (x=0;x<768;x+=3)	 
		{
		l2=sqrt(pal[x]*pal[x]+pal[x+1]*pal[x+1]+pal[x+2]*pal[x+2]);
		r1=pal[x]+mr*(fr*l2/l1-pal[x]);
		if (r1<0) r1=0;if (r1>255) r1=255;
		g1=pal[x+1]+mg*(fg*l2/l1-pal[x+1]);
		if (g1<0) g1=0;if (g1>255) g1=255;
		b1=pal[x+2]+mb*(fb*l2/l1-pal[x+2]);
		if (b1<0) b1=0;if (b1>255) b1=255;
		r1=(fr-pal[x])*mr+pal[x];
		g1=(fg-pal[x+1])*mg+pal[x+1];
		b1=(fb-pal[x+2])*mb+pal[x+2];
		d1=128;
		for (s=0;s<768-16*3;s+=3)
			{
		 	r2=(pal[s]-r1);
			g2=(pal[s+1]-g1);
			b2=(pal[s+2]-b1);
			d2=sqrt(r2*r2+g2*g2+b2*b2);
			if (d2<d1) d1=d2,c=s;
			}
		filt[x/3]=c/3;
		}
	}


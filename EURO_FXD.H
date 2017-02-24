//****************************************************************************
//****************************************************************************
//
//
// FIXED point class ... a replacement for floats in Actua Soccer
//
//	Format: Fixed (1,19,12)
//
//	NOTES :
//		There is very little range checking at the moment so ...
//
//								BE VERY CAREFUL
//
//	
//
//	Author : P.Rankin
//	Version: 1.00.01.08.95
//
//****************************************************************************
//****************************************************************************

#ifndef ABS
#define ABS(a) (( (a) >= 0 ) ? (a):-(a))
#endif
#ifndef f2L
#define f2L(f)	((fixed)((long)((f)*4096)))
#endif

#define ItoF(f) ((long) (f)*4096)
#define FRACTION                12
#define	HALF_FRACTION		6

extern "C" int  mul_64bit(int,int);
extern "C" int  div_64bit(int,int);

class fixed {
public:
		long	f;
		operator char();
		operator unsigned char();
		operator short();
		operator	int();
  		operator	long();

		fixed();
		fixed( int );
		fixed( long );
                fixed( fixed const & );

//		fixed &operator = ( double );
		fixed &operator = ( fixed const & );
//		fixed &operator = ( float  );
		fixed &operator = ( long   );
		fixed &operator = ( int   );
		fixed &operator = ( short    );


		fixed &operator += ( fixed const & );
		fixed &operator += ( long );
		fixed &operator += ( int );
		fixed &operator += ( short );
		fixed &operator -= ( fixed const & );
		fixed &operator -= ( long );
		fixed &operator -= ( int );
		fixed &operator -= ( short );
		fixed &operator *= ( fixed const & );
		fixed &operator *= ( long );
		fixed &operator *= ( int );
		fixed &operator *= ( short );
		fixed &operator /= ( fixed const & );
		fixed &operator /= ( int );
		fixed &operator /= ( short );
		fixed &operator >>= ( int );
		fixed &operator <<= ( int );

		fixed operator + () const;
		fixed operator - () const;

};

fixed operator * ( fixed const &, fixed const &);
fixed operator * ( fixed const &, int);
fixed operator * ( fixed const &, short);
fixed operator * ( fixed const &, long);
fixed operator * ( int   , fixed const & );
fixed operator * ( short , fixed const & );
fixed operator * ( long , fixed const &);

fixed operator + ( fixed const &, fixed const &);
fixed operator + ( fixed const &, long);
fixed operator + ( fixed const &, int);
fixed operator + ( fixed const &, short);
fixed operator + ( long __f1 , fixed const &__f0 );
fixed operator + ( int , fixed const & );
fixed operator + ( short , fixed const & );


fixed operator - ( fixed const &, fixed const &);
fixed operator - ( fixed const &, long);
fixed operator - ( fixed const &, int);
fixed operator - ( fixed const &, short);
fixed operator - ( long   ,fixed const &);
fixed operator - ( int   ,fixed const &);
//fixed operator - ( short ,fixed const &);


fixed operator / ( fixed const &, fixed const &);
fixed operator / ( fixed const &, long);
fixed operator / ( fixed const &, int);
fixed operator / ( fixed const &, short);
fixed operator / ( long , fixed const & );
fixed operator / ( int , fixed const & );

int operator == ( fixed const &, fixed const & );
int operator == ( fixed const &, int );
int operator == ( fixed const &, short );
int operator == ( int ,fixed const & );
int operator == ( short  ,fixed const & );

int operator != ( fixed const &, fixed const & );
int operator != ( fixed const &, int );
int operator != ( fixed const &, short );
int operator != ( int ,fixed const & );
int operator != ( short  ,fixed const & );

int operator < ( fixed const &, fixed const & );
int operator < ( fixed const &, long );
int operator < ( fixed const &, int );
int operator < ( fixed const &, short );
int operator < ( long , fixed const & );
int operator < ( int ,fixed const & );
int operator < ( short  ,fixed const & );

int operator > ( fixed const &, fixed const & );
int operator > ( fixed const &, long );
int operator > ( fixed const &, int );
int operator > ( fixed const &, short );
int operator > ( long , fixed const & );
int operator > ( int ,fixed const & );
int operator > ( short  ,fixed const & );

int operator <= ( fixed const &, fixed const & );
int operator <= ( fixed const &, long );
int operator <= ( fixed const &, int );
int operator <= ( fixed const &, short );
int operator <= ( int ,fixed const & );
int operator <= ( short  ,fixed const & );

int operator >= ( fixed const &, fixed const & );
int operator >= ( fixed const &, long );
int operator >= ( fixed const &, int );
int operator >= ( fixed const &, short );
int operator >= ( int ,fixed const & );
int operator >= ( short  ,fixed const & );




//****************************************************************************
//
//	Constructors
//
//****************************************************************************

inline fixed::fixed() {
}

inline fixed::fixed( int __f0 ) {
		f = __f0 << FRACTION;
}

inline fixed::fixed( long __f0 ) {
		f = __f0 ;
}

inline fixed::fixed( fixed const &__f0 ) {
		f = __f0.f;
}


//****************************************************************************
//
//	Casts
//
//****************************************************************************

inline fixed:: operator char() {
	return( f>>FRACTION );
}

inline fixed:: operator unsigned char() {
	return( f>>FRACTION );
}
inline fixed:: operator short() {
	return( f>>FRACTION );
}

inline fixed:: operator int() {
	return( f>>FRACTION );
}

inline fixed:: operator long() {
	return( f );
}

//****************************************************************************
//
//	=
//
//****************************************************************************

inline fixed &fixed:: operator =(fixed const &__d) {
		f = (long) ( __d.f );
			return(*this);
}

inline fixed &fixed:: operator =(int __d) {
		f = ( ItoF(__d) );
			return(*this);
}

inline fixed &fixed:: operator =(long __d) {
		f = ( (__d) );
			return(*this);
}


inline fixed &fixed:: operator =(short __d) {
		f = ( ItoF(__d) );
			return(*this);
}

//****************************************************************************
//
//	*
//
//****************************************************************************

inline fixed operator * ( fixed const &__f0, fixed const &__f1 ) {
	return((long)mul_64bit(__f0.f,__f1.f));
}

inline fixed operator * ( fixed const &__f0, long __f1 ) {
	return((long)mul_64bit(__f0.f,__f1));
}

inline fixed operator * ( fixed const &__f0, int __f1 ) {
	return( ((long)(__f0.f)) * __f1 );
}

inline fixed operator * ( fixed const &__f0, short __f1 ) {
	return( ((long)(__f0.f)) * __f1 );
}

inline fixed operator * (  int __f1 , fixed const &__f0) {
	return( ((long)(__f0.f)) * __f1 );
}

inline fixed operator * (  short __f1 , fixed const &__f0) {
	return( ((long)(__f0.f)) * __f1 );
}

inline fixed operator * (  long __f1  , fixed const &__f0) {
	return((long)mul_64bit(__f1,__f0.f));
}

//****************************************************************************
//
//	+
//
//****************************************************************************

inline fixed operator + ( fixed const &__f0, fixed const &__f1 ) {
	return( __f0.f + __f1.f );
}

inline fixed operator + ( fixed const &__f0, long __f1 ) {
	return( __f0.f + ((long)__f1) );
}

inline fixed operator + ( fixed const &__f0, int __f1 ) {
	return( __f0.f + (((long)__f1)<<FRACTION) );
}

inline fixed operator + ( fixed const &__f0, short __f1 ) {
	return( __f0.f + (((long)__f1)<<FRACTION) );
}

inline fixed operator + ( long __f1 , fixed const &__f0 ) {
	return( __f0.f + ((long)__f1) );
}

inline fixed operator + ( int __f1 , fixed const &__f0 ) {
	return( __f0.f + (((long)__f1)<<FRACTION) );
}

inline fixed operator + ( short __f1 , fixed const &__f0 ) {
	return( __f0.f + (((long)__f1)<<FRACTION) );
}

//****************************************************************************
//
//	-
//
//****************************************************************************

inline fixed operator - ( fixed const &__f0, fixed const &__f1 ) {
	return( __f0.f - __f1.f );
}

inline fixed operator - ( fixed const &__f0, long __f1 ) {
	return( __f0.f - (((long)__f1)) );
}

inline fixed operator - ( fixed const &__f0, int __f1 ) {
	return( __f0.f - (((long)__f1)<<FRACTION) );
}

inline fixed operator - ( fixed const &__f0, short __f1 ) {
	return( __f0.f - (((long)__f1)<<FRACTION) );
}

inline fixed operator - ( long __f1 , fixed const &__f0 ) {
	return( ( (((long)__f1)) - __f0.f ) );
}

inline fixed operator - ( int __f1 , fixed const &__f0 ) {
	return( ( (((long)__f1)<<FRACTION) - __f0.f ) );
}

/*
inline fixed operator - ( short __f1 , fixed const &__f0 ) {
	return( (((long)__f1)<<FRACTION) - __f0.f ) );
}
*/

//****************************************************************************
//
//	/
//
//****************************************************************************

inline fixed operator / ( fixed const &__f0, fixed const &__f1 ) {
	if(__f1.f!=0)
		return((long)div_64bit(__f0.f,__f1.f));
	else
		return(__f0);

#if	0
	if(( __f0.f <= 0x3ffff )&&(__f0.f >= -0x3ffff))
		{
		if(__f1.f!=0)
			return ( ( (__f0.f << FRACTION) / __f1.f ) );
		else
			return ( __f0.f );
		}
	else			
		{
		if(ABS(__f1.f) < (long)64 )
			return ( __f0.f );
		else
			return ( ( __f0.f / (__f1.f>>HALF_FRACTION) ) <<HALF_FRACTION );
		}
#endif
}

inline fixed operator / ( fixed const &__f0, long __f1 ) {
	if(( __f0.f < 0x3ffff )&&(__f0.f > -0x3ffff))
		return ( ( (__f0.f << FRACTION) / __f1 ) );
	else
		return ( ( __f0.f / (__f1>>HALF_FRACTION) ) <<HALF_FRACTION );
}

inline fixed operator / ( fixed const &__f0, int __f1 ) {
		return ( ( __f0.f / __f1 ) );
}

inline fixed operator / ( fixed const &__f0, short __f1 ) {
		return ( ( __f0.f / __f1 ) );
}

inline fixed operator / ( long __f0 , fixed const &__f1 ) {
	if(__f1.f!=0)
		return((long)div_64bit(__f0,__f1.f));
	else
		return(__f0);

#if	0
	if(( __f0 < 0x3ffff )&&(__f0 > -0x3ffff))
		return ( ( (__f0 << FRACTION) / __f1.f ) );
	else
		return ( ( __f0 / (__f1.f>>HALF_FRACTION) ) <<HALF_FRACTION );
#endif
}

inline fixed operator / ( int __f0 , fixed const &__f1 ) {
	if(__f1.f!=0)
		return((long)div_64bit(__f0 << FRACTION,__f1.f));
	else
		return(__f0);

#if	0
	if(( __f0 <= 0x7f )&&(__f0 >= -0x7f))
		{
		if( __f1.f != 0 )
			return ( ( (__f0 << (2*FRACTION)) / __f1.f ) );
		else
			return ( __f0 );
		}
	else
		{
		if(ABS(__f1.f)< (long)64 )
			return ( __f0 );
		else
			return ( ( (__f0 << FRACTION) / (__f1.f>>HALF_FRACTION) ) <<HALF_FRACTION );
		}
#endif
}


//****************************************************************************
//
//	+=
//
//****************************************************************************

inline fixed &fixed::operator += ( fixed const &__cv ) {
	f += __cv.f;
	return ( *this );
}

inline fixed &fixed::operator += ( long __cv ) {
	f += ( __cv );
	return ( *this );
}

inline fixed &fixed::operator += ( int __cv ) {
	f += ( __cv<<FRACTION );
	return ( *this );
}

inline fixed &fixed::operator += ( short __cv ) {
	f += ( __cv<<FRACTION );
	return ( *this );
}

//****************************************************************************
//
//	-=
//
//****************************************************************************

inline fixed &fixed::operator -= ( fixed const &__cv ) {
	f -= __cv.f;
	return ( *this );
}

inline fixed &fixed::operator -= ( long __cv ) {
	f += ( __cv );
	return ( *this );
}

inline fixed &fixed::operator -= ( int __cv ) {
	f -= ( __cv<<FRACTION );
	return ( *this );
}

inline fixed &fixed::operator -= ( short __cv ) {
	f -= ( __cv<<FRACTION );
	return ( *this );
}

//****************************************************************************
//
//	*=
//
//****************************************************************************


inline fixed &fixed::operator *= ( fixed const &__cv ) {
	f = (f >> HALF_FRACTION ) * (__cv.f >> HALF_FRACTION);
	return ( *this );
}

inline fixed &fixed::operator *= ( long __cv ) {
	f = (f >> HALF_FRACTION ) * (__cv >> HALF_FRACTION);
	return ( *this );
}
inline fixed &fixed::operator *= ( int __cv ) {
	f *= ( __cv );
	return ( *this );
}

inline fixed &fixed::operator *= ( short __cv ) {
	f *= ( __cv );
	return ( *this );
}


//****************************************************************************
//
//	/=
//
//****************************************************************************


inline fixed &fixed::operator /= ( fixed const &__cv ) {
	if(ABS(__cv.f)<64)
		return (*this);
	else
		f = ( ( f / (__cv.f>>HALF_FRACTION) ) <<HALF_FRACTION );
	return( *this );
}

inline fixed &fixed::operator /= ( int __cv ) {
	if(f!=0)
		f /= ( __cv );
	return ( *this );
}

inline fixed &fixed::operator /= ( short __cv ) {
	if(f!=0)
		f /= ( __cv );
	return ( *this );
}


//****************************************************************************
//
//	<< >> <<= >>=
//
//****************************************************************************

#if	0
inline int operator << ( int __i ) {
//        f = f << __i;
        return ( f<<__i );
}
#endif

inline fixed &fixed::operator <<= ( int __i ) {
	f <<= __i;
	return ( *this );
}

#if	0
inline int operator >> ( int __i ) {
//        f = f >> __i;
        return (f >>__i );
}
#endif

inline fixed &fixed::operator >>= ( int __i ) {
	f >>= __i;
	return ( *this );
}



inline fixed fixed::operator + () const {
	return( *this );
}

inline fixed fixed::operator - () const {
	return( -f );
}

//****************************************************************************
//
// Conditionals
//
//		==
//
//****************************************************************************

inline int operator == ( fixed const &__f0, fixed const &__f1 ) {
	return ( __f0.f == __f1.f );
}

inline int operator == ( fixed const &__f0, int __f1 ) {
        return ( __f0.f == (__f1<<FRACTION) );
}

inline int operator == ( fixed const &__f0, short __f1 ) {
        return ( __f0.f == (__f1<<FRACTION) );
}

inline int operator == ( int __f1 , fixed const &__f0 ) {
        return ( __f0.f == (__f1<<FRACTION) );
}

inline int operator == ( short __f1 , fixed const &__f0 ) {
        return ( __f0.f == (__f1<<FRACTION) );
}


//****************************************************************************
//
//	!=
//
//****************************************************************************

inline int operator != ( fixed const &__f0, fixed const &__f1 ) {
	return ( __f0.f != __f1.f );
}

inline int operator != ( fixed const &__f0, int __f1 ) {
        return ( __f0.f != (__f1<<FRACTION) );
}

inline int operator != ( fixed const &__f0, short __f1 ) {
        return ( __f0.f != (__f1<<FRACTION) );
}

inline int operator != ( int __f1 , fixed const &__f0 ) {
        return ( __f0.f != (__f1<<FRACTION) );
}

inline int operator != ( short __f1 , fixed const &__f0 ) {
        return ( __f0.f != (__f1<<FRACTION) );
}


//****************************************************************************
//
//	<
//
//****************************************************************************

inline int operator < ( fixed const &__f0, fixed const &__f1 ) {
	return ( __f0.f < __f1.f );
}

inline int operator < ( fixed const &__f0, long __f1 ) {
	return ( __f0.f < __f1 );
}

inline int operator < ( fixed const &__f0, int __f1 ) {
	return ( (__f0.f) < (__f1<<FRACTION) );
}

inline int operator < ( fixed const &__f0, short __f1 ) {
	return ( (__f0.f) < (__f1<<FRACTION) );
}

inline int operator < ( long __f1 , fixed const &__f0 ) {
	return ( __f1 < __f0.f  );
}

inline int operator < ( int __f1 , fixed const &__f0 ) {
	return ( (__f1<<FRACTION) < (__f0.f) );
}

inline int operator < ( short __f1 , fixed const &__f0 ) {
	return ( (__f1<<FRACTION) < (__f0.f) );
}

//****************************************************************************
//
//	>
//
//****************************************************************************

inline int operator > ( fixed const &__f0, fixed const &__f1 ) {
	return ( __f0.f > __f1.f );
}

inline int operator > ( fixed const &__f0, long __f1 ) {
	return ( __f0.f > __f1 );
}

inline int operator > ( fixed const &__f0, int __f1 ) {
	return ( (__f0.f) > (__f1<<FRACTION) );
}

inline int operator > ( fixed const &__f0, short __f1 ) {
	return ( (__f0.f) > (__f1<<FRACTION) );
}

inline int operator > ( long __f1 , fixed const &__f0 ) {
	return ( __f1 > __f0.f );
}

inline int operator > ( int __f1 , fixed const &__f0 ) {
	return ( (__f1<<FRACTION) > (__f0.f) );
}

inline int operator > ( short __f1 , fixed const &__f0 ) {
	return ( (__f1<<FRACTION) > (__f0.f) );
}

//****************************************************************************
//
//	<=
//
//****************************************************************************

inline int operator <= ( fixed const &__f0, fixed const &__f1 ) {
	return ( __f0.f <= __f1.f );
}

inline int operator <= ( fixed const &__f0, long __f1 ) {
	return ( __f0.f <= __f1 );
}

inline int operator <= ( fixed const &__f0, int __f1 ) {
	return ( (__f0.f) <= (__f1<<FRACTION) );
}

inline int operator <= ( fixed const &__f0, short __f1 ) {
	return ( (__f0.f) <= (__f1<<FRACTION) );
}

inline int operator <= ( int __f1 , fixed const &__f0 ) {
	return ( (__f1<<FRACTION) <= (__f0.f) );
}

inline int operator <= ( short __f1 , fixed const &__f0 ) {
	return ( (__f1<<FRACTION) <= (__f0.f) );
}


//****************************************************************************
//
//	>=
//
//****************************************************************************

inline int operator >= ( fixed const &__f0, fixed const &__f1 ) {
	return ( __f0.f >= __f1.f );
}

inline int operator >= ( fixed const &__f0, long __f1 ) {
	return ( __f0.f >= __f1 );
}

inline int operator >= ( fixed const &__f0, int __f1 ) {
	return ( (__f0.f) >= (__f1<<FRACTION) );
}

inline int operator >= ( fixed const &__f0, short __f1 ) {
	return ( (__f0.f) >= (__f1<<FRACTION) );
}

inline int operator >= ( int __f1 , fixed const &__f0 ) {
	return ( (__f1<<FRACTION) >= (__f0.f) );
}

inline int operator >= ( short __f1 , fixed const &__f0 ) {
	return ( (__f1<<FRACTION) >= (__f0.f)  );
}





#if	0

inline Complex conj( Complex const &__cv ) {
    return Complex( __cv.real(), -__cv.imag() );
}

inline double Complex::real() const {
    return( __r );
}

inline double real( Complex const &__cv ) {
    return( __cv.real() );
}

inline double norm( Complex const &__cv ) {
		return( __cv.real() * __cv.real() + __cv.imag() * __cv.imag() );
}

double  abs  ( Complex const & );	    // magnitude of vector
Complex acos ( Complex const & );	    // arccosine
Complex acosh( Complex const & );	    // hyperbolic arccosine
double  arg  ( Complex const & );	    // angle of vector
Complex asin ( Complex const & );	    // arcsin
Complex asinh( Complex const & );	    // hyperbolic arcsin
Complex atan ( Complex const & );	    // arctangent
Complex atanh( Complex const & );	    // hyperbolic arctangent
Complex conj ( Complex const & );	    // conjugate
Complex cos  ( Complex const & );	    // cosine
Complex cosh ( Complex const & );	    // hyperbolic cosine
Complex exp  ( Complex const & );	    // e raised to a power
double  imag ( Complex const & );	    // imaginary part
Complex log  ( Complex const & );	    // log base e
Complex log10( Complex const & );	    // log base 10
double  norm ( Complex const & );	    // square of magnitude
Complex polar( double __mag,
				 double __angle = 0 );	    // polar to Complex
Complex pow  ( Complex const &__base,	    // Complex ** Complex
				 Complex const &__power );
Complex pow  ( Complex const &__base,	    // Complex ** double
				 double         __power );
Complex pow  ( double	      __base,	    // double ** Complex
				 Complex const &__power );
Complex pow  ( Complex const &__base,	    // Complex ** int
				 int            __power );
double  real ( Complex const & );	    // real part
Complex sin  ( Complex const & );	    // sin
Complex sinh ( Complex const & );	    // hyperbolic sin
Complex sqrt ( Complex const & );	    // square root
Complex tan  ( Complex const & );	    // tan
Complex tanh ( Complex const & );	    // hyperbolic tangent

#endif


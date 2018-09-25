#include "simple_complex.h"
#define _PI_ (3.141592653589793)

//2 db sajat fuggveny:

namespace scomplex
{

// komplex szam abszoluterteket meghatarozo fuggveny:
	double COMPLEX::AbszolutErtek(const COMPLEX& z)
	{
		return sqrt( z.re * z.re + z.im * z.im );
	}



//komplex szam 2db negyzetgyoke kozul az egyiket szolgaltato fuggveny:

//a Laguerre modszer kepleteiben szukseg van komplex szam negyzetgyokenek meghatarozasara,
//az ott szereplo keplet viszont kezeli a +- elojelet, (origo koroli 180 fokos forgatas azaz origora valo tukrozes)
//igy itt elegendo az egyik negyzetgyok meghatarozasa
 
	COMPLEX COMPLEX::NegyzetGyok(const COMPLEX& z)
	{
		double x;
		double y;			
		double Fi;
		double hossz;
		
		hossz = AbszolutErtek(z);
		Fi = acos(z.re / hossz);
		
		if(z.im < 0)
		{
			Fi = 2*_PI_ - Fi;
		}
		
		Fi = Fi / 2;
		hossz = sqrt(hossz);
		
		x = hossz * cos(Fi);
		y = hossz * sin(Fi);
		
		COMPLEX gyok(x,y);
		
		return gyok;			
	}
}
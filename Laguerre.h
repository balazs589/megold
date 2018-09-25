#ifndef LAGUERRE_H
#define LAGUERRE_H

#include "simple_complex.h"
#include "Polinom.h"

/*********************************************************************************/
//Laguerre modszert megvalosito fuggvenyt magaba foglalo osztaly
/*********************************************************************************/

namespace megold
{
	class Laguerre
	{
	private:
		Laguerre();
		~Laguerre();
	
	public:
		static scomplex::COMPLEX Lepes(Polinom& cPolinom, scomplex::COMPLEX cZ0);
 	};	
}
#endif
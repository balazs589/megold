#ifndef POLINOM_H
#define POLINOM_H

#include "simple_complex.h"

namespace megold
{
/*********************************************************************************/
//komplex egyutthatos ( N = m_nN - 1) -edfoku polinomokat megvalosito osztaly
// N = 1,2,3,4...
//A feladatban elofordulo pozitiv fokszamu polinomokra vonatkozo muveletek leirasa.
//Hibakezelesek nincsenek megvalositva: pl. negativ fokszam megadasa eseten nem jelez.
/*********************************************************************************/

	class Polinom
	{
	private:
		int m_nN;						//polinom egyutthatoinak szama
		scomplex::COMPLEX* m_pacP;		//polinom egyutthatoit tartalmazo dinamikus tomb
	
	public:
		Polinom();									//
		Polinom(int nN);							//
		Polinom(int nN, scomplex::COMPLEX* pacP);	//
		Polinom(const Polinom& cP);					//
		
		~Polinom();									//
		
		Polinom& operator=(const Polinom& cP);								//polinom = polinom ertekadas
		scomplex::COMPLEX& operator[](const int nIndex);					//polinom egyutthatoinak elerese
		scomplex::COMPLEX operator()(const scomplex::COMPLEX cZ) const;		//polinom behelyettesitesi erteke (cZ) helyen
		Polinom& Derivalt() const;											//polinom derivaltpolinomjat adja
		Polinom& PolinomGyokOsztas(const scomplex::COMPLEX cZ) const;		//(x - cZ) elsofoku polinommal valo osztas utan kapott polinom / cZ az eredeti polinom gyoke /
		int FokSzam() const;												//polinom (akar 0-val egyenlo) egyutthatoinak szama
				
		friend std::ostream& operator<<(std::ostream& out, const Polinom& cP);		//kiiratas
	};
}
#endif
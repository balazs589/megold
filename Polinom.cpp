#include "Polinom.h"

using namespace scomplex;

namespace megold
{
//Polinom osztaly fuggvenyeinek megvalositasa:
//poztiv egyutthatokkal mukodik,
//ertelmetlen adatokkal valo letrehozas esetere hibakezeles nincs megvalositva

	Polinom::Polinom()
	:m_nN(0), m_pacP(NULL)
	{}
	
	Polinom::Polinom(int nN)					// (N = m_nN - 1) -edfoku polinom letrehozasa
	: m_nN(nN)
	{
		m_pacP = new COMPLEX[m_nN];
	}
	
	Polinom::Polinom(int nN, COMPLEX* pacP)		// (N = m_nN - 1) -edfoku polinom letrehozasa, egyutthatok megadasa
	: m_nN(nN)
	{
		m_pacP = new COMPLEX[m_nN];
		for(int iii = 0; iii < m_nN; iii++)
		{
			m_pacP[iii] = pacP[iii];
		}
	}
	
	Polinom::Polinom(const Polinom& cP)				//masolo konstruktor
	{
		m_nN = cP.m_nN;
		
		if(cP.m_pacP != NULL)
		{
			m_pacP = new COMPLEX[m_nN];
			for(int iii = 0; iii < m_nN; iii++)
			{
				m_pacP[iii] = cP.m_pacP[iii];
			}
		}
		else
		{
			m_pacP = NULL;
		}
	}
	
	Polinom::~Polinom()
	{
		delete[] m_pacP;		//dinamikusan foglalt memoria felaszabaditasa
	}

	Polinom& Polinom::operator=(const Polinom& cP)		//polinom ertekadas
	{
		if (this == &cP)
		{
			return *this;
		}
        		
		delete[] m_pacP;
		m_nN = cP.m_nN;
		
		if(cP.m_pacP != NULL)
		{
			m_pacP = new COMPLEX[m_nN];
			for(int iii = 0; iii < m_nN; iii++)
			{
				m_pacP[iii] = cP.m_pacP[iii];
			}
		}
		else
		{
			m_pacP = NULL;
		}
		
		return *this;	
	}
	
	COMPLEX& Polinom::operator[](int nIndex)		//egyutthatok kozvetlen elerese
	{
		return m_pacP[nIndex];
	}
	
	COMPLEX Polinom::operator()(const COMPLEX cZ) const		//behelyetteseitesei ertek "cZ" helyen
	{
		COMPLEX cErtek;
		cErtek = m_pacP[m_nN-1];
		for(int iii = m_nN-1; iii > 0; iii--)
		{
			cErtek = (cErtek * cZ) + m_pacP[iii-1];			//Horner-elrendezes szerint szamitva
		}
		
		return cErtek;		
	}
	
	Polinom& Polinom::Derivalt() const			//derivalt polinom meghatarozasa
	{
		Polinom* pcDerivalt;
		pcDerivalt = new Polinom(m_nN-1);
		for(int iii = m_nN-1; iii > 0; iii--)
		{
			(*pcDerivalt).m_pacP[iii-1] = iii * m_pacP[iii];
		}
		
		return *pcDerivalt;
	}
	
	Polinom& Polinom::PolinomGyokOsztas(const COMPLEX cZ) const		//"cZ" az eredeti polinom gyoke
	{
		Polinom* pcHanyados;
		pcHanyados = new Polinom(m_nN-1);
		(*pcHanyados).m_pacP[m_nN-2] = m_pacP[m_nN-1];
		
		for(int iii = m_nN-2; iii > 0; iii--)		//Horner-elrendezes szerint meghatarozva:
		{
			(*pcHanyados).m_pacP[iii-1] = (cZ * (*pcHanyados).m_pacP[iii]) + m_pacP[iii];
		}
		
		return *pcHanyados;				// (x - cZ)	elsofoku polinommal valo osztas utani hanyados polinom
										// 			/ cZ: eredeti polinom gyoke kell hogy legyen, a fuggveny ezt kulon nem vizsgalja /
	}
	
	int Polinom::FokSzam() const	// polinom (akar az osszes 0-val egyenlo is lehet) egyutthatoinak szama
	{								// N-edfoku polinom eseten: m_nN = N+1
		return m_nN;
	}
	
	std::ostream& operator<<(std::ostream& out, const Polinom& cP)		//polinom kiiratasa
	{
		for(int iii = 0; iii < cP.m_nN; iii++)
		{
			out << "a" << cP.m_nN-1-iii << "="<< cP.m_pacP[cP.m_nN-1-iii] << " ";
		}
		
		return out;
	}
}
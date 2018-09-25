#include <string>
#include "Laguerre.h"

using namespace scomplex;

namespace megold
{
/*********************************************************************************/
//Pozitiv egesz legalabb masodfoku P(x) polinom
//P(zi) = 0 N-edfoku egyenletenek
//"z" komplex kezdoertekbol 1 db "zi" komplex gyokhoz valo kozelitesnek 1 lepese
//a fuggvenyt egymas utan meghivva a polinommal es a fuggveny
//altal adott elozo komplex visszateresi ertekkel tetszoleges kezdeti ertekbol
//kiindulva a visszateresi ertekek sorozata a polinom egy gyokehez konvergal

//ha az aktualis lepesben P(z) = 0, akkor ezt 0-val valo osztaskor dobott
//kivetel jelzi es "z" erteket kivetelkent tovabbitjuk a fuggveny meghivojanak

/*
felhasznalt irodalom:
//http://www.fmt.bme.hu/fmt/oktatas/feltoltesek/BMEEOFTMKT2/fejezet_03.pdf
3.4 fejezet
*/
/*********************************************************************************/

	COMPLEX Laguerre::Lepes(Polinom& cPolinom, COMPLEX z)
	{
		Polinom P = cPolinom;
		Polinom P1 = cPolinom.Derivalt();
		Polinom P2 = cPolinom.Derivalt().Derivalt();
		
		double N;
		COMPLEX g_z, h_z, q_z, n_z, a_z;
		
		N = cPolinom.FokSzam() - 1;		//a polinom foka = egyutthatok szama -1
		
		try		//megprobalunk osztani "P(z)" -vel
		{
			g_z = ( P1(z) ) / ( P(z) );
			h_z = (g_z *g_z) - ( P2(z) ) / ( P(z) );
		}
		catch(char const* S)		//ha 0-val probaltunk meg osztani kivetelt dob a rendszer
		{	
			throw z;				//ekkor "z" aktualis erteket tovabbitjuk
		}

		q_z = COMPLEX::NegyzetGyok( (N - 1) * ( (N * h_z) - (g_z * g_z) ) );
		n_z =  ( COMPLEX::AbszolutErtek(g_z + q_z) > COMPLEX::AbszolutErtek(g_z - q_z) ) ? (g_z + q_z) : (g_z - q_z);

		a_z = N / n_z;
		
		COMPLEX z1;
		z1 = z -a_z;
		return z1;					//egyebbkent az iteracio kovetkezo lepesevel terunk vissza
	}
}
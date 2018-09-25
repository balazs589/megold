#include <iostream>
#include <fstream>

#include "Kiszamol.h"
#include "Polinom.h"
#include "Laguerre.h"
#include "simple_complex.h"

using namespace std;
using namespace scomplex;

namespace megold
{
/*********************************************************************************/
//a Kiszamol fuggveny a parameterkent megkapott 4 elemu tomb elemeit valos egyutthatokkent
//ertelmezve letrehoz egy 3-ad foku polinomot, ennek a polinomnak
//Laguerre iteracios modszer hasznalataval meghatarozza a 3db komplex(valos is lehet) gyoket,

//az egyuthatokat, a gyokoket es a visszahelyettesiteseket a parameterkent megkapott
//szoveges output fajlba irja soronkent
/*********************************************************************************/

void Kiszamol(double input[4], ofstream& outfile)
{
	outfile <<							//kimeneti fajl 1. soraba irjuk az egyutthatokat
	". a=" << input[0] << ", "
	<< "b=" << input[1] << ", "
	<< "c=" << input[2] << ", "
	<< "d="<< input[3] << endl;

	COMPLEX P[4];							//a Laguerre modszer komplex ertekekkel szamol
	P[3] = COMPLEX(input[0], 0.0);			//az egyenlet egyutthatoit komplex szamok valos reszekent ertelmezzuk
	P[2] = COMPLEX(input[1], 0.0);
	P[1] = COMPLEX(input[2], 0.0);
	P[0] = COMPLEX(input[3], 0.0);
	
	COMPLEX Gyokok[3];					//megoldasok tarolasara
	int GyokSorszam = 0;
	
	//double HIBA = numeric_limits<double>::epsilon()
	Polinom cP(4, P);					//letrehozzuk az egyutthatoknak megfelelo polinomot
	COMPLEX z0;							//valamint a iteracios lepesek aktualis erteket tartalmazo valtozot
	
	while(cP.FokSzam() > 2)					//amig a polinom legalabb masodfoku
											//( FokSzam = polinom egyutthatoinak szama
											//  azaz masodfoku polinom eseten 3 )
	{
		z0 = COMPLEX(1.2345, 5.4321);				//iteracio kezdoerteke - Laguerre modszer eseten tetszoleges
											
											//a modszerrol elerheto irodalmak szerint
											//tetszoleges kezdoertek eseten konvergal a Laguerre modszer
											//a polinom egy gyokehez
		
		for(int iii = 0; iii < 1000; iii++)		//adunk sok lehetoseget a konvergenciahoz
												//( az 1000-es ciklusokba nehanyszor bveragadva
												//  sem tart tovabb 1 masodpercnel a peldafeladatok
												//  megoldasanak ilyen modon torteno kozelitese
												//  Pentium 4 2GHz processzoron )
		{
			COMPLEX z;
			
			if(cP(z0) != 0.0)					//ha z0 nem gyoke a polinomnak
			{
				try			//megprobaljuk meghatarozni a kovetkezo kozelitoerteket:
							//annak ellenere, hogy az egzakt "cP(z0) == 0.0" gyokoket mar kiszortuk,
							//a Laguerre modszerben valo osztaskor cP(z0) egyebb esetekben is 0-nak adodik,
							//ezt a fuggveny a komplex z0 ertek kivetelkent valo visszadobasaval jelzi
				{
					z = Laguerre::Lepes(cP, z0);	
				}
				catch(COMPLEX hibaZ)	//elkapjuk a visszadobott "z0" -t
				{
					z = hibaZ;		//ha nem tdtunk cP(z0) -lal osztani megvan a gyok kozekito erteke
					break;
				}
				
			}
			else				//ha "cP(z0) == 0" z0 gyoke a polinomnak
			{	
				break;			//es megvan a kovetkezo megoldas
			}
			
			if(z==z0)			//ha a kovetkezo lepes az elozovel megegyezne
			{					//a gepi szamabrazolas veges pontossaga miatt
								//de a polinom behelyettesitesi erteke megsem 0
				break;			//akkor ezt fogadjuk el az iteracio vegenek es nem lepunk vele ertelmetlen ciklusba
			}

			else		//ha eddig nem sikerult gyokot talalni
			{
				z0=z;	//kovetkezo lepesben a legutobbi eredmenyt hasznaljuk fel
			}
			
			//ha 2-3-4... tagu ismetlodesbe esne az iteracio, akkor a for ciklus
			//altal meghatarozott maximalis lepesszam fogja ezt megszakitani,
			//sok lepes utan a Laguerre modszerrol feltetelezve, hogy jol kozeliti
			//az egyenlet egy megoldasat, ezt fogadjuk el az iteracio eredmenyenek
		}
											//miutan valamilyen modon konvergalt a modszer
		Gyokok[GyokSorszam] = z0;			//elfogadjuk a vegeredmenyt
		cP = cP.PolinomGyokOsztas(z0);		//es a meghatarozott gyoktol megszabaditjuk a polinomot
		GyokSorszam++;						//
	}
	//a polinom elsofokig valo egyszerusitese utan, 2 megoldas ismereteben,
	//a 3. gyokot egyszeru osztassal hatarozzuk meg:
	
	Gyokok[2] =  (-1) * (cP[0] / cP[1]);
	
	cP = Polinom(4, P);					//visszaterunk az eredeti polinomhoz
	
	outfile	<< Gyokok[0] << ", "		//egy sorba irjuk a harmadfoku egyenlet gyokeit
			<< Gyokok[1] << ", "		//
			<< Gyokok[2] << endl;		//
			
	outfile	<< "P(x1)=" << cP(Gyokok[0]) << ", "		//es a kovetkezo sorba a behelyettesitesukkel kapott ertekeket
			<< "P(x2)=" << cP(Gyokok[1]) << ", "		//
			<< "P(x3)=" << cP(Gyokok[2]) << endl;		//

	return;
}

}
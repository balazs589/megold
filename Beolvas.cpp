#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <stdlib.h>

#include "Beolvas.h"

using namespace std;

namespace megold
{
/*********************************************************************************/
//a Beolvas fuggveny megszamolja az inputfajlban levo nem ures es nem komment sorokat,
//es a megadott formatumot feltetelezve rogziti a benne talalhato feladatok szamat
//es azok egyutthatoit, nem megfelelo formatum eseten hibat nem jelez, de ertelemszeruen
//helytelen, ertelmetlen adatokkal fog szolgalni
//a sorokat feldolgozo kodreszlet csak valos egyutthatokat kezel,
//komplex egyutthatokra nincs felkesziteve
//a megoldando feladatok szamat referenciakent, a beolvasott egyutthatokra mutato
//pointert visszateresi ertekkent szolgaltatja
/*********************************************************************************/	

double** Beolvas(ifstream& infile, int& _FeladatokSzama)
{
	int SorokSzama = 0;				//csak az ertekes sorokat szamoljuk
	int FeladatokSzama = 0;			//kezdeti ertekeket tartalmazo sorok szama

	while(infile)
	{
		string Sor;
		getline(infile, Sor);							//beolvasunk egy sort
		Sor = Sor.substr(0, Sor.find_first_of('#') );	//elhagyjuk a kommenteket

		//majd megszabadulunk az esetleges sorvegi whitespace -ektol:
		if(Sor.find_last_not_of(" \t\f\v\n\r") == string::npos)
		{
			Sor.clear();
		}

		//ha ezutan marad valami, akkor azt ertekes sorkent ertelmezzuk:
		if(Sor.length() != 0)
		{
			SorokSzama++;			//szamoljuk ezeket
			if(SorokSzama == 1)		//az elso sor tartalmat osszevetjuk a feladatban szereplo ertekkel
			{
				if(Sor == "Programozas 2. 2012. I. hazi feladat")
				{
					cout << Sor << endl;
					cerr << "Az elso sor megegyezik a megadott szoveggel." << endl;
				}
				else
				{
					cerr << "Az elso sor nem egyezik a megadott ertekkel." << endl;
					break;
				}
			}

		}
	}
	//osszeszamoltuk az ertekes sorokat
	//ezaltal ismerjuk a megoldando feladatok szamat:

	FeladatokSzama = SorokSzama - 2;

	double** Egyutthatok;
	Egyutthatok = new double*[FeladatokSzama];	//ennek megfeleo szamu tombunk lesz
													//darabonkent 4 elemmel

	for(int iii = 0; iii < FeladatokSzama; iii++)
	{
		Egyutthatok[iii] = new double[4];
	}

	infile.clear();					//
	infile.seekg(0, ios::beg);		//a beolvasast ujra a fajl elejetol kezdjuk

	SorokSzama = 0;					//az eddigi valtozokat seged valtozokent hasznaljuk
	FeladatokSzama = 0;				//

	while(infile)
	{
		string Sor;
		getline(infile, Sor);
		Sor = Sor.substr(0, Sor.find_first_of('#') );

		if(Sor.find_last_not_of(" \t\f\v\n\r") == string::npos)
		{
			Sor.clear();
		}
								//elvegezzuk a sorok fentivel egyezo beolvasasat
		if(Sor.length() != 0)
		{
			SorokSzama++;		//szamoljuk hogy hol tartunk

			if(SorokSzama > 2)
			{
				string Sor2;

				//a beolvasott sorokbol az elejuktol a vegukig fele haladva
				//egymas utan kiemeljuk az '=' jeltol a ',' -ig tarto reszeket
				//amelyeket utana (a megadott sorrend szerint) a, b, c, d
				//valos egyutthatokent ertelemzunk

				Sor = Sor.substr(Sor.find_first_of('=') + 1);
				Sor2 = Sor.substr(0, Sor.find_first_of(',') );
				Egyutthatok[FeladatokSzama][0] = atof(Sor2.c_str());		//a

				Sor = Sor.substr(Sor.find_first_of('=') + 1);
				Sor2 = Sor.substr(0, Sor.find_first_of(',') );
				Egyutthatok[FeladatokSzama][1] = atof(Sor2.c_str());		//b

				Sor = Sor.substr(Sor.find_first_of('=') + 1);
				Sor2 = Sor.substr(0, Sor.find_first_of(',') );
				Egyutthatok[FeladatokSzama][2] = atof(Sor2.c_str());		//c

				Sor = Sor.substr(Sor.find_first_of('=') + 1);
				Sor2 = Sor.substr(0, Sor.find_first_of(',') );
				Egyutthatok[FeladatokSzama][3] = atof(Sor2.c_str());		//d

				FeladatokSzama++;		//ujra szamoljuk a feladatokat
			}
		}
	}
	//melyek szamat a beolvasas elvegzese utan referencian keresztul adjuk vissza

	_FeladatokSzama = FeladatokSzama;		//fealadatok szama referenciakent
	return Egyutthatok;					//rogzitett adatokat tartalmazo tombokre mutato pointer
}
	
}
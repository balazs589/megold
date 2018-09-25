#include <iostream>
#include <fstream>

#include "simple_complex.h"
#include "Polinom.h"
#include "Laguerre.h"
#include "Beolvas.h"
#include "Kiszamol.h"

using namespace std;
using namespace megold;
using namespace scomplex;

/*********************************************************************************/
//a main fuggveny vegzi a prancssori parameterek feldolgozasat,
//azokat input es opcionalisan output szoveges fajlnevkent ertelmezve
//olvasasra es irasra nyitja meg a megfelelo fajlokat,
//a bemeneti fajl feldolgozasat elvegezteti a Beolvas fuggvennyel
//majd a rogzitett feladatokat a Kiszamol fuggvennyel megoldatja
//es a megoldasokat a megfelelo kimeneti fajlba iratja
/*********************************************************************************/

int main(int argc, char **argv)
{
	//a program legalabb 1 legfeljebb 2 parancssori parametert var
	if( (argc != 2) && (argc != 3) )
	{
		cout << "a program inditasi parametereinek helyes formaja:" << endl;
		cout << "megold <parameterek fajlja> [<eredmeny fajl>]" << endl;
		cout << "pl.: megold input.txt output.txt" << endl;
		cout << "az eredmenyfajl parameter opcionalis" << endl;
		return 1;
	}

	string strInputFajl;						//
	string strOutputFajl;						//a parancssori parameterek tarolasara

	switch(argc)
	{
		case 3:									//teljes prameterlistaval torteno inditas eseten
			strInputFajl = argv[1];				// a megadott sorrend szerint ertelmezzuk a parametereket
			strOutputFajl = argv[2];			//
			break;

		case 2:										//hianyos parameterlistaval torteno inditas eseten
			strInputFajl = argv[1];					//a megadott egyetlen parameter az input fajlt jelenti
			strOutputFajl = "output_BGGUER.txt";	//az outputfajl neve az alapertelmezett ertekeket kapja
			break;
	}

	ifstream infile(strInputFajl.c_str());		//megprobaljuk elerni az inputfajlt
	if(!infile)		//ha nem sikerul, akkor megszakitjuk a program futasat
	{
		cerr << strInputFajl << endl;
		cerr << "a megadott inputfajlt nem sikerult megnyitni" << endl;
		return 1;
	}

	double** Egyutthatok;				//ezen keresztul foguk elerni az input fajlbol szarmazo ertekeket
	int FeladatokSzama = 0;				//megoldando egyenletek szama

	Egyutthatok = Beolvas(infile, FeladatokSzama);		//rogzittjuk a megoldando feladatokat

	ofstream outfile(strOutputFajl.c_str());		//megnyitjuk irasra a megfelelo szoveges fajlt
	if(!outfile)
	{
		cerr << "nem sikerult a fajl megnyitasa irasra: (" << strOutputFajl <<")" << endl;
		return 1;
	}

	outfile << "Programozas 2 I. feladat 2012" << endl;		//feladatban elvart ertek

	cout << endl << "Szamitas folyamatban." << endl;

	for(int iii = 0; iii < FeladatokSzama; iii++)			//egymas utan
	{
		outfile 	<< iii+1;
		Kiszamol( Egyutthatok[iii], outfile);				//megoldjuk az inputfajlbol szarmazo egyenleteket
	}

	outfile.close();		//zarjuk a kimeneti szoveges fajlt

	cout << endl << "Szamitas befejezve." << endl << endl;
	cout 	<< "Az eredmeny a(z) " << strOutputFajl
			<< " szoveges fajlban talalhato meg." << endl;

	return 0;
}
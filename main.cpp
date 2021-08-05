#include <cstdlib>
#include <iostream>
#include "Gro.h"

using namespace std;

void checkcommands(char** gro, char** top, float& a, char** w, char** m, int argc, char** argv);

int main(int argc, char** argv)
{
	string temp;
	char* fgro, *ftop, *wat, *memb;
	float accdisp;
	Water a;
	checkcommands(&fgro, &ftop, accdisp, &wat, &memb, argc, argv);
	Gro gro(fgro, ftop, wat, memb, &a, accdisp);
	
	ofstream o("output.txt");
	if (o.fail())
	{
		cout << "Failed to create output file.";
		return 1;
	}
	
	o << "OUTSIDE BELOW:\t" << a.goodcount[0] << '\t' << "TOTAL WATERS:\t" << a.totalcount[0] << '\t' << "PERCENTAGE:\t" << a.goodcount[0] / a.totalcount[0] * 100 << '\n';
	o << "INSIDE ABOVE:\t" << a.goodcount[1] << '\t' << "TOTAL WATERS:\t" << a.totalcount[1] << '\t' << "PERCENTAGE:\t" << a.goodcount[1] / a.totalcount[1] * 100 << '\n';
	o << "INSIDE BELOW:\t" << a.goodcount[2] << '\t' << "TOTAL WATERS:\t" << a.totalcount[2] << '\t' << "PERCENTAGE:\t" << a.goodcount[1] / a.totalcount[1] * 100 << '\n';
	o << "OUTSIDE ABOVE:\t" << a.goodcount[3] << '\t' << "TOTAL WATERS:\t" << a.totalcount[3] << '\t' << "PERCENTAGE:\t" << a.goodcount[1] / a.totalcount[1] * 100;
}


void checkcommands(char** gro, char** top, float& a, char** w, char** m, int argc, char** argv)
{
	for (int i = 1; i < argc; i++)
	{
		if (!strcmp(argv[i], "-f")) // gro filename
		{
			*gro = argv[i+1];
		}
			
		else if (!strcmp(argv[i], "-dr")) // acceptable distance from membrane
		{
			a = atof(argv[i+1]);
		}
		
		else if (!strcmp(argv[i], "-m")) // membrane name
		{
			*m = argv[i+1];
		}
		
		else if (!strcmp(argv[i], "-w")) // water name
		{
			*w = argv[i+1];
		}
		
		else if (!strcmp(argv[i], "-p")) // topology filename
		{
			*top = argv[i+1];
		}
			
	}
}



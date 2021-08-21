#include <cstdlib>
#include <iostream>
#include "gfile.h"
#include "func.h"

void checkcommands(char** trr, char** index, float& a, char** w, char** m, char** top, int argc, char** argv);

int main(int argc, char** argv)
{
	string temp;
	char *ftrr = nullptr, *findex = nullptr, *wat = nullptr, *memb = nullptr, *ftop = nullptr;
	double membz[4];
	double *d = nullptr, *dpos;
	int g[4] = {0, 0, 0, 0};
	int t[4] = {0, 0, 0, 0};
	float *f = nullptr, *fpos;
	float accdisp = 0;
	Index::group* groups;
	Topol::residue* res;
	int waterind, watersize, grsize, ressize;
	int pos;
	checkcommands(&ftrr, &findex, accdisp, &wat, &memb, &ftop, argc, argv);

	if (!ftrr || !findex || !wat || !memb || !ftop || !accdisp)
	{
		cout << "One (or more) of your inputs are invalid, please try again\n";
		return 1;
	}
	Trr trr(ftrr);
	Index ind(findex);
	//printf("fail on constructor\n");
	Topol top(ftop);

	groups = ind.getGroups(grsize); // we're only concerned with the water index found in the next line.
	//printf("fail on groups\n");

	res = top.getResidues(ressize);

	findwater(groups, grsize, waterind, wat);
	//printf("watername: %s\n", groups[waterind].grname);

	watersize = (groups[waterind].indend[0] - groups[waterind].indstart[0] + 1) / 3;
	//printf("watersize: %d\n", watersize);

	for (int frame = 0; !trr.readFrame(); frame++)
	{
		if (trr.getPrecision())
		{
			d = trr.getX<double>();
			setmemb(membz, groups, grsize, res, ressize, trr, memb, d);
			for (int i = 0; i < groups[waterind].size; i++)
			{
				dpos = d + (groups[waterind].indstart[i] - 1)*DIM + 2;
				for (int j = 0; j < watersize; j++)
				{
					checkResult(accdisp, membz, *(dpos), *(dpos + DIM), *(dpos + DIM*2), g, t); // membz, oxygen, hydrogen1, hydrogen2
					//printf("fpos: %f\nfpos+1: %f\nfpos+2: %f\n", *(fpos), *(fpos + DIM), *(fpos + DIM*2));
					fpos += DIM*3;
				}
			}
		}
		else
		{
			f = trr.getX<float>();
			//printf("beforememb\n");
			setmemb(membz, groups, grsize, res, ressize, trr, memb, f);
			for (int i = 0; i < groups[waterind].size; i++)
			{
				fpos = f + (groups[waterind].indstart[i] - 1)*DIM + 2;
				for (int j = 0; j < watersize; j++)
				{
					checkResult(accdisp, membz, *(fpos), *(fpos + DIM), *(fpos + DIM*2), g, t); // membz, oxygen, hydrogen1, hydrogen2
					//printf("fpos: %f\nfpos+1: %f\nfpos+2: %f\n", *(fpos), *(fpos + DIM), *(fpos + DIM*2));
					fpos += DIM*3;
				}
			}
		}
		printf("MEMB:\t\t\t\t%7.5f %8.5f %8.5f %8.5f\n", membz[0], membz[1], membz[2], membz[3]);
		std::cout << "FRAME: \t\t\t\t" << frame << std::endl;
		std::cout << "OUTSIDE, BELOW:\t\t" << g[0] << "\t\t " << t[0] << std::endl;
		std::cout << "INSIDE, ABOVE:\t\t" << g[1] << "\t\t " << t[1] << std::endl;
		std::cout << "OUTSIDE, BELOW:\t\t" << g[2] << "\t\t " << t[2] << std::endl;
		std::cout << "INSIDE, ABOVE:\t\t" << g[3] << "\t\t " << t[3] << std::endl;

		memset(g, 0, 4*sizeof(int));
		memset(t, 0, 4*sizeof(int));
		
	}
}



void checkcommands(char** trr, char** index, float& a, char** w, char** m, char** top, int argc, char** argv)
{
	for (int i = 1; i < argc; i++)
	{
		if (strcmp(argv[i], "-f") == 0) // trr filename
		{
			*trr = argv[i+1];
		}
			
		else if (strcmp(argv[i], "-dr") == 0) // acceptable distance from membrane
		{
			a = atof(argv[i+1]);
		}
		
		else if (strcmp(argv[i], "-m") == 0) // membrane name
		{
			*m = argv[i+1];
		}
		
		else if (strcmp(argv[i], "-w") == 0) // water name
		{
			*w = argv[i+1];
		}
		
		else if (strcmp(argv[i], "-i") == 0) // index filename
		{
			*index = argv[i+1];
		}

		else if (strcmp(argv[i], "-p") == 0)
		{
			*top = argv[i+1];
		}
			
	}
}



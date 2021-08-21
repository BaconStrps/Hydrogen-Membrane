#include "func.h"
#include <string.h>
void checkResult(double accdisp, double memb[4], const double& o, const double& h1, const double& h2, int g[4], int t[4])
{
    //printf("o: %f\nh1: %f\nh2: %f\n", o, h1, h2);
    //printf("memb: %8.3f, %8.3f %8.3f %8.3f\n", memb[0], memb[1], memb[2], memb[3]);
    if (checkpos(accdisp, memb[0], false, o, h1, h2) == 1) // below, outside
	{
		g[0]++;
		t[0]++;
        //printf("below outside\n");
	}
	else if (checkpos(accdisp, memb[0], false, o, h1, h2) == 2)
		t[0]++;
	else if (checkpos(accdisp, memb[1], true, o, h1, h2) == 1) // above, inside
	{
		g[1]++;
		t[1]++;
        //printf("above inside\n");
	}
	else if (checkpos(accdisp, memb[1], true, o, h1, h2) == 2)
		t[1]++;
	if (checkpos(accdisp, memb[2], false, o, h1, h2) == 1) // below, inside
	{
		g[2]++;
		t[2]++;
        //printf("below inside\n");
	}
	else if (checkpos(accdisp, memb[2], false, o, h1, h2) == 2)
		t[2]++;
	else if (checkpos(accdisp, memb[3], true, o, h1, h2) == 1) // above, outside
	{
		g[3]++;
		t[3]++;
        //printf("above outside\n");
	}
	else if (checkpos(accdisp, memb[3], true, o, h1, h2) == 2)
		t[3]++;
}


int checkpos(double accdisp, double membz, bool ab, const double& o, const double& h1, const double& h2)
{
	if (ab && (o > h1 && o > h2) && (o - membz < accdisp && o - membz > 0))
		return 1;
	else if (ab && (o - membz < accdisp && o - membz > 0))
		return 2;
	else if (!ab && (o < h1 && o < h2) && (membz - o < accdisp && membz - o > 0))
		return 1;
	else if (!ab && (membz - o < accdisp && membz - o > 0))
		return 2;
	else
		return false;
}

void setmemb(double memb[4], Index::group* ind, int grsize, Topol::residue* res, int ressize, Trr& trr, char* membname, void* arr)
{
    float* f;
    double* d;

    int swaps;

    int resindex = -1;
    int membindex = -1;
    int offset;



    if (trr.getPrecision())
    {
        d = static_cast<double*>(arr);
    }
    else
    {
        f = static_cast<float*>(arr);
    }

    for (int i = 0; i < grsize; i++)
    {
        //printf("Grname: %s\n", ind[i].grname);
        if (strcmp(ind[i].grname, "MEMB") == 0)
        {
            //printf("past first strcmp\n");
            membindex = i;
            break;
        }
    }


    for (int i = 0; i < ressize; i++)
    {
        //printf("Resname: %s\n", res[i].resname);
        if (strcmp(res[i].resname, membname) == 0)
        {
            //printf("past second strcmp\n");
            resindex = i;
            break;
        }
    }

    swaps = ind[membindex].size;
   // printf("size: %d\n", swaps);

    offset = (ind[membindex].indend[0] - ind[membindex].indstart[0] + 1) / res[resindex].nmolc;

    if (trr.getPrecision())
    {
        for (int i = 0; i < swaps; i++)
        {
            checkmemb(memb[i*swaps + 1], memb[i*swaps], ind[membindex].indstart[i], res[resindex].nmolc, d, offset, Z);
        }
    }
    else
    {
        for (int i = 0; i < swaps; i++)
        {
            checkmemb(memb[i*swaps + 1], memb[i*swaps], ind[membindex].indstart[i], res[resindex].nmolc, f, offset, Z);
        }
    }
}

void findwater(Index::group* p, int grsize, int& waterind, char* watername)
{
   // printf("watername: %s\n", watername);

    for (int i = 0; i < grsize; i++)
    {
      //  printf("grname: %s\nwtname: %s\n", p[i].grname, watername);
        if (strcmp(p[i].grname, watername) == 0)
        {
            waterind = i;
         //   printf("grname: %s\nIndex: %d", p[i].grname, i);
        }
    }
}
#ifndef FUNC
#define FUNC
#include "gfile.h"

enum POS{X, Y, Z};

void checkResult(double accdisp, double memb[4], const double& o, const double& h1, const double& h2, int g[4], int t[4]);

int checkpos(double accdisp, double membz, bool ab, const double& o, const double& h1, const double& h2);

void setmemb(double memb[4], Index::group* ind, int grsize, Topol::residue* res, int ressize, Trr& trr, char* membname, void* arr);

void findwater(Index::group* p, int grsize, int& waterind, char* watername);

template<typename T>
void checkmemb(double& top, double& bot, int startingindex, int postocheck, T* arr, int offset, POS pos)
{
    startingindex -= 1;
    postocheck -= 1;
    T min = 0xffff;
    T max = 0;
    T cur;
    int topmembind = postocheck/2;
    T* curpos = arr + pos + (startingindex*DIM);
    //printf("starting index: %d\n", startingindex);

    for (int i = 0; i < postocheck; i++)
    {
        curpos += offset*DIM;
        cur = *curpos;
        if (i+1 == topmembind)
        {
            top = min;
        }

        if (cur < min)
            min = cur;
        if (cur > max && i > topmembind)
            max = cur;
    }

    //printf("top: %f\n", top);
    bot = max;
    //printf("bot: %f\n", bot);
}

#endif
#include "Water.h"


int Water::checkifnear(double accdisp, double membz, bool ab)
	{
		if (ab && (o[2] > h1[2] && o[2] > h2[2]) && (o[2] - membz < accdisp && o[2] - membz > 0))
			return 1;
		else if (ab && (o[2] - membz < accdisp && o[2] - membz > 0))
			return 2;
		else if (!ab && (o[2] < h1[2] && o[2] < h2[2]) && (membz - o[2] < accdisp && membz - o[2] > 0))
			return 1;
		else if (!ab && (membz - o[2] < accdisp && membz - o[2] > 0))
			return 2;
		else
			return false;
	}
	
void Water::checkResult(double memb[4], double accdisp)
{
	if (checkifnear(accdisp, memb[0], false) == 1) // below, outside
	{
		goodcount[0]++;
		totalcount[0]++;
	}
	else if (checkifnear(accdisp, memb[0], false) == 2)
		totalcount[0]++;
	else if (checkifnear(accdisp, memb[1], true) == 1) // above, inside
	{
		goodcount[1]++;
		totalcount[1]++;
	}
	else if (checkifnear(accdisp, memb[1], true) == 2)
		totalcount[1]++;	
			
	if (checkifnear(accdisp, memb[2], false) == 1) // below, inside
	{
		goodcount[2]++;
		totalcount[2]++;
	}
	else if (checkifnear(accdisp, memb[2], false) == 2)
		totalcount[2]++;
	else if (checkifnear(accdisp, memb[3], true) == 1) // above, outside
	{
		goodcount[3]++;
		totalcount[3]++;
	}
	else if (checkifnear(accdisp, memb[3], true) == 2)
		totalcount[3]++;
}

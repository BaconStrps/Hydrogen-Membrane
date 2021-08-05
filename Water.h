#define WATER 1
#include <iostream>

class Water
{
	public: // Everything is public for now just cause it's easier to work with although not as safe
	
		double h1[3];
		double h2[3];
		double o[3];
		double goodcount[4] = {0, 0, 0, 0};
		double totalcount[4] = {0, 0, 0, 0};
		char name[3];
		
		void setH1(float x, float y, float z, char n)
		{
			name[1] = n;
			h1[0] = x;
			h1[1] = y;
			h1[2] = z;
		}
		
		void setH2(float x, float y, float z, char n)
		{
			name[2] = n;
			h2[0] = x;
			h2[1] = y;
			h2[2] = z;
		}
		
		void setO(float x, float y, float z, char n)
		{
			name[3] = n;
			o[0] = x;
			o[1] = y;
			o[2] = z;
		}
		
		/*
			If above,
				Oxygen z coord > hydrogen z coords
				Oxygen z coord - memb z coord < dist & > 0
			If below,
				Oxygen z coord < hydrogen z coords
				Memb z coord - oxygen z coord < dist & > 0
		*/
		
		int checkifnear(double accdisp, double membz, bool ab)
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
		
		void checkResult(double memb[4], double accdisp)
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
		
		
};

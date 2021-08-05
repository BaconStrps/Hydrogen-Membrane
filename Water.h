#define WATER 1

class Water
{
	public: // Everything is public for now just cause it's easier to work with although not as safe
	
		double h1[3];
		double h2[3];
		double o[3];
		double goodcount[4] = {0, 0, 0, 0};
		double totalcount[4] = {0, 0, 0, 0};
		char name[3];
		
		/*
			If above,
				Oxygen z coord > hydrogen z coords
				Oxygen z coord - memb z coord < dist & > 0
			If below,
				Oxygen z coord < hydrogen z coords
				Memb z coord - oxygen z coord < dist & > 0
		*/
		
		int checkifnear(double accdisp, double membz, bool ab);
		
		void checkResult(double memb[4], double accdisp);

		
		
};

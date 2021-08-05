#include <fstream>
#include "Water.h"
#include <string>
#include <string.h>
#include <iostream>
using namespace std;

class Gro
{
	public: // Everything is public for now just cause it's easier to work with although not as safe
	
		string currentline;
		string resatom;
		string watername;
		string membname;
		int atomnum;
		int membcount;
		int watercount;
		double coords[3];
		double memb[4];
		double lowest;
		double highest;
		double accdisp;
		Water* water;
		ifstream gro;
		ifstream top;
		
		Gro(string g, string t, string w, string m, Water* wt, double acc); // g is gro file, t is top file, w is watername, m is membname

		
		void checkTopol();

		void splitLine();
	
		void getLowestMemb();
		
		void waterCheck();
};

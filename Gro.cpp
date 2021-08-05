#include "Gro.h"

Gro::Gro(string g, string t, string w, string m, Water* wt, double acc) // g is gro file, t is top file, w is watername, m is membname
{			
	gro.open(g.c_str());
	top.open(t.c_str());
	
	for (int i = 0; i < 4; i++)
	{
		memb[i] = 1000; // Initialize to a large number to make sure we don't get any errors while checking boundaries
	}
	
	
	accdisp = acc;
	watername = w;
	membname = m;
	water = wt;

	lowest = 0xffff; // big number just to make sure we aren't comparing against 0
				
	checkTopol();
	
	// Filler to get rid of the first 2 lines of the .gro file
	getline(gro, currentline);
	getline(gro, currentline);
		
	getLowestMemb();
}
		
void Gro::checkTopol()
		{
			while (!top.eof())
			{
				getline(top, currentline);
				
				if (currentline.length() < 19)
					continue;
				
				
				if (currentline.substr(0, membname.length()).compare(membname.c_str()) == 0)
					membcount = atoi(currentline.substr(currentline.length()-4, 4).c_str()); // assumption, only up to 9999 lipids on one line, only one type of lipid
					
				else if (currentline.substr(0, watername.length()).compare(watername.c_str()) == 0)
					watercount = atoi(currentline.substr(currentline.length()-5, 5).c_str()); // assumption, only up to 99999 waters on one line
			}
		}
		
void Gro::splitLine()
		{
			
			getline(gro, currentline);
			if (currentline.length() < 44)
			{
				return;
			}

			
			resatom = currentline.substr(0, 15);
			coords[0] = atof(currentline.substr(20, 8).c_str());
			coords[1] = atof(currentline.substr(28, 8).c_str());
			coords[2] = atof(currentline.substr(36, 8).c_str());
		}
		
		
void Gro::getLowestMemb()
		{
			bool m0 = false, m1 = false, m2 = false, m3 = false;
			while (!gro.eof())
			{
				splitLine();
				if (currentline.length() < 44)
					continue;
				if (atoi(resatom.substr(0, 5).c_str()) >= membcount / 2 && !m1) // Top leaflet, bottom membrane
				{
					memb[1] = lowest;
					lowest = 0xffff;
					highest = 0;
					m1 = true;
				}
				
				else if (atoi(resatom.substr(0, 5).c_str()) >= membcount && !m0) // Bottom leaflet, bottom membrane
				{
					memb[0] = highest;
					lowest = 0xffff;
					highest = 0;
					m0 = true;
				}
				
				else if (atoi(resatom.substr(0, 5).c_str()) >= membcount * 1.5 + watercount && !m3) // Top leaflet, top membrane
				{
					memb[3] = lowest;
					lowest = 0xffff;
					highest = 0;
					m3 = true;
				}
				
				else if (atoi(resatom.substr(0, 5).c_str()) >= membcount * 2 + watercount && !m2) // Bottom leaflet, top membrane
				{
					memb[2] = highest;
					lowest = 0xffff;
					highest = 0;
					m2 = true;
				}
				
				else if (resatom.substr(5, membname.length()).compare(membname.c_str()) == 0 && resatom.substr(14, 1).compare("N") == 0)
				{
					if (lowest > coords[2])
					{
						lowest = coords[2];
					}
					if (highest < coords[2])
						highest = coords[2];
						
				}
			}
			waterCheck();
		}

void Gro::waterCheck()
		{
			gro.clear();
			gro.seekg(0);
			while (!gro.eof())
			{
				splitLine();
				if (currentline.length() < 44)
					continue;
				if (resatom.substr(5, watername.length()).compare(watername.c_str()) == 0)
				{
					
					if (resatom.substr(10, 5).find("O") != -1)
					{
						for (int i = 0; i < 3; i++)
							water->o[i] = coords[i];
					}
					else if (resatom.substr(10, 5).find("H1") != -1)
					{
						for (int i = 0; i < 3; i++)
							water->h1[i] = coords[i];
					}
					else
					{
						for (int i = 0; i < 3; i++)
							water->h2[i] = coords[i];
							
						water->checkResult(memb, accdisp);
					}
				}
			}
		}

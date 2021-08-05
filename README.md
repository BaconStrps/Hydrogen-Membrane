# Usage
Usage: ./main.exe [options]

The program currently requires that the water molecules are arranged in the O, H1, H2 sequence in the .gro file.
It takes a topology file, reads it for the corresponding membrane (assuming a dual bilayer system is inputted),
calculates the boundaries of the membrane, then calculates how many hydrogens are facing the membrane on each water and adds them up
outputting everything to output.txt.

*THIS PROGRAM CURRENTLY ASSUMES THE HEADGROUP HAS A NITROGEN. THIS CAN BE CHANGED IN GRO.H AT LINE 136*

-f (step.gro) (string)
   	filename / path to file (.gro file)
-p (topol.top) (string
	filename / path to file (.top file)
-dr (3.1) (real)
   	the acceptable distance from the membrane to look for waters
-w (TIP3) (string)
	water residue name
-m (DPPC) (string)
	membrane residue name

# To Do
- Use a .trr file to check for multiple frames instead of just one with a .gro
- Clean everything up, it's kind of trashy at the moment.
- Get more useful information and usage out of the water class.

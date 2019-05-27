#include <iostream>
#include <string>
#include "ppm/ppm.h"
#include "Image.h"
#include "Array.h"
#include "Vec3.h"
#include "FilterLinear.h"
#include "FilterGamma.h"
#include "FilterBlur.h"
#include "FilterLaplace.h"
#include <cstdlib>

using namespace std;
using namespace math;

int main(int argc, char *argv[]){
	
	float aR, aG, aB, cR, cG, cB, gamma,N;
	Color a, c;
	
	Image img = Image();
	//img = Image(img);
	string filename = argv[argc - 1];
	
	//Load the image given as an argument
	bool loaded = img.load(filename, "ppm");
	if (!loaded){
		// Wrong/no image name
		return - 1;
	}
	
	//Create all filter objects
	FilterLinear fl;
	FilterGamma fg;
	FilterBlur fb;
	FilterLaplace flp;

	int position = 1;
	while (position < argc-2){
		if (strcmp(argv[position], "-f") == 0){
			position++;
			
			if (strcmp(argv[position], "linear") == 0){
				// When "linear" the next 6 arguments are r,g,b values of a and c colors , respectively
				aR = atof(argv[++position]);
				aG = atof(argv[++position]);
				aB = atof(argv[++position]);
				cR = atof(argv[++position]);
				cG = atof(argv[++position]);
				cB = atof(argv[++position]);

				a = { aR, aG, aB };
				c = { cR, cG, cB };
				//Create the linear filter
				fl = FilterLinear(a, c);
				//Apply the filter to the image
				img = fl << img;
				
				position++;
			}
			else if (strcmp(argv[position], "gamma") == 0){
				//When "gamma" the next argument is a float number that represents gamma.
				gamma = atof(argv[++position]);
				
				//Create the gamma filter
				fg = FilterGamma(gamma);
				
				//Apply the filter to the image
				img = fg << img;
				
				position++;
			}
			else if (strcmp(argv[position], "blur") == 0){
				//When "blur" the next argument is a float number that represents the size of the matrix used for the filter (N*N).
				N = atof(argv[++position]);

				//Create the blur filter
				fb = FilterBlur(N);
				
				//Apply the filter to the image
				img = fb << img;
				position++;
			}
			else if (strcmp(argv[position], "laplace") == 0){
				//When "laplace" we dont need any arguments.
				
				//Create the lamplace filter
				flp = FilterLaplace();
				
				//Apply the filter to the image
				img = flp << img;
				
				position++;
			}
			else{
				// wrong filter name used at the arguments
				cout << "Wrong filter"  << endl;
				return -1;
			}
		}
		else{
			// no filter found
			//break;
			return -1;
		}
	}
	//Change the name of the new image
	filename = "filtered_" + filename;

	//save the image
	bool saved = img.save(filename, "ppm");

	system("PAUSE");
	return 0;
}


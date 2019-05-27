#include "FilterGamma.h"
#include "Array.h"
#include "Image.h"
using namespace math;


Image FilterGamma::operator << (const Image & input){
	Image gammaFiltered = Image(input);

	//For each pixel do p'(i,j) = p(i,j) ^ gamma
	for (unsigned int j = 0; j <gammaFiltered.getHeight(); j++){
		for (unsigned int i = 0; i < gammaFiltered.getWidth(); i++){

			// create a new pixel 
			float red = gammaFiltered.getElement(i, j).r;
			float green = gammaFiltered.getElement(i, j).g;
			float blue = gammaFiltered.getElement(i, j).b;
			Color newColor = {red,green,blue};

			// multiply each component(r,g,b) with itself gamma times
			newColor.r = pow(newColor.r, gamma);
			newColor.g = pow(newColor.g, gamma);
			newColor.b = pow(newColor.b, gamma);

			
			// set the new pixel 
			gammaFiltered.setElement(i, j, newColor);
		}
	}

	return gammaFiltered ;

}
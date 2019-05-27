#include "FilterLaplace.h"
#include "Image.h"

using namespace math;

Image FilterLaplace::operator << (const Image & input){
	Color sumN = { 0, 0, 0 };
	Color sumM = { 0, 0, 0 };

	Image laplaceFiltered = Image(input);
	Image temp = Image(input);

	// For each pixel
	for (unsigned int i = 0; i < laplaceFiltered.getWidth(); i++){
		for (unsigned int j = 0; j < laplaceFiltered.getHeight(); j++){
			
			// For each neighbor pixel.
			for (int m = -1; m < 2; m++){
				for (int n = -1; n< 2; n++){
					sumN = (temp.getElement(i + m, j + n) * getElement(m+1,n+1)) + sumN;
				}
				sumM = sumN + sumM;
				sumN = 0;
			}
			//To clamp values that are under 0 or over 1
			sumM = sumM.clampToUpperBound(1);
			sumM = sumM.clampToLowerBound(0);
			
			//Set the new pixel
			laplaceFiltered.setElement(i, j, sumM);
			sumM = 0;
		}
	}


	return laplaceFiltered;
}
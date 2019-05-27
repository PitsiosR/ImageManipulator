#include "FilterBlur.h"
#include "Image.h"

using namespace math;

Image FilterBlur::operator << (const Image & input){
	
	Color sumN = { 0, 0, 0};
	Color sumM = { 0, 0, 0};
	float value = 1.0f / (N*N);
	
	Image blurFiltered = Image(input);
	Image temp = Image(input);
	int max;
	// If N is an even number we need to add 1.
	if (N % 2 == 1){
		max = N / 2 + 1;
	}
	else{
		max = N / 2;
	}
	
	//For each pixel
	for (unsigned int i = 0; i < blurFiltered.getWidth(); i++){
		for (unsigned int j = 0; j < blurFiltered.getHeight(); j++){
			// For each neighbor pixel.
			for (int m = -N/2; m < max; m++){
				for (int n = -N/2;  n< max; n++){
					
					// Check if the pixel is in bounds
					if (i + m >= 0 && i + m < blurFiltered.getWidth() && j + n >= 0 && j + n < blurFiltered.getHeight()){	
						sumN = (temp.getElement(i + m, j + n) * value) + sumN;
					}					
				}
				sumM = sumN + sumM;
				sumN = 0;		
			}

			// set the new pixel
			blurFiltered.setElement(i, j, sumM);		
			sumM = 0;
		}
	}

	
	return blurFiltered;
}
#include "FilterLinear.h"
#include "Array.h"
#include "Image.h"
using namespace math;


Image FilterLinear::operator << (const Image & input){
	Image linearFiltered = Image(input);
	
	//For each pixel do P'(x,y) = a * p(x,y) + c
	for (unsigned int j = 0; j <linearFiltered.getHeight(); j++){
		for (unsigned int i = 0; i < linearFiltered.getWidth(); i++){

			Color newColor = a * linearFiltered.getElement(i, j) + c;	

			//To clamp values that are under 0 or over 1
			newColor = newColor.clampToLowerBound(0);
			newColor = newColor.clampToUpperBound(1);

			//Set the pixel with the new value
			linearFiltered.setElement(i, j, newColor);
		}	
	}

	return linearFiltered;
	
}
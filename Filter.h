#ifndef _FILTER
#define _FILTER
#include "Image.h"

using namespace math;

class Filter{
	public:
		//constructor
		Filter(){};
		
		//copy constructor 
		Filter(const Filter &f){};
		
		//Operator << will be overloaded
		virtual Image operator << (const Image & image) = 0;

};
#endif
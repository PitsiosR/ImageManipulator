#ifndef _FILTERLAPLACE
#define _FILTERLAPLACE
#include "FilterBlur.h"

using namespace math;

class FilterLaplace : public FilterBlur {
	public:
		//Operator << overload
		Image operator << (const Image & image);

		//Default constructor
		FilterLaplace() :FilterBlur(){
			width = 3;
			height = 3;
			float value = 0.0f;
			buffer = std::vector<float>(9);
			
			setElement(0, 0, value);
			setElement(0, 2, value);
			setElement(2, 0, value);
			setElement(2, 2, value);

			value = 1.0f;
			setElement(0, 1, value);
			setElement(1, 0, value);
			setElement(1, 2, value);
			setElement(2, 1, value);

			value = -4.0f;
			setElement(1, 1, value);
		};
		
		//Copy constructor
		FilterLaplace(const FilterLaplace &f){
			FilterLaplace();
		};

		//Destructor
		~FilterLaplace(){};

};

#endif
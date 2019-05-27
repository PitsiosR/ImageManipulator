#ifndef _FILTERBLUR
#define _FILTERBLUR
#include "Filter.h"
using namespace math;

class FilterBlur : public Filter , public Array<float>{
	protected :
		int N;

	public:
	//Operator << overload
	Image operator << (const Image & image);

	//Constructor with unsigned int as argument
	FilterBlur(unsigned int n) : Array<float>(n, n) {
		N = n;
		float value = 1.0f / (n*n);
		for (int i = 0; i < n; i++){
			for (int j = 0; j < n; j++){
				setElement(i, j, value);
			}
		}
	};
	
	//Constructor with unsigned int and std::vector<float> as arguments
	FilterBlur(unsigned int n, const std::vector<float> data_ptr) : Array<float>(n, n, data_ptr){
		N = n;
		float value = 1.0f / (n*n);

		for (int i = 0; i < n; i++){
			for (int j = 0; j < n; j++){
				setElement(i, j, value);
			}
		}
	};

	//Default constructor
	FilterBlur() :Array<float>(){
		N = 0;
	};

	//Copy constructor
	FilterBlur(const FilterBlur &f){
		N = f.N;
	};

	//Destructor
	~FilterBlur(){};


	//Getters and setters
	int getN(){
		return N;
	};

	void setN(int n){
		N = n;
	};

};
#endif
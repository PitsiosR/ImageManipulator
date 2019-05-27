#ifndef _FILTERGAMMA
#define _FILTERGAMMA
#include "Filter.h"
using namespace std;

class FilterGamma : public Filter{
private:
	float gamma;

public:
	//Operator << overload
	Image operator << (const Image & image);

	//Constructor with a float as argument
	FilterGamma(float power){
		gamma = power;
	}
	
	//Default constructor
	FilterGamma(){
		gamma = 0;
	}
	
	//Copy constructor
	FilterGamma(const FilterGamma &f){
		gamma = f.gamma;
	};

	//Destructor
	~FilterGamma(){};

	//Getters and setters
	Color getGamma(){
		return gamma;
	}

	void setGamma(float power){
		gamma = power;
	}


};
#endif
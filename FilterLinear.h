#ifndef _FILTERLINEAR
#define _FILTERLINEAR
#include "Filter.h"
using namespace std;

class FilterLinear : public Filter{
	private: 
		Color a, c;
	
	public:
		//Operator << overload
		Image operator << (const Image & image);

		//Constructor with 2 colors as arguments
		FilterLinear(Color color1, Color color2){
			a = color1;
			c = color2;
		};
		
		//Default Constructor
		FilterLinear(){
			a = 0;
			c = 0;
		};
		
		//Copy Constructor
		FilterLinear(const FilterLinear &f){
			a = f.a;
			c = f.c;
		};

		//Destructor
		~FilterLinear(){};


		// Getters and setters
		Color getA(){
			return a;
		}

		Color getC(){
			return c;
		}

		void setA(Color newColor){
			a = newColor;
		}

		void setC(Color newColor){
			c = newColor;
		}
	
};
#endif

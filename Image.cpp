#include "Image.h"
#include "Array.h"
#include <vector>
#include "ppm/ppm.h"
#include <iostream>
#include <algorithm> //Used by transform operation.

namespace math
{

	Image::Image() : Array<Color>(){}

	Image::Image(unsigned int w, unsigned int h) : Array<Color>(w, h) {}

	Image::Image(unsigned int w, unsigned int h, const std::vector<Color> data_ptr) : Array<Color>(w, h, data_ptr){}

	Image::Image(const Array<Color> &src) :Array<Color>(src) {}

	Image::~Image(){
		buffer.clear();
	}



	bool Image::load(const std::string & filename, const std::string & format) {
		//Get the format of the image.
		std::string extension = filename.substr(filename.rfind("."));

		//transform(Iterator inputBegin, Iterator inputEnd,
		//Iterator OutputBegin, unary_operation)

		transform(extension.begin(), extension.end(), extension.begin(), ::tolower);

		// When the file format is ppm
		if (extension.compare(".ppm") == 0) {
			const char* file = filename.c_str();
			int h = 0;
			int w = 0;
			width = 0;
			height = 0;

			float* temp = imaging::ReadPPM(file, &w, &h);
			if (temp == nullptr) {
				return false;
			}

			width = w;
			height = h;
			buffer = std::vector<Color>(width*height);
			int j = 0;
			for (int i = 0; i < width*height * 3; i += 3) {
				
				buffer[j].r = temp[i];
				buffer[j].g = temp[i + 1];
				buffer[j].b = temp[i + 2];
				j++;
			}
			return true;
			delete temp;
		}
		else {
			return false;
		}

	}




	/*!
	* Stores the image data to the specified file, if the extension of the filename matches the format string.
	*
	* Only the "ppm" extension is supported for now. The extension comparison should be case-insensitive. If the
	* Image object is not initialized, the method should return immediately with a false return value.
	*
	* \param filename is the string of the file to write the image data to.
	* \param format specifies the file format according to which the image data should be encoded to the file.
	* Only the "ppm" format is a valid format string for now.
	*
	* \return true if the save operation completes successfully, false otherwise.
	*/



	bool Image::save(const std::string & filename, const std::string & format) {
		//Get the format of the image.
		std::string extension = filename.substr(filename.rfind("."));

		//transform(Iterator inputBegin, Iterator inputEnd,
		//Iterator OutputBegin, unary_operation)
		transform(extension.begin(), extension.end(), extension.begin(), ::tolower);

		// When the file format is ppm
		if (extension.compare(".ppm") == 0) {
			float * temp = new float[width*height * 3];
			int j = 0;
			for (int i = 0; i < width*height * 3; i += 3) {
				temp[i] = buffer[j].r;
				temp[i + 1] = buffer[j].g;
				temp[i + 2] = buffer[j].b;
				j++;
			}

			const char* file = filename.c_str();

			bool write = imaging::WritePPM(temp, width, height, file);
			return write;
			//delete [] temp;
		}
		else {
			return false;
		}
	}
}

#include "ppm.h"
#include <iostream>
#include <stdlib.h>
#include <string>
#include <cstring>
#include <cstdio>
#include <fstream>

using namespace std;
namespace imaging {

	float * ReadPPM(const char * filename, int * w, int * h) {

		//Open the file
		ifstream file;
		file.open(filename, ios::binary);

		//Check if the file is open
		if (!file.is_open()) {
			cout << "Could not open the file" << endl;
			return nullptr;
		}

		/* 
		*  temp_img contains the header of the image
		*  temp_img[0] contains the version of ppm (whether it is P6,P3 etc.).
		*  temp_img[1] contains the width of the image.
		*  temp_img[2] contains the height of the image.
		*  temp_img[3] contains the maximum allowed value of pixels (max = 255 in our case).
		*/
		string temp_img[4] = { "", "", "", "" };

		//Read the image header and save its values in temp_img accordingly.
		char next = (char)file.peek();
		for (int i = 0; i < 4; i++) {
			file >> temp_img[i];
			while ((next == '\n' || next == ' ' || next == '\t')) {
				next = (char)file.peek();
				file.get();

			}
		}
		
		//ignore the first whitespace.
		file.ignore(1, ' ');

		//Check if the header data contains correct values.
		
		if (strcmp(temp_img[0].c_str(), "P6") != 0) {
			cout << "The format of the file is not P6" << endl;
			return nullptr;
		}
		if (atoi(temp_img[3].c_str()) > 255) {
			cout << "The image is not 24 bit" << endl;
			return nullptr;
		}

		*w = atoi(temp_img[1].c_str());
		*h = atoi(temp_img[2].c_str());
		int maxValue = 0;
		maxValue = atoi(temp_img[3].c_str());

		int dimensions = 3 * *w * *h;
		unsigned char *buffer = new unsigned char[dimensions];
		file.read((char *)buffer, dimensions);
		float* temp = new float[dimensions];

		for (int i = 0; i < dimensions; i++) {
			temp[i] = buffer[i];
			//transform from int 0-255 to float 0.0-1.0
			temp[i] = temp[i] / maxValue;
		}
		file.close();

		return temp;

	}


	bool WritePPM(const float * data, int w, int h, const char * filename) {

		//Check if buffer is initialized
		if (data == nullptr) {
			cout << "Error creating the image !" << endl;
			return false;
		}
		ofstream file;
		file.open(filename, ofstream::out | ofstream::binary);
		
		//Write the header to the file.
		file << "P6" << endl;
		file << w << endl;
		file << h << endl;
		file << 255 << endl;

		int dimensions = 3 * w * h;

		//Change data from float 0.0-1.0 to int 0-255.
		unsigned char* temp_img = new unsigned char[dimensions];
		for (int i = 0; i < dimensions; i++) {
			temp_img[i] = data[i] * 255;
		}

		//Write the file.
		file.write((char *)temp_img, dimensions);
		file.close();

		cout << "The image is saved !" << endl;

		return true;
		delete temp_img;
	}

}
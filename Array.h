
#ifndef _ARRAY
#define _ARRAY

#include <string>
#include <iostream>
#include <vector>
#include "Vec3.h"

/*! The imaging namespace contains every class or function associated with the image storage, compression and manipulation.
*/
namespace math
{

	//------------------------------------ class Array ------------------------------------------------


	template <typename T>
	class Array
	{
	public:

	protected:
		std::vector<T> buffer;                              //! Holds the image data.

		unsigned int width, 						 //! The width of the image (in pixels)
			height;		                 //! The height of the image (in pixels)

	public:
		// metric accessors

		/*! Returns the width of the image
		*/
		const unsigned int getWidth() const { return width; }

		/*! Returns the height of the image
		*/
		const unsigned int getHeight() const { return height; }

		// data accessors

		/*! Obtains a pointer to the internal data.
		*
		*  This is NOT a copy of the internal image data, but rather a pointer
		*  to the internally allocated space, so DO NOT attempt to delete the pointer.
		*/
		std::vector<T> getRawDataPtr() {
			return buffer;
		}

		/*! Obtains the color of the image at location (x,y).
		*
		*  The method should do any necessary bounds checking.
		*
		*  \param x is the (zero-based) horizontal index of the pixel to get.
		*  \param y is the (zero-based) vertical index of the pixel to get.
		*
		*  \return The color of the (x,y) pixel as a Color object. Returns a black (0,0,0) color in case of an out-of-bounds x,y pair.
		*/
		T getElement(unsigned int x, unsigned int y) const {
			//Out of bounds case
			if ((x < 0) || (x > width - 1) || (y < 0) || (y > height - 1)) {
				T col = 0;
				return col;
			}
			else {
				return buffer.at(width*y + x);
			}
		}

		// data mutators

		/*! Sets the RGB values for an (x,y) pixel.
		*
		*  The method should perform any necessary bounds checking.
		*
		*  \param x is the (zero-based) horizontal index of the pixel to set.
		*  \param y is the (zero-based) vertical index of the pixel to set.
		*  \param value is the new color for the (x,y) pixel.
		*/
		void setElement(unsigned int x, unsigned int y, T & value) {
			//Out of bounds case
			if ((x < 0) || (x > width - 1) || (y < 0) || (y > height - 1)) {
				return;
			}
			else {
				buffer.at(y*width+x) = value;
			}
		}

		/*! Copies the image data from an external raw buffer to the internal image buffer.
		*
		*  The member function ASSUMES that the input buffer is of a size compatible with the internal storage of the
		*  Image object and that the data buffer has been already allocated. If the image buffer is not allocated or the
		*  width or height of the image are 0, the method should exit immediately.
		*
		*  \param data_ptr is the reference to the preallocated buffer from where to copy the data to the Image object.
		*/
		void setData(const std::vector<T> & data_ptr) {
			if (data_ptr.empty() || width == 0 || height == 0) {
				std::cout << " Wrong dimensions and/or faulty Image given" << std::endl;
				return;
			}
			else {
				//initialize the buffer and insert data
				buffer = std::vector<T>(width * height);
				buffer = data_ptr;

			}
		}

		// constructors and destructor

		/*! Default constructor.
		*
		* By default, the dimensions of the image should be zero and the buffer must be set to nullptr.
		*/
		Array() {
			width = 0;
			height = 0;
			buffer.clear();
		}

		/*! Constructor with width and height specification.
		*
		* \param width is the desired width of the new image.
		* \param height is the desired height of the new image.
		*/
		Array(unsigned int w, unsigned int h){
			width = w;
			height = h;
			buffer = std::vector<T>(width*height);
		}

		/*! Constructor with data initialization.
		*
		* \param width is the desired width of the new image.
		* \param height is the desired height of the new image.
		* \param data_ptr is the source of the data to copy to the internal image buffer.
		*
		* \see setData
		*/
		Array(unsigned int w, unsigned int h, const std::vector <T> data_ptr){
			width = w;
			height = h;
			setData(data_ptr);
		}

		/*! Copy constructor.
		*
		* \param src is the source image to replicate in this object.
		*/
		Array(const Array<T> &src){
			if (&src != this){
				width = src.getWidth();
				height = src.getHeight();
				buffer = std::vector<T>(width*height);
				const std::vector<T>temp_buffer = src.buffer;
				setData(temp_buffer);
			}
		}

		/*! The Image destructor.
		*/
		~Array(){
			buffer.clear();
		}

		/*! Copy assignment operator.
		*
		* \param right is the source image.
		*/
		Array<T> & operator = (const Array<T> & right) {
			width = right.getWidth();
			height = right.getHeight();
			buffer = std::vector<T>(width*height);
			const std::vector<T>temp_buffer = right.buffer;
			setData(temp_buffer);
			return *this;
		}
			
		// Operator () overload.
		T& operator() (unsigned int i, unsigned int j){
			if ((i < 0) || (i > width - 1) || (j < 0) || (j > height - 1)) {
				T col = Vec3<float>(0.0, 0.0, 0.0);
				return col;
			}
			else {
				return buffer.at(width*j + i);
			}
		}


	};

}

#endif
/**
 * File: block.cpp
 * Description: student implementation for Block functions
 *              for CPSC 221 2023W1 PA1
 *
 *              THIS FILE WILL BE SUBMITTED.
**/

#include "block.h"

/**
 * Creates a square Block that is dimension x dimension pixels in size,
 * starting at (x, y) on img. Assumes that the requested
 * Block fits on the image (inputs are feasible)
**/
void Block::Build(PNG& img, unsigned int x, unsigned int y, unsigned int dimension) {
	// complete your implementation below
	data.resize(dimension);
	for (unsigned int row=0; row<dimension; row++) {
		data[row].resize(dimension);
		for (unsigned int column=0; column<dimension; column++) {
			data[row][column] = *(img.getPixel(row + y,column + x));
		}
	}
    
}

/**
 * Renders this Block onto img with its upper-left corner at (x, y).
 * Assumes block fits on the image.
 * 
 * @param full - whether to render the entire contents to the target PNG,
 *               or the average color to a single pixel in the target PNG.
**/
void Block::Render(PNG& img, unsigned int x, unsigned int y, bool full) const {
	// complete your implementation below
	int dimension = Dimension();

	if (full) {
		for (int row=0; row<dimension; row++) {
			for (int column=0; column<dimension; column++) {
				*(img.getPixel(row + y,column + x)) = data[row][column];
			}
		}
	} else {
		RGBAPixel averageColor = GetAverageColor();
		img.getPixel(y,x)->r = averageColor.r;
		img.getPixel(y,x)->g = averageColor.g;
		img.getPixel(y,x)->b = averageColor.b;
		img.getPixel(y,x)->a = averageColor.a;
	}	
}

/**
 * Flips the Block's pixel data horizontally by a simple reflection
 * across the vertical axis through its middle.
**/
void Block::FlipHorizontal() {
	// complete your implementation below
	int dimension = Dimension();

	for (int row=0; row<dimension/2; row++) {
		for (int column=0; column<dimension; column++) {
			RGBAPixel temp = data[row][column];
			data[row][column] = data[dimension-1-row][column];
			data[dimension-1-row][column] = temp;
		}
	}	
}

/**
 * Flips the Block's pixel data vertically by a simple reflection
 * across the horizontal axis through its middle.
**/
void Block::FlipVertical() {
	// complete your implementation below
	int dimension = Dimension();

	for (int column=0; column<dimension/2; column++) {
		for (int row=0; row<dimension; row++) {
			RGBAPixel temp = data[row][column];
			data[row][column] = data[row][dimension-1-column];
			data[row][dimension-1-column] = temp;
		}
	}	
}

/**
 * Returns the dimension of the block (its width or height).
 */
unsigned int Block::Dimension() const {
	// replace the statement below with your implementation
	return data[0].size();
}

/**
 * Returns the average color of the pixels in the block's data.
**/
RGBAPixel Block::GetAverageColor() const {
	// replace the statement below with your implementation
	int dimension = Dimension();
	int red=0, green=0, blue=0;
	double alpha=0.0;
	int num_pixcels = dimension * dimension;

	for (int row=0; row<dimension; row++) {
		for (int column=0; column<dimension; column++) {
			red += data[row][column].r;
			green += data[row][column].g;
			blue += data[row][column].b;
			alpha += data[row][column].a;
		}
	}

	red = red/num_pixcels;
	green = green/num_pixcels;
	blue = blue/num_pixcels;
	alpha = alpha/num_pixcels;

	return RGBAPixel(red,green,blue,alpha);
}

/**
 * Replaces all pixel data in the block with the block's average color.
**/
void Block::FillAverage() {
	// complete your implementation below
	RGBAPixel averageColor = GetAverageColor();
	int dimension = Dimension();

	for (int row=0; row<dimension; row++) {
		for (int column=0; column<dimension; column++) {
			data[row][column].r = averageColor.r;
			data[row][column].g = averageColor.g;
			data[row][column].b = averageColor.b;
			data[row][column].a = averageColor.a;
		}
	}
}
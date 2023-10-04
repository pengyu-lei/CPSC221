#include <iostream>
using namespace std;
/**
 * File: chain.cpp
 * Description: student implementation for Chain functions
 *              for CPSC 221 2023W1 PA1
 *
 *              THIS FILE WILL BE SUBMITTED.
**/

#include <math.h>

#include "chain.h"

/**
 * Constructs a Chain from an input image
 * Each Node will cover a nodedimension x nodedimension (in pixels)
 * region in the source image.
 * @param img the input image
 * @param nodedimension number of pixels along the width and height of the Block region
 * @pre input image's width and height are evenly divisible by nodedimension
**/
Chain::Chain(PNG& img, unsigned int nodedimension) {
	// complete your implementation below
	NW = NULL;
	SE = NULL;
	length_ = 0;
	
	for (unsigned int column=0; column<img.height(); column+=nodedimension) {
		for (unsigned int row=0; row<img.width(); row+=nodedimension) {
			Block b;
			b.Build(img, column, row, nodedimension);
			InsertBack(b);
		}
	}
    
}

/**
 * Renders the Chain's pixel data into an output PNG.
 * The PNG should be sized according to the number of nodes
 * specified by the cols parameter.
 * It is possible that there may not be enough nodes to fill
 * the bottom row of the PNG. If this happens, just render
 * as many nodes as there are, from left to right, and leave
 * the rest of the row as opaque white pixels.
 * @pre this Chain is not empty
 * @param cols the number of Blocks to use for the width of the image
 * @param full whether to render all pixel data into a full-size image,
 *             or block averages into a tiny image
**/
PNG Chain::Render(unsigned int cols, bool full) {
	// replace the line below with your implementation
	int dimension = NW->data.Dimension();
	PNG img;
	RGBAPixel white_pixel(255,255,255,1);

	if (full) {
		if (length_%cols == 0) {
			img.resize(cols*dimension, (length_/cols)*dimension);
		} else {
			img.resize(cols*dimension, (length_/cols+1)*dimension);
		}
		
		Node *curr = NW;
		for (unsigned int column=0; column<img.height(); column+=dimension) {
			for (unsigned int row=0; row<img.width(); row+=dimension) {
				if (curr != nullptr) {
					curr->data.Render(img, column, row, true);
					curr = curr->next;
				} else {
					for (int x=0; x<dimension; x++) {
						for (int y=0; y<dimension; y++) {
						*(img.getPixel(row + y,column + x)) = white_pixel;
						}
					}
				}		
			}
		}
	} else {
		if (length_%cols == 0) {
			img.resize(cols, length_/cols);
		} else {
			img.resize(cols, length_/cols+1);
		}

		for(unsigned int row=0; row<img.width(); row++) {
			for(unsigned int column=0; column<img.height(); column++) {
				RGBAPixel *pixel = img.getPixel(row, column);
				pixel->r = 255;
				pixel->g = 255;
				pixel->b = 255;
				pixel->a = 1.0;
			}
		}
		
		Node *curr = NW;
		for (unsigned int column=0; column<img.height(); column++) {
			for (unsigned int row=0; row<img.width(); row++) {
				if (curr != nullptr) {
					curr->data.Render(img, column, row, false);
					curr = curr->next;
				}			
			}
		}	
	}
	return img;
}

/**
 * Inserts a new Node containing ndata at the back of the Chain
**/
void Chain::InsertBack(const Block& ndata) {
	// complete your implementation below
	if (NW == nullptr) {
		NW = new Node(ndata);
		SE = NW;
		length_++;
	} else {
		SE->next = new Node(ndata);
		SE->next->prev = SE;
		SE= SE->next;
		length_++;
	}
}

/**
 * Reverses the structure of the list. This must be done by
 * pointer assignments. You may not deallocate or allocate any Nodes.
 * Example:
 *	before:	NW -> A <-> B <-> C <-> D <-> E <-> F <-> G <-> H <- SE
 *  
 *  after:	NW -> H <-> G <-> F <-> E <-> D <-> C <-> B <-> A <- SE
**/
void Chain::Reverse() {
	// complete your implementation below
	Node *curr = NW, *prev = curr->prev, *next = nullptr;
	while (curr != nullptr) {
		next = curr->next;
		curr->prev = next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}

	Node *temp = NW;
	NW = SE;
	SE = temp;
}

/**
 * Rearranges the Node structure and internal pixel data to be flipped over a vertical axis.
 * This must be done using pointer assignments.
 * You may not deallocate or allocate any Nodes.
 * Example, length = 6:
 *  before, flipping with 3 columns (2 rows):
 *
 *		NW -> A> <-> B> <-> C> <->
 *            D> <-> E> <-> F> <- SE
 * 
 *  after, visualized with 3 columns (2 rows):
 * 
 *		NW -> <C <-> <B <-> <A <->
 *            <F <-> <E <-> <D <- SE
 * 
 * @param cols number of Blocks to use for the initial width of the image
 * @pre length_ is divisible by cols (i.e. no "partially-filled" rows)
**/
void Chain::FlipHorizontal(unsigned int cols) {
	// complete your implementation below
	int rows = length_/cols;

	for (int i=0; i<rows; i++) {
		ReverseBetween(i*cols+1, (i+1)*cols);
	}
	
	Node *curr = NW;
	while (curr != nullptr) {
		curr->data.FlipHorizontal();
		curr = curr->next;
	}
}

/**
 * Rearranges the Node structure and internal pixel data to be flipped over a horizontal axis.
 * This must be done using pointer assignments.
 * You may not deallocate or allocate any Nodes.
 * Example, length = 6:
 *	before, flipping with 3 columns (2 rows):
 *                         
 *      NW -> A <-> B <-> C <->
 *            D <-> E <-> F <- SE
 * 
 *  after, visualized with 3 columns (2 rows):
 * 
 *      NW -> D <-> E <-> F <->
 *            A <-> B <-> C <- SE
 * 
 * @param cols number of Blocks to use for the initial width of the image
 * @pre length_ is divisible by cols (i.e. no "partially-filled" rows)
**/
void Chain::FlipVertical(unsigned int cols) {
	// complete your implementation below
    int rows = length_/cols;

	for (unsigned int i=1; i<=cols; i++) {
		for (int j=1; j<=rows/2; j++) {
			swap((j-1)*cols+i,(rows-j)*cols+i);
		}
	}

	Node *curr = NW;
	while (curr != nullptr) {
		curr->data.FlipVertical();
		curr = curr->next;
	}
}

/**
 * Produces a blocky, pixellated effect (in a rendered image) by replacing each
 * block's pixel data with the average color of the block.
**/
void Chain::Blockify() {
	// complete your implementation below
	Node *curr = NW;
	while (curr != nullptr) {
		curr->data.FillAverage();
		curr = curr->next;
	}
}

/**
 * Destroys all dynamically allocated memory associated with
 * this Chain object. Called by destructor and operator=.
 * You must complete its implementation for PA1.
**/
void Chain::Clear() {
	// complete your implementation below
	if (NW == nullptr) return;
	
	Node *curr = NW->next;
	while (curr != nullptr) {
		curr->prev->next = nullptr;
		delete curr->prev;
		curr->prev=nullptr;
		if (curr->next == nullptr) {
			delete curr;
			curr = nullptr;
		} else {
			curr=curr->next;
		}
	}
    NW = nullptr;
	SE = nullptr;
	length_ = 0;
}

/**
 * Copies the parameter other Chain into the current Chain.
 * Does not free any memory. Called by copy constructor and
 * operator=.
 * You must complete its implementation for PA1.
 * @param other The Chain to be copied.
**/
void Chain::Copy(const Chain& other) {
	// complete your implementation below
	NW = NULL;
	SE = NULL;
	length_ = 0;
	Node *currOld = other.NW;

	if (currOld == nullptr) return;
	while (currOld != nullptr) {
		InsertBack(currOld->data);
		currOld = currOld->next;
	}
}

/**
 * If you have declared any private helper functions in chain_private.h,
 * add your completed implementations below.
**/

void Chain::ReverseBetween(int left_, int right_) {
	cout<<left_<<right_<<endl;
	Node *left = GoTo(NW, left_-1);
	Node *right = GoTo(NW, right_-1);

	Node *start = nullptr, *end = nullptr;

	if(left->prev == nullptr) {
		start = nullptr;
		end = right->next;

		end->prev = nullptr;
		right->next = nullptr;
	} else if (right->next == nullptr) {
		start = left->prev;
		end = nullptr;

		start->next = nullptr;
		left->prev = nullptr;
	} else {
		start = left->prev;
		end = right->next;

		start->next = nullptr;
		left->prev = nullptr;

		end->prev = nullptr;
		right->next = nullptr;
	}

	Node *curr = left, *prev = curr->prev, *next = nullptr;
	while (curr != nullptr) {
		next = curr->next;
		curr->prev = next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}

	Node *temp = right;
	right = left;
	left = temp;

	if(start == nullptr) {
		end->prev = right;
		right->next = end;
		left->prev = nullptr;
		NW = left;
	} else if (end == nullptr) {
		start->next = left;
		left->prev = start;
		right->next = nullptr;
		SE = right;
	} else {
		start->next = left;
		left->prev = start;

		end->prev = right;
		right->next = end;
	}
}

Node* Chain::GoTo(Node *curr, int i) {
	if (i == 0 || curr == nullptr)
		return curr;
	else
		return GoTo(curr->next, i-1);
}

void Chain::swap(int i, int j) {
	Node *nodei = GoTo(NW, i-1);
	Node *nodej = GoTo(NW, j-1);

	Node *temp_prev = nullptr, *temp_next = nullptr;
	if (nodei->prev == nullptr) {
		temp_prev = nullptr;
		temp_next = nodei->next;

		temp_next->prev = nullptr;
		nodei->next = nullptr;

		nodej->prev->next = nodei;
		nodei->prev = nodej->prev;
		nodej->next->prev = nodei;
		nodei->next = nodej->next;

		nodej->prev = temp_prev;
		nodej->next = temp_next;
		temp_next->prev = nodej;

		NW = nodej;
	} else if (nodej->next == nullptr) {
		temp_prev = nodei->prev;
		temp_next = nodei->next;

		temp_prev->next = nullptr;
		nodei->prev = nullptr;
		temp_next->prev = nullptr;
		nodei->next = nullptr;
	
		nodej->prev->next = nodei;
		nodei->prev = nodej->prev;
		nodei->next = nodej->next;

		nodej->prev = temp_prev;
		temp_prev->next = nodej;
		nodej->next = temp_next;
		temp_next->prev = nodej;

		SE = nodei;
	} else {
		temp_prev = nodei->prev;
		temp_next = nodei->next;

		temp_prev->next = nullptr;
		nodei->prev = nullptr;
		temp_next->prev = nullptr;
		nodei->next = nullptr;
	
		nodej->prev->next = nodei;
		nodei->prev = nodej->prev;
		nodej->next->prev = nodei;
		nodei->next = nodej->next;

		nodej->prev = temp_prev;
		temp_prev->next = nodej;
		nodej->next = temp_next;
		temp_next->prev = nodej;
	}
}


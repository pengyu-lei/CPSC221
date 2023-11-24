/**
 * @file qtree.cpp
 * @description student implementation of QTree class used for storing image data
 *              CPSC 221 PA3
 *
 *              SUBMIT THIS FILE
 */

#include "qtree.h"

/**
 * Constructor that builds a QTree out of the given PNG.
 * Every leaf in the tree corresponds to a pixel in the PNG.
 * Every non-leaf node corresponds to a rectangle of pixels
 * in the original PNG, represented by an (x,y) pair for the
 * upper left corner of the rectangle and an (x,y) pair for
 * lower right corner of the rectangle. In addition, the Node
 * stores a pixel representing the average color over the
 * rectangle.
 *
 * The average color for each node in your implementation MUST
 * be determined in constant time. HINT: this will lead to nodes
 * at shallower levels of the tree to accumulate some error in their
 * average color value, but we will accept this consequence in
 * exchange for faster tree construction.
 * Note that we will be looking for specific color values in our
 * autograder, so if you instead perform a slow but accurate
 * average color computation, you will likely fail the test cases!
 *
 * Every node's children correspond to a partition of the
 * node's rectangle into (up to) four smaller rectangles. The node's
 * rectangle is split evenly (or as close to evenly as possible)
 * along both horizontal and vertical axes. If an even split along
 * the vertical axis is not possible, the extra line will be included
 * in the left side; If an even split along the horizontal axis is not
 * possible, the extra line will be included in the upper side.
 * If a single-pixel-wide rectangle needs to be split, the NE and SE children
 * will be null; likewise if a single-pixel-tall rectangle needs to be split,
 * the SW and SE children will be null.
 *
 * In this way, each of the children's rectangles together will have coordinates
 * that when combined, completely cover the original rectangle's image
 * region and do not overlap.
 */
QTree::QTree(const PNG& imIn) {
	// ADD YOUR IMPLEMENTATION BELOW
	pair<unsigned int, unsigned int> ul = make_pair(0, 0);
	pair<unsigned int, unsigned int> lr = make_pair(imIn.width()-1, imIn.height()-1);
	//cout<<lr.first<<","<<lr.second<<endl;
	height = imIn.height();
	width = imIn.width();
	root = BuildNode(imIn, ul, lr);
}

/**
 * Overloaded assignment operator for QTrees.
 * Part of the Big Three that we must define because the class
 * allocates dynamic memory. This depends on your implementation
 * of the copy and clear funtions.
 *
 * @param rhs The right hand side of the assignment statement.
 */
QTree& QTree::operator=(const QTree& rhs) {
	// ADD YOUR IMPLEMENTATION BELOW
	if (this != &rhs) {
		ClearHelper(root);
		root = CopyHelper(rhs.root);
	}
	return *this;
}

/**
 * Render returns a PNG image consisting of the pixels
 * stored in the tree. may be used on pruned trees. Draws
 * every leaf node's rectangle onto a PNG canvas using the
 * average color stored in the node.
 *
 * For up-scaled images, no color interpolation will be done;
 * each rectangle is fully rendered into a larger rectangular region.
 *
 * @param scale multiplier for each horizontal/vertical dimension
 * @pre scale > 0
 */
PNG QTree::Render(unsigned int scale) const {
	// Replace the line below with your implementation
	PNG out(width*scale, height*scale);
	RenderHelper(out, root, scale);
	return out;
}

/**
 *  Prune function trims subtrees as high as possible in the tree.
 *  A subtree is pruned (cleared) if all of the subtree's leaves are within
 *  tolerance of the average color stored in the root of the subtree.
 *  NOTE - you may use the distanceTo function found in RGBAPixel.h
 *  Pruning criteria should be evaluated on the original tree, not
 *  on any pruned subtree. (we only expect that trees would be pruned once.)
 *
 * You may want a recursive helper function for this one.
 *
 * @param tolerance maximum RGBA distance to qualify for pruning
 * @pre this tree has not previously been pruned, nor is copied from a previously pruned tree.
 */
void QTree::Prune(double tolerance) {
	// ADD YOUR IMPLEMENTATION BELOW
	PruneHelper(root, tolerance);
}

/**
 *  FlipHorizontal rearranges the contents of the tree, so that
 *  its rendered image will appear mirrored across a vertical axis.
 *  This may be called on a previously pruned/flipped/rotated tree.
 *
 *  After flipping, the NW/NE/SW/SE pointers must map to what will be
 *  physically rendered in the respective NW/NE/SW/SE corners, but it
 *  is no longer necessary to ensure that 1-pixel wide rectangles have
 *  null eastern children
 *  (i.e. after flipping, a node's NW and SW pointers may be null, but
 *  have non-null NE and SE)
 * 
 *  You may want a recursive helper function for this one.
 */
void QTree::FlipHorizontal() {
	// ADD YOUR IMPLEMENTATION BELOW 
	FlipHelper(root);
}

/**
 *  RotateCCW rearranges the contents of the tree, so that its
 *  rendered image will appear rotated by 90 degrees counter-clockwise.
 *  This may be called on a previously pruned/flipped/rotated tree.
 *
 *  Note that this may alter the dimensions of the rendered image, relative
 *  to its original dimensions.
 *
 *  After rotation, the NW/NE/SW/SE pointers must map to what will be
 *  physically rendered in the respective NW/NE/SW/SE corners, but it
 *  is no longer necessary to ensure that 1-pixel tall or wide rectangles
 *  have null eastern or southern children
 *  (i.e. after rotation, a node's NW and NE pointers may be null, but have
 *  non-null SW and SE, or it may have null NW/SW but non-null NE/SE)
 *
 *  You may want a recursive helper function for this one.
 */
void QTree::RotateCCW() {
	// ADD YOUR IMPLEMENTATION BELOW
	swap(height, width);
	swap(root->lowRight.first, root->lowRight.second);
	//cout<<root->lowRight.first<<","<<root->lowRight.second<<endl;
	RotateHelper(root);
}

/**
 * Destroys all dynamically allocated memory associated with the
 * current QTree object. Complete for PA3.
 * You may want a recursive helper function for this one.
 */
void QTree:: Clear() {
	// ADD YOUR IMPLEMENTATION BELOW
	if (root != nullptr) {
		ClearHelper(root);
	}
}

/**
 * Copies the parameter other QTree into the current QTree.
 * Does not free any memory. Called by copy constructor and operator=.
 * You may want a recursive helper function for this one.
 * @param other The QTree to be copied.
 */
void QTree::Copy(const QTree& other) {
	// ADD YOUR IMPLEMENTATION BELOW
	root = CopyHelper(other.root);
}

/**
 * Private helper function for the constructor. Recursively builds
 * the tree according to the specification of the constructor.
 * @param img reference to the original input image.
 * @param ul upper left point of current node's rectangle.
 * @param lr lower right point of current node's rectangle.
 */
Node* QTree::BuildNode(const PNG& img, pair<unsigned int, unsigned int> ul, pair<unsigned int, unsigned int> lr) {
	// Replace the line below with your implementation
	Node* newNode = new Node(ul, lr, RGBAPixel(0, 0, 0));
	
	//base case: one single pixel
	if (ul == lr) {
		newNode->avg = *img.getPixel(ul.first, ul.second);
		return newNode;
	}

	int centerHeight, centerWidth;
	int width = lr.first - ul.first+1;
	int height = lr.second - ul.second+1;

	//一格高
	if (ul.second == lr.second) {
		//cout<<"一格高"<<endl;
		if (width%2 == 0) {
			centerWidth = width/2-1;
		} else {
			centerWidth = width/2;
		}

		pair<int, int> NWul = ul;
		pair<int, int> NWlr = make_pair(ul.first+centerWidth, ul.second);
		pair<int, int> NEul = make_pair(ul.first+centerWidth+1, ul.second);
		pair<int, int> NElr = lr;

		newNode->NW = BuildNode(img, NWul, NWlr);
		newNode->NE = BuildNode(img, NEul, NElr);
	} 
	//一格宽
	else if (ul.first == lr.first) { 

		if (height%2 == 0) {
			centerHeight = height/2 - 1;
		} else {
			centerHeight = height/2;
		}
		pair<int, int> NWul = ul;
		pair<int, int> NWlr = make_pair(ul.first, ul.second+centerHeight);
		pair<int, int> SWul = make_pair(ul.first, ul.second+centerHeight+1);
		pair<int, int> SWlr = lr;
		newNode->NW = BuildNode(img, NWul, NWlr);
		newNode->SW = BuildNode(img, SWul, SWlr);
	} else {
		if (height%2 == 0) {
			centerHeight = height/2 - 1;
		} else {
			centerHeight = height/2;
		}
		if (width%2 == 0) {
			centerWidth = width/2-1;
		} else {
			centerWidth = width/2;
		}
	
		pair<int, int> NWul = ul;
		pair<int, int> NWlr = make_pair(ul.first+centerWidth, ul.second+centerHeight);

		pair<int, int> NEul = make_pair(ul.first+centerWidth+1, ul.second);
		pair<int, int> NElr = make_pair(lr.first, ul.second+centerHeight);

		pair<int, int> SWul = make_pair(ul.first, ul.second+centerHeight+1);
		pair<int, int> SWlr = make_pair(ul.first+centerWidth, lr.second);

		pair<int, int> SEul = make_pair(ul.first+centerWidth+1, ul.second+centerHeight+1);
		pair<int, int> SElr = lr;

		newNode->NW = BuildNode(img, NWul, NWlr);
		newNode->NE = BuildNode(img, NEul, NElr);
		newNode->SW = BuildNode(img, SWul, SWlr);
		newNode->SE = BuildNode(img, SEul, SElr);
	}
	//calculate the average color from  2 or 4 children
	newNode->avg = calculateAvg(newNode);
	return newNode;
}

/*********************************************************/
/*** IMPLEMENT YOUR OWN PRIVATE MEMBER FUNCTIONS BELOW ***/
/*********************************************************/

RGBAPixel QTree::calculateAvg(Node* node) {

	if (node->SW==nullptr && node->SE==nullptr) {
		//cout<<"一格高"<<endl;
		RGBAPixel NWAvg = node->NW->avg;
		RGBAPixel NEAvg = node->NE->avg;
		int NWArea = (node->NW->lowRight.first - node->NW->upLeft.first+1) * (node->NW->lowRight.second - node->NW->upLeft.second+1);
		int NEArea = (node->NE->lowRight.first - node->NE->upLeft.first+1) * (node->NE->lowRight.second - node->NE->upLeft.second+1);
		int totalArea = NWArea+NEArea;

		double red = (NWAvg.r*NWArea + NEAvg.r*NEArea)/totalArea;
		double green = (NWAvg.g*NWArea + NEAvg.g*NEArea)/totalArea;
		double blue = (NWAvg.b*NWArea + NEAvg.b*NEArea)/totalArea; 
		return RGBAPixel(red, green, blue);
	} else if (node->NE==nullptr && node->SE==nullptr) {
		//cout<<"一格宽"<<endl;
		RGBAPixel NWAvg = node->NW->avg;
		RGBAPixel SWAvg = node->SW->avg;
		int NWArea = (node->NW->lowRight.first - node->NW->upLeft.first+1) * (node->NW->lowRight.second - node->NW->upLeft.second+1);
		int SWArea = (node->SW->lowRight.first - node->SW->upLeft.first+1) * (node->SW->lowRight.second - node->SW->upLeft.second+1);
		int totalArea = NWArea+SWArea;

		double red = (NWAvg.r*NWArea + SWAvg.r*SWArea)/totalArea;
		double green = (NWAvg.g*NWArea + SWAvg.g*SWArea)/totalArea;
		double blue = (NWAvg.b*NWArea + SWAvg.b*SWArea)/totalArea; 
		return RGBAPixel(red, green, blue);
	} else {
		//cout<<"正常情况"<<endl;
		RGBAPixel NWAvg = node->NW->avg;
		RGBAPixel NEAvg = node->NE->avg;
		RGBAPixel SWAvg = node->SW->avg;
		RGBAPixel SEAvg = node->SE->avg;

		int NWArea = (node->NW->lowRight.first - node->NW->upLeft.first+1) * (node->NW->lowRight.second - node->NW->upLeft.second+1);
		int NEArea = (node->NE->lowRight.first - node->NE->upLeft.first+1) * (node->NE->lowRight.second - node->NE->upLeft.second+1);
		int SWArea = (node->SW->lowRight.first - node->SW->upLeft.first+1) * (node->SW->lowRight.second - node->SW->upLeft.second+1);
		int SEArea = (node->SE->lowRight.first - node->SE->upLeft.first+1) * (node->SE->lowRight.second - node->SE->upLeft.second+1);
		int totalArea = NWArea+NEArea+SWArea+SEArea;

		double red = (NWAvg.r*NWArea + NEAvg.r*NEArea + SWAvg.r*SWArea + SEAvg.r*SEArea)/totalArea;
		double green = (NWAvg.g*NWArea + NEAvg.g*NEArea + SWAvg.g*SWArea + SEAvg.g*SEArea)/totalArea;
		double blue = (NWAvg.b*NWArea + NEAvg.b*NEArea + SWAvg.b*SWArea + SEAvg.b*SEArea)/totalArea;
		return RGBAPixel(red, green, blue);
	}	
}

void QTree::RenderHelper(PNG& img, Node* subroot, int scale) const {
	if(subroot == nullptr) return;

	if (scale != 1) {
		if (subroot->upLeft == subroot->lowRight) {
			int xx = subroot->upLeft.first*scale;
			int yy = subroot->upLeft.second*scale;
			for(int i=0;i<scale;i++) {
				for (int j=0;j<scale;j++) {
					*img.getPixel(xx+i, yy+j) = subroot->avg;
				}
			}
		return;
		}
	} else {
		int width = subroot->lowRight.first - subroot->upLeft.first+1;
		int height = subroot->lowRight.second - subroot->upLeft.second+1;

		for (int x = 0; x < width; x++) {
			for (int y = 0; y < height; y++) {
				*img.getPixel(subroot->upLeft.first + x, subroot->upLeft.second + y) = subroot->avg;
    		}
  		}
	}
	

	
	RenderHelper(img, subroot->NW, scale);
	RenderHelper(img, subroot->NE, scale);
	RenderHelper(img, subroot->SW, scale);
	RenderHelper(img, subroot->SE, scale);
}

void QTree::ClearHelper(Node* subroot) {
	if(subroot == nullptr) return;

	ClearHelper(subroot->NW);
	ClearHelper(subroot->NE);
	ClearHelper(subroot->SW);
	ClearHelper(subroot->SE);
	delete subroot;
	subroot = nullptr;
}

Node* QTree::CopyHelper(Node* other) {
	if (other == nullptr) return nullptr;

	Node* newNode = new Node(other->upLeft, other->lowRight, other->avg);
	newNode->NW = CopyHelper(other->NW);
	newNode->NE = CopyHelper(other->NE);
	newNode->SW = CopyHelper(other->SW);
	newNode->SE = CopyHelper(other->SE);

	return newNode;
}

void QTree::PruneHelper(Node* subroot, double tolerance) {
	if (!subroot) return;

	if (ShouldPrune(subroot->avg, subroot, tolerance)) {
		ClearHelper(subroot->NW);
    	ClearHelper(subroot->NE);
		ClearHelper(subroot->SW);
		ClearHelper(subroot->SE);
    	subroot->NW = nullptr;
    	subroot->NE = nullptr;
		subroot->SW = nullptr;
    	subroot->SE = nullptr;

  	} else {
    	PruneHelper(subroot->NW, tolerance);
    	PruneHelper(subroot->NE, tolerance);
		PruneHelper(subroot->SW, tolerance);
		PruneHelper(subroot->SE, tolerance);
	}
}

bool QTree::ShouldPrune(RGBAPixel rootAvgColor, Node* subroot, double tolerance) {
	if (!subroot) return true;

	if (!subroot->NW && !subroot->NE && !subroot->SW && !subroot->SE) {
    	return rootAvgColor.distanceTo(subroot->avg) <= tolerance;
  	} else {
    	return (ShouldPrune(rootAvgColor, subroot->NW, tolerance) 
			&& ShouldPrune(rootAvgColor, subroot->NE, tolerance)
			&& ShouldPrune(rootAvgColor, subroot->SW, tolerance)
			&& ShouldPrune(rootAvgColor, subroot->SE, tolerance));
  	}
}

void QTree::FlipHelper(Node* subroot) {
	if (!subroot) return;

	pair<int, int> ul = subroot->upLeft;
	pair<int, int> lr = subroot->lowRight;
	int rightWidth, leftWidth, upHeight, lowHeight;
	int width = lr.first - ul.first+1;
	int height = lr.second - ul.second+1;
	Node* NW = subroot->NW;
	Node* NE = subroot->NE;
	Node* SW = subroot->SW;
	Node* SE = subroot->SE;

	//single pixel
	if(!NW && !NE && !SW && !SE) {
		return;
  	}

	//W
	else if(NE == nullptr && SE == nullptr) {
		lowHeight = SW->lowRight.second - SW->upLeft.second + 1;
		upHeight = height - lowHeight;

		NW->upLeft = ul;
		NW->lowRight = {ul.first, ul.second+upHeight-1};
		SW->upLeft = {ul.first, ul.second+upHeight};
		SW->lowRight = lr;

		swap(subroot->NW,subroot->NE);
	 	swap(subroot->SW,subroot->SE);

		FlipHelper(subroot->NE);
		FlipHelper(subroot->SE);
	}

	//E
	else if(NW == nullptr && SW == nullptr) {
		lowHeight = SE->lowRight.second - SE->upLeft.second + 1;
		upHeight = height - lowHeight;

		NE->upLeft = ul;
		NE->lowRight = {ul.first, ul.second+upHeight-1};
		SE->upLeft = {ul.first, ul.second+upHeight};
		SE->lowRight = lr;

		swap(subroot->NW,subroot->NE);
	 	swap(subroot->SW,subroot->SE);

		FlipHelper(subroot->NW);
		FlipHelper(subroot->SW);
	}

	//N
	else if(SW == nullptr && SE == nullptr) {
		rightWidth = NE->lowRight.first - NE->upLeft.first + 1;
		leftWidth = width - rightWidth;

		NW->upLeft = {ul.first+rightWidth, ul.second};
		NW->lowRight = lr;
		NE->upLeft = ul;
		NE->lowRight = {ul.first+rightWidth-1, ul.second};

		swap(subroot->NW,subroot->NE);

		FlipHelper(subroot->NW);
		FlipHelper(subroot->NE);
	}

	//S
	else if(NW == nullptr && NE == nullptr) {
		rightWidth = SE->lowRight.first - SE->upLeft.first + 1;
		leftWidth = width - rightWidth;

		SW->upLeft = {ul.first+rightWidth, ul.second};
		SW->lowRight = lr;
		SE->upLeft = ul;
		SE->lowRight = {ul.first+rightWidth-1, ul.second};

		swap(subroot->SW,subroot->SE);

		FlipHelper(subroot->SW);
		FlipHelper(subroot->SE);
	}

	//4 children
	else {
		//update children coordinate based on ul and lr
		lowHeight = SW->lowRight.second - SW->upLeft.second + 1;
		upHeight = height - lowHeight;
		rightWidth = NE->lowRight.first - NE->upLeft.first + 1;
		leftWidth = width - rightWidth;

		NW->upLeft = {ul.first+rightWidth, ul.second};
		NW->lowRight = {ul.first+width-1, ul.second+upHeight-1};
		NE->upLeft = ul;
		NE->lowRight = {ul.first+rightWidth-1, ul.second+upHeight-1};
		SW->upLeft = {ul.first+rightWidth, ul.second+upHeight};
		SW->lowRight = lr;
		SE->upLeft = {ul.first, ul.second+upHeight};
		SE->lowRight = {ul.first+rightWidth-1, lr.second};

		swap(subroot->NW,subroot->NE);
		swap(subroot->SW,subroot->SE);

		FlipHelper(subroot->NW);
		FlipHelper(subroot->NE);
		FlipHelper(subroot->SW);
		FlipHelper(subroot->SE);
	}
}

void QTree::RotateHelper(Node* subroot) {
	if (!subroot) return;

	pair<int, int> ul = subroot->upLeft;
	pair<int, int> lr = subroot->lowRight;
	int rightWidth, leftWidth, upHeight, lowHeight;
	int width = lr.second - ul.second+1;
	int height = lr.first - ul.first+1;
	Node* NW = subroot->NW;
	Node* NE = subroot->NE;
	Node* SW = subroot->SW;
	Node* SE = subroot->SE;

	//single pixel
	if(!NW && !NE && !SW && !SE) {
		return;
  	}

	//W
	else if(NE == nullptr && SE == nullptr) {
		lowHeight = SW->lowRight.second - SW->upLeft.second + 1;
		upHeight = height - lowHeight;

		NW->upLeft = ul;
		NW->lowRight = {ul.first+upHeight-1, ul.second};
		SW->upLeft = {ul.first+upHeight, ul.second};
		SW->lowRight = lr;

		RotateSwap(subroot);

		RotateHelper(subroot->SW);
		RotateHelper(subroot->SE);
	}

	//E
	else if(NW == nullptr && SW == nullptr) {
		lowHeight = SE->lowRight.second - SE->upLeft.second + 1;
		upHeight = height - lowHeight;

		NE->upLeft = ul;
		NE->lowRight = {ul.first+upHeight-1, ul.second};
		SE->upLeft = {ul.first+upHeight, ul.second};
		SE->lowRight = lr;

		RotateSwap(subroot);

		RotateHelper(subroot->NW);
		RotateHelper(subroot->NE);
	}

	//N
	else if(SW == nullptr && SE == nullptr) {
		rightWidth = NE->lowRight.first - NE->upLeft.first + 1;
		leftWidth = width - rightWidth;

		NW->upLeft = {ul.first, ul.second+rightWidth};
		NW->lowRight = lr;
		NE->upLeft = ul;
		NE->lowRight = {ul.first, ul.second+rightWidth-1};

		RotateSwap(subroot);

		RotateHelper(subroot->NW);
		RotateHelper(subroot->SW);
	}

	//S
	else if(NW == nullptr && NE == nullptr) {
		rightWidth = SE->lowRight.first - SE->upLeft.first + 1;
		leftWidth = width - rightWidth;

		SW->upLeft = {ul.first, ul.second+rightWidth};
		SW->lowRight = lr;
		SE->upLeft = ul;
		SE->lowRight = {lr.first, ul.second+rightWidth-1};

		RotateSwap(subroot);

		RotateHelper(subroot->NE);
		RotateHelper(subroot->SE);
	}

	//4 children
	else {
		//update children coordinate based on ul and lr
		lowHeight = SW->lowRight.second - SW->upLeft.second + 1;
		upHeight = height - lowHeight;
		rightWidth = NE->lowRight.first - NE->upLeft.first + 1;
		leftWidth = width - rightWidth;

		NW->upLeft = {ul.first, ul.second+rightWidth};
		NW->lowRight = {ul.first+upHeight-1, ul.second+width-1};
		NE->upLeft = ul;
		NE->lowRight = {ul.first+upHeight-1, ul.second+rightWidth-1};
		SW->upLeft = {ul.first+upHeight, ul.second+rightWidth};
		SW->lowRight = lr;
		SE->upLeft = {ul.first+upHeight, ul.second};
		SE->lowRight = {lr.first, ul.second+rightWidth-1};

		RotateSwap(subroot);

		RotateHelper(subroot->NW);
		RotateHelper(subroot->NE);
		RotateHelper(subroot->SW);
		RotateHelper(subroot->SE);
	}
}

void QTree::RotateSwap(Node* subroot) {
	Node* temp = subroot->NW;
	subroot->NW = subroot->NE;
	subroot->NE = subroot->SE;
	subroot->SE = subroot->SW;
	subroot->SW = temp;
}

// cout<<"begin"<<endl;
// 	cout<<subroot->NW->upLeft.first<<","<<subroot->NW->upLeft.second<<endl;
// 	cout<<subroot->NW->lowRight.first<<","<<subroot->NW->lowRight.second<<endl;
// 	cout<<subroot->NE->upLeft.first<<","<<subroot->NE->upLeft.second<<endl;
// 	cout<<subroot->NE->lowRight.first<<","<<subroot->NE->lowRight.second<<endl;
// 	cout<<subroot->SW->upLeft.first<<","<<subroot->SW->upLeft.second<<endl;
// 	cout<<subroot->SW->lowRight.first<<","<<subroot->SW->lowRight.second<<endl;
// 	cout<<subroot->SE->upLeft.first<<","<<subroot->SE->upLeft.second<<endl;
// 	cout<<subroot->SE->lowRight.first<<","<<subroot->SE->lowRight.second<<endl;
// 	cout<<"end"<<endl;
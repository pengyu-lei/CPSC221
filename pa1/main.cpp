/**
 * File: main.cpp
 * Description: entry point for test program
 *              for CPSC 221 2023W1 PA1
 *
 *              Add or modify test code as needed.
 * 
 *              THIS FILE WILL NOT BE SUBMITTED.
 */

#include <iostream>

#include "chain.h"

using namespace std;
using namespace cs221util;

/**
 * Test function declarations
 */

void TestChainRenderFull();
void TestChainRenderTiny();
void TestChainReverse();
void TestChainFlipHorizontal();
void TestChainFlipVertical();
void TestChainBlockify();
void TestOutput();

/**
 * Program entry point
 */
int main(void) {

	// add or remove calls to testing functions as needed
	TestChainRenderFull();
	cout << "TestChainRenderFull completed.\n" << endl;
	TestChainRenderTiny();
	cout << "TestChainRenderTiny completed.\n" << endl;
	TestChainReverse();
	cout << "TestChainReverse completed.\n" << endl;
	TestChainFlipHorizontal();
	cout << "TestChainFlipHorizontal completed.\n" << endl;
	TestChainFlipVertical();
	cout << "TestChainFlipVertical completed.\n" << endl;
	TestChainBlockify();
	cout << "TestChainBlockify completed.\n" << endl;
	TestOutput();
	cout << "TestOutput completed.\n" << endl;
	return 1;
}

/**
 * Test function implementations
 */

void TestChainRenderFull() {
	cout << "Entered TestChainRenderFull." << endl;
	// load a PNG file
	PNG alphabetpng;
	alphabetpng.readFromFile("images-original/alphabet-240x40.png");

	cout << "Creating a Chain from PNG... ";
	Chain c(alphabetpng, 40);
	cout << "done." << endl;

	cout << "Rendering Chain to output PNG with 2 columns... ";
	PNG alphabet2 = c.Render(2, true);
	cout << "done." << endl;

	cout << "Writing output PNG to file... ";
	alphabet2.writeToFile("images-output/alphabet-240x40-render2-full.png");
	cout << "done." << endl;

	cout << "Rendering Chain to output PNG with 3 columns... ";
	PNG alphabet3 = c.Render(3, true);
	cout << "done." << endl;

	cout << "Writing output PNG to file... ";
	alphabet3.writeToFile("images-output/alphabet-240x40-render3-full.png");
	cout << "done." << endl;

	cout << "Rendering Chain to output PNG with 4 columns... ";
	PNG alphabet4 = c.Render(4, true);
	cout << "done." << endl;

	cout << "Writing output PNG to file... ";
	alphabet4.writeToFile("images-output/alphabet-240x40-render4-full.png");
	cout << "done." << endl;

	cout << "Rendering Chain to output PNG with 5 columns... ";
	PNG alphabet5 = c.Render(5, true);
	cout << "done." << endl;

	cout << "Writing output PNG to file... ";
	alphabet5.writeToFile("images-output/alphabet-240x40-render5-full.png");
	cout << "done." << endl;

	cout << "Rendering Chain to output PNG with 6 columns... ";
	PNG alphabet6 = c.Render(6, true);
	cout << "done." << endl;

	cout << "Writing output PNG to file... ";
	alphabet6.writeToFile("images-output/alphabet-240x40-render6-full.png");
	cout << "done." << endl;

	cout << "Leaving TestChainRenderFull..." << endl;

	cout << "Rendering Chain to output PNG with 10 columns... ";
	PNG alphabet10 = c.Render(10, true);
	cout << "done." << endl;

	cout << "Writing output PNG to file... ";
	alphabet10.writeToFile("images-output/alphabet-240x40-render10-full.png");
	cout << "done." << endl;

	cout << "Leaving TestChainRenderFull..." << endl;

	cout << "Rendering Chain to output PNG with 7 columns... ";
	PNG alphabet7 = c.Render(7, true);
	cout << "done." << endl;

	cout << "Writing output PNG to file... ";
	alphabet7.writeToFile("images-output/alphabet-240x40-render7-full.png");
	cout << "done." << endl;

	cout << "Leaving TestChainRenderFull..." << endl;
}

void TestChainRenderTiny() {
	cout << "Entered TestChainRenderTiny." << endl;
	// load a PNG file
	PNG alphabetpng;
	alphabetpng.readFromFile("images-original/alphabet-240x40.png");

	cout << "Creating a Chain from PNG... ";
	Chain c(alphabetpng, 40);
	cout << "done." << endl;

	cout << "Rendering Chain to output PNG with 4 columns... ";
	PNG alphabet4 = c.Render(4, false);
	cout << "done." << endl;

	cout << "Writing output PNG to file... ";
	alphabet4.writeToFile("images-output/alphabet-240x40-render4-tiny.png");
	cout << "done." << endl;

	cout << "Leaving TestChainRenderTiny..." << endl;
}

void TestChainReverse() {
	cout << "Entered TestChainReverse." << endl;

	// load a PNG file
	PNG alphabetpng;
	alphabetpng.readFromFile("images-original/alphabet-240x40.png");

	cout << "Creating a Chain from PNG... ";
	Chain c(alphabetpng, 40);
	cout << "done." << endl;

	cout << "Calling Reverse... ";
	c.Reverse();
	cout << "done." << endl;

	cout << "Rendering reversed Chain to output PNG with 6 columns... ";
	PNG alphabetreversed = c.Render(6, true);
	cout << "done." << endl;

	cout << "Writing output PNG to file... ";
	alphabetreversed.writeToFile("images-output/alphabet-240x40-reverse-render6.png");
	cout << "done." << endl;

	cout << "Leaving TestChainReverse..." << endl;
}

void TestChainFlipHorizontal() {
	cout << "Entered TestChainFlipHorizontal." << endl;
	// load a PNG file
	PNG alphabetpng;
	alphabetpng.readFromFile("images-original/alphabet-240x40.png");

	cout << "Creating a Chain from PNG... ";
	Chain c(alphabetpng, 40);
	cout << "done." << endl;

	cout << "Calling FlipHorizontal with 3 columns... ";
	c.FlipHorizontal(3);
	cout << "done." << endl;

	cout << "Rendering flipped Chain to output PNG with 3 columns... ";
	PNG alphabetflipped = c.Render(3, true);
	cout << "done." << endl;

	cout << "Writing output PNG to file... ";
	alphabetflipped.writeToFile("images-output/alphabet-240x40-fliph3-render3-full.png");
	cout << "done." << endl;

	cout << "Leaving TestChainFlipHorizontal..." << endl;
}

void TestChainFlipVertical() {
	cout << "Entered TestChainFlipVertical." << endl;
	// load a PNG file
	PNG alphabetpng;
	alphabetpng.readFromFile("images-original/alphabet-240x40.png");

	cout << "Creating a Chain from PNG... ";
	Chain c(alphabetpng, 40);
	cout << "done." << endl;

	cout << "Calling FlipVertical with 3 columns... ";
	c.FlipVertical(3);
	cout << "done." << endl;

	cout << "Rendering flipped Chain to output PNG with 3 columns... ";
	PNG alphabetflipped = c.Render(3, true);
	cout << "done." << endl;

	cout << "Writing output PNG to file... ";
	alphabetflipped.writeToFile("images-output/alphabet-240x40-flipv3-render3-full.png");
	cout << "done." << endl;

	cout << "Leaving TestChainFlipVertical..." << endl;
}

void TestChainBlockify() {
	cout << "Entered TestChainBlockify." << endl;
	// load a PNG file
	PNG alphabetpng;
	alphabetpng.readFromFile("images-original/alphabet-240x40.png");

	cout << "Creating a Chain from PNG... ";
	Chain c(alphabetpng, 40);
	cout << "done." << endl;

	cout << "Calling Blockify... ";
	c.Blockify();
	cout << "done." << endl;

	cout << "Rendering flipped Chain to output PNG with 3 columns... ";
	PNG alphabetblocky = c.Render(3, true);
	cout << "done." << endl;

	cout << "Writing output PNG to file... ";
	alphabetblocky.writeToFile("images-output/alphabet-240x40-blockify-render3-full.png");
	cout << "done." << endl;

	cout << "Leaving TestChainBlockify..." << endl;
}

void TestOutput() {
	cout << "Entered TestOutput." << endl;

	PNG output_render_full, soln_render_full;

	output_render_full.readFromFile("images-output/alphabet-240x40-render2-full.png");
	soln_render_full.readFromFile("images-soln/soln-alphabet-240x40-render2-full.png");
	if (output_render_full == soln_render_full) {
		cout<<"render2-full equal"<<endl;
	} else {
		cout<<"render2-full not equal"<<endl;
	}

	output_render_full.readFromFile("images-output/alphabet-240x40-render3-full.png");
	soln_render_full.readFromFile("images-soln/soln-alphabet-240x40-render3-full.png");
	if (output_render_full == soln_render_full) {
		cout<<"render3-full equal"<<endl;
	} else {
		cout<<"render3-full not equal"<<endl;
	}

	output_render_full.readFromFile("images-output/alphabet-240x40-render4-full.png");
	soln_render_full.readFromFile("images-soln/soln-alphabet-240x40-render4-full.png");
	if (output_render_full == soln_render_full) {
		cout<<"render4-full equal"<<endl;
	} else {
		cout<<"render4-full not equal"<<endl;
	}

	output_render_full.readFromFile("images-output/alphabet-240x40-render4-tiny.png");
	soln_render_full.readFromFile("images-soln/soln-alphabet-240x40-render4-tiny.png");
	if (output_render_full == soln_render_full) {
		cout<<"render4-tiny equal"<<endl;
	} else {
		cout<<"render4-tiny not equal"<<endl;
	}

	output_render_full.readFromFile("images-output/alphabet-240x40-reverse-render6.png");
	soln_render_full.readFromFile("images-soln/soln-alphabet-240x40-reverse-render6.png");
	if (output_render_full == soln_render_full) {
		cout<<"reverse-render6 equal"<<endl;
	} else {
		cout<<"reverse-render6 not equal"<<endl;
	}

	output_render_full.readFromFile("images-output/alphabet-240x40-blockify-render3-full.png");
	soln_render_full.readFromFile("images-soln/soln-alphabet-240x40-blockify-render3-full.png");
	if (output_render_full == soln_render_full) {
		cout<<"blockify-render3 equal"<<endl;
	} else {
		cout<<"blockify-render3 not equal"<<endl;
	}

	cout << "Leaving TestOutput..." << endl;
}
/**
 * @file RGBAPixel.h
 *
 * @author Aaron Lei
 */

#ifndef RGBAPixel_H
#define RGBAPixel_H

using namespace std;

namespace cs221util {
    class RGBAPixel {
    public:

    unsigned char r,g,b;
    double a;

    /**
      * Creates the default pixel to white, 
      * which is a pixel with the maximum contribution on 
      * all visible colour channels, and alpha 1.0.
      */
    RGBAPixel();

    /**
      * Creates an pixel with given
      * @param r red 
      * @param g green 
      * @param b blue
      * and full opacity(alpha 1.0).
      */
    RGBAPixel(int red, int green,int blue);

    /**
      * Creates an pixel with given
      * @param r red 
      * @param g green 
      * @param b blue
      * @param a alpha
      */
    RGBAPixel(int red, int green, int blue, double alpha);

    };
}

#endif
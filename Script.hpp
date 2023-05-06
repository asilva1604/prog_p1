#ifndef __prog_Script_hpp__
#define __prog_Script_hpp__

#include <string>
#include <fstream>
#include "Image.hpp"

namespace prog
{
  class Script
  {
  public: 
    Script(const std::string &filename);
    ~Script();
    void run();
  private:
    // Current image.
    Image *image;
    // Input stream for reading script commands.
    std::ifstream input;
  private:
    // Private functions
    void clear_image_if_any();
    void open();
    void blank();
    void save();
    void invert(); // Transforms each pixel to its inverted color
    void to_gray_scale(); // Transforms each pixel to its grayscale representation
    void replace(); // Replace all pixels with a specific color to another color
    void fill(); // Fills a rectangle(width=w, height=h) with a specific color
    void h_mirror(); // Mirrors the image horizontally
    void v_mirror(); // Mirrors the image vertically
    void add(); //copies pixels stored in filename except neutral pixels 
    void crop(); //Crop the image, reducing it to all pixels contained in the rectangle defined by top-left corner (x, y), width w, and height h.You may assume that the rectangle is always within the current image bounds.
    void median_filter(); //Apply a median filter with window size ws >= 3 to the current image.
    void xpm2_open();
    void xpm2_save();
    void rotate_left(); // Rotate image left by 90 degrees.
    void rotate_right(); // Rotate image right by 90 degrees.
  };
}
#endif


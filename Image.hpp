#ifndef __prog_Image_hpp__
#define __prog_Image_hpp__
#include <vector>
#include "Color.hpp"

namespace prog
{
  class Image
  {
  private:
    //vector of vectors of colors. this vector holds y vectors which
    //have x positions each, making the matrix
    std::vector<std::vector<Color>> matrix_;  
    int width_;   //width of matrix
    int height_;  //height of matrix
  public:
    Image(int w, int h, const Color &fill = {255, 255, 255});
    ~Image();
    int width() const;
    int height() const;
    Color &at(int x, int y);
    const Color &at(int x, int y) const;
    void reverseMatrix();
    void reverseMatrixMembers();
  };
}
#endif

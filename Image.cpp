#include <vector>
#include <algorithm>
#include "Image.hpp"

namespace prog
{
  Image::Image(int w, int h, const Color &fill)
  {
    std::vector <Color> row (w, fill);              //auxiliary vector that represents one row
    std::vector<std::vector<Color>> aux (h, row);   //auxiliary vector that represents the whole matrix
    matrix_ = aux;                                  //assigning auxiliary matrix to matrix_
    width_ = w;                                     //assigning width
    height_ = h;                                    //assigning height
  }
  Image::~Image()
  {
    //empty constructor as we do not use dynamic memory
  }
  int Image::width() const
  {
    return width_;  //returns width of matrix
  }
  int Image::height() const
  {
    return height_; //returns height of matrix
  }



  Color& Image::at(int x, int y)
  {
    auto &pixel = matrix_[y][x];   //acesses the pixel
    return pixel;                  //returns the pixel reference
  }

  const Color& Image::at(int x, int y) const
  {
    return matrix_[y][x];          //returns the immutable pixel reference
  }

  void Image::reverseMatrix() {
    //reverses the matrix
    std::reverse(matrix_.begin(), matrix_.end());
  }

  void Image::reverseMatrixMembers() {
    //reverses each matrix member
    for (auto &a : matrix_) {
      std::reverse(a.begin(), a.end());
    }
  }
}

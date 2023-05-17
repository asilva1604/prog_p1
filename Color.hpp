#ifndef __prog_Color_hpp__
#define __prog_Color_hpp__

namespace prog
{
  typedef unsigned char rgb_value;
  class Color
  {
    private:
      //r, g and b values
      rgb_value r_;      
      rgb_value g_;
      rgb_value b_;

    public:
      Color();                                      //default constriuctor
      Color(const Color& c);                        //copy constructor
      Color(rgb_value r, rgb_value g, rgb_value b); //constructor with r,g and b values
      rgb_value red() const;                        //getter
      rgb_value& red();                             //setter
      rgb_value green() const;                      //getter
      rgb_value& green();                           //setter
      rgb_value blue() const;                       //getter
      rgb_value& blue();                            //setter
  };
}
#endif

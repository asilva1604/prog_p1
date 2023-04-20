#include "Color.hpp"

namespace prog {
    Color::Color() {
        //default constructor initiates a black color
        r_ = 0;
        g_ = 0;
        b_ = 0;
    }
    Color::Color(const Color& other) {
        //copies values from other color
        r_ = other.red();
        g_ = other.green();
        b_ = other.blue();
    }
    Color::Color(rgb_value red, rgb_value green, rgb_value blue) {
        //construct from args
        r_ = red;
        g_ = green;
        b_ = blue;
    }
    rgb_value Color::red() const {
        return r_;
    }
    rgb_value Color::green() const {
        return g_;
    }
    rgb_value Color::blue() const {
        return b_;
    }

    rgb_value& Color::red()  {
        auto &o = this->r_;
        return o;
    }
    rgb_value& Color::green()  {
      auto &g = this->g_;
      return g;
    }
    rgb_value& Color::blue()  {
      auto &b = this->b_;
      return b;
    }
}

#include "color.hpp"
#include <iostream>

Color::Color(int r, int g, int b): red_(r), green_(g), blue_(b) {
  if (r < kColorValueMin || g < kColorValueMin || b < kColorValueMin || r > kColorValueMax || g > kColorValueMax || b > kColorValueMax) {
    throw std::runtime_error("INVALID COLOR");
  }
  // need to ensure valid color has been constructed...
}

// do not modify
bool operator==(const Color& rhs, const Color& lhs) {
  return (rhs.Red() == lhs.Red() && rhs.Green() == lhs.Green() &&
          rhs.Blue() == lhs.Blue());
}
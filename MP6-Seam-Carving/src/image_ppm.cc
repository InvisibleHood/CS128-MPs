#include "image_ppm.hpp"
#include <iostream>
#include <string>


// implement the rest of ImagePPM's functions here

// given functions below, DO NOT MODIFY

ImagePPM::ImagePPM(const std::string& path) {
  std::ifstream input_file(path);
  input_file >> *this;
  input_file.close();
}

ImagePPM::ImagePPM(const ImagePPM& source) { *this = source; }

ImagePPM& ImagePPM::operator=(const ImagePPM& source) {
  if (this == &source) {
    return *this;
  }

  Clear();

  height_ = source.height_;
  width_ = source.width_;
  max_color_value_ = source.max_color_value_;

  pixels_ = new Pixel*[height_];
  for (int row = 0; row < height_; row++) {
    pixels_[row] = new Pixel[width_];

    for (int col = 0; col < width_; col++) {
      pixels_[row][col] = source.pixels_[row][col];
    }
  }

  return *this;
}

ImagePPM::~ImagePPM() { Clear(); }

void ImagePPM::Clear() {
  for (int i = 0; i < height_; i++) {
    delete[] pixels_[i];
  }

  delete[] pixels_;

  height_ = 0;
  width_ = 0;
  pixels_ = nullptr;
}

std::istream& operator>>(std::istream& is, ImagePPM& image) {
  image.Clear();
  std::string line;
  // ignore magic number line
  getline(is, line);
  // check to see if there's a comment line
  getline(is, line);
  if (line[0] == '#') {
    getline(is, line);
  }
  // parse width and height
  int space = line.find_first_of(' ');
  image.width_ = std::stoi(line.substr(0, space));
  image.height_ = std::stoi(line.substr(space + 1));
  // get max color value
  getline(is, line);
  image.max_color_value_ = std::stoi(line);
  // init and fill in Pixels array
  image.pixels_ = new Pixel*[image.height_];
  for (int i = 0; i < image.height_; i++) {
    image.pixels_[i] = new Pixel[image.width_];
  }
  for (int row = 0; row < image.height_; row++) {
    for (int col = 0; col < image.width_; col++) {
      getline(is, line);
      int red = std::stoi(line);
      getline(is, line);
      int green = std::stoi(line);
      getline(is, line);
      int blue = std::stoi(line);

      Pixel p(red, green, blue);
      image.pixels_[row][col] = p;
    }
  }
  return is;

}//========================================================

Pixel ImagePPM::GetPixel(int row, int col) const {
  if (row > GetHeight() || col > GetWidth() || row < 0 || col < 0) {
    throw std::invalid_argument("INVALID ROW OR COL");
  }
  return pixels_[row][col];
}

int ImagePPM::GetMaxColorValue() const {
  return max_color_value_;
}

void ImagePPM::RemoveVerticalSeam(const int* seam) {    
  Pixel** newpixels = new Pixel* [GetHeight()];
  int idx_newpixels = 0;
  for (int row = 0; row < height_; row++) {
    newpixels[row] = new Pixel [width_ - 1];
    for (int col = 0; col < width_; col++) {
      if (col == seam[row]) {
        continue;
      }
      newpixels[row][idx_newpixels] = pixels_[row][col];
      idx_newpixels++; 
    }
    idx_newpixels = 0;
  }
  for (int i = 0; i < height_; i++) {
    delete[] pixels_[i];
  }
  delete[] pixels_;
  pixels_ = newpixels;
  width_--;
  delete[] seam; 
  seam = nullptr; 
}

void ImagePPM::RemoveHorizontalSeam(const int* seam) { 
  //seam here is also a copy but the copy points to the same address the original seam has, 
  //so if we 'delete' the copy(address) the original one is also deleted
  Pixel** newpixels = new Pixel* [GetHeight() - 1];
  int newrow = 0;
  for (int row = 0; row < GetHeight() - 1; row++) {
    newpixels[row] = new Pixel [GetWidth()];
  }
  for (int col = 0; col < GetWidth(); col++) {
    for (int row = 0; row < height_; row++) {
      if (row == seam[col]) {
        continue;
      }
      newpixels[newrow][col] = pixels_[row][col];
      newrow++;
    }
    newrow = 0;
  }
  for (int row = 0; row < GetHeight(); row++) {
    delete[] pixels_[row];
  }
  delete[] pixels_;
  pixels_ = newpixels;
  height_--;
  delete[] seam;  
  seam = nullptr; 
}
//========================================================= friends

std::ostream& operator<<(std::ostream& os, const ImagePPM& image) {
  os << "P3" << std::endl;
  os << image.GetWidth() << " " << image.GetHeight() << std::endl;
  os << image.GetMaxColorValue() << std::endl;
  for (int row = 0; row < image.GetHeight(); row++) {
    for (int col = 0; col < image.GetWidth(); col++) {
      os << image.GetPixel(row, col).GetRed() << '\n';
      os << image.GetPixel(row, col).GetGreen() << '\n';
      if (row == image.GetHeight() - 1 && col == image.GetWidth() - 1) {
        os << image.GetPixel(row, col).GetBlue();
        break;
      }
      os << image.GetPixel(row, col).GetBlue() << '\n';
    }
  }
  return os;
}

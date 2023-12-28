#include "grayscale_image.hpp"

#include <cmath>
#include <iostream>
#include <fstream>


GrayscaleImage::GrayscaleImage(const ElevationDataset& dataset) {
  height_ = dataset.Height();
  width_ = dataset.Width();
  std::vector<std::vector<Color>> img_vec(height_, std::vector<Color> (width_, {0,0,0}));
  image_ = img_vec;
  int shade_on_gray = 0;
  for (size_t row = 0; row < height_; row++) {
    for (size_t col = 0; col < width_; col++) {
      if (dataset.MaxEle() - dataset.MinEle() != 0) {
        double dif = dataset.MaxEle() - dataset.MinEle();
        double numerator = (dataset.DatumAt(row, col) - dataset.MinEle()) * kMaxColorValue;
        shade_on_gray = (int) round(numerator / dif);
      } 
      image_.at(row).at(col) = {shade_on_gray, shade_on_gray, shade_on_gray};
    }
  }
}

GrayscaleImage::GrayscaleImage(const std::string& filename, size_t width, size_t height) : GrayscaleImage(ElevationDataset(filename, width, height)) {
  /*
  std::ifstream file(filename);
  if (!file.is_open()) {throw std::runtime_error("FAILED TO OPEN");}
  int min_ele = 0;
  int max_ele = 0;
  std::vector<std::vector<int>> data_vec(height, std::vector<int> (width, 0));
  std::vector<std::vector<Color>> img_vec(height_, std::vector<Color> (width_, {0,0,0}));
  image_ = img_vec;
  data_ = data_vec;
  int datum = 0;
  width_ = width;
  height_ = height;
  for (size_t row = 0; row < height_; row++) {
      for (size_t col = 0; col < width_; col++) {
          file >> datum;
          if (file.fail() || file.bad()) {throw std::runtime_error("FORMAT READ ERROR");}
          if (file.eof() && row != height - 1 && col != width - 1) {throw std::runtime_error("TOO FEW");}
          if (row == height_ - 1 && col == width_ - 1 && (!file.eof())) {
              int test = 0;
              file >> test;
              if (file.good()) {throw std::runtime_error("TOO MUCH");}
          }
          if ((row == 0 && col == 0) || datum > max_ele) {max_ele = datum;}
          if ((row == 0 && col == 0) || min_ele > datum) {min_ele = datum;}
          data_.at(row).at(col) = datum;
      }
  }
  int shade_on_gray = 0;
  for (size_t row = 0; row < height_; row++) {
    for (size_t col = 0; col < width_; col++) {
      if (max_ele - min_ele != 0) {
        shade_on_gray = (int) round(data_.at(row).at(col) - min_ele) * kMaxColorValue / (max_ele - min_ele);
      }
      Color gray(shade_on_gray, shade_on_gray, shade_on_gray);
      image_.at(row).at(col) = gray;
    }
  }
  */
}


void GrayscaleImage::ToPpm(const std::string& name) const {
  std::ofstream output(name);
  output << "P3" << std::endl;
  output << width_ << " " << height_ << std::endl;
  output << kMaxColorValue << std::endl;
  if (output.is_open()) {
    for (size_t row = 0; row < height_; row++) {
      for (size_t col = 0; col < width_; col++) {
        output << image_.at(row).at(col).Red() << " ";
        output << image_.at(row).at(col).Green() << " ";
        output << image_.at(row).at(col).Blue() << " ";
      }
      output << "\n";
    }
  }
  //output.close();
}

size_t GrayscaleImage::Width() const {
  return width_;
}

size_t GrayscaleImage::Height() const {
  return height_;
}

unsigned int GrayscaleImage::MaxColorValue() const {
  return kMaxColorValue;
}

const Color& GrayscaleImage::ColorAt(int row, int col) const {
  return image_.at(row).at(col);
}

const std::vector<std::vector<Color>>& GrayscaleImage::GetImage() const {
  return image_;
}
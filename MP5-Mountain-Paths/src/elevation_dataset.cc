#include "elevation_dataset.hpp"
#include <iostream>
#include <fstream>
#include <limits>


ElevationDataset::ElevationDataset(const std::string& filename, size_t width, size_t height) {
    std::ifstream file(filename);
    if (!file.is_open()) {throw std::runtime_error("FAILED TO OPEN");}
    std::vector<std::vector<int>> datum(height, std::vector<int> (width, 0));
    data_ = datum;
    int data = 0;
    max_ele_ = 0;
    min_ele_ = 0;
    width_ = width;
    height_ = height;
    for (size_t row = 0; row < height_; row++) {
        for (size_t col = 0; col < width_; col++) {
            file >> data;
            if (file.fail() || file.bad()) {
                throw std::runtime_error("FORMAT READ ERROR");
            }
            if (file.eof() && row != height - 1 && col != width - 1) {
                throw std::runtime_error("TOO FEW");
            }
            if (row == height_ - 1 && col == width_ - 1 && (!file.eof())) {
                int test = 0;
                file >> test;
                if (file.good()) {
                    //std::cout << data << " DATA" << std::endl;
                    throw std::runtime_error("TOO MUCH");
                }
            }
            if ((row == 0 && col == 0)|| data > max_ele_) {max_ele_ = data;}
            if ((row == 0 && col == 0) || min_ele_ > data) {
                min_ele_ = data;
            }
            //std::cout << data << " DATA" << std::endl;
            data_.at(row).at(col) = data;
        }
    }
}

size_t ElevationDataset::Width() const {
    return width_;
}

size_t ElevationDataset::Height() const {
    return height_;
}

int ElevationDataset::MaxEle() const {
    return max_ele_;
}

int ElevationDataset::MinEle() const {
    return min_ele_;
}

int ElevationDataset::DatumAt(size_t row, size_t col) const {
    if (row >= height_ || col >= width_) {
        throw std::runtime_error("INVALID ROW AND COL TO FETCH DATUM");
    }
    return data_.at(row).at(col);
}

const std::vector<std::vector<int>>& ElevationDataset::GetData() const {
    return data_;
}



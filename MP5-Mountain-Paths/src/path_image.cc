#include "color.hpp"
#include "path_image.hpp"
#include "path.hpp"
#include "limits"
#include "iostream"
#include "fstream"


PathImage::PathImage(const GrayscaleImage &image, const ElevationDataset& dataset) {
    height_ = dataset.Height();
    width_ = dataset.Width();
    paths_.resize(height_, {0, 0});
    path_image_ = image.GetImage();
    size_t the_best_row = 0;
    unsigned int least_elec = std::numeric_limits<unsigned int>::max();
    for (size_t row = 0; row < height_; row++) {
        Path path(width_, row);
        path.SetLoc(0, row);
        size_t current_row = row;
        for (size_t col = 0; col < width_ - 1; col++) {
            path_image_.at(current_row).at(col) = Color{kRedR, kRedG, kRedB};
            unsigned int cur = abs(dataset.DatumAt(current_row, col) - dataset.DatumAt(current_row, col + 1));
            unsigned int pre = std::numeric_limits<unsigned int>::max();
            unsigned int next = std::numeric_limits<unsigned int>::max();
            if (current_row != height_ - 1) {next = abs(dataset.DatumAt(current_row, col) - dataset.DatumAt(current_row + 1, col + 1));} 
            if (current_row != 0) {pre = abs(dataset.DatumAt(current_row, col) - dataset.DatumAt(current_row - 1, col + 1));}
            if (pre < cur && pre < next) {
                path.SetLoc(col + 1, current_row - 1);
                path.IncEleChange(pre);
                current_row = current_row - 1;
            } else if (cur <= next && cur <= pre) {
                path.SetLoc(col + 1, current_row);
                path.IncEleChange(cur);
            } else {
                path.SetLoc(col + 1, current_row + 1);
                path.IncEleChange(next);
                current_row = current_row + 1;
            }
            path_image_.at(current_row).at(col + 1) = Color{kRedR, kRedG, kRedB};
        }
        if (path.EleChange() < least_elec) {   
            the_best_row = path.StartingRow();
            least_elec = path.EleChange();
        }
        paths_[row] = path;
    }
    Path best = paths_.at(the_best_row);
    for (size_t col = 0; col < width_; col++) {path_image_.at(best.GetPath().at(col)).at(col) = Color{kGreenR, kGreenG, kGreenB};}
}

size_t PathImage::Width() const {
    return width_;
}

size_t PathImage::Height() const {
    return height_;
}

unsigned int PathImage::MaxColorValue() const {
    return kMaxColorValue;
}

const std::vector<Path>& PathImage::Paths() const {
    return paths_;
}

const std::vector<std::vector<Color>>& PathImage::GetPathImage() const {
    return path_image_;
}

void PathImage::ToPpm(const std::string& name) const {
    std::ofstream output(name);
    output << "P3" << std::endl;
    output << width_ << " " << height_ << std::endl;
    output << kMaxColorValue << std::endl;
    for (size_t row = 0; row < height_; row++) {
      for (size_t col = 0; col < width_; col++) {
        output << path_image_.at(row).at(col).Red() << " ";
        output << path_image_.at(row).at(col).Green() << " ";
        output << path_image_.at(row).at(col).Blue() << " ";
      }
      output << "\n";
    }
}
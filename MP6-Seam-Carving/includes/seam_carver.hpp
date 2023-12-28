#ifndef SEAM_CARVER_HPP
#define SEAM_CARVER_HPP

#include "image_ppm.hpp"

class SeamCarver {
public:
  // default constructor
  //
  // Not tested, but you are welcome to intialize (or not) member variables
  // however you like in this function
  SeamCarver() = default;

  // overloaded constructor
  //
  // sets the instances' image_ as a DEEP COPY of the image parameter. Note
  // that if ImagePPM's copy constructor is implemented correctly, you
  // shouldn't have to worry about the details of a deep copy here
  SeamCarver(const ImagePPM& image); // DONE

  // sets the instances' image_ as a DEEP COPY of the image parameter. Same
  // note as above regarding ImagePPM
  void SetImage(const ImagePPM& image);    // DONE  

  // returns the instance's image_
  const ImagePPM& GetImage() const; // DONE

  // returns the image's height
  int GetHeight() const; // DONE

  // returns the image's width
  int GetWidth() const; // DONE

  // returns the energy of the pixel at row col in image_
  int GetEnergy(int row, int col) const; // DONE

  // returns the horizontal seam of image_ with the least amount of
  // energy
  //
  // the ith int in the returned array corresponds to which row at
  // col i is in the seam. example:
  //
  //    | x |   |
  // ---+---+---+---
  //  x |   | x |
  // ---+---+---+---
  //    |   |   | x
  // returns {1, 0, 1, 2}
  int* GetHorizontalSeam() const;

  // returns the vertical seam of image_ with the least amount of
  // energy
  //
  // the ith int in the returned array corresponds to which col at
  // row i is in the seam. example:
  //
  //    | x |   |
  // ---+---+---+---
  //    |   | x |
  // ---+---+---+---
  //    |   | x |
  // returns {1, 2, 2}
  int* GetVerticalSeam() const; // DONE

  // removes one horizontal seam in image_. example:
  //
  // image_ before:
  //  0 | 1 | 2 | 3
  // ---+---+---+---
  //  4 | 5 | 6 | 7
  // ---+---+---+---
  //  8 | 9 | 10| 11
  //
  // seam to remove:
  //    | x |   |
  // ---+---+---+---
  //  x |   | x |
  // ---+---+---+---
  //    |   |   | x
  //
  // image_ after:
  //  0 | 5 | 2 | 3
  // ---+---+---+---
  //  8 | 9 | 10| 7
  void RemoveHorizontalSeam();

  // removes one vertical seam in image_. example:
  //
  // image_ before:
  //  0 | 1 | 2 | 3
  // ---+---+---+---
  //  4 | 5 | 6 | 7
  // ---+---+---+---
  //  8 | 9 | 10| 11
  //
  // seam to remove:
  //    | x |   |
  // ---+---+---+---
  //    |   | x |
  // ---+---+---+---
  //    |   | x |
  //
  // image_ after:
  //  0 | 2 | 3
  // ---+---+---
  //  4 | 5 | 7
  // ---+---+---
  //  8 | 9 | 11
  void RemoveVerticalSeam();

  /**
   * Add any helper methods you may need
   */
  //void EnergyBoard(); // DONE
  int FindSmall(int left, int below, int right, int& col) const;
  int SeamBoardFindSmall(int left, int below, int right) const;
  int SeamBoardFindSmallH(int left, int below, int right) const;
  int FindSmallH(int left, int below, int right, int& row) const;
  void Clean(int** arr, int row) const;
  //int Formula(Pixel up, Pixel down, Pixel left, Pixel right) const;
  int Colform(int row, int col) const;
  int Rowform(int row, int col) const;
  int** VerticalSeamBoard() const;
  int** HorizontalSeamBoard() const;
  

private:
  ImagePPM image_;
  int height_ = 0;
  int width_ = 0;

  /**
   * Add any helper methods you may need
   */
};

#endif
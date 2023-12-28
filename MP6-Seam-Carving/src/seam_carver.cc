#include "seam_carver.hpp"
#include "image_ppm.hpp"

// implement the rest of SeamCarver's functions here

// given functions below, DO NOT MODIFY

void SeamCarver::RemoveHorizontalSeam() {
  image_.RemoveHorizontalSeam(GetHorizontalSeam());
  height_--;
}

int* SeamCarver::GetHorizontalSeam() const { 
  int* seam = new int [GetWidth()];
  const int kMAX = 2147483647;
  int** seam_board = HorizontalSeamBoard();
  int min_row = 0;
  int min_seam = seam_board[0][0];
  for (int row = 1; row < height_; row++) {
    if (seam_board[row][0] < min_seam) {
      min_seam = seam_board[row][0];
      min_row = row;
    }
  }
  for (int col = 0; col < width_; col++) {
    if (col == 0) {
      seam[col] = min_row;
    } else {
      if (min_row == 0) {
        seam[col] = FindSmallH(seam_board[min_row + 1][col], seam_board[min_row][col], kMAX, min_row);
      } else if (min_row == GetHeight() - 1) {
        seam[col] = FindSmallH(kMAX, seam_board[min_row][col], seam_board[min_row - 1][col], min_row);
      } else {
        seam[col] = FindSmallH(seam_board[min_row + 1][col], seam_board[min_row][col], seam_board[min_row - 1][col], min_row);
      }
    }
  }
  Clean(seam_board, GetHeight());
  return seam;
}

int SeamCarver::FindSmallH(int left, int below, int right, int& row) const {
  if (below <= left && below <= right) {
    return row;
  } 
  if (right <= below && right <= left) {
    row = row - 1;
    return row;
  }
  row = row + 1;
  return row;
}

int** SeamCarver::HorizontalSeamBoard() const {   //done
  int** seam_board = new int* [GetHeight()];
  const int kMAX = 2147483647;
  for (int row = 0; row < GetHeight(); row++) {
    seam_board[row] = new int [GetWidth()];
  }
  for (int col = GetWidth() - 1; col >= 0; col--) {
    for (int row = 0; row < GetHeight(); row++) {
      if (col == GetWidth() - 1) {
        seam_board[row][col] = GetEnergy(row, col);
      } else {
        if (row == 0) {
          seam_board[row][col] = GetEnergy(row, col) + SeamBoardFindSmallH(seam_board[row + 1][col + 1], seam_board[row][col + 1], kMAX);
        } else if (row == GetHeight() - 1) {
          seam_board[row][col] = GetEnergy(row, col) + SeamBoardFindSmallH(kMAX, seam_board[row][col + 1], seam_board[row - 1][col + 1]);
        } else {
          seam_board[row][col] = GetEnergy(row, col) + SeamBoardFindSmallH(seam_board[row + 1][col + 1], seam_board[row][col + 1], seam_board[row - 1][col + 1]);
        }
      }
    }
  }
  return seam_board;
}


int SeamCarver::SeamBoardFindSmallH(int left, int below, int right) const {
  if (below <= left && below <= right) {
    return below;
  } 
  if (right <= below && right <= left) {
    return right;
  }
  return left;
}


//========================================================

int** SeamCarver::VerticalSeamBoard() const {
  int** seam_board = new int* [GetHeight()](); // three
  const int kMAX = 2147483647;
  for (int i = 0; i < GetHeight(); i++) {
    seam_board[i] = new int [GetWidth()]();
  }
  for (int row = GetHeight() - 1; row >= 0; row--) { 
    for (int col = 0; col < GetWidth(); col++) {
      if (row == GetHeight() - 1) {
        seam_board[row][col] = GetEnergy(row, col);
      } else {
        if (col == 0) {
          seam_board[row][col] = GetEnergy(row, col) + SeamBoardFindSmall(kMAX, seam_board[row + 1][col], seam_board[row + 1][col + 1]);
        } else if (col == GetWidth() - 1) {
          seam_board[row][col] = GetEnergy(row, col) + SeamBoardFindSmall(seam_board[row + 1][col], seam_board[row + 1][col - 1], kMAX);
        } else {
          seam_board[row][col] = GetEnergy(row, col) + SeamBoardFindSmall(seam_board[row + 1][col - 1], seam_board[row + 1][col], seam_board[row + 1][col + 1]);
        }
      }
    }
  }
  return seam_board;
}


int* SeamCarver::GetVerticalSeam() const {
  int* seam = new int [GetHeight()]();   // two
  int** seam_board = VerticalSeamBoard(); //three
  int min_col = 0;
  int min_seam = seam_board[0][0];
  for (int col = 1; col < GetWidth(); col++) {
    if (seam_board[0][col] < min_seam) {
      min_seam = seam_board[0][col];
      min_col = col;
    }
  }
  const int kMAX = 2147483647;
  //find the seam with the least energy sum;
  for (int row = 0; row < GetHeight(); row++) {
    if (row == 0) {
      seam[row] = min_col;
    } else {
      if (min_col == 0) {
        seam[row] = FindSmall(kMAX, seam_board[row][min_col], seam_board[row][min_col + 1], min_col);
      } else if (min_col == GetWidth() - 1) {
        seam[row] = FindSmall(seam_board[row][min_col - 1], seam_board[row][min_col], kMAX, min_col);
      } else {
        seam[row] = FindSmall(seam_board[row][min_col - 1], seam_board[row][min_col], seam_board[row][min_col + 1], min_col);
      }
    }
  }
  Clean(seam_board, GetHeight());
  return seam;
}

void SeamCarver::RemoveVerticalSeam() {
  image_.RemoveVerticalSeam(GetVerticalSeam());
  width_--;
}


int SeamCarver::FindSmall(int left, int below, int right, int& col) const {
  if (below <= left && below <= right) {
    return col;
  } 
  if (left <= below && left <= right) {
    col = col - 1;
    return col;
  }
  col = col + 1;
  return col;
}

int SeamCarver::SeamBoardFindSmall(int left, int below, int right) const {
  if (below <= left && below <= right) {
    return below;
  } 
  if (left <= below && left <= right) {
    return left;
  }
  return right;
}

void SeamCarver::Clean(int** arr, int row) const {
  for (int i = 0; i < row; i++) {
    delete[] arr[i];
  }
  delete[] arr;
  arr = nullptr;
}


//===================================================================== getters

SeamCarver::SeamCarver(const ImagePPM& image): image_(image) {
  height_ = image.GetHeight();
  width_ = image.GetWidth();
}

void SeamCarver::SetImage(const ImagePPM& image) {
  image_ = image;
  width_ = image.GetWidth();
  height_ = image.GetHeight();
}

const ImagePPM& SeamCarver::GetImage() const {
  return image_;
}

int SeamCarver::GetHeight() const {
  return height_;
}

int SeamCarver::GetWidth() const {
  return width_;
}

int SeamCarver::GetEnergy(int row, int col) const {
  int col_dif = Colform(row, col);
  int row_dif = Rowform(row, col);
  return col_dif + row_dif;
}


int SeamCarver::Colform(int row, int col) const {
  int col_dif = 0;
  if (col == 0) {
    int red = (image_.GetPixel(row, width_ - 1).GetRed() - image_.GetPixel(row, col + 1).GetRed()) * (image_.GetPixel(row, width_ - 1).GetRed() - image_.GetPixel(row, col + 1).GetRed());
    int green = (image_.GetPixel(row, width_ - 1).GetGreen() - image_.GetPixel(row, col + 1).GetGreen()) * (image_.GetPixel(row, width_ - 1).GetGreen() - image_.GetPixel(row, col + 1).GetGreen());
    int blue = (image_.GetPixel(row, width_ - 1).GetBlue() - image_.GetPixel(row, col + 1).GetBlue()) * (image_.GetPixel(row, width_ - 1).GetBlue() - image_.GetPixel(row, col + 1).GetBlue());
    col_dif = red + green + blue;
  } else if (col == width_ - 1) {
    int red = (image_.GetPixel(row, col - 1).GetRed() - image_.GetPixel(row, 0).GetRed()) * (image_.GetPixel(row, col - 1).GetRed() - image_.GetPixel(row, 0).GetRed());
    int green = (image_.GetPixel(row, col - 1).GetGreen() - image_.GetPixel(row, 0).GetGreen()) * (image_.GetPixel(row, col - 1).GetGreen() - image_.GetPixel(row, 0).GetGreen());
    int blue = (image_.GetPixel(row, col - 1).GetBlue() - image_.GetPixel(row, 0).GetBlue()) * (image_.GetPixel(row, col - 1).GetBlue() - image_.GetPixel(row, 0).GetBlue());
    col_dif = red + green + blue;
  } else {
    int red = (image_.GetPixel(row, col - 1).GetRed() - image_.GetPixel(row, col + 1).GetRed()) * (image_.GetPixel(row, col - 1).GetRed() - image_.GetPixel(row, col + 1).GetRed());
    int green = (image_.GetPixel(row, col - 1).GetGreen() - image_.GetPixel(row, col + 1).GetGreen()) * (image_.GetPixel(row, col - 1).GetGreen() - image_.GetPixel(row, col + 1).GetGreen());
    int blue = (image_.GetPixel(row, col - 1).GetBlue() - image_.GetPixel(row, col + 1).GetBlue()) * (image_.GetPixel(row, col - 1).GetBlue() - image_.GetPixel(row, col + 1).GetBlue());
    col_dif = red + green + blue;
  }
  return col_dif;
}

int SeamCarver::Rowform(int row, int col) const {
  int row_dif = 0;
  if (row == 0) {
    int red = (image_.GetPixel(height_ - 1, col).GetRed() - image_.GetPixel(row + 1, col).GetRed()) * (image_.GetPixel(height_ - 1, col).GetRed() - image_.GetPixel(row + 1, col).GetRed());
    int green = (image_.GetPixel(height_ - 1, col).GetGreen() - image_.GetPixel(row + 1, col).GetGreen()) * (image_.GetPixel(height_ - 1, col).GetGreen() - image_.GetPixel(row + 1, col).GetGreen());
    int blue = (image_.GetPixel(height_ - 1, col).GetBlue() - image_.GetPixel(row + 1, col).GetBlue()) * (image_.GetPixel(height_ - 1, col).GetBlue() - image_.GetPixel(row + 1, col).GetBlue());
    row_dif = red + green + blue;
  } else if (row == height_ - 1) {
    int red = (image_.GetPixel(row - 1, col).GetRed() - image_.GetPixel(0, col).GetRed()) * (image_.GetPixel(row - 1, col).GetRed() - image_.GetPixel(0, col).GetRed());
    int green = (image_.GetPixel(row - 1, col).GetGreen() - image_.GetPixel(0, col).GetGreen()) * (image_.GetPixel(row - 1, col).GetGreen() - image_.GetPixel(0, col).GetGreen());
    int blue = (image_.GetPixel(row - 1, col).GetBlue() - image_.GetPixel(0, col).GetBlue()) * (image_.GetPixel(row - 1, col).GetBlue() - image_.GetPixel(0, col).GetBlue());
    row_dif = red + green + blue;
  } else {
    int red = (image_.GetPixel(row - 1, col).GetRed() - image_.GetPixel(row + 1, col).GetRed()) * (image_.GetPixel(row - 1, col).GetRed() - image_.GetPixel(row + 1, col).GetRed());
    int green = (image_.GetPixel(row - 1, col).GetGreen() - image_.GetPixel(row + 1, col).GetGreen()) * (image_.GetPixel(row - 1, col).GetGreen() - image_.GetPixel(row + 1, col).GetGreen());
    int blue = (image_.GetPixel(row - 1, col).GetBlue() - image_.GetPixel(row + 1, col).GetBlue()) * (image_.GetPixel(row - 1, col).GetBlue() - image_.GetPixel(row + 1, col).GetBlue());
    row_dif = red + green + blue;
  }
  return row_dif;
}

//============================================================= trash

// int SeamCarver::Formula(Pixel up, Pixel down, Pixel left, Pixel right) const {
//     int hor = (left.GetRed() - right.GetRed()) * (left.GetRed() - right.GetRed()) 
//             + (left.GetGreen() - right.GetGreen()) * (left.GetGreen() - right.GetGreen()) 
//             + (left.GetBlue() - right.GetBlue()) * (left.GetBlue() - right.GetBlue());
//     int ver = (up.GetRed() - down.GetRed()) * (up.GetRed() - down.GetRed()) 
//             + (up.GetGreen() - down.GetGreen()) * (up.GetGreen() - down.GetGreen()) 
//             + (up.GetBlue() - down.GetBlue()) * (up.GetBlue() - down.GetBlue());
//     int energy = hor + ver;
//     return energy;
// }

// void SeamCarver::EnergyBoard() {
//   int** energy_board_ = new int* [GetHeight()]();  // one
//   for (int i = 0; i < GetHeight(); i++) {
//     energy_board_[i] = new int [GetWidth()]();
//   }
//   for (int row = 0; row < GetHeight(); row++) {
//     for (int col = 0; col < GetWidth(); col++) {
//       Pixel left;Pixel right;Pixel up;Pixel down;
//       if (col == 0) {       // column delta
//         left = image_.GetPixel(row, image_.GetWidth() - 1);
//         right = image_.GetPixel(row, col + 1);
//       } else if (col == image_.GetWidth() - 1) {
//         right = image_.GetPixel(row, 0);
//         left = image_.GetPixel(row, col - 1);
//       } else {
//         left = image_.GetPixel(row, col - 1);
//         right = image_.GetPixel(row, col + 1);
//       }
//       if (row == 0) { // row delta 
//         up = image_.GetPixel(image_.GetHeight() - 1, col);
//         down = image_.GetPixel(row + 1, col);
//       } else if (row == image_.GetHeight() - 1) {
//         up = image_.GetPixel(row - 1, col);
//         down = image_.GetPixel(0, col);
//       } else {
//         up = image_.GetPixel(row - 1, col);
//         down = image_.GetPixel(row + 1, col);
//       }      
//       energy_board_[row][col] = Formula(up, down, left, right);
//     }
//   }
// }
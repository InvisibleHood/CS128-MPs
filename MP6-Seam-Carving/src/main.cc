#include <fstream>
#include <iostream>

#include "image_ppm.hpp"
#include "seam_carver.hpp"

void PrintUsage(const std::string& command) {
  std::cout << "Usage: " << command << " INPUT_FILE [options] -o OUTPUT_FILE\n"
            << "Options:\n"
            << "\t-h times\tcarve times horizontal seams\n"
            << "\t-v times\tcarve times vertical seams\n";
}

int main(int argc, char* argv[]) {
  //int *null = nullptr;
  //int *n = null;
  //*n = 3;      segmentation fault: cannot dereference a null pointer unless we initilize it with a 'new' (even not set it with a number directly after dereferencing it)
  std::string out_option = "-o";
  if (argc < 4 || out_option != argv[argc - 2]) {
    PrintUsage(argv[0]);
    return 1;
  }

  std::ifstream infile(argv[1]);
  //std::cout << "HELLO" << std::endl;
  if (!infile.good()) {
    std::cout << "file '" << argv[1] << "' not found" << std::endl;
    return 1;
  }

  /* UNCOMMENT COMMENTED CODE BELOW AS YOU IMPLEMENT */
  //std::cout << "START" << std::endl;
  ImagePPM image;
  infile >> image;
  infile.close();
  
  SeamCarver carver( image );
  //std::cout << "START" << std::endl;
  //carver.GetHorizontalSeam();
  //std::cout << "GET" << std::endl;
  for ( int i = 2; i < argc - 2; i += 2 ) {
    std::string times_string = argv[i + 1];
    int times = 0;
    try {
      times = std::stoi( times_string );
    } catch ( const std::exception& e ) {
      std::cout << "Malformed option" << std::endl;
      PrintUsage( argv[0] );
      return 1;
    }

    std::string option = argv[i];
    if ( option == "-h" ) {
      for ( int t = 0; t < times; t++ ) {
        carver.RemoveHorizontalSeam();
      }
    } else if ( option == "-v" ) {
      for ( int t = 0; t < times; t++ ) {
        carver.RemoveVerticalSeam();
      }
    } else {
      std::cout << argv[i] << " not an option" << std::endl;
      PrintUsage( argv[0] );
      return 1;
    }
  }

  std::ofstream outfile( argv[argc - 1] );
  outfile << carver.GetImage();
  outfile.close();
}

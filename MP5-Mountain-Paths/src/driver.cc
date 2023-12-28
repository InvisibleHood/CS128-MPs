#include "elevation_dataset.hpp"
#include "grayscale_image.hpp"
#include "path_image.hpp"

int main() {
    ElevationDataset e("/home/vagrant/src/mp5-mountain-paths-InvisibleHood/example-data/ex_input_data/map-input-w51-h55.dat", 51, 55);
    std::string image = "grayscale.ppm";
    std::string final = "final.ppm";
    GrayscaleImage gI(e);
    gI.ToPpm(image);
    PathImage pI(gI, e);
    pI.ToPpm(final);
}
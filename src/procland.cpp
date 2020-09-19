#include <iostream>
#include <fstream>
#include <libnoise/noise.h>
#include <chrono>
#include "noiseutils.h"
#include <Rcpp.h>

using namespace Rcpp;
using namespace noise;

// a function that makes wrapped perlin noise
//' Prints Perlin noise to file.
//' 
//' @param n_octaves Number of octaves. May be thought of as small scale 
//' variability. Must be an integer value between 1 and 8. Higher values
//' result in landscapes with more small scale noise.
//' @param frequency Frequency of noise. May be thought of as large scale
//' variability. May be any double value between 1.0 and 16.0. Higher values
//' result in noise that is closer to white noise.
//' @param image_pixels Landscape size in pixels. The image saved will be a
//' square with this side.
//' @param increment The increment at which to move through the landscape.
//' @param save_image A boolean of whether to save the image.
//' @param wrapped A boolean value indicating whether the landscape is
//' tiled, that is, whether the pattern repeats. Useful when generating
//' landscapes for simulations.
//' @param output_path The image filepath to write the landscape.
//' @return A matrix of Perlin noise. Optionally, writes an image to file.
// [[Rcpp::export]]
Rcpp::NumericMatrix pln_get_noise(const int n_octaves, const double frequency,
                                  const double increment,
                                  const bool save_image,
                                  const double image_pixels,
                                  const bool wrapped,
                                  const std::string output_path) {
    
    // get seed
    unsigned seed = static_cast<unsigned> 
    (std::chrono::system_clock::now().time_since_epoch().count());
    // make Perlin noise
    module::Perlin noise;
    noise.SetOctaveCount(n_octaves);
    noise.SetFrequency(frequency);
    noise.SetPersistence(0.5); // hardcoded and fixed
    noise.SetSeed(static_cast<int>(seed));

    if (save_image) {
        // make height map
        utils::NoiseMap thisMap;
        utils::NoiseMapBuilderPlane mapBuilder;
        mapBuilder.SetSourceModule(noise);
        mapBuilder.SetDestNoiseMap(thisMap);
        mapBuilder.SetDestSize(image_pixels, image_pixels);
        mapBuilder.EnableSeamless(wrapped);
        mapBuilder.SetBounds(1.0, 5.0, 
                             1.0, 5.0);
        mapBuilder.Build();

        // render image
        utils::RendererImage renderer;
        utils::Image image;
        renderer.SetSourceNoiseMap(thisMap);
        renderer.SetDestImage(image);
        renderer.Render();

        // no colours for now

        // write to file
        utils::WriterBMP writer;
        writer.SetSourceImage(image);
        writer.SetDestFilename(output_path);
        writer.WriteDestFile();
    }

    // make matrix
    Rcpp::NumericMatrix noise_matrix (image_pixels);
    // make increment size
    const double step_size = 4.0 /static_cast<double> (image_pixels);
    for (size_t i = 0; i < image_pixels; i++)
    {
        for (size_t j = 0; j < image_pixels; j++)
        {
            noise_matrix (i, j) = noise.GetValue(static_cast<double>(i) * step_size, 
                static_cast<double> (j) * step_size, 0.0);
        }
    }
    return noise_matrix;
}

#include <iostream>
#include <fstream>
#include <noise/noise.h>
#include <noise/noiseutils.h>
#include <Rcpp.h>

using namespace Rcpp;
using namespace noise;

// a function that makes wrapped perlin noise
//' Prints Perlin noise to file.
//' 
//' @param nOctaves Number of octaves. May be thought of as small scale 
//' variability. Must be an integer value between 1 and 8. Higher values
//' result in landscapes with more small scale noise.
//' @param frequency Frequency of noise. May be thought of as large scale
//' variability. May be any double value between 1.0 and 16.0. Higher values
//' result in noise that is closer to white noise.
//' @param landSize Landscape size in pixels. The image saved will be a
//' square with this side.
//' @param isWrapped A boolean value indicating whether the landscape is
//' tiled, that is, whether the pattern repeats. Useful when generating
//' landscapes for simulations.
//' @param outputPath A string specifying the image file to write the landscape.
//' @return Nothing. Writes an image to file.
// [[Rcpp::export]]
void getPerlin(const int nOctaves, const double frequency,
               const double landSize, const bool isWrapped,
               std::string outputPath) {
    
    // make Perlin noise
    module::Perlin noise;
    noise.SetOctaveCount(nOctaves);
    noise.SetFrequency(frequency);
    noise.SetPersistence(0.5); // hardcoded and fixed

    // make height map
    utils::NoiseMap thisMap;
    utils::NoiseMapBuilderPlane mapBuilder;
    mapBuilder.SetSourceModule(noise);
    mapBuilder.SetDestNoiseMap(thisMap);
    mapBuilder.SetDestSize(landSize, landSize);
    mapBuilder.EnableSeamless(isWrapped);
    mapBuilder.SetBounds(1.0, 5.0, 1.0, 5.0);
    mapBuilder.Build();

    // render image
    utils::RendererImage renderer;
    utils::Image image;
    renderer.SetSourceNoiseMap(thisMap);
    renderer.SetDestImage(image);
    renderer.ClearGradient ();
    renderer.AddGradientPoint ( 0.0000, utils::Color (  0,   0,   0, 255));
    renderer.AddGradientPoint ( 1.0000, utils::Color (255, 255, 255, 255));
    renderer.Render();

    // no colours for now

    // write to file
    utils::WriterBMP writer;
    writer.SetSourceImage(image);
    writer.SetDestFilename(outputPath);
    writer.WriteDestFile();
}

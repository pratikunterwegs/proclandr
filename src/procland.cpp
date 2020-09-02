#include <iostream>
#include <fstream>
#include <noise/noise.h>
#include <noise/noiseutils.h>
#include <Rcpp.h>

using namespace Rcpp;
using namespace noise;

// a function that makes wrapped perlin noise
// [[Rcpp::export]]
void getPerlin(const int nOctaves, const float frequency,
               const float landSize, const bool isWrapped,
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
    mapBuilder.EnableSeamless(wrapped);
    mapBuilder.SetBounds(1.0, 5.0, 1.0, 5.0);
    mapBuilder.Build();

    // render image
    utils::RendererImage renderer;
    utils::Image image;
    renderer.SetSourceNoiseMap(thisMap);
    renderer.SetDestImage(image);

    // no colours for now
    // write to file
    utils::WriterBMP writer;
    writer.SetSourceImage(image);
    writer.SetDestFilename(outputPath);
    writer.WriteDestFile();
}

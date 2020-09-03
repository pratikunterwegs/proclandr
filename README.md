# Wrapped Perlin noise in R

<!-- badges: start --> 
  [![Build Status](https://travis-ci.org/pratikunterwegs/atlastools.svg?branch=master)](https://travis-ci.org/pratikunterwegs/proclandr) 
  [![codecov.io](https://codecov.io/github/pratikunterwegs/atlastools/coverage.svg?branch=master)](https://codecov.io/github/pratikunterwegs/proclandr/branch/master)
  [![Project Status: WIP – Initial development is in progress, but there has not yet been a stable, usable release suitable for the public.](https://www.repostatus.org/badges/latest/wip.svg)](https://www.repostatus.org/#wip)
  
<!-- badges: end -->

`proclandr` is an `R` package using `Rcpp` that makes wrapped images of Perlin noise.

![Wrapped Perlin Noise](https://github.com/pratikunterwegs/proclandr/blob/master/inst/test_noise_1.png)

## Installation

Install the `libnoise` dependency first. This is easy enough on Linux.

```bash
sudo apt install libnoise-dev
```

Install using `devtools`.

```r
install.packages("devtools")
devtools::install_github("pratikunterwegs/proclandr")
```

## More options

`proclandr` currently implements a very specific form of Perlin noise.
Use the `libnoise` library in `C++` for more options. There is no plan to add these options to `proclandr` anytime soon. 🤷

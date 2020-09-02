#!/bin/bash
cd
git clone https://github.com/pratikunterwegs/libnoise.git
cd libnoise
mkdir build
cd build
cmake ..
make
sudo make install
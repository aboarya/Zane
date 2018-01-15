#!/bin/bash
set -xe

mkdir -p build
cd build
cmake ../ -DMODELDIR=\"`pkg-config --variable=modeldir pocketsphinx`\" -DWAKEUP=\"zane\"
make
#!/bin/bash

set -e

# Configure and generate build files
mkdir -p build
cd build

cmake .. -G Ninja
cmake --build .

cd ..

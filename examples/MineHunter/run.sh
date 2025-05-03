#!/bin/bash
clear

# Navigate to project root
cd "$(dirname "$0")/../.."

# Run premake to generate build files
echo "Generating build files with premake..."
cd build
./premake5 gmake2
cd ..

# Build the project with make
echo "Building MineHunter example..."
make config=debug_x64 MineHunter

# Run the example
echo "Running Mine Hunter..."
cd examples/MineHunter
./MineHunter

echo "Press any key to exit."
read -n 1 
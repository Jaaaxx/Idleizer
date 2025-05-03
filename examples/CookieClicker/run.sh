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
echo "Building CookieClicker example..."
make config=debug_x64 CookieClicker

# Run the example
echo "Running Mine Hunter..."
cd examples/CookieClicker
./CookieClicker

echo "Press any key to exit."
read -n 1 
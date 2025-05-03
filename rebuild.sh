#!/bin/bash
clear

echo "Regenerating build files with premake..."
cd build
./premake5 gmake2 --verbose
cd ..

echo "Building the project (clean + build)..."
make clean config=debug_x64
make config=debug_x64

echo "Done! Run './run.sh' to launch examples." 
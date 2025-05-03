#!/bin/bash
clear

# Run premake to generate build files
echo "Generating build files with premake..."
cd build
./premake5 gmake2
cd ..

# Build the projects
echo "Building Idleizer and examples..."
make config=debug_x64

echo
echo "Idleizer - An idle game engine written in C99 with Raylib"
echo "Available examples:"
echo "1) Mine Hunter"
echo "2) (C)ookie Clicker"
echo
read -p "Enter number to run (or any other key to exit): " choice

case $choice in
  1)
    echo "Running Mine Hunter..."
    cd examples/MineHunter
    ./MineHunter
    ;;
  2)
    echo "Running (C)ookie Clicker..."
    cd examples/CookieClicker
    ./CookieClicker
    ;;
  *)
    echo "Exiting."
    ;;
esac

echo "Press any key to exit."
read -n 1

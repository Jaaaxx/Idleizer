# Idleizer

An idle game engine written in pure C99 with Raylib. This project provides a framework for building idle/incremental games with a clean, modular architecture.

## Features

- **Modular Architecture**: Core components for building idle games
- **Section-based UI**: Organize game elements in customizable sections
- **Currency System**: Built-in support for multiple in-game currencies
- **Building System**: Create buildings that generate resources over time
- **Ticker System**: Schedule recurring events and updates
- **Label System**: Display text information
- **Button System**: Create interactive UI elements with custom handlers

## Dependencies

- [Raylib](https://www.raylib.com/) - A simple and easy-to-use library to learn videogame programming (included in the build directory)
- C99 compatible compiler

## Building from Source

### Prerequisites

- GCC or compatible C compiler
- Make
- Premake5 (included in the build directory)

### Build Instructions

1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/Idleizer.git
   cd Idleizer
   ```

2. Run the rebuild script to regenerate build files and compile:
   ```bash
   ./rebuild.sh
   ```

3. Run the example launcher:
   ```bash
   ./run.sh
   ```

## Project Structure

The project follows a traditional C project layout:

- `/src` - Source files (.c)
- `/include` - Header files (.h)
- `/examples` - Example games using the engine
  - `/MineHunter` - Mine Hunter example game
- `/resources` - Game resources (images, sounds, etc.)
- `/bin` - Compiled binaries
- `/build` - Premake5 and build intermediate files

## Build System

Idleizer uses Premake5 to generate build files. The main components are:

- `build/premake5.lua` - The Premake configuration file
- `rebuild.sh` - Script to regenerate build files and compile
- `run.sh` - Script to build and run examples

To regenerate build files manually:

```bash
cd build
./premake5 gmake2
cd ..
make config=debug_x64
```

## Core Components

### Core

The main container for all game elements, including:
- Sections
- Currencies
- Buttons
- Labels
- Tickers
- Buildings

### Sections

Rectangular areas that organize the UI. Each section can:
- Have a parent section (hierarchical structure)
- Be hidden/shown
- Have its own background color

### Currencies

In-game resources that can be earned and spent:
- Customizable name and position
- Automatically updated display

### Buildings

Structures that generate resources over time:
- Customizable cost and production rate
- Upgradable with increasing costs
- Automatically generate currencies

### Tickers

Time-based event handlers:
- Schedule recurring events
- Update game state at specified intervals

### Buttons

Interactive UI elements:
- Custom click handlers
- Text or image-based
- Positioned within sections

### Labels

Text display elements:
- Customizable position and color
- Can be updated dynamically

## Examples

### Mine Hunter

A simple idle game demonstrating the engine's capabilities:
- Multiple currencies (Gold and Silver)
- Various buildings to generate currencies
- UI sections for game display, shop, and options

To build and run with premake:

```bash
cd build
./premake5 gmake2
cd ..
make config=debug_x64 MineHunter
./examples/MineHunter/MineHunter
```

Or use the convenience script:

```bash
./examples/MineHunter/run.sh
```

## Creating Your Own Game

To create your own idle game with Idleizer:

1. Set up your project structure
2. Include the Idleizer headers:
   ```c
   #include "idleizer.h"
   #include "core.h"
   #include "section.h"
   // ... other components as needed
   ```
3. Initialize a Core structure
4. Set up your sections, currencies, and other game elements
5. Create buildings with custom generation rates
6. Add tickers for time-based events
7. Add UI elements (buttons, labels)
8. Call `runGame()` with your core

See the `/examples/MineHunter` directory for a complete example.

## License

This project is licensed under the terms of the included LICENSE file.

## Contributing

Contributions are welcome! Please feel free to submit a Pull Request.

## Status

This project is currently in active development. Features and APIs may change.

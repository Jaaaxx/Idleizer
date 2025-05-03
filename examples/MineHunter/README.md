# Mine Hunter

A simple example game built with the Idleizer engine.

## Game Description

Mine Hunter is an idle/incremental game where you build miners to generate resources.
The game features two main currencies:
- Gold
- Silver

Each currency can be used to purchase buildings that generate the other currency.

## Game Features

- Multiple sections for UI organization
- Resource generation buildings with increasing costs
- Interactive buttons for showing/hiding sections
- Random flavor text that changes periodically
- Persistent resource counters

## Building and Running

From this directory:

```bash
make
./MineHunter
```

Or from the project root:

```bash
make examples
./examples/MineHunter/MineHunter
```

## Controls

- Click the Options, Stats, Info, and Legacy buttons to reveal different UI sections
- Purchase buildings to generate resources automatically

## Game Structure

The game demonstrates several Idleizer features:
- Section-based UI layout
- Currency system
- Building creation and management
- Button handlers
- Ticker system for time-based events
- Label system for displaying information

This example serves as a reference implementation for creating your own games with Idleizer. 
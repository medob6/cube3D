# cube3D
A 3D game from 42 schole project

# Raycaster (MiniLibX)

This is a simple raycasting 3D engine written in C using the MiniLibX graphics library, inspired by early games like Wolfenstein 3D.

## Features

- Raycasting for 3D perspective rendering
- Player movement (forward/backward/strafe/rotate)
- Wall textures
- Collision detection
- Custom map format (`.cub`)

## Controls

| Key        | Action             |
|------------|--------------------|
| W / S      | Move forward/back  |
| A / D      | Strafe left/right  |
| ← / →      | Rotate view        |
| ESC        | Exit the game      |

## Map Format (`.cub`)

Example:

NO ./textures/north.xpm
SO ./textures/south.xpm
WE ./textures/west.xpm
EA ./textures/east.xpm
F 220,100,0
C 225,30,0

111111
100001
1000N1
111111


- `NO`, `SO`, `WE`, `EA`: texture paths for wall directions
- `F`, `C`: floor and ceiling colors (RGB)
- Map layout:
  - `1` = wall
  - `0` = empty space
  - `N`, `S`, `E`, `W` = player start position and direction

## Build & Run

### Requirements

- Linux or macOS
- gcc or clang
- MiniLibX (usually provided in your project environment)

### Steps

```bash
make
./cub3D maps/example.cub

Structure

    src/ — game logic and rendering

    include/ — headers

    maps/ — sample maps

    textures/ — wall textures

    Makefile — build script



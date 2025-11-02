# 🎮 Cub3D – Optimized 3D Raycasting Engine

![Cub3D Banner](path/to/banner_image.png)

[![C](https://img.shields.io/badge/Language-C-blue?logo=c)](https://www.iso.org/standard/74528.html)
[![42 Project](https://img.shields.io/badge/42-Project-orange)](https://projects.intra.42.fr/)
[![Performance](https://img.shields.io/badge/Performance-Optimized-green)](https://permadi.com/1996/05/ray-casting-tutorial-table-of-contents/)

---

## 🧠 Project Overview

**Cub3D** is a **highly optimized 3D raycasting game engine** developed at **42 / 1337 School**, inspired by **Wolfenstein 3D**.  

The main goal of this project was to **create the most performant and flexible game engine possible** using the restricted tools provided, while adding advanced features and robust algorithms for validation, rendering, and gameplay logic.  

Key highlights:  
- Smooth 3D rendering with raycasting  
- Optimized scene drawing for high FPS  
- Interactive features: doors, start menu, and custom video player  
- A clean **engine API** to simplify game logic and feature integration  

---

## 🔧 Mandatory Features

**Raycasting Engine**  
- Implemented using **DDA (Digital Differential Analyzer)**.  
- Optimized distance calculations and **angle correction** for realistic perspective.  
- Only redraws parts of the scene that have changed for performance.  

**Map Parsing & Validation**  
- Configuration files parsed according to Cub3D specifications.  
- Spaces fill gaps to prevent invalid map errors.  
- Automatic detection of invalid maps (0 tiles next to empty space).  

**Rendering Optimizations**  
- Partial sky/floor redraw based on player movement.  
- Reuses previously calculated distances for nearby columns.  
- Profiling to detect and optimize bottlenecks.  

---

## 🌟 Bonus Features

**Start Menu**  
- Fully functional menu with clickable buttons: Start, Exit, Controls.  
- Pixel-perfect detection for smooth user interaction.  

**Video Player**  
- Built from scratch using **libav / avcodec**.  
- Supports playback from **URLs** (including HTTPS via OpenSSL).  
- Optimized for smooth playback and integration with in-game events.  

**Interactive Doors**  
- Doors open and close based on **precise mathematical equations**.  
- Fully integrated with raycasting and collision detection.  
- Optimized to update only when necessary for performance.  

**Advanced Map Validation**  
- **Flood-fill algorithm** ensures map is enclosed and valid.  
- Additional algorithms applied to improve reliability and error detection.  

**Custom Game Engine API**  
- Exposes a **simple, clean interface** to handle rendering, movement, events, and assets.  
- Makes integration of features like menus, video playback, and doors **straightforward and modular**.  

---

## 🕹️ Controls

- **Move Forward/Backward:** W / S  
- **Strafe Left/Right:** A / D  
- **Rotate View:** Arrow Keys ← →  
- **Exit Game:** ESC  
- **Interact with Menu:** Mouse Click  

---

## 📂 Project Structure



cub3D/
├── mandatory/
│ ├── src/
│ ├── include/
│ └── config/
├── bonus/
│ ├── src/
│ └── include/
├── engine/ → Custom game engine API
├── mlx_linux/
├── textures/
├── maps/
├── Makefile
└── README.md


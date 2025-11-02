# 🎮 Cub3D – High‑Performance 3D Raycasting Engine

![Cub3D Banner](path/to/banner_image.png)

[![Language: C](https://img.shields.io/badge/Language‑C‑blue?logo=c)](https://www.iso.org/standard/74528.html) [![42 Project](https://img.shields.io/badge/42‑Project‑orange)](https://projects.intra.42.fr/) [![Performance Optimized](https://img.shields.io/badge/Performance‑Optimized‑green)](https://permadi.com/1996/05/ray‑casting‑tutorial‑table‑of‑contents/)

**Overview**  
Cub3D is a 3D raycasting engine born from the 42/1337 curriculum, inspired by classic titles like Wolfenstein 3D. My objective: build a **lightweight yet extremely performant engine** using only the tools permitted, pushing beyond expectations with optimized rendering, smart algorithms and a clean engine API.  

**Mandatory Features**  
In the core engine I implemented:  
- A DDA‑based raycasting algorithm for wall collision and rendering.  
- Angle correction and distance reuse to eliminate distortion and reduce computation.  
- Map parsing with gap‑filling (spaces) to avoid invalid map configurations; automatic map validation.  
- Optimized scene drawing: sky, floor and walls are redrawn only when necessary—reducing CPU load and boosting FPS.  

**Bonus Features**  
Going beyond the base requirements, this project also includes:  
- A fully functional **start menu** with clickable buttons (Start, Exit, Controls) and mouse interaction.  
- A custom **video player** module built with libav/avcodec and OpenSSL, enabling playback of remote HTTPS video URLs integrated with in‑game events.  
- **Interactive doors** governed by precise mathematical equations, integrated into collision detection and optimized for minimal updates.  
- Advanced **map validation algorithms** including flood‑fill to ensure maps are fully enclosed and valid before gameplay begins.  
- A modular **engine API** that simplifies rendering, entity management, input handling, and feature integration—enabling easier expansion and maintenance.  

**Controls**  
W / S → Move forward / backward  
A / D → Strafe left / right  
← / → → Rotate view  
ESC → Exit game  
Mouse → Interact with the menu  

**Project Structure**
```bash
cub3D/
├── mandatory/               → Core game logic and resources
│   ├── includes/            → Header files for mandatory part
│   ├── libft/               → Custom C library used in mandatory part
│   ├── maps/                → Example maps for mandatory part
│   ├── src/                 → Source code for mandatory game engine
│   └── textures/            → Wall and sprite textures
├── bonus/                   → Bonus features and enhancements
│   ├── audio/               → Sound effects and music
│   ├── includes/            → Header files for bonus features
│   ├── libft/               → Custom C library used in bonus part
│   ├── maps/                → Example maps for bonus part
│   ├── src/                 → Source code for bonus features
│   ├── textures/            → Additional textures
│   └── video/               → Video player module
├── cub3D                    → Main executable (after compilation)
├── Makefile                 → Build system
├── mlx_linux/               → MiniLibX library (Linux)
├── setup.sh                 → Environment setup script
├── testing_video_playing.c  → Video player testing file
└── README.md                → Project documentation
```

**Tools & Libraries**  
Written in C, rendered with MiniLibX, video capabilities via libav/avcodec, secure URL support via OpenSSL, and optimization achieved through native time and math libraries.  

**Build & Run Instructions**  
```bash
git clone https://github.com/medob6/cube3D.git  
cd cube3D  
make  
./cub3D maps/example.cub  
```
Visual Showcase
(Replace the links below with your actual screenshots/GIFs)

Performance Highlights

    Selective redraw logic to only update changed scene segments.

    Distance reuse across raycasts to reduce redundant computation.

    Angle correction for accurate perspective rendering.

    Custom video playback smoothly integrated with game flow.

    Algorithmic door logic and map flood‑fill validation to enhance robustness and performance.

**References / Resources**  
- [Raycasting Algorithm Inspiration – Permadi Tutorial](https://permadi.com/1996/05/ray-casting-tutorial-table-of-contents/)  
- [MiniLibX Documentation](https://harm-smits.github.io/42docs/libs/minilibx)  
- [OpenSSL Documentation](https://www.openssl.org/docs/)  
- [FFmpeg / libav Tutorial – Dranger](http://dranger.com/ffmpeg/)  
- [FFmpeg Wiki – Using libavcodec](https://trac.ffmpeg.org/wiki/Using%20Libav%20Codec)  
- [FFmpeg Official Documentation](https://ffmpeg.org/documentation.html)


**Authors**  
- [Mohamed Boussetta – 42 / 1337 School](https://github.com/medob6) – Core engine, raycasting optimizations, rendering, video player, performance improvements  
- [Omar Bencherif – 42 / 1337 School](https://github.com/omar-bencherif) – Map parsing, menu system, game logic, bonus feature integration

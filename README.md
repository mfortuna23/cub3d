# 🕹️ cub3D – The Retro FPS Engine

Welcome to our mini 3D world!  
`cub3D` is a raycasting project inspired by *Wolfenstein 3D*, where pixels become corridors and you become the player. 
Built from scratch in C, this project is part of the **42 School curriculum** and our first dive into the world of graphical engines.

## 👥 Teamwork Makes the Dream Work

This project was brought to life by a dynamic duo:  
- 🧠 Myself 
- 🔧 Alex-mfs (https://github.com/Alex-mfs)

## 💡 About the Project

The goal? Create a simple 3D game engine using the **raycasting** technique (a bit like how early FPS games rendered 3D environments). 
Our engine loads a map, renders walls and sprites in 3D, and lets you move around as if you’re inside a pixelated labyrinth.

### Features:
- 3D rendering with raycasting 🧱
- Textured walls and floor/ceiling colors 🌈
- WASD movement & camera rotation 🎮
- Wall colision 🚧
- Configurable via `.cub` map files 📄
- mini map (in bonus)

Runs on **Linux** and **macOS**! 🐧🍎

## 🚀 How to Use

### 🛠 Requirements
- Make sure you have the following installed:
  - `make`
  - `gcc`
  - macOS or Linux

### Clone
```bash
  git clone https://github.com/mfortuna23/cub3d/
```

### 🧱 Build
```bash
  cd cub3d
  make
```

### 🎮 Run
```bash
  ./cub3d map_files/valid/valid1.cub
```

# Raytracer

A configurable 3D ray tracer written in C++17. It reads a scene description with `libconfig++` and renders an image. Primitives, lights and materials are loaded as plugins (shared libraries), so new ones can be added without touching the core.

## Features

- Primitives: sphere, plane, cylinder, cone, cube
- Lights: point, directional
- Materials: flat color, reflection
- Plugin architecture: each primitive, light and material builds to its own `.so` in `plugins/`
- Scene files parsed with libconfig

## Requirements

- g++ with C++17 support
- `libconfig++` (Debian/Ubuntu: `sudo apt install libconfig++-dev`)
- make

## Build

```bash
make
```

This builds the `raytracer` binary and every plugin under `plugins/`. Use `make clean` / `make fclean` / `make re` as usual.

## Usage

```bash
./raytracer <scene_file.cfg>
```

## Project layout

```
Raytracer/
  Core/        renderer, light handling, interfaces (IObject, ILight, IMaterial)
  Scene/       scene loading
  math/        points, rays, transforms
  Lights/      Point, Directional
  Materials/   FlatColor, Reflection
makefile
```

## Credits

Built as a team project at Epitech by Andrei Kocherzhinskii, Keigan Baldwin and Khushan Hitesh Kanakrai. Full commit history is preserved.

<p align="center">
  <img src="https://github.com/Ego8316/Ego8316/blob/main/42-badges/minirt.png" height="150" alt="42 miniRT Badge"/>
</p>

<p align="center">
  <img src="https://img.shields.io/badge/42-Project-blue" height="32"/>
  <img src="https://img.shields.io/github/languages/code-size/Ego8316/minishell?color=5BCFFF" height="32"/>
</p>

<p align="center">
  <img src="https://img.shields.io/badge/Linux-0a97f5?style=for-the-badge&logo=linux&logoColor=white" height="32"/>
  <img src="https://img.shields.io/badge/mac%20os-000000?style=for-the-badge&logo=apple&logoColor=white" height="32"/>
  <img src="https://img.shields.io/badge/WSL-0a97f5?style=for-the-badge&logo=linux&logoColor=white" height="32"/>
</p>

# miniRT

### 🎓 42 School – Final Grade: **125/100**

Minimal ray tracer written in C. Parses a scene description, casts rays against basic primitives, shades with ambient/diffuse/specular lighting, and renders via MiniLibX.

---

## 📦 Features
- Scene parser: camera, ambient, point lights, spheres, planes, cylinders, cones, textures, and bump maps loaded from `.rt` files.
- Ray/object intersections: analytic solutions for sphere, plane, finite cylinder, and finite cone (caps included).
- Shading: ambient + Lambertian diffuse + Phong-like specular, per-light shadow checks.
- Texturing/UVs: planar/spherical/cylindrical/conical mapping, checkerboard, optional bump perturbation.
- Camera: configurable origin, direction, and FOV with perspective projection.
- Output: rendered with MiniLibX (Linux or macOS variants) in an interactive window.

---

## 🛠️ Building
```bash
make          # build ./miniRT
make clean    # remove object files
make fclean   # remove objects + binaries
make re       # rebuild from scratch
```
Requirements: `gcc`, `make`, and MiniLibX (submodules provided: `minilibx-linux` / `minilibx-macos`). On Linux: link with X11 (`-lX11 -lXext -lm -lz`). Tested on Linux/WSL; macOS uses the MLX AppKit/OpenGL flags.

---

## 🚀 Usage
```bash
./miniRT scenes/example.rt             # render a scene file
./miniRT scenes/sphere_in_box.rt       # try another preset
./miniRT scenes/sphere_in_box_textures.rt   # textured/bumped example
```

### Example `.rt` scene
```
A 0.1 255,255,255               # ambient (ratio, color)
C 0,0,-10 0,0,1 60              # camera (pos, dir, fov)
L 5,5,-5 0.7 255,200,200        # light (pos, brightness, color)

sp 0,0,5 4 200,100,100          # sphere (pos, diameter, color)
pl 0,-3,0 0,1,0 150,150,150     # plane (pos, normal, color)
cy 2,0,8 0,1,0 2 6 100,200,255  # cylinder (pos, axis, diameter, height, color)
co -3,0,10 0,1,0 3 6 255,220,180 # cone (pos, axis, diameter, height, color)
```
Textures and bump maps can be attached by replacing the color with a texture name present in `textures/` (see `scenes/sphere_in_box_textures.rt`).
You can generate new texture/bump CSVs with the helper script `convert_texture.py` in the repo root.

---

## 🧩 Architecture Overview
MiniRT follows a modular architecture:
- **Parser** – reads `.rt` files, validates bounds, builds scene objects/lights.
- **Raycasting** – intersection routines per primitive; hit reordering and shadow rays.
- **Shading** – color selection (solid/checker/texture), bump mapping, ambient/diffuse/specular accumulation.
- **Camera/View** – builds camera basis and per-pixel view rays.
- **Graphics** – MiniLibX window and pixel buffer blitting.

---

## ⚠️ Limitations (per subject)
- No triangles/meshes, reflections, refractions, or global illumination.
- Camera inside/through geometry may show clipping/weird normals.
- Single bounce only; no post-processing/antialiasing in this version.

---

## 👥 Contributors
- [Ego8316](https://github.com/Ego8316)
- [victorviterbo](https://github.com/victorviterbo/)

---

## 📄 License
MIT — see `LICENSE`.

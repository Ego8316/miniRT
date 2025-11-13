# miniRT - Minimal Ray Tracer

A minimalistic raytracing engine written in C. It renders simple 3D scenes described in a configuration file, applying lighting, shadows, and reflections to create realistic images.

## ✨ Features
- Renders geometric primitives: spheres, planes, cylinders, squares, triangles
- Implements ambient, diffuse, and specular lighting
- Phong reflection model for realistic materials
- Camera movement and multiple viewpoints
- Saves the rendered image to a BMP file
- Handles shadows and basic reflections

## 🎨 Supported Elements
- **Camera**: Position, orientation, field of view
- **Lights**: Ambient, point lights
- **Objects**: Spheres, planes, cylinders, etc.
- **Materials**: Colors, reflectivity, specular components

## 🚀 Usage
### Generate image
./miniRT [scene_file.rt]
### Scene syntax
A 0.2 255,255,255 -> ambiant light (A) of intensity 0.2 and white (R=255, G=255, B=255)

C 5,0,0	-1,0,0	100 -> Camera (C) at position (5, 0, 0) oriented along the (-1, 0, 0) axis and a Field-Of-View of 100 ([0, 180])

L 5,0,0	1.0	255,255,255     -> singular light at position (5, 0, 0), of intensity 1 and white (R=255, G=255, B=255)

cy 0,0,0 0,-1,0 2 4 160,0,160 s 150     -> cylinder at position (5, 0, 0), oriented along the (-1, 0, 0) axis of width 2, height 4, color purple (R=160, G=0, B=160)

pl -8,0,0    1,0,0      checkerboard    -> plane at position (-8, 0, 0), normal to the (1, 0, 0) axis using a covered with a checkerboard pattern

co 0,-2,0 0,1,0 2 4 160,0,160 s 150 -> cone with it's tip at position (0, -2, 0) expanding along the (0, 1, 0) axis, with a base of diameter 2 and a height of 4


For the latter 3, one can replace the color with one of the available texture, and add one or both of the following flags: 
- specify a specular intensity ("shininess") with "s ###" (### a number between 10 and 1500)
- specify the texture roughness ("bumpiness") with "b ###" (### a number between 0 and 1)

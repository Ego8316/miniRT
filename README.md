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
`###_vec` values have to be passed as a,b,c 
`color_vec` values have to be bassed as R,G,B

`A \<intensity\> \<color_vec\>  -> Ambiant Light`
->ex: `A 0.2 255,255,255`

`C \<position_vec\>	\<direction_vec\>	\<field of view\>`  -> Camera
->ex: `C 5,0,0 -1,0,0  100`

`L \<position_vec\> \<intensity\> \<color_vec\>`  -> Singular Light
->ex: `L 5,0,0 1.0`

`sp \<position_vec_center\> \<radius\> \<color_vec\> [s \<surface_shininess\>] [b \<surface_roughness\>]`  -> 
->ex: `sp 0,0,0 5 snow s 150 b 1`

`cy \<position_vec_center\> \<direction_vec\> \<base_width\> \<heigh\> \<color_vec\> [s \<surface_shininess\>] [b \<surface_roughness\>]`  -> cylinder
->ex: `cy 0,0,0 0,-1,0 2 4 160,0,160 s 150`

`pl \<position_vec\> \<normal_vec\> \<color_vec\> [s \<surface_shininess\>] [b \<surface_roughness\>]`  -> plane
-> ex: `pl -8,0,0 1,0,0 checkerboard`

`co  \<position_vec_tip\> \<direction_vec\> \<base_diameter\> \<height\> \<color_vec\> [s \<surface_shininess\>] [b \<surface_roughness\>]` -> cone 
-> ex: `co 0,-2,0 0,1,0 2 4 160,0,160 s 150`


For the latter 3, one can replace the color with one of the available texture, and add one or both of the following flags: 
- specify a specular intensity ("shininess") with "s ###" (### a number between 10 and 1500)
- specify the texture roughness ("bumpiness") with "b ###" (### a number between 0 and 1)

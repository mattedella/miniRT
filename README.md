# miniRT
**My First Ray Tracer with MiniLibX**

![Ray Traced Scene](https://upload.wikimedia.org/wikipedia/commons/7/76/Raytraced_image.png)

## 🖼️ Overview

**miniRT** is a minimal ray tracing engine written in C using the [MiniLibX](https://harm-smits.github.io/42docs/libs/minilibx) graphics library. This project is an introduction to the fundamentals of ray tracing, 3D rendering, and low-level graphical programming.

You will build a program that can generate computer-generated images of scenes described by `.rt` files, supporting basic geometric shapes, camera manipulation, and light effects.

> “After this project, you'll never fear implementing mathematical formulas again.”

---

## 📦 Features

### ✅ Mandatory

- Basic ray tracing engine
- Support for:
  - **Spheres**
  - **Planes**
  - **Cylinders**
- Ambient and diffuse lighting
- Multiple light sources
- Simple scene description via `.rt` files
- Window rendering using MiniLibX
- Camera field of view and transformations
- Proper input parsing with error handling
- Clean exit on ESC or window close
- Norm-compliant, memory-safe code

### 🔥 Bonus (if mandatory is perfect)

- Specular reflection (Phong model)
- Checkerboard pattern materials
- Colored and multi-spot lights
- Additional objects: cone, hyperboloid, etc.
- Bump mapping
- Extended `.rt` file support

---

## 📁 File Format

Scene files must have the `.rt` extension and define elements such as:

```plaintext
A 0.2 255,255,255
C -50,0,20 0,0,1 70
L -40,0,30 0.7 255,255,255
sp 0,0,20 20 255,0,0
pl 0,0,0 0,1,0 255,0,255
cy 50,0,20.6 0,0,1 14.2 21.42 10,0,255
```

---

## 🛠️ Compilation

This project is written in **C** and follows the **42 Norm**.

```bash
make              # Compile the project
make clean        # Remove object files
make fclean       # Remove binaries and object files
make re           # Recompile everything
make bonus        # Compile with bonus features
```

> Compile with `-lm` flag to link the math library.

---

## 🚀 Usage

```bash
./miniRT scenes/example.rt
```

Press `ESC` or close the window to exit the program cleanly.

---

## 📚 Requirements

- Language: C (Norm-compliant)
- Libraries:
  - [MiniLibX](https://harm-smits.github.io/42docs/libs/minilibx)
  - `math.h` (`-lm`)
  - Standard C functions: `malloc`, `free`, `read`, `write`, `printf`, `exit`, etc.
- Proper memory handling and error reporting

---

## 💡 Learning Goals

- Understand 3D graphics rendering concepts
- Implement mathematical algorithms for ray-object intersections
- Practice file parsing and graphical output
- Improve modular and maintainable C programming
- Learn about light, shadows, and geometry in rendering

---

## 🧠 Tips

- Debug using simple test `.rt` files
- Build scenes step-by-step for easier troubleshooting
- Use normalized vectors for directions
- Verify object intersections visually and mathematically

---

## 📸 Gallery

Add your own screenshots
<!-- <p float="left">
  <img src="screenshots/sphere.png" width="300"/>
  <img src="screenshots/shadows.png" width="300"/>
</p> -->

---

## ✅ Evaluation Checklist

- [x] Clean compilation with Makefile
- [x] Handles `.rt` parsing correctly
- [x] Supports camera and light configurations
- [x] Renders sphere, plane, and cylinder correctly
- [x] Handles invalid input gracefully
- [x] Fully functional bonus features (if included)

---

## 🧪 Testing

You are encouraged to write your own test scenes to validate features. Peer-evaluations may include:

- Adding objects dynamically
- Tweaking FOV or camera angles
- Scene parsing error testing

---

## 📄 License

This project is part of the 42 School curriculum and is subject to its peer-review process.

---

## 🙌 Acknowledgements

- MiniLibX by 42
- Ray Tracing research and pioneers since 1968
- The 42 community and your awesome peers!

---

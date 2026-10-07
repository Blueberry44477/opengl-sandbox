# OpenGL Sandbox

A personal C++ learning playground and sandbox for exploring modern OpenGL.

---

## 🛠️ Tech Stack & Dependencies

- **Language:** C++17
- **Build System:** CMake (3.16+)
- **Graphics API:** OpenGL (Core Profile)
- **Windowing & Input:** [GLFW](https://www.glfw.org/)
- **OpenGL Function Loader:** [GLAD](https://glad.dav1d.de/) (OpenGL 4.1 Core)

---

## 📋 Prerequisites

On macOS, install the required dependencies via [Homebrew](https://brew.sh/):

```bash
brew install cmake glfw
```

*(GLAD headers and source are already vendored under `include/` and `src/`.)*

---

## 🔨 Building and Running

### 1. Configure and Build

From the root of the repository:

```bash
# Create build directory and generate build files
cmake -B build -S .

# Compile executable
cmake --build build
```

### 2. Run

```bash
./build/app
```

---

## 📁 Project Structure

```text
opengl-sandbox/
├── CMakeLists.txt     # Build configuration
├── include/           # Third-party headers (GLAD, KHR)
├── src/               # Supporting source files (glad.c)
├── main.cpp           # Entry point and render loop
└── README.md          # Project documentation
```

---

## 🎯 Learning Roadmap & Goals

- [x] Basic window creation & context initialization (GLFW + GLAD)
- [x] Render loop & Retina framebuffer scaling
- [ ] Triangle rendering (VBO, VAO, EBO)
- [ ] GLSL Shaders & uniform buffers
- [ ] Textures & Samplers
- [ ] 3D Coordinate systems (Model, View, Projection matrices)
- [ ] Basic lighting (Phong / Blinn-Phong)
- [ ] Model loading (Assimp)

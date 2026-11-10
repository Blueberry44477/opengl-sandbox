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
./build/labs/01_primitives/lab01_primitives
```

---

## 📁 Project Structure

```text
opengl-sandbox/
├── CMakeLists.txt        # Root build configuration
├── core/                 # Shared graphics framework (static library)
│   ├── CMakeLists.txt
│   ├── include/          # Headers (core/Application.hpp, core/Shader.hpp, glad, KHR)
│   └── src/              # Sources (Application.cpp, Shader.cpp, glad.c)
├── labs/                 # Laboratory assignments
│   ├── CMakeLists.txt
│   └── 01_primitives/    # Lab 01: Primitives (Hello Triangle)
│       ├── CMakeLists.txt
│       ├── HELLO_TRIANGLE_UA.md
│       ├── main.cpp
│       └── shaders/
└── README.md             # Project documentation
```

---

## 🎯 Learning Roadmap & Goals

- [x] Basic window creation & context initialization (GLFW + GLAD)
- [x] Render loop & Retina framebuffer scaling
- [x] Triangle rendering (VBO, VAO) — *див. [Детальне пояснення (UA)](./labs/01_primitives/HELLO_TRIANGLE_UA.md)*
- [x] Basic GLSL Shaders (Vertex & Fragment compilation/linking)
- [ ] Element Buffer Objects (EBO / Index Buffers)
- [ ] Uniform variables & dynamic colors
- [ ] Textures & Samplers
- [ ] 3D Coordinate systems (Model, View, Projection matrices)
- [ ] Basic lighting (Phong / Blinn-Phong)
- [ ] Model loading (Assimp)

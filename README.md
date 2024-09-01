# miniRT

miniRT is a minimalist ray tracing engine built as part of a learning project. It is implemented in C and use MLX42. This project is intended to serve as an educational tool to understand the fundamental concepts of ray tracing.

## Features

- **Basic Shapes:** Supports rendering of basic shapes such as spheres, planes and cylinder.
- **Lighting:** Implements basic lighting models including ambient and diffuse light.
- **Shadows:** Basic shadow computation.
- **Camera:** Basic camera setup and transformations.
- **Multithreading:** Utilizes multithreading to speed up the rendering process.

## Getting Started

### Prerequisites

- **Compiler:** cc
- **Make and CMake:** Ensure make and CMake are installed.

### Building the Project

1. **Clone the repository:**
    ```bash
    git clone <repository-url>
    cd miniRT
    ```

2. **Build using make:**
    ```bash
    make
    ```

### Running the Project

To run the renderer with a predefined scene, use the following command:
```bash
./miniRT scenes/example_scene.rt
```

### Project Structure

- `src/` - Contains the source code.
- `include/` - Contains header files.
- `scenes/` - Example scene files.
- `Makefile` - Build configuration file.

### Configuration

Modify the `scenes/example_scene.rt` file to change the scene setup. Scenes are defined using a custom description language.

### Usage

After building the project, you can render a scene by running the `miniRT` executable with a scene description file as input.

### Example:

```bash
./miniRT scenes/simple_scene.rt
```

## License

This project is licensed under the Supreme Licence.


---

Happy Ray Tracing!
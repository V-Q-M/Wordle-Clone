# Wordle OpenGL Game - Design Overview

## Architecture

The project is divided into two main versions:

- **OpenGL Version:** Uses modern OpenGL to render the game board and text with shaders.
- **CLI Version:** A minimal command-line interface version for quick testing and fallback.

### Core Components

- **Game Logic (`game.cpp` / `game.h`):**  
  Handles the Wordle gameplay mechanics, such as word validation, tracking guesses, and determining correct/incorrect letter positions.

- **Rendering (`main.cpp` and shaders):**  
  Uses OpenGL for drawing the game board grid, letters, and feedback colors (green, yellow, gray).  
  The shaders are located in `assets/shaders/`:

  - `shader.vs` / `shader.fs` — basic rendering shaders.
  - `text.vs` / `text.fs` — shaders specialized for rendering font glyphs.

- **Input Handling:**  
  Processes keyboard events to capture user guesses and interact with the game.

### File Organization

- **`src/`** — Main source files.
- **`include/`** — Header files and third-party includes (`glad`, `KHR`).
- **`assets/shaders/`** — GLSL shader files for rendering.
- **`fonts/`** — TrueType font files used for text rendering.
- **`CLI-VERSION/`** — Command-line interface variant of the game.

### Rendering Pipeline

1. Load and compile shaders.
2. Load font texture atlas from `arial.ttf`.
3. Render the game grid using OpenGL primitives.
4. Render letters using textured quads with the font shaders.
5. Color tiles according to Wordle feedback rules.

### Game State

- Stores current guesses, the target word, and guess count.
- Updates visual feedback each frame based on game state.
- Resets on win/loss or user request.

---

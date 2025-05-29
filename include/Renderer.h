#pragma once

#include "../include/Shader.h"

class Renderer {
public:
  // Pass in the shader paths here, or you can pass in an already-constructed
  // Shader
  Renderer(Shader &shader);
  ~Renderer();

  // Call once per frame to draw the triangle
  void Draw();

private:
  Shader &shader;
  unsigned int VAO, VBO;

  void SetupGeometry();
};

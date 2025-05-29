#include "../include/Renderer.h"
#include "../include/glad/glad.h"

// clang-format off
static float triangleVerts[] = {
    // positions         // colors
     0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,
     0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f};

// clang-format on
Renderer::Renderer(Shader &shaderRef) : shader(shaderRef) { SetupGeometry(); }

Renderer::~Renderer() {
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
}

void Renderer::SetupGeometry() {
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);

  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVerts), triangleVerts,
               GL_STATIC_DRAW);

  // position
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
  // color
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                        (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

void Renderer::Draw() {
  shader.use();
  shader.setFloat("someUniform", 1.0f);
  glBindVertexArray(VAO);
  glDrawArrays(GL_TRIANGLES, 0, 3);
  glBindVertexArray(0);
}

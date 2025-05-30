#include "../include/Renderer.h"
#include "../include/glad/glad.h"
#include <vector>

// clang-format off
/*
static float fake_positions[] = {
   500,  500, 0, 1000, 0, 0,
  -500,  500, 0, 0, 1000, 0,
   500, -500, 0, 0, 0, 1000,
  -500, -500, 0, 1000, 0, 0,
  -500,  500, 0, 0, 1000, 0,
   500, -500, 0, 0, 0, 1000,
  
};
*/
// Very cheap solution. But for now it works

#define BOARD_OFFSET_X -239
#define BOARD_OFFSET_Y -360
#define MAKE_SQUARE(size, x, y) \
  size + x + BOARD_OFFSET_X, size + y + BOARD_OFFSET_Y, 0, 1000, 0, 0, \
 -size + x + BOARD_OFFSET_X, size + y + BOARD_OFFSET_Y, 0, 0, 1000, 0, \
  size + x + BOARD_OFFSET_X, -size + y + BOARD_OFFSET_Y, 0, 0, 0, 1000, \
 -size + x + BOARD_OFFSET_X, -size + y + BOARD_OFFSET_Y, 0, 1000, 0, 0, \
 -size + x + BOARD_OFFSET_X, size + y + BOARD_OFFSET_Y, 0, 0, 1000, 0, \
  size + x + BOARD_OFFSET_X, -size + y + BOARD_OFFSET_Y, 0, 0, 0, 1000


int fake_positions[] {
  MAKE_SQUARE(50, 0, 0),
  MAKE_SQUARE(50, 120, 0),
  MAKE_SQUARE(50, 240, 0),
  MAKE_SQUARE(50, 360, 0),
  MAKE_SQUARE(50, 480, 0),

  MAKE_SQUARE(50, 0, 120),
  MAKE_SQUARE(50, 120, 120),
  MAKE_SQUARE(50, 240, 120),
  MAKE_SQUARE(50, 360, 120),
  MAKE_SQUARE(50, 480, 120),

  MAKE_SQUARE(50, 0, 240),
  MAKE_SQUARE(50, 120, 240),
  MAKE_SQUARE(50, 240, 240),
  MAKE_SQUARE(50, 360, 240),
  MAKE_SQUARE(50, 480, 240),

  MAKE_SQUARE(50, 0, 360),
  MAKE_SQUARE(50, 120, 360),
  MAKE_SQUARE(50, 240, 360),
  MAKE_SQUARE(50, 360, 360),
  MAKE_SQUARE(50, 480, 360),

  MAKE_SQUARE(50, 0, 480),
  MAKE_SQUARE(50, 120, 480),
  MAKE_SQUARE(50, 240, 480),
  MAKE_SQUARE(50, 360, 480),
  MAKE_SQUARE(50, 480, 480),

  MAKE_SQUARE(50, 0, 600),
  MAKE_SQUARE(50, 120, 600),
  MAKE_SQUARE(50, 240, 600),
  MAKE_SQUARE(50, 360, 600),
  MAKE_SQUARE(50, 480, 600),

};

//make_square(50, fake_positions);


const static int num_of_vertices = sizeof(fake_positions) / sizeof(fake_positions[0]);


static float triangleVerts[num_of_vertices];




void translate_vertices() {
  for (int i=0; i < num_of_vertices; i++){
    triangleVerts[i] = float(fake_positions[i] / 1000.0f);
  }
}

// clang-format on
Renderer::Renderer(Shader &shaderRef) : shader(shaderRef) { SetupGeometry(); }

Renderer::~Renderer() {
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
}

void Renderer::SetupGeometry() {

  translate_vertices();

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
  glDrawArrays(GL_TRIANGLES, 0, 6 * 5 * 6);
  glBindVertexArray(0);
}

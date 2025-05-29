#pragma once

#include "../include/Shader.h"
#include <glm/glm.hpp>
#include <map>
#include <string>

class TextRenderer {
public:
  TextRenderer(const char *fontPath, unsigned int fontSize = 48);
  ~TextRenderer();

  void RenderText(Shader &shader, const std::string &text, float x, float y,
                  float scale, glm::vec3 color);

private:
  struct Character {
    unsigned int TextureID;
    glm::ivec2 Size;
    glm::ivec2 Bearing;
    unsigned int Advance;
  };

  std::map<char, Character> Characters;
  unsigned int VAO, VBO;

  void LoadFont(const char *fontPath, unsigned int fontSize);
  void SetupBuffers();
};

#include "../include/TextRenderer.h"

#include <ft2build.h>
#include <iostream>
#include FT_FREETYPE_H

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

// Constructor: initialize FreeType, load font and glyphs, set up buffers
TextRenderer::TextRenderer(const char *fontPath, unsigned int fontSize) {
  LoadFont(fontPath, fontSize);
  SetupBuffers();
}

// Destructor: clean up OpenGL textures and buffers
TextRenderer::~TextRenderer() {
  for (auto &pair : Characters) {
    glDeleteTextures(1, &pair.second.TextureID);
  }
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
}

// FontLoader: Takes a fontpath and a fontsize
void TextRenderer::LoadFont(const char *fontPath, unsigned int fontSize) {
  FT_Library ft;
  if (FT_Init_FreeType(&ft)) {
    std::cerr << "ERROR::FREETYPE: Could not init FreeType Library\n";
    throw std::runtime_error("Failed to initialize FreeType");
  }

  FT_Face face;
  if (FT_New_Face(ft, fontPath, 0, &face)) {
    std::cerr << "ERROR::FREETYPE: Failed to load font " << fontPath << "\n";
    FT_Done_FreeType(ft);
    throw std::runtime_error("Failed to load font");
  }

  FT_Set_Pixel_Sizes(face, 0, fontSize);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Disable byte-alignment restriction

  // Load first 128 ASCII characters
  for (unsigned char c = 0; c < 128; c++) {
    if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
      std::cerr << "ERROR::FREETYPE: Failed to load Glyph for char '" << c
                << "'\n";
      continue;
    }

    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width,
                 face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE,
                 face->glyph->bitmap.buffer);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    Character character = {
        texture,
        glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
        glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
        static_cast<unsigned int>(face->glyph->advance.x)};

    Characters.insert(std::pair<char, Character>(c, character));
  }

  FT_Done_Face(face);
  FT_Done_FreeType(ft);
}

void TextRenderer::SetupBuffers() {
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);

  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  // 6 vertices, 4 floats each (x, y, u, v)
  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, nullptr,
               GL_DYNAMIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), nullptr);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

void TextRenderer::RenderText(Shader &shader, const std::string &text, float x,
                              float y, float scale, glm::vec3 color) {
  shader.use();
  shader.setVec3("textColor", color);
  glActiveTexture(GL_TEXTURE0);
  glBindVertexArray(VAO);

  float origX = x; // store the original x for new lines

  for (const char &c : text) {
    if (c == '\n') {
      x = origX;
      y -= (Characters['H'].Size.y + 10) * scale; // line height heuristic
      continue;
    }
    Character ch = Characters[c];

    float xpos = x + ch.Bearing.x * scale;
    float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

    float w = ch.Size.x * scale;
    float h = ch.Size.y * scale;

    float vertices[6][4] = {
        {xpos, ypos + h, 0.0f, 0.0f},    {xpos, ypos, 0.0f, 1.0f},
        {xpos + w, ypos, 1.0f, 1.0f},

        {xpos, ypos + h, 0.0f, 0.0f},    {xpos + w, ypos, 1.0f, 1.0f},
        {xpos + w, ypos + h, 1.0f, 0.0f}};

    glBindTexture(GL_TEXTURE_2D, ch.TextureID);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

    glDrawArrays(GL_TRIANGLES, 0, 6);

    x += (ch.Advance >> 6) * scale; // advance is in 1/64 pixels
  }

  glBindVertexArray(0);
  glBindTexture(GL_TEXTURE_2D, 0);
}

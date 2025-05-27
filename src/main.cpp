#include "../include/game.h"
#include "../include/glad/glad.h"
#include "../include/input.h"
#include "../include/renderer.h"
#include <GLFW/glfw3.h>

// WORDLE
int main(int argc, char *argv[]) {

  glfwInit();
  GLFWwindow *window = glfwCreateWindow(800, 600, "Wordle", NULL, NULL);
  glfwMakeContextCurrent(window);

  init_input(window);
  init_game();
  while (!glfwWindowShouldClose(window)) {

    // game loop
    if (!is_game_over()) {
      update_input();
      update_game();
      update_visuals();
    } else {

      // lose screen here
      show_lose_screen();
    }

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  return 0;
}

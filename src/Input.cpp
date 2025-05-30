#include "../include/Input.h"
#include <GLFW/glfw3.h>

static bool enter_key_pressed = false;
static bool backspace_key_pressed = false;
static char letter_key_char = 0;

// Gets input
static void key_callback(GLFWwindow *window, int key, int scancode, int action,
                         int mods) {
  if (key == GLFW_KEY_ENTER) {
    if (action == GLFW_PRESS)
      enter_key_pressed = true;
    else if (action == GLFW_RELEASE)
      enter_key_pressed = false;
  }

  if (key == GLFW_KEY_BACKSPACE) {
    if (action == GLFW_PRESS)
      backspace_key_pressed = true;
    else if (action == GLFW_RELEASE)
      backspace_key_pressed = false;
  }
  // Handle alphabet keys: A-Z
  if (key >= GLFW_KEY_A && key <= GLFW_KEY_Z) {
    if (action == GLFW_PRESS) {
      letter_key_char = key - GLFW_KEY_A + 'A';
    } else if (action == GLFW_RELEASE) {
      // return 0 terminator
      letter_key_char = 0;
    }
  }
}

int init_input(GLFWwindow *window) {
  glfwSetKeyCallback(window, key_callback);
  return 0;
}

bool get_enter_pressed() {
  //
  return enter_key_pressed;
}

bool get_backspace_pressed() {
  //
  return backspace_key_pressed;
}

char get_letter_key_pressed() {
  // return letter
  return letter_key_char;
}

void release_keys() {
  enter_key_pressed = false;
  backspace_key_pressed = false;
  letter_key_char = 0;
}

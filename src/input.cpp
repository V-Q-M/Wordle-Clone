#include "../include/input.h"

static bool enter_key_pressed = false;
static bool backspace_key_pressed = false;
static bool letter_key_pressed = false;
int key_id = 0;

static void key_callback(GLFWwindow *window, int key, int scancode, int action,
                         int mods) {
  if (key == GLFW_KEY_ENTER) {
    if (action == GLFW_PRESS) {
      enter_key_pressed = true;
    } else if (action == GLFW_RELEASE) {
      enter_key_pressed = false;
    }
  }
  if (key == GLFW_KEY_A) {
    if (action == GLFW_PRESS) {
      letter_key_pressed = true;
      key_id = key;
    } else if (action == GLFW_RELEASE) {
      letter_key_pressed = false;
      key_id = 0;
    }
  }
}

void init_input(GLFWwindow *window) {
  //
  glfwSetKeyCallback(window, key_callback);
}

bool letter_pressed() { return letter_key_pressed; }

int get_key() { return key_id; }

bool enter_pressed() {
  //
  return enter_key_pressed;
}

bool backspace_pressed() { return backspace_key_pressed; }

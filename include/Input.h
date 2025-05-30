#pragma once
#include <GLFW/glfw3.h>

int init_input(GLFWwindow *window);

bool get_enter_pressed();

bool get_backspace_pressed();

char get_letter_key_pressed();

void release_keys();

// input.h
#ifndef INPUT_H
#define INPUT_H
#include <GLFW/glfw3.h>

void init_input(GLFWwindow *window);

void update_input();

bool letter_pressed();
int get_key();
bool enter_pressed();
bool backspace_pressed();

#endif

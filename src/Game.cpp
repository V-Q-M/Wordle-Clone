#include "../include/Game.h"
#include "../include/Input.h"
#include "../include/WordPicker.h"
#include <iostream>

int MAX_ATTEMPT_COUNT = 6;
int MAX_WORD_LENGTH = 5;
int MAX_AMOUNT_CHARS = MAX_WORD_LENGTH * MAX_ATTEMPT_COUNT + MAX_ATTEMPT_COUNT;

int attempt_count = 0;
int word_pos = 0;

std::string solution;
std::string attempt(MAX_WORD_LENGTH, ' ');

std::string board_letters(MAX_AMOUNT_CHARS, ' ');
int board_letters_index = 0; //:
//
//

std::string get_board_letters() {
  //
  return board_letters;
}

int init_game() {
  // pick random word
  // reset all values to default
  attempt_count = 0;
  word_pos = 0;
  attempt = "";
  solution = random_word();
  /*
    board_letters[0] = 'p';
    board_letters[1] = 'i';
    board_letters[2] = 'n';
    board_letters[3] = 'g';
    board_letters[4] = 'o';
    word_pos += 5;
    board_letters_index += 5;
  */
  return 0;
}

int count = 0;
int index = 0;

void test_font_render() {
  if (count == 100 && index < 36) {
    board_letters[index] = 'a';
    count = 0;
    index++;
    if (index % 5 == 0) {
      board_letters[index] = '\n';
      index++;
    }
  }
  count++;
}

void update_input() {
  bool enter_pressed = get_enter_pressed();
  bool backspace_pressed = get_backspace_pressed();
  char key_char = get_letter_key_pressed();

  // Check if outofbounds
  if (board_letters_index != MAX_AMOUNT_CHARS) {

    // enter sets attempt and adds linebreak
    if (enter_pressed && word_pos == MAX_WORD_LENGTH) {
      // try attempt
      attempt.resize(MAX_WORD_LENGTH);
      for (int i = 0; i < MAX_WORD_LENGTH; i++) {
        int check_index = board_letters_index - MAX_WORD_LENGTH + i;
        attempt[i] = board_letters[check_index];
      }

      // process attempt
      if (attempt_is_valid(attempt)) {
        // Append newline safely
        if (board_letters_index < MAX_AMOUNT_CHARS) {
          board_letters[board_letters_index] = '\n';
          board_letters_index++;
        }

        attempt_count++;
        enter_pressed = false;
        // reset word_pos
        word_pos = 0;
        board_letters[board_letters_index] = '\\';
      } else {
        // std::cout << "Invalid guess.";
      }
    }

    if (backspace_pressed && word_pos > 0) {
      board_letters_index--;
      board_letters[board_letters_index] = ' ';
      word_pos--;
    }

    if (key_char != 0 && word_pos < MAX_WORD_LENGTH) {
      board_letters[board_letters_index] = key_char;
      board_letters_index++;
      word_pos++;
      // std::cout << key_char;
    }
  }
  release_keys();
}

int update_game() {

  // test_font_render();
  update_input();

  if (attempt == solution) {
    // has won
    std::cout << "YOU WON";
    return 1;
  } else if (attempt_count == MAX_ATTEMPT_COUNT) {
    // has lost
    std::cout << "YOU LOST. Word was: " << solution;
    return 2;
  } else {
    // continue
    return 0;
  }
}

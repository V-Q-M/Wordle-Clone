#include "../include/Game.h"
#include "../include/WordPicker.h"

int MAX_ATTEMPT_COUNT = 6;
int MAX_WORD_POS = 5;

int attempt_count = 0;
int word_pos = 0;

std::string solution;
std::string attempt(MAX_WORD_POS, ' ');

std::string board_letters(MAX_ATTEMPT_COUNT *MAX_WORD_POS + MAX_ATTEMPT_COUNT,
                          ' ');
int board_letters_index = 0; //:
//
//

std::string get_board_letters() {
  //
  return board_letters;
}

void init_game() {
  // pick random word
  // reset all values to default
  attempt_count = 0;
  word_pos = 0;
  attempt = "";
  solution = random_word();

  board_letters[0] = 'p';
  board_letters[1] = 'i';
  board_letters[2] = 'n';
  board_letters[3] = 'g';
  board_letters[4] = 'o';
  word_pos += 5;
  board_letters_index += 5;
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

bool enter_pressed = true;

void update_input() {
  // enter sets attempt and adds linebreak
  if (enter_pressed) {
    // try attempt
    attempt.resize(MAX_WORD_POS);
    for (int i = 0; i < MAX_WORD_POS; i++) {
      int check_index = board_letters_index - MAX_WORD_POS + i;
      attempt[i] = board_letters[check_index];
    }

    // Append newline safely
    if (board_letters_index <
        MAX_ATTEMPT_COUNT * MAX_WORD_POS + MAX_ATTEMPT_COUNT) {
      board_letters[board_letters_index] = '\n';
      board_letters_index++;
    }

    attempt_count++;
    enter_pressed = false;
    // reset word_pos
    word_pos = 0;
    board_letters[board_letters_index] = 'x';
  }
}

int update_game() {

  // test_font_render();
  update_input();

  if (attempt == solution) {
    // has won
    return 2;
  } else if (attempt_count == MAX_ATTEMPT_COUNT) {
    // has lost
    return 1;
  } else {
    // continue
    return 0;
  }
}

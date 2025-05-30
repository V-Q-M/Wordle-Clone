#include "../include/Game.h"
#include "../include/WordPicker.h"

int MAX_ATTEMPT_COUNT = 6;
int MAX_WORD_POS = 5;

int attempt_count = 0;
int word_pos = 0;

std::string solution;
std::string attempt;

std::string board_letters(MAX_ATTEMPT_COUNT *MAX_WORD_POS + MAX_ATTEMPT_COUNT,
                          ' ');

//
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
}

int count = 0;
int index = 0;
void test_font_render() {
  if (count == 100 && index < 30) {
    board_letters[index] = 'a';
    count = 0;
    index++;
    if (index % 6 == 0) {
      board_letters[index] = '\n';
      index++;
    }
  }
  count++;
}

int update_game() {

  test_font_render();

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

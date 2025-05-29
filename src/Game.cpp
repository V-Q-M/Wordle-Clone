#include "../include/Game.h"
#include "../include/WordPicker.h"

int MAX_ATTEMPT_COUNT = 6;
int MAX_WORD_POS = 6;

int attempt_count = 0;
int word_pos = 0;

std::string solution;
std::string attempt;

// TODO need the entered letters buffer
std::string board_letters = "Hajo Schnuggi";

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

void update_game() {

  if (attempt == solution) {
    // has won
  } else if (attempt_count == MAX_ATTEMPT_COUNT) {
    // has lost
  } else {
    // continue
  }
}

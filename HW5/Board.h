//
// Created by Anıl Sümer Topaloğlu on 13.05.2024.
//

#ifndef HW5_BOARD_H
#define HW5_BOARD_H
#ifndef BOARD_H
#define BOARD_H

class Board {
private:
    char** matrix;
    int size;
    int win_length;
    bool checkLine(int startRow, int startCol, int stepRow, int stepCol);
public:
    Board(int size, int win_length);
    ~Board();
    void print_board();
    bool put_piece(char piece, int column);
    void turn_board_clockwise();
    char get_game_status();
};

#endif // BOARD_H

#endif //HW5_BOARD_H

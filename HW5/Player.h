//
// Created by Anıl Sümer Topaloğlu on 13.05.2024.
//

#ifndef HW5_PLAYER_H
#define HW5_PLAYER_H
#ifndef PLAYER_H
#define PLAYER_H

#include "Board.h"

class Player {
private:
    Board& board;
    char piece;

public:
    Player(Board& board, char piece);
    bool put(int column);
    void turn_board();
    bool is_winner();
    char get_symbol() const;
};

#endif // PLAYER_H

#endif //HW5_PLAYER_H

//
// Created by Anıl Sümer Topaloğlu on 13.05.2024.
//
#include "Player.h"

Player::Player(Board& board, char piece) : board(board), piece(piece) {}

bool Player::put(int column) {
    return board.put_piece(piece, column);
}

void Player::turn_board() {
    board.turn_board_clockwise();
}

bool Player::is_winner() {
    char status = board.get_game_status();
    return status == piece;
}

char Player::get_symbol() const {
    return piece;
}

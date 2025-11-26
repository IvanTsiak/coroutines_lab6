#pragma once

#include <vector>
#include <iostream>
#include "task.h"

const int N=5;
const int WIN_LEN=4;

enum Cell {
    EMPTY = 0,
    P1 = 1,
    P2 = 2,
    P3 = 3
};

using board = std::vector<std::vector<int>>;

void print_board(const board& b);
bool check_win(const board& b, int p);
bool is_full(const board& b);

Task player_actor(int id, board& b);

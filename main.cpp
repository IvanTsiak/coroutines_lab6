#include <iostream>
#include <vector>
#include "game_logic.h"

int main() {
    board b(N, std::vector<int>(N, EMPTY));

    Task p1 = player_actor(P1, b);
    Task p2 = player_actor(P2, b);
    Task p3 = player_actor(P3, b);

    Task* players[] = {&p1, &p2, &p3};
    int current_player_idx = 0;

    std::cout << "Tic-tac-toe 3 players\n";
    std::cout << "Board: " << N << "x" << N;
    print_board(b);

    bool game_over = false;

    while (!game_over) {
        int pid = current_player_idx + 1;

        players[current_player_idx]->resume();

        print_board(b);

        if (check_win(b, pid)) {
            std::cout << "Player " << pid << " WIN!!!!!!!!!!!!!\n";
            game_over = true;
        } else if (is_full(b)) {
            std::cout << "Draw";
            game_over = true;
        }

        current_player_idx = (current_player_idx + 1) % 3;
    }

    return 0;
}
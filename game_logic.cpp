#include "game_logic.h"
#include <random>
#include <iomanip>

static std::mt19937 rng(std::random_device{}());

void print_board(const board& b) {
    std::cout << "\n  ";
    for (int i=0; i<N; ++i) {
        std::cout << i << " ";
    }
    std::cout << "\n";
    for (int i=0; i<N; ++i) {
        std::cout << i << " ";
        for (int j=0; j<N; ++j) {
            char symbol = '.';
            if (b[i][j] == P1) {
                symbol = 'X';
            } else if (b[i][j] == P2) {
                symbol = 'O';
            } else if (b[i][j] == P3) {
                symbol = '#';
            }
            std::cout << symbol << " ";
        }
        std::cout << "\n";
    }
    std::cout << "-------------------\n";
}

bool check_win(const board& b, int p) {
    for (int i=0; i<N; ++i) {
        for (int j=0; j<N; ++j) {
            if (b[i][j] != p) {
                continue;
            }

            int dirs[4][2] = {{0, 1}, {1, 0}, {1, 1}, {1, -1}};

            for (auto d : dirs) {
                int count = 0;
                for (int k=0; k<WIN_LEN; ++k) {
                    int ni = i + d[0]*k;
                    int nj = j + d[1]*k;
                    if (ni >= 0 && ni < N && nj >= 0 && nj < N && b[ni][nj] == p) {
                        count++;
                    } else {
                        break;
                    }
                }
                if (count == WIN_LEN) {
                    return true;  
                }
            }
        }
    }
    return false;
}

bool is_full(const board& b) {
    for (const auto& row : b) {
        for (int cell : row) {
            if (cell == EMPTY) {
                return false;
            }
        }
    }
    return true;
}

Task player_actor(int id, board& b) {
    while (true)
    {
        std::vector<std::pair<int, int>> moves;
        for (int i=0; i<N; ++i) {
            for (int j=0; j<N; ++j) {
                if (b[i][j] == EMPTY) {
                    moves.push_back({i, j});
                }
            }
        }

        if (moves.empty()) {
            co_yield 0;
            break;
        }

        std::uniform_int_distribution<int> dist(0, static_cast<int>(moves.size()) - 1);
        auto move = moves[dist(rng)];
        b[move.first][move.second] = id;

        std::cout << "Player " << id << " makes a move in (" << move.first << ", " << move.second << ")\n";
    
        co_yield 0;
    }
}
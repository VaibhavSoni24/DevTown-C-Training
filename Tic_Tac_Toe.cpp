#include <iostream>
#include <cstdlib>
#include <ctime>

#define BOARD_SIZE 3
#define X 'X'
#define O 'O'

struct Score {
    int player;
    int computer;
    int draw;
};

int difficulty;
Score score = {.player = 0, .computer = 0, .draw = 0};

void input_difficulty();
void clear_screen();
void print_board(char board[BOARD_SIZE][BOARD_SIZE]);
int check_win(char board[BOARD_SIZE][BOARD_SIZE], char player);
int check_draw(char board[BOARD_SIZE][BOARD_SIZE]);
void play_game();
void player_move(char board[BOARD_SIZE][BOARD_SIZE]);
void computer_move(char board[BOARD_SIZE][BOARD_SIZE]);
int is_valid_move(char board[BOARD_SIZE][BOARD_SIZE], int row, int col);

int main() {
    srand(time(NULL));
    int choice;
    input_difficulty();
    do {
        play_game();
        std::cout << "\nPlay again? (1 for yes, 0 for no): ";
        std::cin >> choice;
    } while (choice == 1);
    std::cout << "\nBye Bye, thanks for playing." << std::endl;
}

void play_game() {
    char board[BOARD_SIZE][BOARD_SIZE] = {
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '},
    };
    char current_player = rand() % 2 == 0 ? X : O;

    print_board(board);
    while (true) {
        if (current_player == X) {
            player_move(board);
            print_board(board);
            if (check_win(board, X)) {
                score.player++;
                print_board(board);
                std::cout << "Congratulations! You have won!!!" << std::endl;
                break;
            }
            current_player = O;
        } else {
            computer_move(board);
            print_board(board);
            if (check_win(board, O)) {
                score.computer++;
                print_board(board);
                std::cout << "I won !!! But you played well..." << std::endl;
                break;
            }
            current_player = X;
        }

        if (check_draw(board)) {
            score.draw++;
            print_board(board);
            std::cout << "\nIt's a draw!" << std::endl;
            break;
        }
    }
}

int is_valid_move(char board[BOARD_SIZE][BOARD_SIZE], int row, int col) {
    return !(row < 0 || col < 0 || row > 2 || col > 2 || board[row][col] != ' ');
}

void player_move(char board[BOARD_SIZE][BOARD_SIZE]) {
    int count = 0, x, y;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == ' ') {
                count++;
                x = i;
                y = j;
            }
        }
    }

    if (count == 1) {
        board[x][y] = X;
        return;
    }

    int row, col;
    do {
        std::cout << "\nPlayer X's turn.";
        std::cout << "\nEnter row and column (1-3) for X: ";
        std::cin >> row >> col;
        row--; col--;
    } while (!is_valid_move(board, row, col));
    board[row][col] = X;
}

void computer_move(char board[BOARD_SIZE][BOARD_SIZE]) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = O;
                if (check_win(board, O)) {
                    return;
                }
                board[i][j] = ' ';
            }
        }
    }
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = X;
                if (check_win(board, X)) {
                    board[i][j] = O;
                    return;
                }
                board[i][j] = ' ';
            }
        }
    }
    if (difficulty == 2) {
        if (board[1][1] == ' ') {
            board[1][1] = O;
            return;
        }
        int corner[4][2] = {
            {0, 0},
            {0, 2},
            {2, 0},
            {2, 2}
        };
        for (int i = 0; i < 4; i++) {
            if (board[corner[i][0]][corner[i][1]] == ' ') {
                board[corner[i][0]][corner[i][1]] = O;
                return;
            }
        }
    }
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = O;
                return;
            }
        }
    }
}

int check_win(char board[BOARD_SIZE][BOARD_SIZE], char player) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player) {
            return 1;
        }
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player) {
            return 1;
        }
    }
    if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
        (board[2][0] == player && board[1][1] == player && board[0][2] == player)) {
        return 1;
    }
    return 0;
}

int check_draw(char board[BOARD_SIZE][BOARD_SIZE]) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == ' ') {
                return 0;
            }
        }
    }
    return 1;
}

void print_board(char board[BOARD_SIZE][BOARD_SIZE]) {
    clear_screen();
    std::cout << "Score - Player X: " << score.player << ", Computer: " << score.computer << ", Draws: " << score.draw << std::endl;
    std::cout << "Tic-Tac-Toe\n";
    for (int i = 0; i < BOARD_SIZE; i++) {
        std::cout << "\n";
        for (int j = 0; j < BOARD_SIZE; j++) {
            std::cout << " " << board[i][j] << " ";
            if (j < BOARD_SIZE - 1) {
                std::cout << "|";
            }
        }
        if (i < BOARD_SIZE - 1) {
            std::cout << "\n---+---+---";
        }
    }
    std::cout << "\n\n";
}

void input_difficulty() {
    while (true) {
        std::cout << "\nSelect difficulty level:";
        std::cout << "\n1. God (Impossible to win)";
        std::cout << "\n2. Human (Standard)";
        std::cout << "\nEnter your choice: ";
        std::cin >> difficulty;
        if (difficulty != 1 && difficulty != 2) {
            std::cout << "\nIncorrect choice enter (1/2)!!" << std::endl;
        } else {
            break;
        }
    }
}

void clear_screen() {
    system("cls");
}

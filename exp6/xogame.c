#include <stdio.h>

char board[3][3];

void print_board() {
    for (int i = 0; i < 3; i++) {
        printf(" %c | %c | %c\n", board[i][0], board[i][1], board[i][2]);
        if (i < 2) printf("-----------\n");
    }
}

int evaluate(char player) {
    for (int i = 0; i < 3; i++)
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player)
            return 1;

    for (int i = 0; i < 3; i++)
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player)
            return 1;

    if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
        (board[0][2] == player && board[1][1] == player && board[2][0] == player))
        return 1;

    return 0;
}

int is_board_full() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == ' ')
                return 0;

    return 1;
}

int minimax(char player) {
    if (evaluate('X')) return 1;
    if (evaluate('O')) return -1;
    if (is_board_full()) return 0;

    int best = (player == 'X') ? -1000 : 1000;

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == ' ') {
                board[i][j] = player;
                int score = minimax((player == 'X') ? 'O' : 'X');
                board[i][j] = ' ';
                if ((player == 'X' && score > best) || (player == 'O' && score < best))
                    best = score;
            }

    return best;
}

void make_ai_move() {
    int best = -1000, row, col;

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == ' ') {
                board[i][j] = 'X';
                int score = minimax('O');
                board[i][j] = ' ';
                if (score > best) {
                    best = score;
                    row = i;
                    col = j;
                }
            }

    board[row][col] = 'X';
}

int main() {
    printf("Welcome to Tic-Tac-Toe!\n");
    printf("You are playing as O, and the computer is playing as X.\n");
    printf("Enter your moves using row and column numbers (e.g., 1 1 for the top-left corner).\n");

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            board[i][j] = ' ';

    while (1) {
        print_board();
        int row, col;
        scanf("%d %d", &row, &col);
        row--; col--;
       
        if (board[row][col] != ' ') {
            printf("That cell is already occupied! Try again.\n");
            continue;
        }
       
        board[row][col] = 'O';
       
        if (evaluate('O')) {
            print_board();
            printf("Congratulations! You win!\n");
            break;
        }
       
        if (is_board_full()) {
            print_board();
            printf("It's a tie!\n");
            break;
        }
       
        make_ai_move();
       
        if (evaluate('X')) {
            print_board();
            printf("The computer wins!\n");
            break;
        }
       
        if (is_board_full()) {
            print_board();
            printf("It's a tie!\n");
            break;
        }
    }

    return 0;
}

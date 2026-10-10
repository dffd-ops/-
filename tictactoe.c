#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 5

char board[MAX][MAX];
int size;

void init_board() {
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            board[i][j] = ' ';
}

void print_board() {
    printf("\n    ");
    for (int i = 0; i < size; i++) printf("%d   ", i + 1);
    printf("\n");

    for (int i = 0; i < size; i++) {
        printf("%d ", i + 1);
        for (int j = 0; j < size; j++) {
            printf(" %c ", board[i][j]);
            if (j < size - 1) printf("|");
        }
        printf("\n");

        if (i < size - 1) {
            printf("  ");
            for (int j = 0; j < size; j++) {
                printf("---");
                if (j < size - 1) printf("+");
            }
            printf("\n");
        }
    }
    printf("\n");
}

int check_win(char s) {
    for (int i = 0; i < size; i++) {
        int row_ok = 1, col_ok = 1;
        for (int j = 0; j < size; j++) {
            if (board[i][j] != s) row_ok = 0;
            if (board[j][i] != s) col_ok = 0;
        }
        if (row_ok || col_ok) return 1;
    }

    int ok = 1;
    for (int i = 0; i < size; i++)
        if (board[i][i] != s) ok = 0;
    if (ok) return 1;

    ok = 1;
    for (int i = 0; i < size; i++)
        if (board[i][size - 1 - i] != s) ok = 0;
    if (ok) return 1;

    return 0;
}

int is_full() {
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            if (board[i][j] == ' ') return 0;
    return 1;
}

void bot_move() {
    int free_cells[MAX * MAX][2];
    int n = 0;

    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            if (board[i][j] == ' ') {
                free_cells[n][0] = i;
                free_cells[n][1] = j;
                n++;
            }

    if (n == 0) return;

    int pick = rand() % n;
    int row = free_cells[pick][0];
    int col = free_cells[pick][1];

    board[row][col] = 'O';
    printf("Бот поставил O в (%d, %d)\n", row + 1, col + 1);
}

int main() {
    srand(time(NULL));

    printf("=== КРЕСТИКИ-НОЛИКИ ===\n");

    printf("Введите размер поля (от 3 до %d): ", MAX);
    if (scanf("%d", &size) != 1) {
        printf("Ошибка ввода.\n");
        return 1;
    }

    if (size < 3 || size > MAX) {
        printf("Неверный размер. Использую 3.\n");
        size = 3;
    }

    init_board();

    int player_turn = rand() % 2;
    printf("\nВы играете за X, бот за O.\n");
    if (player_turn)
        printf("Первым ходите ВЫ.\n");
    else
        printf("Первым ходит БОТ.\n");

    int game_over = 0;

    while (!game_over) {
        print_board();

        if (player_turn) {
            int row, col;
            printf("Ваш ход (строка столбец): ");

            if (scanf("%d %d", &row, &col) != 2) {
                printf("Неверный ввод.\n");
                while (getchar() != '\n');
                continue;
            }

            row--;
            col--;

            if (row < 0 || row >= size || col < 0 || col >= size) {
                printf("Вне поля. Введите от 1 до %d.\n", size);
                continue;
            }
            if (board[row][col] != ' ') {
                printf("Клетка занята.\n");
                continue;
            }

            board[row][col] = 'X';

            if (check_win('X')) {
                print_board();
                printf("Вы победили!\n");
                game_over = 1;
            } else if (is_full()) {
                print_board();
                printf("Ничья.\n");
                game_over = 1;
            } else {
                player_turn = 0;
            }
        } else {
            bot_move();

            if (check_win('O')) {
                print_board();
                printf("Бот победил.\n");
                game_over = 1;
            } else if (is_full()) {
                print_board();
                printf("Ничья.\n");
                game_over = 1;
            } else {
                player_turn = 1;
            }
        }
    }

    return 0;
}

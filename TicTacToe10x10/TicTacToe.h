#ifndef TICTACTOE10X10_TICTACTOE_H
#define TICTACTOE10X10_TICTACTOE_H


int board[10][10];

//max and min of integers
int max(int a, int b);
int min(int a, int b);


char int_to_char(int a);
void print_board();
void initialize();

//return -1, 0 1
int check_win();

//static evaluation of a board
int rate_board();

//main algorithm
int minimax(int player, int depth, int alfa, int beta);
int computer_move(int depth);

//
int get_user_input();

//exit if sb won
void check_end_of_game();

//changing depth of minimax
void calculate_depth(int* depth, int miliseconds);


#endif //TICTACTOE10X10_TICTACTOE_H

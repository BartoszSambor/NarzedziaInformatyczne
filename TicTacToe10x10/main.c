#include <stdio.h>
#include <time.h>
#include "TicTacToe.h"


int main() {
    initialize();
    print_board();
    int depth = 1;
    while(1){
        int k;
        clock_t start = clock();
        int result = computer_move(3);
        clock_t  stop = clock();
        printf("TIME : %.3f s with depth %d", (stop - start)/1000.0, depth);
        calculate_depth(&depth, (stop - start));
        board[result/10][result%10] = 1;
        print_board();
        check_end_of_game();
        k = get_user_input();
        if(k == -1) {
            printf("Wyjscie...\n");
            return 0;
        }
        board[k/10][k%10] = -1;
        print_board();
        check_end_of_game();
    }
}

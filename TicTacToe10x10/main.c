#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 1 - computer
// -1 - user

int board[10][10];

int max(int a, int b){
    return a > b ? a : b;
}
int min(int a, int b){
    return a < b ? a : b;
}

char int_to_char(int a){
    if(a == 0) return '-';
    if(a == 1) return 'x';
    if(a == -1) return 'o';
}

void print_board(){
    printf("\n");
    printf("\\ 0 1 2 3 4 5 6 7 8 9\n");
    for(int i = 0; i < 10; ++i){
        printf("%d ", i);
        for(int j = 0; j < 10; ++j){
            printf("%c ", int_to_char(board[i][j]));
        }
        printf("\n");
    }
}

void initialize(){
    for(int i = 0; i < 10; ++i){
        for(int j = 0; j < 10; ++j){
            board[i][j] = 0;
        }
    }
}

int check_win(){
    for(int row = 0; row < 10; ++row){
        int start = 0;
        int end = 0;
        while(start < 6){
            while(board[row][start] != 0 && end < 10 && board[row][start] == board[row][end]){
                end++;
            }
            if((end - start) >= 5){
                return board[row][start];
            }
            start = end + 1;
            end = start;
        }
    }
    for(int column = 0; column < 10; ++column){
        int start = 0;
        int end = 0;
        while(start < 6){
            while(board[start][column] != 0 && end < 10 && board[start][column] == board[end][column]){
                end++;
            }
            if((end - start) >= 5){
                return board[start][column];
            }
            start++;
            end = start;
        }
    }
    for(int diagonal = 0; diagonal < 6; ++diagonal){
        int start = 0;
        int end = 0;
        while ((start + diagonal) < 10){
            while((end+diagonal) < 10 && board[start+diagonal][start] != 0 &&
                board[start+diagonal][start] == board[end+diagonal][end]){
                end++;
            }
            if((end - start) >= 5){
                return board[start+diagonal][start];
            }
            start++;
            end = start;
        }
    }
    for(int diagonal = 0; diagonal < 6; ++diagonal){
        int start = 0;
        int end = 0;
        while ((start + diagonal) < 10){
            while((end+diagonal) < 10 && board[start][start+diagonal] != 0 &&
                board[start][start+diagonal] == board[end][end+diagonal]){
                end++;
            }
            if((end - start) >= 5){
                return board[start][start+diagonal];
            }
            start++;
            end = start;
        }
    }
    for(int diagonal = 0; diagonal < 6; ++diagonal){
        int start = 0;
        int end = 0;
        while ((start + diagonal) < 10){
            while((end+diagonal) < 10 && board[9-start][start+diagonal] != 0 &&
                  board[9-start][start+diagonal] == board[9-end][end+diagonal]){
                end++;
            }
            if((end - start) >= 5){
                return board[9-start][start+diagonal];
            }
            start++;
            end = start;
        }
    }
    for(int diagonal = 0; diagonal < 6; ++diagonal){
        int start = 0;
        int end = 0;
        while ((start + diagonal) < 10){
            while((end+diagonal) < 10 && board[9-start-diagonal][start] != 0 &&
                  board[9-start-diagonal][start] == board[9-end-diagonal][end]){
                end++;
            }
            if((end - start) >= 5){
                return board[9-start-diagonal][start];
            }
            start++;
            end = start;
        }
    }
    return 0;
}

int rate_board(){
    int rate = 0;
    for(int row = 0; row < 10; ++row){
        int rowrate = 0;
        for(int start = 0; start < 9; ++start){
            if(board[row][start] != 0 && board[row][start] == board[row][start + 1]){
                rowrate = rowrate ? rowrate*10 : 10*board[row][start];
            }
            else{
                rate += rowrate;
                rowrate = 0;
            }
        }
        rate += rowrate;
    }
    for(int column = 0; column < 10; ++column){
        int colrate = 0;
        for(int start = 0; start < 9; ++start){
            if(board[start][column] != 0 && board[start][column] == board[start+1][column]){
                colrate = colrate ? colrate * 10 : 10 * board[start][column];
            }
            else{
                rate += colrate;
                colrate = 0;
            }
        }
        rate += colrate;
    }
    for(int diagonal = 0; diagonal < 9; ++diagonal){
        int diarate = 0;
        for(int start = 0; start < (9-diagonal); ++start){
            if(board[diagonal+start][start] != 0 && board[diagonal+start+1][start+1] == board[diagonal+start][start]){
                diarate = diarate ? diarate * 10 : 10 * board[diagonal+start][start];
            }else{
                rate += diarate;
                diarate = 0;
            }
        }
        rate += diarate;
    }
    for(int diagonal = 1; diagonal < 9; ++diagonal){
        int diarate = 0;
        for(int start = 0; start < (9-diagonal); ++start){
            if(board[start][start+diagonal] != 0 && board[start+1][start+1+diagonal] == board[start][start+diagonal]){
                diarate = diarate ? diarate * 10 : 10 * board[start][start+diagonal];
            }else{
                rate += diarate;
                diarate = 0;
            }
        }
        rate += diarate;
    }
    for(int diagonal = 0; diagonal < 9; ++diagonal){
        int diarate = 0;
        for(int start = 0; start < (9-diagonal); ++start){
            if(board[9-start][start+diagonal] != 0 && board[9-start][start+diagonal] == board[8-start][start+1+diagonal]){
                diarate = diarate ? diarate * 10 : 10 * board[9-start][start+diagonal];
            }else{
                rate += diarate;
                diarate = 0;
            }
        }
        rate += diarate;
    }
    for(int diagonal = 1; diagonal < 9; ++diagonal){
        int diarate = 0;
        for(int start = 0; start < (9-diagonal); ++start){
            if(board[9-start-diagonal][start] != 0 && board[9-start-diagonal][start] == board[8-start-diagonal][start+1]){
                diarate = diarate ? diarate * 10 : 10 * board[9-start-diagonal][start];
            }else{
                rate += diarate;
                diarate = 0;
            }
        }
        rate += diarate;
    }
    return rate;
}

int minimax(int player, int depth, int alfa, int beta){
    int tmp1 = check_win();
    if(tmp1 != 0){
        return tmp1*9999999; // ktoś wygrał
    }
    if(depth == 0){
        return rate_board();
    }
    if(player == 1){
        for(int i = 0; i < 10; ++i){
            for(int j = 0; j < 10; ++j){
                if(board[i][j] == 0){
                    board[i][j] = 1;
                    alfa = max(alfa, minimax(-1, depth - 1, alfa, beta));
                    board[i][j] = 0;
                    if(alfa > beta){
                        //break;
                        //return alfa;
                        goto b;

                    }
                }
            }
        }
        b:
        return alfa;
    }
    else{
        for(int i = 0; i < 10; ++i){
            for(int j = 0; j < 10; ++j){
                if(board[i][j] == 0){
                    board[i][j] = -1;
                    beta = min(beta, minimax(1, depth - 1, alfa, beta));
                    board[i][j] = 0;
                    if(alfa > beta){
                        goto a;
                    }
                }
            }
        }
        a:
        return beta;

    }
}

int computer_move(int depth){
    depth--;
    int bestscore = -10000000;
    int bestindex = -1;
    for(int i = 0; i < 10; ++i){
        for(int j = 0; j < 10; ++j){
            if(board[i][j] == 0){
                board[i][j] = 1;
                int score = minimax(-1, depth, -10000000, 10000000);
                board[i][j] = 0;
                if(score > bestscore){
                    bestscore = score;
                    bestindex = i*10+j;
                }
            }
        }
    }
    printf("Computer chosen: %d\n", bestindex);
    return bestindex;
}

int get_user_input(){
    while(1){
        int k;
        printf("Podaj nr pola lub -1 aby wyjsc");
        scanf("%d", &k);
        if(k == -1){
            return k;
        }
        if(k > 0 && k < 100 && board[k/10][k%10] == 0){
            return k;
        }else{
            printf("Bledne pole\n");
        }
    }
}

void check_end_of_game(){
    int result = check_win();
    if(result){
        printf("Wygral: %c\nGratulacje dla obu graczy!\n", int_to_char(1));
        exit(0);
    }
}

void calculate_depth(int* depth, int miliseconds){
    if(miliseconds < 100){
        *depth++;
    }
    if(miliseconds > 8000){
        *depth--;
    }
}

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

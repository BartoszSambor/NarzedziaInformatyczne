import time


def print_board(b):
    print("  |  0 1 2 3 4 5 6 7")
    print("  |-----------------")
    for i in range(8):
        print(i, "|  ", end="")
        for j in range(8):
               print(str(b[i][j])+" ",end="")
        print("")


def initialize(b):
    b[0][0] = 1
    b[0][2] = 1
    b[0][4] = 1
    b[0][6] = 1
    b[1][1] = 1
    b[1][3] = 1
    b[1][5] = 1
    b[1][7] = 1

    b[6][0] = 2
    b[6][2] = 2
    b[6][4] = 2
    b[6][6] = 2
    b[7][1] = 2
    b[7][3] = 2
    b[7][5] = 2
    b[7][7] = 2


def check_win(board):
    if len(firstset) == 0:
        return 1
    elif len(secondset) == 0:
        return 2
    else:
        return 0


def static_evaluation(board):
    return len(secondset) - len(firstset)


def get_user_input(board, round):
    while True:
        x = int(input("Podaj y pionka: "))
        y = int(input("Podaj x pionka: "))
        if not (0 <= x < 8 and 0 <= y < 8 and board[x][y] == round):
            print("Niewłaściwe pole")
            continue

        nx = int(input("Podaj y celu: "))
        ny = int(input("Podaj x celu: "))
        if not (0 <= nx < 8 and 0 <= ny < 8 and board[nx][ny] == 0):
            print("Niewłaściwe pole")
            continue

        if abs(x - nx) == 2 and 2 == abs(y - ny):
            if board[(x + nx) // 2][(y + ny) // 2] == (1 if round == 2 else 2):
                return x, y, nx, ny, 2
        elif abs(x - nx) == 1 and 1 == abs(y - ny):
            if (round == 1 and x < nx) or (round == 2 and x > nx):
                return x, y, nx, ny, 1
        print("Niewłaściwe pole2")


def make_move(board, round, ox, oy, nx, ny, dist):
    if round == 1:
        roundset = firstset
        nextroundset = secondset
    elif round == 2:
        roundset = secondset
        nextroundset = firstset
    else:
        print("ERROR in make_move")
        return

    if dist == 1:
        board[ox][oy] = 0
        board[nx][ny] = round
        roundset.remove((ox, oy))
        roundset.add((nx, ny))
    elif dist == 2:
        board[ox][oy] = 0
        board[nx][ny] = round
        board[(ox + nx) // 2][(oy + ny) // 2] = 0
        roundset.remove((ox, oy))
        roundset.add((nx, ny))
        nextroundset.remove(((ox + nx) // 2, (oy + ny) // 2))
    return 1 if dist == 2 else 0


def undo_move(board, round, ox, oy, nx, ny, dist):
    if round == 1:
        roundset = firstset
        nextroundset = secondset
    elif round == 2:
        roundset = secondset
        nextroundset = firstset
    else:
        print("ERROR in undo_move")
        return
    if dist == 1:
        board[ox][oy] = round
        board[nx][ny] = 0
        roundset.add((ox, oy))
        roundset.remove((nx, ny))
    elif dist == 2:
        board[ox][oy] = round
        board[nx][ny] = 0
        board[(ox + nx) // 2][(oy + ny) // 2] = next_round(round)
        roundset.add((ox, oy))
        roundset.remove((nx, ny))
        nextroundset.add(((ox + nx) // 2, (oy + ny) // 2))


def next_round(round):
    return 1 if round == 2 else 2


def computer_move(board, round):
    moves = for_each_move(board, round)
    best_index = -1
    best_value = -10000
    for i in range(len(moves)):
        make_move(board, round, *moves[i])
        res = minimax(board, next_round(round), 9, -1000, 1000)
        undo_move(board, round, *moves[i])
        if res > best_value:
            best_index = i
            best_value = res
    if best_index == -1:
        print("Error in computer_move()")
        return
    else:
        print("Computer_move(): ", moves[best_index])
        return moves[best_index]


def minimax(board, round, depth, alfa, beta):
    if check_win(board) or depth == 0:
        return static_evaluation(board)
    if round == 1:
        for state in for_each_move(board, round):
            make_move(board, round, *state)
            alfa = max(alfa, minimax(board, next_round(round), depth - 1, alfa, beta))
            undo_move(board, round, *state)
            if alfa >= beta:
                break
        return alfa
    else:
        for state in for_each_move(board, round):
            make_move(board, round, *state)
            beta = min(beta, minimax(board, next_round(round), depth - 1, alfa, beta))
            undo_move(board, round, *state)
            if alfa >= beta:
                break
        return beta


def for_each_move(board, round):
    moves = []
    if round == 2:
        for cords in secondset:
            i = cords[0]
            j = cords[1]
            if board[i][j] == round:
                if i > 0 and j > 0 and board[i-1][j-1] == 0:
                    moves.append((i, j, i - 1, j - 1, 1))
                if i > 0 and j < 7 and board[i-1][j+1] == 0:
                    moves.append((i, j, i - 1, j + 1, 1))
                if i > 1 and j > 1 and board[i-1][j-1] == 1 and board[i-2][j-2] == 0:
                    moves.append((i, j, i - 2, j - 2, 2))
                if i < 6 and j < 6 and board[i+1][j+1] == 1 and board[i+2][j+2] == 0:
                    moves.append((i, j, i + 2, j + 2, 2))
                if i > 1 and j < 6 and board[i-1][j+1] == 1 and board[i-2][j+2] == 0:
                    moves.append((i, j, i - 2, j + 2, 2))
                if i < 6 and j > 1 and board[i+1][j-1] == 1 and board[i+2][j-2] == 0:
                    moves.append((i, j, i + 2, j - 2, 2))
    else:
        for cords in firstset:
            i = cords[0]
            j = cords[1]
            if board[i][j] == round:
                if i < 7 and j > 0 and board[i + 1][j - 1] == 0:
                    moves.append((i, j, i + 1, j - 1, 1))
                if i < 7 and j < 7 and board[i + 1][j + 1] == 0:
                    moves.append((i, j, i + 1, j + 1, 1))
                if i > 1 and j > 1 and board[i - 1][j - 1] == 2 and board[i - 2][j - 2] == 0:
                    moves.append((i, j, i - 2, j - 2, 2))
                if i < 6 and j < 6 and board[i + 1][j + 1] == 2 and board[i + 2][j + 2] == 0:
                    moves.append((i, j, i + 2, j + 2, 2))
                if i > 1 and j < 6 and board[i - 1][j + 1] == 2 and board[i - 2][j + 2] == 0:
                    moves.append((i, j, i - 2, j + 2, 2))
                if i < 6 and j > 1 and board[i + 1][j - 1] == 2 and board[i + 2][j - 2] == 0:
                    moves.append((i, j, i + 2, j - 2, 2))
    return moves


def get_set_from_board(board, player):
    pawnset = set()
    for i in range(8):
        for j in range(8):
            if board[i][j] == player:
                pawnset.add((i, j))
    return pawnset


if __name__ == '__main__':
    board = [[0 for _ in range(8)] for _ in range(8)]
    initialize(board)
    round = 1
    firstset = get_set_from_board(board, 1)
    secondset = get_set_from_board(board, 2)

    while not check_win(board):
        print_board(board)
        print("Runda gracza: ", round)
        make_move(board, round,  *get_user_input(board, round))
        round = next_round(round)
        if check_win(board):
            break
        print_board(board)
        print("Runda gracza: ", round)
        start = time.time()
        make_move(board, round, *computer_move(board, round))
        print("TIME WITH DEPTH 9: ", time.time() - start)
        round = next_round(round)
    print_board(board)
    print("Wygrywa gracz: ", next_round(round))

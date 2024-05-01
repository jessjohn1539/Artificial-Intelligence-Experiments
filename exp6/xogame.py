import random

def print_board(board):
    for row in board:
        print(" | ".join(row))
        print("-" * 5)

def check_winner(board, player):
    for i in range(3):
        if all(board[i][j] == player for j in range(3)) or all(board[j][i] == player for j in range(3)):
            return True
    if all(board[i][i] == player for i in range(3)) or all(board[i][2-i] == player for i in range(3)):
        return True
    return False

def is_board_full(board):
    return all(board[i][j] != '-' for i in range(3) for j in range(3))

def get_empty_cells(board):
    return [(i, j) for i in range(3) for j in range(3) if board[i][j] == '-']

def user_move(board):
    while True:
        try:
            row = int(input("Enter row (1-3): ")) - 1
            col = int(input("Enter column (1-3): ")) - 1
            if board[row][col] == '-':
                return row, col
            else:
                print("That cell is already occupied. Try again.")
        except (ValueError, IndexError):
            print("Invalid input. Please enter a number between 1 and 3.")

def computer_move(board):
    empty_cells = get_empty_cells(board)
    best_move = None
    best_score = -float('inf')

    for row, col in empty_cells:
        board[row][col] = 'O'
        score = minimax(board, 0, False)
        board[row][col] = '-'
        if score > best_score:
            best_score = score
            best_move = (row, col)

    return best_move

def minimax(board, depth, isMaximizingPlayer):
    result = evaluate(board)
    if result is not None:
        return result

    if isMaximizingPlayer:
        bestVal = -float('inf')
        for i in range(3):
            for j in range(3):
                if board[i][j] == '-':
                    board[i][j] = 'O'
                    value = minimax(board, depth + 1, False)
                    board[i][j] = '-'
                    bestVal = max(bestVal, value)
        return bestVal
    else:
        bestVal = float('inf')
        for i in range(3):
            for j in range(3):
                if board[i][j] == '-':
                    board[i][j] = 'X'
                    value = minimax(board, depth + 1, True)
                    board[i][j] = '-'
                    bestVal = min(bestVal, value)
        return bestVal

def evaluate(board):
    if check_winner(board, 'X'):
        return -1
    elif check_winner(board, 'O'):
        return 1
    elif is_board_full(board):
        return 0
    else:
        return None

def play_game():
    board = [['-' for _ in range(3)] for _ in range(3)]
    print("Welcome to Tic-Tac-Toe!")
    print_board(board)

    while True:
        # User's turn
        print("\nYour turn (X)")
        row, col = user_move(board)
        board[row][col] = 'X'
        print_board(board)
        if check_winner(board, 'X'):
            print("Congratulations! You win!")
            break
        if is_board_full(board):
            print("It's a draw!")
            break

        # Computer's turn
        print("\nComputer's turn (O)")
        row, col = computer_move(board)
        board[row][col] = 'O'
        print_board(board)
        if check_winner(board, 'O'):
            print("Sorry, you lose!")
            break
        if is_board_full(board):
            print("It's a draw!")
            break

    print("Thanks for playing!")

play_game()

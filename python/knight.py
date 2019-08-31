from collections import deque

def new_board(r, c):
    return [[0 for _ in range(c)] for _ in range (r)]

def all_moves(k):
    x, y = k
    moves = [(x, y), (-1 * x, y), (x, -1 * y), (-1 * x, -1 * y)]
    return moves + [(y, x) for x, y in moves]

def move_valid(r, c):
    def valid(m):
        x, y = m
        return (x >= 0 and x < c and y >= 0 and y < r)
    return valid

def make_move(s, m):
    return (s[0] + m[0], s[1] + m[1])

def print_board(b):
    for row in b:
        print(row)

def search(r, c, k = (2, 1)):
    board = new_board(r, c)
    moves = all_moves(k)
    valid = move_valid(r, c)
    q = deque()
    sr, sc = 0, 0
    board[sr][sc] = 1
    q.append((sc, sr))
    while q:
        x, y = q.popleft()
        i = board[y][x]
        next_moves = [make_move((x, y), m) for m in moves] 
        next_moves = [m for m in next_moves if valid(m)]
        for nx, ny in next_moves:
            if board[ny][nx]:
                continue
            board[ny][nx] = i + 1
            q.append((nx, ny))
    return board

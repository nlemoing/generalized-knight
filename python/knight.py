from collections import deque

def new_board(n):
    return [[0 for _ in range(n)] for _ in range (n)]

def all_moves(k):
    x, y = k
    moves = [(x, y), (-1 * x, y), (x, -1 * y), (-1 * x, -1 * y)]
    return moves + [(y, x) for x, y in moves]

def move_valid(n):
    def valid(m):
        x, y = m
        return (x >= 0 and x < n and y >= 0 and y < n)
    return valid

def make_move(s, m):
    return (s[0] + m[0], s[1] + m[1])

def print_board(b):
    for row in b:
        print(row)

def search(n, k = (2, 1)):
    board = new_board(n)
    moves = all_moves(k)
    valid = move_valid(n)
    q = deque()
    c = (n-1)//2
    board[c][c] = 1
    q.append((c, c))
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

b = search(11)
print_board(b)

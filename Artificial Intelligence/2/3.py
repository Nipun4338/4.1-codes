def horizontal(pos):
    for i in range(len(pos)):
        countHorizontal(i, pos)

def diagonalUp(pos):
    for i in range(len(pos)):
        countDiagonalUp(i, pos)

def diagonalDown(pos):
    for i in range(len(pos)):
        countDiagonalDown(i, pos)

def countHorizontal(point, pos):
    global count
    for i in range(point + 1, len(pos)):
        if pos[i] == pos[point]:
            count += 1

def countDiagonalUp(point, pos):
    global count
    for i in range(point + 1, len(pos)):
        if pos[i] == pos[point] + i - point:
            count += 1

def countDiagonalDown(point, pos):
    global count
    for i in range(point + 1, len(pos)):
        if pos[i] == pos[point] - i + point:
            count += 1

count=0
pos=[6, 1, 5, 7, 4, 3, 8, 1]

horizontal(pos)
diagonalUp(pos)
diagonalDown(pos)
print(count)

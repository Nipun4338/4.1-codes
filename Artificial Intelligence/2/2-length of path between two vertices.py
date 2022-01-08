def graph(begin, end, cost=0):
    if (begin, end) in pair:
        print(str(cost + value[(begin, end)]) + ' ')

    for (i, j) in pair:
        if i == begin:
            graph(j, end, cost + value[(i, j)])


value = {('i', 'a') : 35, ('i', 'b') : 45, ('a', 'c') : 22, ('a', 'd') : 32,
            ('b', 'd') : 28, ('b', 'e') : 36, ('b', 'f') : 27, ('c', 'd') : 31,
            ('c', 'g') : 47, ('d', 'g') : 30, ('e', 'g') : 26}

pair = [('i', 'a'), ('i', 'b'), ('a', 'c'), ('a', 'd'), ('b', 'd'),
            ('b', 'e'), ('b', 'f'), ('c', 'd'), ('c', 'g'), ('d', 'g'),
            ('e', 'g')]


begin = str(input('Enter Begining node: '))
end = str(input('Enter Ending node: '))
print('The length of the path is: ')
graph(begin, end)

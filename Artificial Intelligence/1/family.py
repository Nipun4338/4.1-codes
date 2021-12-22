tupleList1=[('parent', 'Hasib', 'Rakib'),
            ('parent', 'Rakib', 'Sohel'),
            ('parent', 'Rakib', 'Rebeka'),
            ('parent', 'Rashid', 'Hasib'),
            ('parent', 'Hasib', 'Rahim')]

X=str(input("Grandchildren:"))

print('Grandparent:', end=' ')
i,j=0,0

while(i<=3):
    if ((tupleList1[i][0] == 'parent') &( tupleList1[i][2] == X)):
        for j in range(4):
            if ((tupleList1[j][0] == 'parent') &
                (tupleList1[i][1] == tupleList1[j][2])):
                print(tupleList1[j][1], end=' ')
    i=i+1
    
print('\n')
X=str(input("Brother/Sister of:"))

print('Brother/Sister:', end=' ')
i,j=0,0

while(i<=3):
    if ((tupleList1[i][0] == 'parent') &( tupleList1[i][2] == X)):
        for j in range(4):
            if ((tupleList1[j][0] == 'parent') &
                (tupleList1[i][1] == tupleList1[j][1]) & (X!=tupleList1[j][2])):
                print(tupleList1[j][2], end=' ')
    i=i+1

print('\n')
X=str(input("Uncle/Aunt of:"))

print('Uncle/Aunt:', end=' ')
i,j=0,0

while(i<=3):
    if ((tupleList1[i][0] == 'parent') &( tupleList1[i][2] == X)):
        for j in range(4):
            if ((tupleList1[j][0] == 'parent') &
                (tupleList1[i][1] == tupleList1[j][2])):
                for k in range(4):
                    if((tupleList1[k][0] == 'parent') & (tupleList1[j][1]==tupleList1[k][1]) & (tupleList1[k][2]!=tupleList1[j][2])):
                        print(tupleList1[k][2], end=' ')
    i=i+1

def series(term, n, gap):
    if n==1:
        return term
    else:
        return term+(n-1)*gap+series(term, n-1, gap)

x=int(input("Enter 1st term: "))
y=int(input('Enter n: '))
z=int(input('Enter interval: '))
print('Sum of series ',series(x,y,z))

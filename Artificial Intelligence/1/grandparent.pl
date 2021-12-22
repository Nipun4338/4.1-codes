parent('Hasib','Rakib').
parent('Rakib','Sohel').
parent('Rakib','Rebeka').
parent('Rashid','Hasib').

grandparent(X,Z):-
    parent(X,Y),parent(Y,Z).


findGc:-
    write('Grandchildren:'),read(Gc),write('Grandparent: '),
    grandparent(Gp,Gc),write(Gp),tab(5),fail.
findGc.

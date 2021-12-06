%esteInMultime(e:element,L:list)
%(i,i) -determinist, (o,i) -nedeterminist
esteInMultime(E,[E|_]):- !.
esteInMultime(E,[_|L]):-esteInMultime(E,L).

%esteMultime(L:list)
%(i) -determinist
esteMultime([]).
esteMultime([H|T]):-
	esteMultime(T),
    not(esteInMultime(T, H)).

go1:-esteMultime([9,'a',[b,'5'],2,3]).
go2:-esteMultime([]).
go3:-esteMultime([9,'a',[b,9],2]).
go4:-not(esteMultime([1,2,1])).
testeA:-go1,go2,go3,go4.


%elimina(L:list,e:element,k:integer,Rez:list)
%(i,i,i,o) -determinist
elimina([], _, _, []).
elimina([H|T], E, K, Rez) :-
	H = E,
	K =\= 0, !,
	K1 is K-1,
	elimina(T, E, K1, Rez).
elimina([H|T], E, K, [H|Rez]) :-
	elimina(T, E, K, Rez).

go5:-elimina([],3,3,R), R=[].
go6:-elimina([1,2,1,1,3,4],1,3,R), R=[2,3,4].
go7:-elimina([[1,2],3,[1,2],4],[1,2],3,R), R=[3,4].
go8:-elimina([1,1,1,1],1,3,R), R=[1].
go9:-elimina([1,1,1,1],2,3,R), R=[1,1,1,1].
testeB:-go5,go6,go7,go8,go9.

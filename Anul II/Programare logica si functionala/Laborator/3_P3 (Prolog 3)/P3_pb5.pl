%submultimi(L:list, N:integer, Rez:list)
%(i,i,o) -nedeterminist.
%(i,i,i) -nedeterminist.
submultimi([H|_], 1, [H]).
submultimi([_|T], N, Rez):-
    	submultimi(T, N, Rez).
submultimi([H|T], N, [H|Rez]):-
    	N > 1,
    	N1 is N - 1,
    	submultimi(T, N1, Rez).

%getSubmultimi(L:list, N:integer, RezTotal:list)
%(i,i,o) -determinist.
%(i,i,i) -determinist.
getSubmultimi(L, N, Total):-
		findall(Rez, submultimi(L, N, Rez), Total).

test1:- Total=
[[4, 5],
[3, 4],
[3, 5],
[2, 3],
[2, 4],
[2, 5],
[1, 2],
[1, 3],
[1, 4],
[1, 5]], getSubmultimi([1,2,3,4,5],2,Total).
test2:- getSubmultimi([1,2],1,[[1],[2]]).
test3:- getSubmultimi([],2,[]).
test4:- getSubmultimi([2,3,4],2,[[3,4],[2,3],[2,4]]).
teste:- test1, test2, test3, test4.
gets(L,N,T):- getSubmultimi(L,N,T).

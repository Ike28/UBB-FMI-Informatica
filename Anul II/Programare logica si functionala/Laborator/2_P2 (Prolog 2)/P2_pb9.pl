% A)
%lungimeSecventaSublista(L: list, LastValue: integer, Rez: integer)
%(i,i,o) -determinist.
%(i,i,i) -determinist.
lungimeSecventaSublista([], _, 1):- !.
lungimeSecventaSublista([H|T], LastValue, 1):-
		H =\= LastValue + 1, !.
lungimeSecventaSublista([H|T], LastValue, Rez):-
		H =:= LastValue + 1, !,
		lungimeSecventaSublista(T, H, InterRez),
		Rez is InterRez + 1.

testLungime1:- R = 5, lungimeSecventaSublista([2,3,4,5,8], 1, R).
testLungime2:- R = 1, lungimeSecventaSublista([], 1, R).
testLungime3:- R = 1, lungimeSecventaSublista([0, -1, -2, 3, 4], 1, R).
testLungime4:- R = 1, lungimeSecventaSublista([1,1,2,3,4], 1, R).

testeLungime:- testLungime1, testLungime2, testLungime3, testLungime4.
lss(L,LV,R):- lungimeSecventaSublista(L,LV,R).

%stergeSecventaDeLaInceputulListei(L: list, SequenceLength: integer, Rez: list)
%(i,i,o) -determinist.
%(i,i,i) -determinist.
%(o,i,i) -determinist.
%(o,o,o) -determinist.
%(i,o,o) -determinist.
%(o,o,i) -determinist.
%(o,i,o) -determinist.
stergeSecventaDeLaInceputulListei([], _, []):- !.
stergeSecventaDeLaInceputulListei(L, 0, L):- !.
stergeSecventaDeLaInceputulListei([H|T], SLength, Rez):-
		SLengthRed is SLength -1,
		SLength > 0,
		stergeSecventaDeLaInceputulListei(T, SLengthRed, Rez), !.

testStergere1:- R = [5], stergeSecventaDeLaInceputulListei([1,2,3,4,5],4,R).
testStergere2:- R = [], stergeSecventaDeLaInceputulListei([],4,R).
testStergere3:- R = [1,2], stergeSecventaDeLaInceputulListei([1,2],0,R).
testStergere4:- R = [], stergeSecventaDeLaInceputulListei([1],4,R).
testStergere5:- R = [], stergeSecventaDeLaInceputulListei([5],1,R).

testeStergere:- testStergere1, testStergere2, testStergere3, testStergere4, testStergere5.
ssdl(L,SL,R):- stergeSecventaDeLaInceputulListei(L,SL,R).

%stergeSecventeConsecutive(L:list, Rez:list)
%(i,o) -determinist.
%(o,i) -determinist.
%(i,i) -determinist.
%(o,o) -determinist.
stergeSecventeConsecutive([], []):- !.
stergeSecventeConsecutive([H|T], Rez):-
		lss(T, H, Lungime),
		Lungime < 2,
		Rez = [H|InterRez],
		stergeSecventeConsecutive(T, InterRez), !.
stergeSecventeConsecutive(L, RezDel):-
		[H|T] = L,
		lss(T, H, Lungime),
		Lungime > 1,
		ssdl(L, Lungime, LCLear),
		stergeSecventeConsecutive(LCLear, RezDel), !.

testCerintaA1:- R = [4,10], stergeSecventeConsecutive([1,2,4,6,7,8,10], R).
testCerintaA2:- R = [], stergeSecventeConsecutive([1,2,3,4,5], R).
testCerintaA3:- R = [10], stergeSecventeConsecutive([1,2,4,5,7,8,10], R).
testCerintaA4:- R = [1,1,1,1], stergeSecventeConsecutive([1,1,1,1], R).
testCerintaA5:- R = [1,1,1,1,1], stergeSecventeConsecutive([1,1,1,2,3,1,1,1], R).
testeCerintaA:- testCerintaA1, testCerintaA2, testCerintaA3, testCerintaA4, testCerintaA5.
sterg(L,R):- stergeSecventeConsecutive(L,R).

% B)
%eliminareConsecutive(L:list, Rez:list)
%(i,o) -determinist.
%(o,o) -nedeterminist.
%(i,i) -determinist.
%(o,i) -nedeterminist.
eliminareConsecutive([], []).
eliminareConsecutive([H|T], Rez):-
		is_list(H), !,
		stergeSecventeConsecutive(H, Hnew),
		eliminareConsecutive(T, RezDel),
		Rez = [Hnew|RezDel].
eliminareConsecutive([H|T], Rez):-
		not(is_list(H)),
		eliminareConsecutive(T, RezDel),
		Rez = [H|RezDel].

testCerintaB1:- R = [1,[5],9,[4,7,9],11,[5,8,2],7],
		eliminareConsecutive([1,[2,3,5],9,[1,2,4,3,4,5,7,9],11,[5, 8, 2],7], R).
testCerintaB2:- R = [1,[2,5],9,[2,4],11,[5],7],
		eliminareConsecutive([1,[2,5],9,[2,4],11,[5],7], R).
testCerintaB3:- R = [1,[],9,[],11,[],7],
		eliminareConsecutive([1,[2,3],9,[2,3,4],11,[5,6],7], R).
testCerintaB4:- R = [[],[],[]],
		eliminareConsecutive([[1,2,3],[4,5,6],[7,8,9]], R).
testCerintaB5:- R = [1,2,3,4,5,6],
		eliminareConsecutive([1,2,3,4,5,6], R).
testCerintaB6:- R = [],
		eliminareConsecutive([], R).
testCerintaB7:- R = [[]],
		eliminareConsecutive([[5,6]], R).
testeCerintaB:- testCerintaB1, testCerintaB2, testCerintaB3, testCerintaB4, testCerintaB5,
		testCerintaB6, testCerintaB7.

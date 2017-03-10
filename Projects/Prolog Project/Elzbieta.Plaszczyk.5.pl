%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%% Elżbieta Plaszczyk %%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%% Numer indeksu: 273005 %%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%% Numer zadania: 5 %%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

:-[checker].

solve(LiczbaLiczb, KolejneWierszePlanszy,ZgadnieteLiczbyIRozmieszczenie) :-
	flatten1(KolejneWierszePlanszy,SplaszczonaPlaszna),
	stworzListeWsp(LiczbaLiczb,SplaszczonaPlaszna,ListaWspolrzednych),
	generuj3(LiczbaLiczb,2,Liczby,5),
	przemnoz1(Liczby,Liczby,LiczbaPrzemnozonychLiczb),
	sprawdz(LiczbaPrzemnozonychLiczb,ListaWspolrzednych,ListaWspolrzednych,Wspolrzedne),
	flatten1(Wspolrzedne,SplaszczoneWspolrzedne),
	polacz(SplaszczoneWspolrzedne,Liczby,ZgadnieteLiczbyIRozmieszczenie).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%%%%%%%%% Funkcja spłaszczająca daną listę. %%%%%%%%%%% 

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% Lista([[1,2],[3,4]],X). -> X= [1,2,3,4]
flatten1(Lista,Wynik) :-
	flatten1(Lista,[],Wynik).

flatten1([],Wynik,Wynik).

flatten1([PierwszyElement|Lista], Akumulator, Wynik) :-
    is_list(PierwszyElement) ->
	(
	   flatten1(PierwszyElement, NowyAkumulator, Wynik),
	   flatten1(Lista, Akumulator, NowyAkumulator)
	);
    	(
	   Wynik = [PierwszyElement|SzukanaLista],
	   flatten1(Lista, Akumulator, SzukanaLista)
	).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%%%%%% Funkcja stwarzająca listę wpółrzędnych %%%%%%%%%

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% Dla tablicy (NxN-1) tworzy listę ktora dla każdy element tablicy umieszcza w podliście zawierającej na początku jej współrzędne a później ten element. Wywołuje predykat stw(LiczbaWierszy, początkowe wpółrzędne(1,1), tablcica,N-1, N+1) Np.:
% tablica(3,[[2,3,4],[5,6,7]],X) -> X = [[1,1,2],[1,2,3],[1,3,4],[2,1,5],[2,2,6],[2,3,7]]

stworzListeWsp(LiczbaLiczb,Tablica,ListaLiczbIWspolrzednych) :-
	LiczbaWierszy is LiczbaLiczb-1,
	LiczbaKolumnPlus1 is LiczbaLiczb+1,	
	stw(LiczbaLiczb,1,1,Tablica,ListaLiczbIWspolrzednych,LiczbaWierszy,LiczbaKolumnPlus1),!.

% Podstawa indukcji. Gdy dodany zostanie ostatni element tablicy w wspolrzednych (N-1,N+1).

stw(_,LiczbaWierszy,LiczbaKolumnPlus1,_,[],LiczbaWierszy,LiczbaKolumnPlus1):-!.

% Dodaj X,Y,H do listy listy współrzędnych.
	% H- element tablicy
	% X- pierwsza wpsółrzędna(numer wiersza)
	% Y- druga współrzędna (numer kolumny)
	% N1 = N-1
	% N2 = N+1 
% Jeżeli Y<=N stwórz Y1 = Y+1 i wywołaj funkcję stw dla Y1 i pozostałej listy.

stw(LiczbaLiczb,X,Y,[H|Tablica],[[X,Y,H|[]]|ListaLiczbIWspolrzednych],LiczbaWierszy,LiczbaKolumnPlus1) :-
	(Y=<LiczbaLiczb) ->
	(
		Y1 is Y+1,
		stw(LiczbaLiczb,X,Y1,Tablica,ListaLiczbIWspolrzednych,LiczbaWierszy,LiczbaKolumnPlus1)
	).

% Jeżeli doszliśmy do końca szerokości kolumny zwiększamy X o 1 a Y ustawiamy na 1 i wywołujemy funkcję stw(N,X+1,1,KWPLW,N1,N2).

stw(LiczbaLiczb,X,Y,Tablica,ListaLiczbIWspolrzednych,LiczbaWierszy,LiczbaKolumnPlus1) :-
	(Y>LiczbaLiczb,X<LiczbaLiczb) ->
	(
		X1 is X+1,
		stw(LiczbaLiczb,X1,1,Tablica,ListaLiczbIWspolrzednych,LiczbaWierszy,LiczbaKolumnPlus1)
	).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%%%%%%%%%%%%% Generowanie wszystkich możliwych n-elementowych ciągów liczb które pomnożone przez siebie dają liczby dwucyfrowe. %%%%%%%%%%%%%%%	

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	
% Podstawa indukcji, Gdy zostaje jeden element do dodania, dodajemy go i zwracamy wygenerowaną listę.

generuj3(1,L,[L|[]],_).

% Dodaj Element L do tablicy, dodaj L jako ostani element tablicy, a następnie sprawdź czy ten element, przemnożony przez siebie daje liczbe dzisiętną. Jeżeli tak to wywołaj funkcję generuj3(N-1,L,W,L). 
% W przeciwnym przypadku:
%     Gdy L = 2 (ponieważ: 2*2,2*3, 2*4 są liczba jedności). Wówczas dodaj 2 do tablicy i wywołąj generuj3(N-1,5,W,2). 
%     Gdy L = 3 (ponieważ: 3*3,3*4 są liczba jedności). Wówczas dodaj 3 do tablicy i wywołąj generuj3(N-1,4,W,3).  

generuj3(N,L,[L|Wynik],_) :-
	(N>1) ->
		(
			N1 is N-1,
			Wynik1 is L*L,
			(
				czyDziesietna(Wynik1) ->
					(
						generuj3(N1,L,Wynik,L)
					);
					(
						(L==2) ->	
							(
								generuj3(N1,5,Wynik,2)
							);
							(
								(L==3) ->
									generuj3(N1,4,Wynik,3)
							)
					)
			)
		).

% Licznik zwiększ o jeden, zapisz wynik do L1. Jeżeli L1*Ostatni Element Tablicy jest licz”ą dzisiętnę i lista nie jest pełna, wywołaj funkcję generuj(N,L1,W,OstatniElementTablicy).

generuj3(LiczbaLiczb,Licznik,WynikowaLista,OstElementListy) :-
	L1 is Licznik+1,
	Wynik is L1*OstElementListy,
	(LiczbaLiczb>0,czyDziesietna(Wynik)) ->
	(
		generuj3(LiczbaLiczb,L1,WynikowaLista,OstElementListy)
	).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%%% Sprawdzanie czy liczba N jest liczbą dziesiętną. %%%%%

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

czyDziesietna(N) :-
     N1 is N div 10,
     N1\==0,
     N2 is N1 div 10,
     N2==0.  

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%%%%%%% Przemażanie przez siebie elementów listy. %%%%%%%%%

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% Dostaje listę liczb. Przemnaża każdą liczbe przez kolejne (pierwszą przez drugą, trzecią itd. drugą przez trzecią, czwartą itd.) i wynik umieszcza nowej liście liczb.
% Przemnoz([1,2,3,4],R) --> R = [2,3,4,6,8,12] --> [2,3,4,6,8,1,2].

% Podstawa indukcji
przemnoz1(_,[],[]).

% Pomija pierwszy element listy, aby nie byl przemnozony przez siebie
przemnoz1(R,[_|T],PL) :-
	przemnoz2(R,T,PL,T).

% Jeżeli pierwszy element zostal przemnozony przez cala pozostalą listę to wez drugi element.
przemnoz2([_|R],[],PL,K) :-
	przemnoz1(R,K,PL).

% Przemnaża listy i rozdziela je na liczby jedności. [5*6] --> [32] --> [3],[2].
przemnoz2([H1|R],[H2|T],PL,K) :-
	H3 is H1*H2,
	H4 is H3 mod 10,
	H5 is H3 div 10,
	dodaj([H1|R],T,PL,K,H4,H5).
	
% Dodaje rozbity wynik mnożenia do listy wynikowej.
dodaj(R,T,[[H5,H4|[]]|PL],K,H4,H5) :-
	przemnoz2(R,T,PL,K).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%% Przeszukiwanie tablicy w poszukiwaniu elementów z listy. %%%%

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% Podstawa indukcij

sprawdz([],[],[],[]).

% Sprawdza pierwszy element przemnożonej listy z każdym elementem tablicy (czy taki istnieje).

sprawdz([H1|LP],[_|LW],SLW,Odp) :-
	sprawdz([H1|LP],LW,SLW,Odp).

% Sprawdza czy element H1 listy z przemnożonych cyfr jet równy trzeciemu elementowi listy H2. Jeżeli tak to pod X,Y podstawia współrzędne tego punktu, a pod zmienną Druga- drugi element listy licz przemnożonych (liczba jedności cyfry dziesiętnej).

sprawdz([H1|LP],[H2|_],SLW,Odp) :-
	sprCzyRowne(H1,H2,X,Y,Druga),
	X1 is X-1,
	X2 is X+1,
	Y1 is Y-1,
	Y2 is Y+1,
	czyIstnieje1([_,_,_|[]],SLW,X1,X,X2,Y1,Y,Y2,LP,[H2|_],Odp,Druga).

% Sprawdza wszystkie pola wokół punktu X,Y szukając drugiej cyfry liczby dwucyfrowej.
% Jeżeli istnieje usuwa dwie podlisty w których znajduje się ta liczba, a wspołrzędne jej cyfr (pierwsze 2 wartości), umieszcza w liście odpowiedzi. 


% Np. Liczby 53, oraz dla punktu [2,2,5], generuje listę [1,1,3], [1,2,3],[1,3,3],[2,1,3] itd. i każdą listę sprawdz- czy istnieje w liście współrzędnych.
czyIstnieje1([X1,Y1,Druga|[]],SLW,X1,_,_,Y1,_,_,LP,[H2|_],Odp,Druga) :-
	czyIstnieje([X1,Y1,Druga|[]],SLW) ->
	(
	delete(SLW,H2,PSLW),
	delete(PSLW,[X1,Y1,Druga|[]],PSLW1),
	genOdpowiedz(H2,X1,Y1,Odp,LP,PSLW1)
	).

czyIstnieje1([X1,Y,Druga|[]],SLW,X1,_,_,_,Y,_,LP,[H2|_],Odp,Druga) :-
	czyIstnieje([X1,Y,Druga|[]],SLW) ->
	(	
	delete(SLW,H2,PSLW),
	delete(PSLW,[X1,Y,Druga|[]],PSLW1),
	genOdpowiedz(H2,X1,Y,Odp,LP,PSLW1)
	).

czyIstnieje1([X1,Y2,Druga|[]],SLW,X1,_,_,_,_,Y2,LP,[H2|_],Odp,Druga) :-
	czyIstnieje([X1,Y2,Druga|[]],SLW) ->
	(
	delete(SLW,H2,PSLW),
	delete(PSLW,[X1,Y2,Druga|[]],PSLW1),
	genOdpowiedz(H2,X1,Y2,Odp,LP,PSLW1)
	).	

czyIstnieje1([X,Y1,Druga|[]],SLW,_,X,_,Y1,_,_,LP,[H2|_],Odp,Druga) :-
	czyIstnieje([X,Y1,Druga|[]],SLW) ->
	(
	delete(SLW,H2,PSLW),
	delete(PSLW,[X,Y1,Druga|[]],PSLW1),
	genOdpowiedz(H2,X,Y1,Odp,LP,PSLW1)
	).
	
czyIstnieje1([X,Y2,Druga|[]],SLW,_,X,_,_,_,Y2,LP,[H2|_],Odp,Druga) :-
	czyIstnieje([X,Y2,Druga|[]],SLW) ->	
	(
	delete(SLW,H2,PSLW),
	delete(PSLW,[X,Y2,Druga|[]],PSLW1),
	genOdpowiedz(H2,X,Y2,Odp,LP,PSLW1)
	).
	
czyIstnieje1([X2,Y1,Druga|[]],SLW,_,_,X2,Y1,_,_,LP,[H2|_],Odp,Druga) :-
	czyIstnieje([X2,Y1,Druga|[]],SLW) ->
	(
	delete(SLW,H2,PSLW),
	delete(PSLW,[X2,Y1,Druga|[]],PSLW1),
	genOdpowiedz(H2,X2,Y1,Odp,LP,PSLW1)
	).
	
czyIstnieje1([X2,Y,Druga|[]],SLW,_,_,X2,_,Y,_,LP,[H2|_],Odp,Druga) :-
	czyIstnieje([X2,Y,Druga|[]],SLW) ->
	(
	delete(SLW,H2,PSLW),
	delete(PSLW,[X2,Y,Druga|[]],PSLW1),
	genOdpowiedz(H2,X2,Y,Odp,LP,PSLW1)
	).
	
czyIstnieje1([X2,Y2,Druga|[]],SLW,_,_,X2,_,_,Y2,LP,[H2|_],Odp,Druga) :-
	czyIstnieje([X2,Y2,Druga|[]],SLW) ->
	(
	delete(SLW,H2,PSLW),
	delete(PSLW,[X2,Y2,Druga|[]],PSLW1),
	genOdpowiedz(H2,X2,Y2,Odp,LP,PSLW1)
	).

%%%%%% Sprawdza czy w podliście współrzędnych jest liczba H1 %%%%%%%
sprCzyRowne([H1,T1|[]], [X,Y,H1|[]],X,Y,T1).

% Sprawdza czy dwie listy są sobie równe.
czyIstniejeSprawdz([X,Y,Z|[]],[X,Y,Z|[]]).

%%%%%%% Sprawdzanie czy w tablicy współrzędnych jest lista H
czyIstnieje(H,[H1|_]) :-
	czyIstniejeSprawdz(H,H1).

czyIstnieje(H,[_|T1]) :-
	czyIstnieje(H,T1).

%Jeżeli dana cyfra dwucyfrowa istnieje to umieść jej współrzędne w liście odpowiedzi.
genOdpowiedz([H11,H22|_],H1,H2,[[H11,H22|[]],[H1,H2|[]]|Odp],LP,PSLW1):-
	sprawdz(LP,PSLW1,PSLW1,Odp).


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%% Tworzy odpowiedz poprzez polaczenie listy znalezionych liczb z listą współrzednych. %%%%

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

polacz(ListaWsp,[],([],Rozwiazanie)):-
	polacz2(ListaWsp,Rozwiazanie).

polacz(ListaLWsp,[H|R],([H|R], Rozwiazanie)) :-
	polacz(ListaLWsp,R,(R, Rozwiazanie)).

polacz2([],([])).

polacz2([H1,H2,H3,H4|ListaWsp],([((H1,H2),(H3,H4))|Rozwiazanie])) :-
	polacz2(ListaWsp,(Rozwiazanie)).


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% Testy %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

student_simple_test(5,[[4,6,9,8,4],[1,8,2,2,3],[8,7,1,6,4],[4,2,6,5,2]],([3, 6, 7, 8, 12], [((2,1),(3,1)), ((2,4),(3,3)), ((4,5), (3,5)), ((2,5), (3,4)), ((4,1), (4,2)), ((1,1), (2,2)), ((3, 2), (2,3)), ((4,4), (4,3)), ((1,4), (1,5)), ((1,3), (1,2))])).
student_simple_test(6,[[9,9,3,3,7,7],[4,1,5,6,4,6],[5,8,5,3,2,6],[2,0,3,1,4,5],[1,3,5,5,2,7]],([3, 5, 6, 7, 9, 11], [ ((4, 4), 3, 3), ((2, 2), 3, 2), ((4, 1), 5, 1), ((5, 5), 5, 6), ((4, 3), 3, 4), ((5, 2), 4, 2), ((1, 4), 2, 3), ((4, 5), 4, 6), ((5, 4), 5, 3), ((2, 5), 3, 5), ((3, 1), 2, 1),((3, 6), 2, 6), ((2, 4), 1, 3), ((1, 6), 1, 5), ((1, 2), 1, 1)])).
student_simple_test(7,[[0,9,3,0,1,7,2],[2,1,4,5,8,5,0],[5,0,7,2,4,4,6],[4,5,6,3,2,6,7],[0,9,3,0,1,3,0],[5,4,3,5,5,1,8]],([3, 5, 6, 7, 9, 9, 10], [ ((5, 5), 6, 5), ((6, 6), 6, 7), ((2, 1), 2, 2), ((3, 4), 3, 3), ((1, 7), 1, 6), ((4, 4), 5, 4), ((1, 3), 1, 4), ((6, 3), 6, 4), ((3, 5), 2, 6), ((2, 3), 2, 4), ((3, 1), 3, 2), ((3, 6), 4, 5), ((4, 2), 4, 1), ((6, 1), 6, 2), ((3, 7), 2, 7), ((4, 6), 5, 6), ((4, 3), 5, 3), ((4, 7), 5, 7), ((2, 5), 1, 5), ((1, 2), 1, 1), ((5, 2), 5, 1)])).



student_count_test(5,[[4,6,9,8,4],[1,8,2,2,3],[8,7,1,6,4],[4,2,6,5,2]],4).
student_count_test(6,[[9,9,3,3,7,7],[4,1,5,6,4,6],[5,8,5,3,2,6],[2,0,3,1,4,5],[1,3,5,5,2,7]],320).

% Student_simple_test dla tablicy 7x6 wykonuje się w 176s.
% Wszystko wykonuje się w ok. 250s.


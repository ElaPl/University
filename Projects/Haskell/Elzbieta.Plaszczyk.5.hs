---------------------------------------------------------------------------
--------------------------- Elżbieta Plaszczyk ----------------------------
--------------------------- numer indeksu: 273005 -------------------------
--------------------------- Mozaika iloczynów -----------------------------
---------------------------------------------------------------------------

---------------------------------------------------------------------------
------------------------------ Opis metody --------------------------------
--  Rozwiązanie korzysta z monad.
-- 1. Na początku funkcja "generate (n)" generuje listę możliwych rozwiązań
--    w kolejności rosnącej. Jest to lista list dlugości n,
--    liczb które maja elementy takie,
--    że po przemnożeniu przez siebie dają liste liczb dwucyfrowych. 
--    Są to ciągi zaczynające się od (np.: dla n=4):
--    (2,5,5,5),(2,5,5,6) ... (9,9,9,11). Nazwijmy ją listą X. 
-- 2. Funkcja generateCoordinates dla każdego elementu tablicy tworzy 3-krotke, 
--    zawierającą dwie współrzędne tego elementu w tablicy, oraz ten element.
-- 3. Funckja check bierze każdą listę z listy X, przemnaża ją, tworząc nową listę
--    i wykonuje na niej następujace operacje: 
--    Dla każdego elementu listy, szuka tego elementu w tablicy, następująco:
--    Szuka cyfry dziesiątek w tablicy, jeżeli znajdzie to usuwa ten element z tablicy,
--    oraz pobierane są dwie współrzędne tego elementu i na ich podstawie generowana jest
--    lista jego sąsiadów. Następnie funckja wśród sąsiadów szuka liczby jedności. Jeżeli
--    znajdzie zwracana jest krotka ((x1,y1),(x2,y2)), w przeciwnym razie wraca po porzedniego
--    stanu tablicy i nadal szuka.
--    Jeżeli jakiegoś elementu nie ma w tablicy, funkcja nie szuka dalej, tylko zwraca
--    listę pustą.
--    Jeżeli funkcja usunie wszystkie elementy z tablcy, to zwraca listę współrzędnych.
--    Następie jest ona zwiracana w postaci: (rozwiązanie,[(lista współrzędnych)])
-----------------------------------------------------------------------------


import Puzzle
import Checker

tests :: [Test]
tests = [
-- Time: 0.56s
	SimpleTest
		(Puzzle 5 [[4,6,9,8,4],[1,8,2,2,3],[8,7,1,6,4],[4,2,6,5,2]])
		([3, 6, 7, 8, 12], [((2,1),(3,1)), ((2,4),(3,3)), ((4,5), (3,5)), ((2,5), (3,4)), ((4,1), (4,2)), ((1,1), (2,2)), ((3, 2), (2,3)), ((4,4), (4,3)), ((1,4), (1,5)), ((1,3), (1,2))])  
-- Time: 5.37s	
	,SimpleTest
		(Puzzle 6 [[9,9,3,3,7,7],[4,1,5,6,4,6],[5,8,5,3,2,6],[2,0,3,1,4,5],[1,3,5,5,2,7]])
		([3, 5, 6, 7, 9, 11], [ ((4, 4), (3, 3)), ((2, 2), (3, 2)), ((4, 1), (5, 1)), ((5, 5), (5, 6)), ((4, 3), (3, 4)), ((5, 2), (4, 2)), ((1, 4), (2, 3)), ((4, 5), (4, 6)), ((5, 4), (5, 3)), ((2, 5), (3, 5)), ((3, 1), (2, 1)),((3, 6), (2, 6)), ((2, 4), (1, 3)), ((1, 6), (1, 5)), ((1, 2), (1, 1))]) 
-- Time: 30 min	
	,SimpleTest
		(Puzzle 7 [[0,9,3,0,1,7,2],[2,1,4,5,8,5,0],[5,0,7,2,4,4,6],[4,5,6,3,2,6,7],[0,9,3,0,1,3,0],[5,4,3,5,5,1,8]])
		([3, 5, 6, 7, 9, 9, 10], [ ((5, 5), (6, 5)), ((6, 6), (6, 7)), ((2, 1), (2, 2)), ((3, 4), (3, 3)), ((1, 7), (1, 6)), ((4, 4), (5, 4)), ((1, 3), (1, 4)), ((6, 3), (6, 4)), ((3, 5), (2, 6)), ((2, 3), (2, 4)), ((3, 1), (3, 2)), ((3, 6), (4, 5)), ((4, 2), (4, 1)), ((6, 1), (6, 2)), ((3, 7), (2, 7)), ((4, 6), (5, 6)), ((4, 3), (5, 3)), ((4, 7), (5, 7)), ((2, 5), (1, 5)), ((1, 2), (1, 1)), ((5, 2), (5, 1))])
-- Time: 3.37s
	,SimpleTest
		(Puzzle 6 [[0,3,5,0,4,9],[2,1,4,2,5,0],[6,3,5,0,1,5],[2,7,4,7,8,3],[0,6,3,0,5,1]])
		([3,5,6,7,9,10],[((5,6),(5,5)),((3,5),(4,5)),((2,1),(2,2)),((4,1),(4,2)),((5,3),(5,4)),((1,2),(1,1)),((4,6),(3,6)),((4,3),(3,3)),((2,5),(1,4)),((1,5),(2,4)),((1,3),(2,3)),((5,2),(5,1)),((3,1),(3,2)),((4,4),(3,4)),((1,6),(2,6))])
-- Time: 16.04s	
	,SimpleTest
		(Puzzle 6 [[0,3,5,0,4,9],[2,1,4,2,5,0],[6,3,5,0,1,5],[2,7,4,7,8,3],[0,6,3,0,5,1]])
		([3,5,6,7,9,10],[((3,5),(3,6)),((5,6),(4,5)),((2,1),(2,2)),((4,1),(4,2)),((5,3),(5,4)),((1,2),(1,1)),((4,6),(5,5)),((4,3),(3,3)),((2,5),(1,4)),((1,5),(2,4)),((1,3),(2,3)),((5,2),(5,1)),((3,1),(3,2)),((4,4),(3,4)),((1,6),(2,6))])
-- Time: 20 min
	,SimpleTest
		(Puzzle 7 [[0,3,5,0,4,9,2],[2,1,4,2,5,0,4],[6,3,5,0,1,5,2],[2,7,4,7,8,3,0],[0,6,3,0,5,1,3],[1,2,2,8,0,4,0,6]])
		([3,4,5,6,7,9,10],[((2,2),(2,1)),((3,5),(3,6)),((5,6),(4,5)),((6,2),(6,1)),((4,1),(4,2)),((5,3),(5,4)),((3,7),(4,7)),((1,7),(2,7)),((6,3),(6,4)),((1,2),(0,1)),((6,6),(6,5)),((5,7),(6,7)),((4,6),(5,5)),((1,5),(2,5)),((1,3),(1,4)),((2,3),(2,4)),((3,3),(4,3)),((5,2),(5,1)),((3,1),(3,2)),((4,4),(3,4)),((1,6),(2,6))])

-- Time: 16.00s	
	,CountTest
		(Puzzle 6 [[0,3,5,0,4,9],[2,1,4,2,5,0],[6,3,5,0,1,5],[2,7,4,7,8,3],[0,6,3,0,5,1]])
		16
-- Time: 2.30s	
	,CountTest
		(Puzzle 5 [[4,6,9,8,4],[1,8,2,2,3],[8,7,1,6,4],[4,2,6,5,2]])
		4
-- Time: 20.28s	
	,CountTest
		(Puzzle 6 [[9,9,3,3,7,7],[4,1,5,6,4,6],[5,8,5,3,2,6],[2,0,3,1,4,5],[1,3,5,5,2,7]])
		320
-- Time: 0.12s	
	,CountTest
        	(Puzzle 4 [[0, 8, 4, 0], [5, 3, 0, 4], [6, 3, 4, 2]])
         	0
-- Time: 30 min
	,CountTest
		(Puzzle 7 [[0,9,3,0,1,7,2],[2,1,4,5,8,5,0],[5,0,7,2,4,4,6],[4,5,6,3,2,6,7],[0,9,3,0,1,3,0],[5,4,3,5,5,1,8]])
		9216
	]

main :: IO ()
main = checkerMain solve tests

count [] = 0
count (x:xs) = 1 + count xs

------------------------------------------------------------------------------
-------- solve n xs wywołuje check, który bierze listę kandydatów ------------
------ na wyniki, oraz tablicę składającą się z liczb i ich współrzędnych ----
------------------------------------------------------------------------------

solve :: Solver
solve n xs = check (generate n) (generateCoordinates xs n)   

check :: (Eq t, Eq t1, Num t, Num t1) => [[Int]] -> [(t, t1, Int)] -> [([Int], [((t, t1), (t, t1))])]
check ns xs = do
	n <- ns                                        -- funkcja wywołuje się dla każdego możliwego rozwiązania 
	t1 <- check' (mult n) (mult n) xs xs []        -- jeżeli rozwiązanie istnieje to zwiracana jest tablica współrzędnych, w przeciwnym razie lista pusta
	guard (notEmpty [t1])
        return (n, t1)                                 -- jeżeli lista nie jest pusta, jako rozwiązanie zwracana jest krotka (rozwiązanie, lista wpółrzędnych)
	where 
	check' [] _ _ _ acc = [acc]                    -- jeżeli lista liczb jest pusta zwracany jest akumulator (lista pusta, lub lista współrzędnych)
	check' (n:ns) (n1:ns1) xs org acc= do
	(bool1,(a,b)) <- findN (podziel n) xs          -- jeżeli liczba dziesiątek znajduje się w tablicy, zwróc krotkę (0,(współrzędne)), w przeciwnym razie (1,(współrzędne)
	if (bool1 == 0)                                
	then do
	        t1 <- select (a,b,podziel n) org       -- jeżeli liczba została znaleziona, usuń ja z tablicy
		(bool2,(c,d,e)) <- findNeightbour (neightbour a b (modulo n)) t1   -- znajdź liczbę jedności wśród sąsiadów pierwszego elementu. Jeżeli znajdzie, zwraca krotke (0,(współrzędne, liczba). W przeciwnym razie zwraca krotkę (1,(współrzędne, liczba))
		if (bool2 == 0)                                                             
		then do
		t2 <- select (c,d,e) t1     -- Usuń znaleziony element z listy
		check' ns ns t2 t2 (acc++[((a,b),(c,d))]) else check' [] [] [] [] [] 
	else check' [] [] [] [] []             -- Jeżeli liczba znajduje sie w tablicy szukaj następenej. W przeciwnym razie zwróć liste pustą


-------------------- Modulo --------------------------

modulo :: Integral a => a -> a
modulo n = n`mod`10              -- Zwraca resztę z dzielenia danej liczby przez 10

-------------------- Podziel --------------------------

podziel :: Integral a => a -> a
podziel n = n`div`10             -- Zwraca wynik dzielenia pobranej liczby przez 10

-----------------------------------------------------------------------------------
------------------- Funkcja generująca sąsiadów dwóch współrzędnych ---------------
--------------- generuje 3-krotki (współrzędna, współrzędna, szukana liczba) ------
-----------------------------------------------------------------------------------

neightbour :: (Num t, Num t1) => t -> t1 -> t2 -> [(t, t1, t2)]
neightbour a b p= [(a',b',p) | (a',b',p) <- [((a-1),(b-1),p),((a-1),b,p),((a-1),(b+1),p),(a,(b-1),p),(a,(b+1),p),((a+1),(b-1),p),((a+1),b,p),((a+1),(b+1),p)]]         -- dla dwóch współrzędnych i szukanego elementu generuje jego sąsiadów, którzy znajdują się w odległości 1 od tego elementu. W postaci krotek (współrzędna, współrzędna, szukany element)

-----------------------------------------------------------------------------------
--- Funkcja, która w tablicy xs, szuka 3-krotek z tablicy sąsiadów ----------------
-----------------------------------------------------------------------------------

findNeightbour :: (Eq t1, Num t) => [t1] -> [t1] -> [(t, t1)]
findNeightbour nl xs = do  -- funkcja przeszukuje tablicę xs i tablicę sąsiadów i każdego sąsiada w tej tablicy. 
	n <- nl
	x <- xs
	guard (n == x)     -- jeżeli znajdzie zwraca (0, 3-krotkę)
	return (0,x)

----------------------------------------------------------------------------------------
---------------------- Szukanie liczby n`div`10 w tablicy i jej współrzędnych ----------
----------------------------------------------------------------------------------------

findN :: (Eq a, Num t, Num t1, Num t2) => a -> [(t1, t2, a)] -> [(t, (t1, t2))]

findN n []  = return (1,(0,0))
findN n xs =  do                     -- szuka elementu w tablicy (porównując go z 3 elementem każdek krotki).
	(a,b,c) <- xs
	guard (n == c) 
        return (0,(a,b))              -- jeżeli znajdzie, zwraca (0,(współrzędne))

----------------------------------------------------------------------------------------
------------------- Usuwanie elementu x z tablicy --------------------------------------
----------------------------------------------------------------------------------------

select :: (Eq t, Monad m) => t -> [t] -> m [t]
select x tab = return [t | t <- tab, t /= x] -- usuwa element x z tablicy, zwraca nową tablicę bez tego elementu

---------------------------------------------------------------------------------------
--------------------------- Sprawdza listę czy jest pusta -----------------------------
---------------------------------------------------------------------------------------

notEmpty :: [t] -> Bool
notEmpty [] = False
notEmpty xs = True

---------------------------------------------------------------------------------------
--------------------- Sprawdzanie poprawności wyników ---------------------------------
---------------------------------------------------------------------------------------

guard :: Bool -> Choice ()
guard True  = return ()
guard False = mzero

mzero :: Choice a
mzero = choose []

type Choice a = [a]

choose :: [a] -> Choice a
choose xs = xs



------------------------------------------------------------------------------------------
------------------------- Generuje listę możliwych rozwiązań -----------------------------
-------------- Liczb, które przemnożone przez siebie dają liczby dwucyfrowe --------------
------------------------------------------------------------------------------------------

generate :: Int -> [[Int]]
generate n = (generate' n 2 5)
	where 
	     generate' 0 _ _= [[]];
             generate' n pres prev= [q:qs | q <- [pres..49], (q*prev >9 ), (q*prev< 100), qs <- generate'(n-1) q q]

------------------------------------------------------------------------------------------
------------------------ Przemnaża każdą listę liczb. ------------------------------------
--------------- Każdy element listy jest przemnożony przez wszystkie następne ------------
------------------- Zwraca liste liczb dwucyfrowych w kolejności rosnącej ----------------
------------------------------------------------------------------------------------------
 
mult :: [Int] -> [Int]
mult [x] = []                          -- gdy został tylko jeden element, to nie ma go przez co przemnożyć i zwraca listę pustą.
mult (x:xs) = multi' (x:xs) ++ mult xs -- łączy dwie listy które zwracają te funkcje
	where
	multi' (x:xs) = [x*y| y <- xs] -- przemnaża x przez wszystkie następne elementy tablicy

------------------------------------------------------------------------------------------
-----------------Dla każego elemenetu x tabelki tworzy listę (a,b,x), gdzie --------------
----------- a: pierwsza współrzędna, b: druga współrzędna, x: dany element tabelki--------
------------------------------------------------------------------------------------------

generateCoordinates :: [[Int]] -> Int -> [(Int,Int,Int)]

generateCoordinates xss n= gC (concat xss) n 1 1
	where gC [] _ _ _ = []                         -- gdy tabelka jest pusta funkcja zwraca listę pustą
	      gC xss@(x:xs) n a b
		|b == 0 = gC xss n ((a+1) `mod` n) 1   -- gdy b jest równe zero wiersz zwiększa sie o 1, a kolumna przechodzi na 1. Kolumn jest od 1 do n-1
		|otherwise = (a,b,x) : gC xs n (a `mod` n) ((b+1) `mod` (n+1)) --zwiększaj numer kolumny od 1 do n

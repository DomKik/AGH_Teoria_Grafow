# AGH_Teoria_Grafow
Repo zawierajace projekt z przedmiotu: Teoria Grafow

JAK URUCHOMIĆ PROGRAM:

1. Pobierz repo
2. W terminalu wejdź do lokalizacji gdzie pobrałeś repo i wejdź do niego.
3. Wpisz: g++ -o "out" main.cpp
4. Następnie wpisz: ./out.exe
Gdy wszystko się powiodło program się odpalił i pyta o nazwe pliku w ktorym jest graf.

INPUT:

Na wejściu należy podać nazwe pliku z grafem - najlepiej .txt
WAŻNE: plik musi być w folderze grafy!!!
Przykład: graf_testowy1.txt (Zauważ, że nie grafy/graf_testowy1.txt jak to może sugerować istnienie folderu "grafy")

SZCZEGÓŁY DOT. PLIKU:
format:
[
[ [wierzchołek_połączony_z_0_wierzchołkiem waga] [wierzchołek_połączony_z_0_wierzchołkiem waga] itd...]
[ [wierzchołek_połączony_z_1_wierzchołkiem waga] itd...]
itd...
]
wierzchołek_startowy
wierzchołek_docelowy
koniec pliku

Założenia co do grafu w pliku:
1. Wierzchołki numerujemy od 0.
2. Wierzchołki numerujemy kolejno od 0,1,2 itd, nie dozwolone jest np graf składający się z wierzchołka 0 i 2 (musiałby by być jeszcze wierzchołek 1, aby był poprawny)
3. Wierzchołkami są wyłącznie liczby naturalne (z zerem), nie większe niż 2^31 - 1, aczkolwiek w praktyce program mógłby się wysypać na takiej liczbie wierzchołków - dopuszczalne ilości wierzchołków to około 10000, na wyższych ilościach program nie był testowany.
4. [] pierwszego stopnia (najbardziej zewnętrzne) oznaczają graf, [] drugiego stopnia (w środku pierwszego stopnia []) oznaczają zbiór krawędzi wychodzących z i-tego wierzchołka (iterujemy od 0 do liczby_wierzchołków-1), trzeciego stopnia [] (najbardziej zagnieżdżone, między [] drugiego stopnia) zawierają 2 liczby, odpowiednio wierzchołek, z którym i-ty wierzchołek ma połączenie oraz wagę tego połączenia. Tak jak na formacie wyżej.
5. W pliku jest jeden graf (wiecej grafów niż jeden nie zostanie wczytanych), jeden wierzchołek startowy i jeden wierzchołek docelowy(ten do którego liczymy najkrótszą ścieżkę).
6. Graf jest zapisany jakby był grafem skierowanym (istnienie krawędzi z wierzchołka 0 do 1 nie implikuje istnienia krawędzi z 1 do 0, trzeba to podać wprost, aby otrzymać graf nieskierowany)

Przykładowa zawartość pliku z grafem (bez komentarzy oznaczonych //):

[ 
[ [1 2] [2 5] [4 1] ] // sąsiedzi wierzchołka 0 wraz z wagami krawędzi łączącymi. tutaj sąsiadamy są wierzchołki: 1,2,4
[ [0 2] [3 3] ] // sąsiedzi wierzchołka 1 wraz z wagami krawędzi łączącymi. tutaj sąsiadamy są wierzchołki: 0,3
[ [0 5] ] // sąsiedzi wierzchołka 2 wraz z wagami krawędzi łączącymi. tutaj sąsiadamy są wierzchołki: 0
[ [1 3] ] // sąsiedzi wierzchołka 3 wraz z wagami krawędzi łączącymi. tutaj sąsiadamy są wierzchołki: 1
[ [0 1] ] // sąsiedzi wierzchołka 4 wraz z wagami krawędzi łączącymi. tutaj sąsiadamy są wierzchołki: 1
]
1 // wierzchołek_startowy
3 // wierzchołek_docelowy

OUTPUT:
Na wyjściu zostaje wypisana najkrótsza długość między wierzchołek_startowy a wierzchołek_docelowy.


#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#define INFINITY 1073741824 // 2^30

using namespace std;

struct Krawedz
{
         int wierzcholek, waga;
};

bool operator<(Krawedz a, Krawedz b)
{
         return a.waga < b.waga;
}

struct Zadanie
{
         vector< vector <Krawedz> > graf;
         int wierzcholek_poczatkowy, wierzcholek_docelowy;
         ~Zadanie()
         {
                  graf.clear();
         }
};

bool czy_liczba(char znak)
{
         return znak >= '0' && znak <= '9';
}

void wypisz_listy_sasiedztwa(vector< vector <Krawedz> > graf)
{
         cout << '[' << endl;
         for(int i=0; i<graf.size(); i++)
         {
                  cout << "[ ";
                  for(int j=0; j<graf[i].size(); j++)
                  {
                           cout << "[ " << graf[i][j].wierzcholek << " " << graf[i][j].waga << " ] ";
                  }
                  cout << "]" << endl;
         }
         cout << ']' << endl;
}

Zadanie wczytaj_dane_zadania(const char *nazwa_pliku)
{
         fstream plik;
         Zadanie zwracane;
         plik.open(nazwa_pliku, ios::in);
         if(plik.good())
         {
                  string zawartosc_pliku;
                  char znak;
                  int stopien_nawiasu = 0, nr_wierzcholka, wierzch_pocz, wierzch_doc, waga;
                  vector <Krawedz> lista_sasiedztwa;

                  do
                  {
                           plik >> znak;
                           if(znak == '[') { ++stopien_nawiasu; }
                           else if(znak == ']')
                           {
                                    --stopien_nawiasu;
                                    if(stopien_nawiasu == 1)
                                    {
                                             zwracane.graf.push_back(lista_sasiedztwa);
                                             lista_sasiedztwa.clear();
                                    }
                                    else if(stopien_nawiasu == 0)
                                    {
                                             plik >> wierzch_pocz >> wierzch_doc;
                                             break;
                                    }
                           }
                           else if(czy_liczba(znak))
                           {
                                    plik.unget();
                                    plik >> nr_wierzcholka >> waga;
                                    lista_sasiedztwa.push_back({nr_wierzcholka, waga});
                           }
                  } while(plik);

                  zwracane.wierzcholek_docelowy = wierzch_doc;
                  zwracane.wierzcholek_poczatkowy = wierzch_pocz;
                  plik.close();
                  return zwracane;
         }
         else
         {
                  cerr << "Problem z otwarciem pliku!" << endl;
                  return zwracane;
         }
}

int Dijkstra(Zadanie &zadanie)
{
         int aktualny_wierzch, poczatek = zadanie.wierzcholek_poczatkowy, wynik;
         int *odleglosci = new int[zadanie.graf.size()];
         for(int i=0; i<zadanie.graf.size(); i++) { odleglosci[i] = INFINITY; }
         odleglosci[poczatek] = 0;
         bool visited[zadanie.graf.size()] = {false};

         priority_queue <Krawedz> wierzcholki_do_analizy;

         wierzcholki_do_analizy.push({poczatek, odleglosci[poczatek]});
         visited[poczatek] = true;

         Krawedz *w;
         while(!wierzcholki_do_analizy.empty())
         {
                  aktualny_wierzch = wierzcholki_do_analizy.top().wierzcholek;
                  wierzcholki_do_analizy.pop();
                  for(int i=0; i<zadanie.graf[aktualny_wierzch].size(); i++)
                  {
                           w = &zadanie.graf[aktualny_wierzch][i];
                           if(odleglosci[w->wierzcholek] > odleglosci[aktualny_wierzch] + w->waga)
                           {
                                    odleglosci[w->wierzcholek] = odleglosci[aktualny_wierzch] + w->waga;
                                    if(!visited[w->wierzcholek])
                                    {
                                          visited[w->wierzcholek] = true;
                                          wierzcholki_do_analizy.push({w->wierzcholek, odleglosci[w->wierzcholek]});
                                    }
                           }
                  }
         }
         wynik = odleglosci[zadanie.wierzcholek_docelowy];
         delete [] odleglosci;
         return wynik;
}

int main()
{
    string nazwa_pliku;
    cout << "Podaj nazwe pliku, z ktorego chcesz wczytac dane: ";
    cin >> nazwa_pliku;
    nazwa_pliku = "grafy/" + nazwa_pliku;
    Zadanie zadanie = wczytaj_dane_zadania(nazwa_pliku.c_str());
    int wynik = Dijkstra(zadanie);
    cout << "odleglosc z " << zadanie.wierzcholek_poczatkowy << " do " << zadanie.wierzcholek_docelowy << " wierzcholka = " << wynik << endl;
    return 0;
}

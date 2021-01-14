// author: Grzegorz Prowadzacy
#ifndef List_H
#define List_H

#include <stddef.h> // size_t
#include <stdint.h> // int_fast32_t
#include <stdbool.h>

/** Tresc zadania:  (UWAGA: To wazne, aczkolwiek trudne i czasochlonne zadanie, ale jak ktos je umie zrobic moze smialo isc do pracy w C i ja dostanie)
Panstwa zadaniem jest napisanie listy dwukrotnie wiązanej z glowa, oraz funkcji do jej obslugi. Poza tym prosze o zaimplementowanie struktury ListIterator, do poruszania sie po naszej liscie w obydwie strony.
Nasza Lista ma zawierać elementy typu T (szczegoly ponizej). Nasza implementacja wzorowana C++owym std::list, aczkolwiek inna niz: http://www.cplusplus.com/reference/list/list/

------------ Struktury jakie potrzebujemy:
1. Struktura List powinna zawierac:
    - wskazniki na pierwszy i ostatni wezel (ang. first i last), warto wykorzystac posiadana implementacje listy pojedynczo wiazanej
    - moze zawierac tez pomocnicze informacje np. ilosc elementow (ang. size) itp...

2. Struktura Node powinna zawierac:
    - wskaznik na nastepny element (ang. next)
    - wskaznik na poprzedni element (ang. previous)
    - przechowywana wartosc (ang. value)

3. Poza tym potrzebujemy struktury Iterator, ktora bedzie pamietac aktualna pozycje wezla w liscie i bedzie w stanie przegladac je w obydwie strony.

Dla lubiacych wyzwania:
    - jesli chcielibysmy aby nasza lista mogla zawierac elementy roznych typow?
**/


typedef int_fast32_t T;

#ifdef __cplusplus
extern "C"
    {
#endif
struct List;
typedef struct List List;


struct Node;
typedef struct Node Node;


struct ListIterator;
typedef struct ListIterator ListIterator;


/// Construct and destruct functions:
/// Konstruktory podobne do: http://www.cplusplus.com/reference/list/list/list/
// funkcja, ktora zwraca List zaalokowany dynamicznie z wartoscia w pierwszym wezne podana w argumencie:
List* constructList(T element); /// oryginalnie było List* constructList(void); to chyba bez sensu
// funkcja, ktora zwraca List zaalokowany dynamicznie z okreslona iloscia wezlow zawierajacych wartosc podana w argumencie
List* constructListN(size_t elements, T value);
// funkcja, ktora zwraca List zaalokowany dynamicznie z okreslona iloscia wezlow zawierajacych wartosc skopiowane z podanego zakresu
List* constructListFromRange(const T* from, const T* to);

// funkcja, ktora usuwa cala liste wierzcholkow Lista zwalniajac przy tym pamiec zaalokowana List, funkcja podobna do: http://www.cplusplus.com/reference/list/list/~list/
void destruct(List* l);

// funkcja, ktora kopiuje nasz List i jego elementy (gleboka kopia), podobnie jak C++owy http://www.cplusplus.com/reference/list/list/operator=/
List* cloneList(const List* l);


/// Iterator functions:
// funkcje zwracaja zaalokowany iterator na pozycje pierwszego elementu, oczywiscie u nas potrzebujemy zwracac iterator zaalokowany dynamicznie ze wzgledu na brak koniecznosci znania rozmiaru tego typu, jakbym chcial zwracac przez kopie musialbym w tym pliku zdefiniowac te strukture
ListIterator* begin(List* l);
// funkcje zwracaja zaalokowany iterator na pozycje ostatniego elementu, oczywiscie u nas potrzebujemy zwracac iterator zaalokowany dynamicznie ze wzgledu na brak koniecznosci znania rozmiaru tego typu, jakbym chcial zwracac przez kopie musialbym w tym pliku zdefiniowac te strukture
// w C++ funkcje end() zwracaja iterator ZA KONIEC listy, u nas jednak bedzie to ostatni element
ListIterator* end(List* l);

/// Functions of ListIterator
bool hasNext(const ListIterator* li);
bool hasPrevious(const ListIterator* li);
// ponizsze funkcje przesuwaja "wskaznik" o jedna pozycje w lewo/prawo:
void next(ListIterator* li);
void previous(ListIterator* li);
T* current(ListIterator* li);


/// Capasity functions:
// funkcja zwraca ilosc elementow Listy, podobnie do: http://www.cplusplus.com/reference/list/list/size/
size_t size(const List* l);
// funkcja zwraca true, jesli nasza Lista nie zawiera elementow, podobnie do: http://www.cplusplus.com/reference/list/list/empty/
bool empty(const List* l);


/// Element access:
// zwraca wskaznik do wartosci pierwszego element Lista, podobna do: http://www.cplusplus.com/reference/list/list/front/
T* front(List* l);
// zwraca wskaznik do wartosci ostatniego element listy, podobna do: http://www.cplusplus.com/reference/list/list/back/
T* back(List* l);


///  Modifiers:
// funkcja wrzucajaca element na poczatek Listy, podobnie jak: http://www.cplusplus.com/reference/list/list/push_front/
void push_front(List* l, T element);
// funkcja usuwajaca element z poczatku Listy, podobna do: http://www.cplusplus.com/reference/list/list/pop_front/
void pop_front(List* l);
// funkcja wrzucajaca element na poczatek Listy, podobnie jak: http://www.cplusplus.com/reference/list/list/push_back/
void push_back(List* l, T element); ///chyba na koniec
// funkcja usuwajaca element z poczatku Listy, podobna do: http://www.cplusplus.com/reference/list/list/pop_back/
void pop_back(List* l); ///chyba z konca

// funkcja zamiast ustawia w liscie elementy z zakresu od, do, podobnie jak: http://www.cplusplus.com/reference/list/list/assign/
void assign(List* l, const T* from, const T* to);

// funkcja wstawiajaca dany element na pozycje wskazanej iteratorem, zwracajaca iterator wskazujacy na wstawiony element, podobna do: http://www.cplusplus.com/reference/list/list/insert/
ListIterator* insert(List* l, ListIterator* position, T element);
// funkcja usuwajaca element z List na danej pozycji, zwracając iterator do nastepnej pozycji, podobnie do: http://www.cplusplus.com/reference/list/list/erase/
ListIterator* erase(List* l, ListIterator* position);

// funkcja, ktora zamienia zawartosci list miedzy soba, podobna do: http://www.cplusplus.com/reference/list/list/swap/
void swap(List* l1, List* l2);

// funkcja ustawiajaca zadana ilosc elementow Lista, jesli zmniejszamy zostaja obciete ostatnie elementy, jesli zwiekszamy nowe elementy beda mialy wartosc 0, zupelnie jak: http://www.cplusplus.com/reference/list/list/resize/
void resize(List *l, size_t newSize);

// funkcja, ktora zwalnia pamiec calej List, zostawiajac nasza liste w takim stanie jak po zawolaniu: constructList();, podobne do: http://www.cplusplus.com/reference/list/list/clear/
void clear(List* l);


/// Operations:
// funkcja, ktora przeniesie elementy z drugiej listy wstawiajac je na pozycje position, podobna do: http://www.cplusplus.com/reference/list/list/splice/
void splice(List* l, ListIterator* position, List* list2TransferFrom);
// funkcja, ktora usuwa z listy wszystkie elementy o danej wartosci, podobna do: http://www.cplusplus.com/reference/list/list/remove/
void removeValues(List* l, T value);
// funkcja, ktora usunie z listy wszystkie elementy, dla ktorych wartosc z funkcji przekazanej jako argument zwroci true, podobna do: http://www.cplusplus.com/reference/list/list/remove_if/
void remove_if(List* l, bool(*predicate)(T nodeValue));
// funkcja, ktora posortuje elementy naszej listy, podobna do: http://www.cplusplus.com/reference/list/list/sort/
void sort(List* l);
// funkcja, ktora usunie duplikaty z naszej listy, UWAGA: zakladajac, ze lista jest posortowana, podobnie do: http://www.cplusplus.com/reference/list/list/unique/
void unique(List* l);
// funkcja, ktora polaczy dwie listy przenoszac elementy z l2 na l1, ale tak aby elementy byly posortowane. UWAGA: warunkiem koniecznym jest fakt aby obie listy przed laczeniem byly posortowane, podobna do: http://www.cplusplus.com/reference/list/list/merge/
void merge(List* l1, List* l2);
// funkcja, ktora odwroci kolejnosc elementow, podobna do: http://www.cplusplus.com/reference/list/list/reverse/
void reverse(List* l);
// funkcja, ktora polecam zaimplementowac, ktora wyswietli nasza liste, polecam pythoniczna forme, oczywiscie std::list nie zawiera takowej funkcji
void printList(List* l);
// funkcja, ktora polecam zaimplementowac, ktora zamienia nasza liste na tekst zaalokowany na stercie, oczywiscie std::list nie zawiera takowej funkcji
char* list2Text(const List* l);


/// Functions to cooperate with function pointers:
// funkcja, ktora dla kazdego elementu listy zawola funkcje przekazana jako argument, oczywiscie std::list nie zawiera takowej
void for_each(List* l, void(*f)(T* current));

#ifdef __cplusplus
}
#endif

#endif // List_H


>Denys Klochkov Nr.Ind 294860

>Tablica Haszująca W12, W21, W32

>./htable -htype=(0,1) -size=(0,1,2) (-test) 

htype - typ funkcji haszującej 
size - rozmiar tablicy
test - tryb testowania

./generator file.txt -seq=(0,1) WORD_COUNT

file.txt - plik do generowania słów
seq - losowa lub sekwencyjna generacja
WORD_COUNT - liczba słów


Tryb testowania:
./generator file.txt -seq=(0,1) WORD_COUNT |  ./htable -htype=(0,1) -size=(0,1,2) -test
Tryb "ręczny":
./htable -htype=(0,1) -size=(0,1,2) < file.txt

>Dane wejściowe: plik file.txt - dowolny tekst
 Dane wyjściowe: 
 	dla trybu testowania (-test):
 	plik results.rs - numer słowa, czas wstawiania słowa, długość słowa, "głębokość" w tablicy
 	plik results2.rs- numer słowa, czas wstawiania słowa,  współczynnik zgodności oceny teoretycznej z pomiarem czasu
 	pliki results.png, results2.png- wykres odpowiedniego pliku

 	dla trybu "ręcznego":
 	w konsoli wyświetlana zawartość tablicy mieszającej po wstawieniu/usunięciu kolejnych słów

>Struktury danych: 
record -  reprezentacja napisu 
myHashTable - tablica haszująca

Algorytm:
Wstawianie : wyliczenie hashu, jeśli dany napis mieści się w tablicy(wyszukujemy porównując z kolejnymi napisami w wierszu o danym hashu) - 
zwiększenie licznika instancji odpowiedniego napisu, jeśli nie - wstawianie na koniec wiersza o danym hashu

Przewidywana złożoność O((d+1)*n), n - liczba znaków w napisie, d - liczba porównań z innymi napisami potrzebna do wstawienia dannego napisu("głębokość")

Usunięcie : wyliczenie hashu, porównywanie z kolejnymi napisami w wierszu, zmniejszenie licznika instancji odpowiedniego napisu. Jeśli licznik wynosi 0 - 
usuwamy dany "record" z tablicy  

Testowanie polega na pomiarze czasu wstawiania dla kolejnych słów z genetatora. Wstawianie każdego słowa odbywa się wielokrotnie ( 10 000 razy ). 
Na podstawie tego wyliczany jest średni czas wstawiania,który jest zapisany do pliku	
Przewidywana złożoność O((d+1)*n)

>Pliki:
		makefile
		tekst.txt - duży tekst dla generatora
		words.txt - zbiór słow dla trybu "ręcznego"	
src: 		htable.cpp - główny modul, zawiera logikę testowania oraz trybu "ręcznego"
 	     	htable.h - implementacja metod tablicy haszującej myHashTable
		genetator.cpp - implementacja generatora 
gplot:
		results_plot.p - skrypt gnuplot
		results_plot2.p - skrypt gnuplot
>Decyzje projektowe:
Ograniczenia:
 Maksymalna liczba znaków w słowie : 32
 Maksymalna liczba słów w trybie ręcznego testowania: 50
 Polecany maksymalny rozmiar problemu: 40 000


/*Natalia Kiełbasa*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include "gra_projekt_funkcje.h"

int main(int argc, char** argv){

	char nick[21];

	if((argc == 2) && ((strcmp(argv[1], "--help")) || (strcmp(argv[1], "-h")))){
		printf("Opis programu:\n\n");
		printf("Ten program to gra polegająca na zgadywaniu losowo wygenerowanej sekwencji pięciu liczb. Liczby są całkowite i przyjmują wartości z przedziału 1-8.\n");
			printf("Każda liczba jest inna. Podczas rozgrywki gracz wpisuje sekwencję pięciu liczb próbując zgadnąć tą odpowiednią w jak najmniejszej liczbie prób.\n");
			printf("\nNad nazwą gry została umieszczona wygenerowana sekwencja, jest tam jednak tylko by móc szybko sprawdzić czy program w całości poprawnie działa.\nW rzeczywistej rozgrywce ta jedna linijka printf zostałaby usunięta z kodu.\n\n");
			printf("\n\n Szczegółowy opis programu: \n");
			printf("1. Wyświetlenie instrukcji. żądanie wpisania przez gracza nicku o długości do 20 znaków. Jeśli gracz wpisze dłuższy nick, ten zostanie automatycznie przycięty do założonych 20 znaków.\n");
			printf("2. Generowanie sekwencji 5 losowych liczb spełniających podane wyżej warunki.\n");
			printf("3. Wyświetlenie nazwy gry.\n");
			printf("4. Możliwość przejrzenia tabeli najlepszych dotychczasowych 10 wyników przez wpisanie 'TAK' (i normalizacja słowa, by przy wpisania 'tak' lub 'Tak' lista też się wyświetliła).\n");
			printf("5. Rozpoczęcie pomiaru czasu gry. \n");
			printf("6. Rozpoczęcie rozgrywki, która trwa albo do odgadnięcia odpowiedniej sekwencji przez gracza, albo tyle rund ile jest możliwych wszystkich sekwencji (żeby gracz nie grał w nieskończoność).\n");
			printf("7. Wpisywanie przez gracza zgadywanych liczb.\n");
			printf("8. Przekształcenia liczb z char na int. Jeśli wpisany został zły znak (litera), liczba nie znajdująca się w przedziale 1-8, albo liczba która już wcześniej została podana\n");
					printf("(bo każda liczba musi być inna) wyświetlona zostanie ponownie prośba o wpisanie liczby. Jeśli gracz poda jednocześnie kilka liczb, wczytana zostanie jedynie pierwsza z nich\n");
					printf("i sprawdzona o zgodność z powyższymi założeniami. Całość powtarza się tak długo aż gracz poda akceptowalną sekwencję 5 liczb.\n");
			printf("9. Sprawdzenie ile z podanych liczb spełnia warunki: \n");
					printf("   a) zarówno podana wartość jak i pozycja liczby w sekwencji się zgadza\n");
					printf("   b) zgadza się wartość liczby (czyli że występuje ona gdzieś w sekwencji), ale pozycja jest niepoprawna\n");
			printf("10. Wyświetlenie wyników z pkt. 9 dla bieżącej rundy.\n");
			printf("11. Wyświetlenie wyników ze wszystkich poprzednich rund, by gracz miał na nie łatwiejszy podgląd i nie musiał tyle scrollować i ich szukać.\n");
			printf("12. Powtarzanie pkt. 7-11 aż spełnione zostaną warunki z pkt. 6 potrzebne do poprawnego zakończenia rozgrywki.\n");
			printf("13. Koniec pomiaru czasu rozgrywki.\n");
			printf("14. Wyświetlenie wyników bieżącej rozgrywki.\n");
			printf("15. Wczytanie listy rankingowej TOP 10 z pliku wyników. Jeśli ten nie istnieje stworzony zostaje nowy plik.\n");
			printf("16. Aktualizacja listy rankingowej (top 10. miejsc), zapisanie tych wyników w pliku i wyświetlenie listy w programie.\n");
			printf("17. Opcja ponownej rozgrywki przez wpisanie 'TAK'.\n");
			printf("18. Ewentualna ponowna rozgrywka.\n");
			printf("19. Zakończenie programu. \n\n\n\n");

		return 0;
	}

	printf("\n\n\n\n\n                                              INSTRUKCJA:\n\nZ zestawu liczb od 1 do 8 zostaje wylosowanych pięć różnych liczb. Zadaniem gracza jest odgadnięcie każdej z \nnich. Istotna jest również kolejność występowania danych liczb.\n\n");
	printf("1. Gracz podaje jakie liczby znajdują się według niego w jakiej kolejności.\n   Przykładowe sekwencje:   1  8  7  5  2   lub   2  3  4  8  5    itp.\n");
	printf("2. Komputer podaje ile razy gracz odgadł jednocześnie poprawną pozycję jak i wartość liczby, oraz liczby \n   występujące w sekwencji, ale podane przez gracza na złej pozycji.\n");
	printf("3. Gracz zgaduje liczby i ich kolejność tak często, aż nie odgadnie całości poprawnie. Wtedy gra się kończy.\n\n");
	printf("Przykład: \n\nWylosowana została sekwencja    1 2 3 4 5\n\nGracz zgaduje czy sekwencją jest   2 4 3 8 5\n\n");
	printf("Jako odpowiedź dostaje: \nDobra kolejność i liczba: 1   (bo tylko 5 była na dobrym miejscu w sekwencji) \nZła kolejność ale dobra liczba: 3   (bo odgadł liczby 2, 3, 4, ale znalazły się one w złym miejscu w sekwencji)\n");
	printf("\nTa czynność jest następnie powtarzana, aż do odgadnięcia poprawnej kombinacji.\n\n\n\n");

	getText("NICK (do 20 znaków): ", nick, sizeof(nick));
	printf("\n\n\n\n");

	while (gra(nick) == 1){
		printf("\n\n\n\n");
		gra(nick);
	}

	return 0;
}


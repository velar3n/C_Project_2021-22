/*Natalia Kiełbasa*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include "gra_projekt_funkcje.h"

struct gracz{
    char nick_gr[22];
    int runda_gr;
    long long int czas_gr;
};

struct gracz gracze_tab[13];

/* funkcja nie zezwalająca zbyt długi input od użytkownika i zapobiegająca ewentualnemu zapętleniu programu*/
int getText(char *a, char *buffer, size_t dlugosc){
    int ch, extra;

    if(a != NULL){
        printf ("%s", a);
        fflush (stdout);
    }
    if(fgets (buffer, dlugosc, stdin) == NULL){
        return 1;
    }
    if(buffer[strlen(buffer)-1] != '\n'){
        extra = 0;
        while (((ch = getchar()) != '\n') && (ch != EOF)){
            extra = 1;
        }
        return (extra == 1) ? 2 : 0;
    }
    buffer[strlen(buffer)-1] = '\0';
    return 0;
}

/*funkcja konwertująca char na int, sprawdza czy wpisywane przez gracza liczby rzeczywiście są typu int, a nie np literami*/
long int KonwertujNaLiczbe(){
	char zgad[2];
	long int zgadywane;
	char *endptr = NULL;
	getText(" ", zgad, sizeof(zgad));
	errno = 0;

	zgadywane = strtol(zgad, &endptr, 10);

	if (zgad == endptr){
		return 0;
	}
	else if (errno == 0 && !*endptr){
			return zgadywane;
	}
	else if (errno == 0 && *endptr != 0){
		return zgadywane;
	}
	else{
		return 0;
	}

}

/*porównanie do qsort*/
int porownuj(const void *g1, const void *g2){

	const struct gracz gr1 = *(const struct gracz *)g1;
	const struct gracz gr2 = *(const struct gracz *)g2;

	if((gr1.runda_gr - gr2.runda_gr) > 0){
		return 1;
	}
	if((gr1.runda_gr - gr2.runda_gr) < 0){
		return -1;
	}
	if((gr1.runda_gr - gr2.runda_gr)  == 0){
		if((gr1.czas_gr - gr2.czas_gr)  > 0){
			return 1;
		}
		if((gr1.czas_gr - gr2.czas_gr)  < 0){
			return -1;
		}
		else{
			return 0;
		}
	}
	return 0;
}

void normalizuj(char *a){
	int i;
	for(i = 0; i < strlen(a); i++){
		a[i] = toupper(a[i]);
	}
}

int gra(char *nick){
	int i, j, n;
	int liczba_gra[5], zgad_wyn[56][7], runda = 0, rrr, liczba, x = 0, wszystko_ok = 0, liczba_ok, czas_gry, miejsce = 0, wielkosc, mmm = 1;
	long int ttt, zgadywane_1, zgadywane_2, zgadywane_3, zgadywane_4, zgadywane_5;
	char nnn[22], wpiszTak[4];
	time_t tp, tk;
	FILE *wyniki;

		srand(time(0));

	for(i = 0; i < 5; i++){									/*wygenerowanie 5 różnych losowych liczb z przedziału 1-8 */
		liczba = ((rand() / 1000) % 8) + 1;
		for(j = 0; j <= i; j++){
			if(liczba == liczba_gra[j]){
				x++;
			}
			if(x > 0){
				liczba = ((rand() / 1000) % 8) + 1;
				j = -1;
				x = 0;
			}
		}	
		liczba_gra[i] = liczba;
	}

	printf("%i, %i, %i, %i, %i \n", liczba_gra[0], liczba_gra[1], liczba_gra[2], liczba_gra[3], liczba_gra[4]);  /*poprawna sekwencja, umieszczona tu, by dało się sprawdzić działanie programu na szybko*/

	printf("--------------------------------------------- GRA ZGADNIJ LICZBY ---------------------------------------------\n\n\n\n");

	getText("\n\n\n\nAby wyświetlić dotychczasową listę tankingową wpisz 'TAK'. W przeciwnym wypadku wciśnij ENTER   ", wpiszTak, sizeof(wpiszTak));
	normalizuj(wpiszTak);

	if((!strcmp(wpiszTak, "TAK"))){
		wyniki = fopen("tabelaWynikow.txt", "r");			/*wyświetlenie listy rankingowej*/

		if(wyniki == NULL){
	        fprintf(stderr, "Lista rankingowa nie istnieje\n");
	    }

	    else{
	    	printf("\n\nLISTA RANKINGOWA NAJLEPSZYCH WYNIKÓW\n\n\n");
		    printf("          NICK                            RUNDY   CZAS\n\n");

	    	while(fscanf(wyniki, "%s %d %ld\n", nnn, &rrr, &ttt) != EOF){
	    		wielkosc = strlen(nnn);
	   			wielkosc = (20 - wielkosc) + 15;
	   			printf("%i. %s",mmm, nnn);
	   			for(j = 0; j < wielkosc; j++){
   					printf(" ");
   				}
				printf("      %d      %lds\n", rrr, ttt);
				mmm++;
	    	}
	    }
    	fclose(wyniki);
	}

	printf("\n\n\n");

	tp = time(NULL); 								/*początek licznika czasu rozgrywki*/

	while((wszystko_ok != 5) && (runda != 55)){		/*rozgrywka*/

			zgadywane_1 = 0;
			zgadywane_2 = 0;
			zgadywane_3 = 0;
			zgadywane_4 = 0;
			zgadywane_5 = 0;

			n = runda;
			runda++;

			if(runda != 1){
				printf("\n\nDobra kolejność i liczba: %i Zła kolejność ale dobra liczba: %i \n\n\n", wszystko_ok, liczba_ok);
				printf("Wyniki poprzednich rund:\n");
				for(i = 0; i < (runda-1); i++){
					printf("%i %i %i %i %i  -  Dobra kolejność i liczba: %i    Zła kolejność ale dobra liczba: %i \n", zgad_wyn[i][0], zgad_wyn[i][1], zgad_wyn[i][2], zgad_wyn[i][3], zgad_wyn[i][4], zgad_wyn[i][5], zgad_wyn[i][6]);
				}
			}

			printf("\n");							/*wpisywanie przez gracza zgadywanych liczb - muszą być różne i w przedziale 1-8*/
			while((zgadywane_1 > 8)  || (zgadywane_1 < 1)){
				printf("Wpisz numer na pierwszej pozycji:");
				liczba = KonwertujNaLiczbe();
				if(liczba == 0){
					zgadywane_1 = 0;
				}
				else{
					zgadywane_1 = liczba;
				}
			}
			printf("\n");
			while((zgadywane_2 > 8)  || (zgadywane_2 < 1) || (zgadywane_2 == zgadywane_1)){
				printf("Wpisz numer na drugiej pozycji:");
				liczba = KonwertujNaLiczbe();
				if(liczba == 0){
					zgadywane_2 = 0;
				}
				else{
					zgadywane_2 = liczba;
				}
			}
			printf("\n");
			while((zgadywane_3 > 8)  || (zgadywane_3 < 1) || (zgadywane_3 == zgadywane_1) || (zgadywane_3 == zgadywane_2)){
				printf("Wpisz numer na trzeciej pozycji:");
				liczba = KonwertujNaLiczbe();
				if(liczba == 0){
					zgadywane_3 = 0;
				}
				else{
					zgadywane_3 = liczba;
				}
			}
			printf("\n");
			while((zgadywane_4 > 8)  || (zgadywane_4 < 1) || (zgadywane_4 == zgadywane_1) || (zgadywane_4 == zgadywane_2) || (zgadywane_4 == zgadywane_3)){
				printf("Wpisz numer na czwartej pozycji:");
				liczba = KonwertujNaLiczbe();
				if(liczba == 0){
					zgadywane_4 = 0;
				}
				else{
					zgadywane_4 = liczba;
				}
			}
			printf("\n");
			while((zgadywane_5 > 8)  || (zgadywane_5 < 1) || (zgadywane_5 == zgadywane_1) || (zgadywane_5 == zgadywane_2) || (zgadywane_5 == zgadywane_3) || (zgadywane_5 == zgadywane_4)){
				printf("Wpisz numer na piątej pozycji:");
				liczba = KonwertujNaLiczbe();
				if(liczba == 0){
					zgadywane_5 = 0;
				}
				else{
					zgadywane_5 = liczba;
				}
			}

			wszystko_ok = 0;						/*sprawdzenie ile jest liczb spełnia warunki - dobra liczba i dobra pozycja, dobra liczba ale zła pozycja*/
			liczba_ok = 0;

			for(i = 0; i < 5; i++){
				if(i == 0){
					if(zgadywane_1 == liczba_gra[i]){
						wszystko_ok++;
					}
				}
				else if(zgadywane_1 == liczba_gra[i]){
					liczba_ok++;
				}
			}

			for(i = 0; i < 5; i++){
				if(i == 1){
					if(zgadywane_2 == liczba_gra[i]){
						wszystko_ok++;
					}
				}
				else if(zgadywane_2 == liczba_gra[i]){
					liczba_ok++;
				}
			}		

			for(i = 0; i < 5; i++){
				if(i == 2){
					if(zgadywane_3 == liczba_gra[i]){
						wszystko_ok++;
					}
				}
				else if(zgadywane_3 == liczba_gra[i]){
					liczba_ok++;
				}
			}		

			for(i = 0; i < 5; i++){
				if(i == 3){
					if(zgadywane_4 == liczba_gra[i]){
						wszystko_ok++;
					}
				}
				else if(zgadywane_4 == liczba_gra[i]){
					liczba_ok++;
				}
			}		

			for(i = 0; i < 5; i++){
				if(i == 4){
					if(zgadywane_5 == liczba_gra[i]){
						wszystko_ok++;
					}
				}
				else if(zgadywane_5 == liczba_gra[i]){
					liczba_ok++;
				}
			}
			zgad_wyn[n][0] = zgadywane_1;				/*zapisanie wszystkich danych w tablicy*/
			zgad_wyn[n][1] = zgadywane_2;
			zgad_wyn[n][2] = zgadywane_3;
			zgad_wyn[n][3] = zgadywane_4;
			zgad_wyn[n][4] = zgadywane_5;
			zgad_wyn[n][5] = wszystko_ok;
			zgad_wyn[n][6] = liczba_ok;
	}

	tk = time(NULL);
	czas_gry = tk - tp;
					
	if(wszystko_ok == 5){								/*wyświetlenie wyników rozgrywki*/
		printf("\n\n\n\n\n\n\n                         ************************ GRATULACJE ************************ \n\n\n");
		printf("GRĘ WYGRANO W   %i   PODEJŚCIACH W CZASIE   %i SEKUND \n\n", runda, czas_gry);
		printf("DOBRĄ ODPOWIEDZIĄ BYŁA SEKWENCJA * %i %i %i %i %i * \n\n", liczba_gra[0], liczba_gra[1], liczba_gra[2], liczba_gra[3], liczba_gra[4]); 
	}

	if(runda == 55){
		printf("ILOŚĆ PRÓB ODGADNIĘCIA PRAWIDŁOWEJ SEKWENCJI PRZEKROCZYŁA ILOŚĆ MOŻLIWYCH ODPOWIEDZI. GAME OVER:(\n\n");
	}

	wyniki = fopen("tabelaWynikow.txt", "a+");			/*wyświetlenie listy rankingowej i zapisanie danych z pliku*/

	if(wyniki == NULL){
        fprintf(stderr, "Problemy z załadowaniem listy rankingowej\n");
        return 0;
    }

    printf("\n\nLISTA RANKINGOWA NAJLEPSZYCH WYNIKÓW\n\n\n");
    printf("          NICK                            RUNDY   CZAS\n\n");

    while(fscanf(wyniki, "%s %d %ld\n", nnn, &rrr, &ttt) != EOF){
		strcpy(gracze_tab[miejsce].nick_gr, nnn);
		gracze_tab[miejsce].runda_gr = rrr;
		gracze_tab[miejsce].czas_gr = ttt;
    	miejsce++;
    }

    fclose(wyniki);

    strcpy(gracze_tab[miejsce].nick_gr, nick);			/*dopisanie aktualnego wyniku*/
   	gracze_tab[miejsce].runda_gr = runda;
   	gracze_tab[miejsce].czas_gr = czas_gry;

   	if(miejsce == 0){									/*gdy nie było wcześniejszej listy rankingowej - nowy wpis + plik*/
   		wielkosc = strlen(gracze_tab[0].nick_gr);
   		wielkosc = (20 - wielkosc) + 15;
   		printf("1. %s", gracze_tab[0].nick_gr);
   		for(i = 0; i < wielkosc; i++){
   			printf(" ");
   		}
   		printf("      %d      %llds\n", gracze_tab[0].runda_gr, gracze_tab[0].czas_gr);
   		wyniki = fopen("tabelaWynikow.txt", "w");

   		if(wyniki == NULL){
        	fprintf(stderr, "Problemy z aktualizacją listy rankingowej\n");
        	return 0;
    	}
    	fprintf(wyniki, "%s %d %lld\n", gracze_tab[0].nick_gr, gracze_tab[0].runda_gr, gracze_tab[0].czas_gr);
   		fclose(wyniki);
   		printf("\n\n");  
   	}

   	else{												/*posortowanie wyników dawnych i aktualnego*/
   		if((gracze_tab[miejsce].runda_gr > gracze_tab[miejsce-1].runda_gr) && (miejsce > 9)){
	   		for(i = 0; i <= 9; i++){
	   			wielkosc = strlen(gracze_tab[i].nick_gr);
   				wielkosc = (20 - wielkosc) + 15;
   				printf("%i. %s",i+1, gracze_tab[i].nick_gr);
	   			for(j = 0; j < wielkosc; j++){
   					printf(" ");
   				}
   				printf("      %d      %llds\n", gracze_tab[i].runda_gr, gracze_tab[i].czas_gr);
	   		}
   		}
   		else{
   			qsort(gracze_tab, miejsce+1, sizeof(struct gracz), porownuj);

   			if(miejsce > 9){
   				miejsce = 9;
   			}

   			for(i = 0; i <= miejsce; i++){
	   			wielkosc = strlen(gracze_tab[i].nick_gr);
   				wielkosc = (20 - wielkosc) + 15;
   				printf("%i. %s",i+1, gracze_tab[i].nick_gr);
	   			for(j = 0; j < wielkosc; j++){
   					printf(" ");
   				}
   				printf("      %d      %llds\n", gracze_tab[i].runda_gr, gracze_tab[i].czas_gr);
	   		}

   			wyniki = fopen("tabelaWynikow.txt", "w");	/*zapisanie nowych danych w pliku*/

	   		if(wyniki == NULL){
	        	fprintf(stderr, "Problemy z aktualizacją listy rankingowej\n");
	        	return 0;
	    	}
	    	for(i = 0; i <= miejsce; i++){
	    		fprintf(wyniki, "%s %d %lld\n", gracze_tab[i].nick_gr, gracze_tab[i].runda_gr, gracze_tab[i].czas_gr);
	    	}

	   		fclose(wyniki);
	   	}
   	}

   	getText("\n\n\n\n\nAby zagrać ponownie wpisz 'TAK'. W przeciwnym wypadku wciśnij ENTER: ", wpiszTak, sizeof(wpiszTak));
   	normalizuj(wpiszTak);

	if((!strcmp(wpiszTak, "TAK"))){
		return 1;
	}
	else{
		return 0;
	}										/*koniec*/
}
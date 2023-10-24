
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//#include <dvec.h>

//Generowanie liczb pseudo-losowych do pliku (uzupełnij ścieżkę!)
void Generuj() {

    //Ścieżka do pliku
    const char* nazwa_pliku = "C://Users/artex/downloads/liczby.txt";

    //Liczba liczb, masło maślane
    int liczba_liczb = 5000000;

    //Zmienne odpowiedzialne za zakres liczb losowanych
    int min = 10000;
    int max = 5000000;
    int zakres = min - max + 1;

    // Otwórz plik do zapisu
    FILE* plik = fopen(nazwa_pliku, "w");

    // Sprawdź, czy udało się otworzyć plik
    if (plik == NULL) {
        printf("Nie można otworzyć pliku do zapisu.\n");
        return;
    }

    // Inicjalizacja generatora
    srand(time(NULL));

    // Generowanie i zapisywanie liczb do pliku
    for (int i = 0; i < liczba_liczb; i++) {
        int losowa_liczba = rand();
        fprintf(plik, "%d\n", losowa_liczba);
    }

    // Zamknij plik
    fclose(plik);

    //Komunikat o wykonanej operacji
    printf("Wygenerowano i zapisano %d liczb pseudo-losowych do pliku '%s'.\n", liczba_liczb, nazwa_pliku);
    printf("\n");
}

//Odczytywanie liczb z powstałego pliku tekstowego.
int* Odczytaj() {
    const char* nazwa_pliku = "C://Users/artex/downloads/liczby.txt";
    int* liczba_liczb;
    FILE* plik = fopen(nazwa_pliku, "r");
    
    if (plik == NULL) {
        printf("Nie można otworzyć pliku do odczytu.\n");
        return NULL;
    }

    int* tablica_liczb = NULL;
    int liczba;
    int indeks = 0;

    while (fscanf(plik, "%d", &liczba) == 1) {
        if (tablica_liczb == NULL) {
            tablica_liczb = (int*)malloc(sizeof(int));
        } else {
            tablica_liczb = (int*)realloc(tablica_liczb, (indeks + 1) * sizeof(int));
        }

        tablica_liczb[indeks] = liczba;
        indeks++;
    }

    fclose(plik);
    *liczba_liczb = indeks;
    return tablica_liczb;
}

//-----Funkcja sortowania bombelkowego----- [DZIAŁA]
void BubbleSort(int tab_a[], int a) {
    int i, j;
    //Kontroluje ilość 'powtórzeń' sortowania
    for (i = 0; i < a - 1; i++) {
        //Porownuje ze soba i zamienia elementy w tablicy
        for (j = 0; j < a - i - 1; j++) {
            //Jesli sprawdzana liczba jest wieksza od nastepnej
            if (tab_a[j] > tab_a[j + 1]) {
                //Zamienia miejscami liczby
                int temp = tab_a[j];
                tab_a[j] = tab_a[j + 1];
                tab_a[j + 1] = temp;
            }
        }
    }
}


//-----Funkcja sortowania Shell Sort-----
void ShellSort(int Tab_a[], int b) {
    // Przearanżowuje elementy w interwałach kolejno: b/2, b/4, b/8
    int interval;
    for (interval = b/2; interval > 0; interval /= 2) {
        for (int i = interval; i < b; i += 1) {
            int temp = Tab_a[i];
            int j;
            for (j = i; j >= interval && Tab_a[j - interval] > temp; j -= interval) {
                Tab_a[j] = Tab_a[j - interval];
            }
            Tab_a[j] = temp;
        }
    }
}


int main() {
    const char* nazwa_pliku = "liczby.txt";
    int tab_a[] = {12, 432, 110, 25, 443, 80, 8080}; //Wewnątrz tablicy prawdopodobnie będzie odnośnik do pliku z liczbami.
    int tab_b[] = {34, 13, 727, 17, 69, 420, 2137}; //Wewnątrz tablicy prawdopodobnie będzie odnośnik do pliku z liczbami.

    int a = sizeof(tab_a) / sizeof(tab_a[0]);
    int b = sizeof(tab_b) / sizeof(tab_b[0]);

    Generuj();
    //Odczytaj();
    BubbleSort(tab_a, a);
    ShellSort(tab_b, b);
    
    //Print posortowanego zbioru BubbleSort
    printf("Bubble Sorted array: ");
    printf("\n");

    for (int i = 0; i < a; i++) {
        printf("%d ", tab_a[i]);
    }
    //Koniec printu posortowanego zbioru Shell Sort

    printf("\n");
    printf("\n");
    printf("Shell Sorted array: ");
    printf("\n");

    for (int i = 0; i < b; i++) {
        printf("%d ", tab_b[i]);
    }

    return 0;
}
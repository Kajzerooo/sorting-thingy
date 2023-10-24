
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//-----Generowanie liczb pseudo-losowych do pliku (uzupełnij ścieżkę!)-----
void Generuj() {

    //Ścieżka do pliku
    const char* nazwa_pliku = " ";

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

//------Odczytywanie liczb z powstałego pliku tekstowego.----- [NIE DZIAŁA]
#define MAX_LICZBY 5000000 // Maksymalna liczba liczb w pliku tekstowym
int Odczytaj(const char *nazwaPliku, int tablica[], int *iloscLiczb) {
    //Ścieżka
    nazwaPliku = " ";
    FILE *plik;
    plik = fopen(nazwaPliku, "r");
    if (plik == NULL) {
        perror("Błąd przy otwieraniu pliku");
        return 0;
    }

    int liczba, i = 0;

    while (fscanf(plik, "%d", &liczba) == 1) {
        if (i >= MAX_LICZBY) {
            fprintf(stderr, "Osiągnięto maksymalną liczbę liczb w pliku\n");
            break;
        }
        tablica[i] = liczba;
        i++;
    }

    *iloscLiczb = i; // Przekazujemy ilość odczytanych liczb przez wskaźnik

    fclose(plik);
    return 1; // Zwracamy 1, aby oznaczyć sukces
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


//-----Funkcja sortowania Shell Sort----- [DZIAŁA]
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

//-----Funkcja sortowania Quick Sort----- [IN PROGRESS]
    // Funkcja zamieniająca elementy tablicy
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Funkcja partition do wybierania pivota i dzielenia tablicy
int partition(int tab_c[], int low, int high) {
    int pivot = tab_c[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (tab_c[j] < pivot) {
            i++;
            swap(&tab_c[i], &tab_c[j]);
        }
    }
    swap(&tab_c[i + 1], &tab_c[high]);
    return (i + 1);
}

// Główna funkcja QuickSort
void QuickSort(int tab_c[], int low, int high) {
    if (low < high) {
        int pivotIndex = partition(tab_c, low, high);

        QuickSort(tab_c, low, pivotIndex - 1);
        QuickSort(tab_c, pivotIndex + 1, high);
    }
}
//Ścieżka
int main() {
    FILE *file = fopen(" ", "r");
    if (file == NULL) {
        printf("Nie można otworzyć pliku.\n");
        return 1;
    }
    //Ścieżka
    const char* nazwa_pliku = " ";
    int tab_a[] = {12, 432, 110, 25, 443, 80, 8080}; //Wewnątrz tablicy prawdopodobnie będzie odnośnik do pliku z liczbami.
    int tab_b[] = {34, 13, 727, 17, 69, 420, 2137}; //Wewnątrz tablicy prawdopodobnie będzie odnośnik do pliku z liczbami.
    int tab_c[] = {16, 54, 88, 96, 1, 3, 1910};


    int a = sizeof(tab_a) / sizeof(tab_a[0]);
    int b = sizeof(tab_b) / sizeof(tab_b[0]);
    int c = sizeof(tab_c) / sizeof(tab_c[0]);

    Generuj();
    //Odczytaj();
    
//-------------------------------------------------- 

    //BUBBLE SORT
    BubbleSort(tab_a, a);
    printf("Bubble Sorted array: \n");
    for (int i = 0; i < a; i++){
        printf("%d ", tab_a[i]);
    }

//--------------------------------------------------

    //SHELL SORT
    ShellSort(tab_b, b);
    printf("\n\nShell Sorted array: \n");
    for (int i = 0; i < b; i++){
        printf("%d ", tab_b[i]);
    }

//-------------------------------------------------- 

    //QUICK SORT
    QuickSort(tab_c, 0, c-1);
    printf("\n\nQuick Sorted array: \n");
    for (int i = 0; i < b; i++){
        printf("%d ", tab_c[i]);
    }

    return 0;
}
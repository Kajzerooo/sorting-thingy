#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <locale.h>
#include <string.h>

//Liczba liczb, masło maślane
int liczba_liczb = 0;

clock_t start, end;
double cpu_time_used;
double najszybszy_czas = 0;

void ZapiszNajszybszyCzas(const char *nazwa_pliku, const char *algorytm, double czas_sortowania) {
    FILE *plik_wynikowy = fopen(nazwa_pliku, "a");

    if (plik_wynikowy == NULL) {
        printf("Błąd otwierania pliku.\n");
        return;
    }

    fprintf(plik_wynikowy, "Czas sortowania dla %s: %f sekundy\n", algorytm, czas_sortowania);

    // Jeśli aktualny czas sortowania jest najszybszy, zaktualizuj najszybszy_czas
    if (czas_sortowania < najszybszy_czas || najszybszy_czas == 0) {
        najszybszy_czas = czas_sortowania;
        fprintf(plik_wynikowy, "Najszybsze było Sortowanie %s: %f sekundy\n", algorytm, czas_sortowania);
    }

    fclose(plik_wynikowy);
}


//-----Generowanie liczb pseudo-losowych do pliku----- [DZIAŁA]
void Generuj(int tab[]) 
{
	int min = 100000;
	int max = 5000000;
		srand(time(NULL));
		
	for(int i=0; i<= liczba_liczb; i++)
	{
		tab[i]=(rand() % (max - min + 1)) + min;
		//printf("%d ", tab[i]);
		//printf("\n");
		
	}

}

void ZapiszWyniki(const char *nazwa_pliku, int tab[], int size, double czas_sortowania) {

    FILE *plik_wyjsciowy = fopen(nazwa_pliku, "w");

    if (plik_wyjsciowy == NULL) {
        printf("Błąd otwierania pliku.\n");
        return;
    }

    fprintf(plik_wyjsciowy, "Wyniki dla %d liczb:\n", liczba_liczb);

    for (int i = 0; i < size; i++) {
        fprintf(plik_wyjsciowy, "%d ", tab[i]);
    }

    fprintf(plik_wyjsciowy, "\nCzas sortowania: %f sekundy\n", czas_sortowania);

    fclose(plik_wyjsciowy);
}

void ZapiszCzasySortowania(const char *nazwa_pliku, const char *algorytm, double czas_sortowania) {
    FILE *plik_wynikowy = fopen(nazwa_pliku, "a");

    if (plik_wynikowy == NULL) {
        printf("Błąd otwierania pliku.\n");
        return;
    }

    fprintf(plik_wynikowy, "Czas sortowania dla %s: %f sekundy\n", algorytm, czas_sortowania);

    fclose(plik_wynikowy);
}

//-----Funkcja sortowania bombelkowego----- []
void BubbleSort(int tab_a[], int a) {
	//for(int i=0; i<=9; i++)
	//	{
	//	printf("%d ", tab_a[i]);
	//		
	//	}
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

//-----Funkcja sortowania Quick Sort----- [DZIAŁA]
    // Funkcja zamieniająca elementy tablicy
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}
    // Funkcja partition do wybierania pivota i dzielenia tablicy
int Partition(int tab_c[], int low, int high) {
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
        int pivotIndex = Partition(tab_c, low, high);

        QuickSort(tab_c, low, pivotIndex - 1);
        QuickSort(tab_c, pivotIndex + 1, high);
    }
}

//-----Funkcja Selection Sort----- [DZIAŁA]
void SelectionSort(int tab_d[], int n) {
    int i, j, min_idx;

    // Przesuwa granicę nieposortowanej podtablicy jedna po drugiej
    for (i = 0; i < n - 1; i++) {
        // Znajdź najmniejszy element w nieposortowanej tablicy
        min_idx = i;

        for (j = i + 1; j < n; j++) {
            if (tab_d[j] < tab_d[min_idx]) {
                min_idx = j;
            }
        }

        // Zamień najmniejszy element z pierwszym elementem
        if (min_idx != i) {
            int temp = tab_d[min_idx];
            tab_d[min_idx] = tab_d[i];
            tab_d[i] = temp;
        }
    }
}

//-----Funkcja Comb Sort----- [DZIAŁA]
void swap2(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void CombSort(int tab_e[], int n) {
    int gap = n;  // Inicjalizacja odstępu jako rozmiar tablicy
    float shrink = 1.3;  // Współczynnik zmniejszania odstępu

    int swapped = 1;  // Zmienna flagowa do sprawdzania, czy nastąpiły zamiany

    while (gap > 1 || swapped) {
        // Oblicz nowy odstęp
        gap = (int)(gap / shrink);
        if (gap < 1) {
            gap = 1;
        }

        swapped = 0;  // Resetuj flagę zamiany

        // Porównaj elementy w odstępie i zamień je, jeśli to konieczne
        for (int i = 0; i < n - gap; i++) {
            if (tab_e[i] > tab_e[i + gap]) {
                // Zamień elementy
                int temp = tab_e[i];
                tab_e[i] = tab_e[i + gap];
                tab_e[i + gap] = temp;
                swapped = 1;  // Ustaw flagę zamiany
            }
        }
    }
}


int main() {
	FILE *plik = fopen("CzasySortowania.txt", "w"); // Otwarcie pliku w trybie zapisu (czyszczenie zawartości)

    if (plik == NULL) {
        printf("Błąd otwierania pliku.\n");
        return 1;
    }

    // Tutaj możesz wykonywać operacje zapisu do pliku
    //fprintf(plik, "Nowe wyniki\n");

    fclose(plik); // Zamykanie pliku (czyszczenie zawartości)
	bool kontynuuj = true;
	
	//system("chcp 65001");
	//setlocale(LC_ALL, "pl_PL.utf8");
while (kontynuuj) {
	
//------------------------------------------------------	
	system("cls");
	system("color 0a");
//	int liczba_liczb = 0;

	printf("Wprowadź ilość liczb: \n");
	scanf("%d", &liczba_liczb);
	
	int size = liczba_liczb;
	int tab[size];
	
//-----------------------------------------------------------
    Generuj(tab);
//-----------------------------------------------------------
    int tab_a[size];
    int tab_b[size];
    int tab_c[size];
    int tab_d[size];
    int tab_e[size];
//-----------------------------------------------------------
	for (int i = 0; i <= size; i++) {
        tab_a[i] = tab[i];
    }
    
    for (int i = 0; i <= size; i++) {
        tab_b[i] = tab[i];
    }
    
    for (int i = 0; i <= size; i++) {
        tab_c[i] = tab[i];
    }
    
    for (int i = 0; i <= size; i++) {
        tab_d[i] = tab[i];
    }
    
    for (int i = 0; i <= size; i++) {
        tab_e[i] = tab[i];
    }
//-----------------------------------------------------------
    int a = sizeof(tab_a) / sizeof(tab_a[0]);
    int b = sizeof(tab_b) / sizeof(tab_b[0]);
    int c = sizeof(tab_c) / sizeof(tab_c[0]);
    int d = sizeof(tab_d) / sizeof(tab_d[0]);
    int e = sizeof(tab_e) / sizeof(tab_e[0]);
//-----------------------------------------------------------
    
    

    
//--------------------------------------------------
    //SHELL SORT
    start = clock();
    ShellSort(tab_b, b);
    printf("\n\nShell Sorted array: \n");
    for (int i = 0; i < b; i++){
        printf("%d ", tab_b[i]);
    }
    end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("\nShell Sort Time: %f seconds\n", cpu_time_used);
    ZapiszWyniki("WynikShellSort.txt", tab_b, b, cpu_time_used);
    ZapiszCzasySortowania("CzasySortowania.txt", "Shell Sort", cpu_time_used);


//--------------------------------------------------
	//BUBBLE SORT
    start = clock();
    BubbleSort(tab_a, a);
    printf("\n");
    printf("Bubble Sorted array: \n");
    for (int i = 0; i < a; i++){
        printf("%d ", tab_a[i]);
    }
    end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("\nBubble Sort Time: %f seconds\n", cpu_time_used);
    ZapiszWyniki("WynikBubbleSort.txt", tab_a, a, cpu_time_used);
    ZapiszCzasySortowania("CzasySortowania.txt", "Bubble Sort", cpu_time_used);


//-------------------------------------------------- 
    //QUICK SORT
    start = clock();
    QuickSort(tab_c, 0, c-1);
    printf("\n\nQuick Sorted array: \n");
    for (int i = 0; i < b; i++){
        printf("%d ", tab_c[i]);
    }
    end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("\nQuickSort Time: %f seconds\n", cpu_time_used);
    ZapiszWyniki("WynikQuickSort.txt", tab_c, c, cpu_time_used);
    ZapiszCzasySortowania("CzasySortowania.txt", "Quick Sort", cpu_time_used);

//--------------------------------------------------
    //SELECTION SORT
    start = clock();
    SelectionSort(tab_d, d);
    printf("\n\nSelection Sorted array: \n");
    for (int i = 0; i < b; i++){
        printf("%d ", tab_d[i]);
    }
    end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("\nSelection Sort Time: %f seconds\n", cpu_time_used);
    ZapiszWyniki("WynikSelectionSort.txt", tab_d, d, cpu_time_used);
    ZapiszCzasySortowania("CzasySortowania.txt", "Selection Sort", cpu_time_used);

//--------------------------------------------------
    //COMB SORT
    start = clock();
    CombSort(tab_e, e);
    printf("\n\nComb Sorted array: \n");
    for (int i = 0; i < b; i++){
        printf("%d ", tab_e[i]);
    }
    end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("\nComb Sort Time: %f seconds\n", cpu_time_used);
    ZapiszWyniki("WynikCombSort.txt", tab_e, e, cpu_time_used);
    ZapiszCzasySortowania("CzasySortowania.txt", "Comb Sort", cpu_time_used);
    
//--------------------------------------------------
printf("\nCzy chcesz kontynuować (t/N)? ");
        char decyzja[10];
        scanf("%s", decyzja);
        
        if (strcmp(decyzja, "T") != 0 && strcmp(decyzja, "t") != 0) {
            kontynuuj = false;
        }
    }

return 0;
}
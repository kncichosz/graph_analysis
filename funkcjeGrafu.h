#pragma once
#include <iostream>
#include "Stos.h"

void merge(int* tab, int* tab2, int lewo, int srodek, int prawo) {


    int n1 = srodek - lewo + 1;
    int n2 = prawo - srodek;
    int m = 0, p = 0, k = lewo;
    int* L = new int[n1];
    int* R = new int[n2];
    int* L2 = new int[n1];
    int* R2 = new int[n2];

    for (int i = 0; i < n1; i++) {
        L[i] = tab[lewo + i];
        L2[i] = tab2[lewo + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = tab[srodek + 1 + j];
        R2[j] = tab2[srodek + 1 + j];
    }
 
    while (m < n1 && p < n2) {
        if (L[m] >= R[p]) {
            tab[k] = L[m];
            tab2[k] = L2[m];
            m++;
        }
        else {
            tab[k] = R[p];
            tab2[k] = R2[p];
            p++;
        }
        k++;
    }

    while (m < n1) {
        tab[k] = L[m];
        tab2[k] = L2[m];
        m++;
        k++;
    }

    while (p < n2) {
        tab[k] = R[p];
        tab2[k] = R2[p];
        p++;
        k++;
    }

    delete[] L;
    delete[] R;
    delete[] L2;
    delete[] R2;
}

void mergeSort(int* tab, int* tab2, int lewo, int prawo) {
    if (lewo < prawo) {
        int srodek = lewo + (prawo - lewo) / 2;

        mergeSort(tab, tab2, lewo, srodek);
        mergeSort(tab, tab2, srodek + 1, prawo);

        merge(tab, tab2, lewo, srodek, prawo);
    }
}

void ciagStopniowy(int* liczbaWieszcholkowTab, int* kolejnoscTab, int liczbaWieszcholkow) {

    mergeSort(liczbaWieszcholkowTab, kolejnoscTab, 0, liczbaWieszcholkow - 1);

    for (int i = 0; i < liczbaWieszcholkow; i++) {
        printf("%d ", liczbaWieszcholkowTab[i]);
    }
    printf("\n");
}

void dfs(int** graf, int* odwiedzone, int* liczbaSasiadow, int wierzcholek) {

    Stos stos;
    int sasiad;

    stos.push(wierzcholek);

    while (stos.czy_nie_pusta())
    {
        int obecny = stos.pop();

        odwiedzone[obecny] = 1;

        for (int i = 0; i < liczbaSasiadow[obecny]; i++) {

            sasiad = graf[obecny][i] - 1;

            if (!odwiedzone[sasiad]) {
                stos.push(sasiad);
            }
        }
    }
}

void liczbySkladoweSpojnosci(int** graf, int* liczbaSasiadow, int liczbaWieszcholkow) {
    int wynik = 0;
    int* odwiedzone = new int[liczbaWieszcholkow]();

    for (int i = 0; i < liczbaWieszcholkow; i++) {

        if (odwiedzone[i] == 0) {

            dfs(graf, odwiedzone, liczbaSasiadow, i);

            wynik++;
        }
    }

    printf("%d\n", wynik);
    delete[] odwiedzone;
}

void dopelnienieGrafu(const int& liczbaWieszcholkow, const long long int& sumaKrawedzi) {

    long long int maksimumKrawedzi = (((long long int)liczbaWieszcholkow - 1) * (long long int)liczbaWieszcholkow) / 2;
    long long int wynik = maksimumKrawedzi - sumaKrawedzi;

    printf("%lld\n", wynik);

}

void koloryWierzcholkowA(int** graf, int* liczbaSasiadow, int liczbaWieszcholkow) {

    int* kolory = new int[liczbaWieszcholkow]();
    int* koloryZajete = new int[liczbaWieszcholkow]();
    int kolor, sasiad;

    for (int i = 0; i < liczbaWieszcholkow; i++) {

        for (int j = 0; j < liczbaSasiadow[i]; j++) {

            sasiad = graf[i][j] - 1;

            if (kolory[sasiad] != 0) {
                koloryZajete[kolory[sasiad] - 1] = 1;
            }
        }

        kolor = 1;


        while (kolor < liczbaWieszcholkow && koloryZajete[kolor - 1]) {
            kolor++;
        }

        kolory[i] = kolor;

        for (int j = 0; j < liczbaSasiadow[i]; j++) {

            sasiad = graf[i][j] - 1;

            if (kolory[sasiad] != 0) {
                koloryZajete[kolory[sasiad] - 1] = 0;
            }
        }
    }

    for (int i = 0; i < liczbaWieszcholkow; i++) {
        printf("%d ", kolory[i]);
    }

    printf("\n");

    delete[] kolory;
    delete[] koloryZajete;
}

bool dfsDwudzielnoscGrafu(int** graf, int* stronaGrafu, int* liczbaSasiadow, int wierzcholek) {

    Stos stos;
    stos.push(wierzcholek);

    int obecny, obecnaStrona;

    while (stos.czy_nie_pusta()) {

        obecny = stos.pop();
        obecnaStrona = stronaGrafu[obecny];

        for (int i = 0; i < liczbaSasiadow[obecny]; i++) {

            int sasiad = graf[obecny][i] - 1;

            if (stronaGrafu[sasiad] == 0) {

                if (obecnaStrona == 1) {
                    stronaGrafu[sasiad] = 2;
                }
                else {
                    stronaGrafu[sasiad] = 1;
                }

                stos.push(sasiad);
            }
            else if (stronaGrafu[sasiad] == obecnaStrona) {
                return false;
            }
        }
    }
    return true;
}

void dwudzielnoscGrafu(int** graf, int* liczbaSasiadow, int liczbaWieszcholkow) {

    int* stronaGrafu = new int[liczbaWieszcholkow]();

    for (int i = 0; i < liczbaWieszcholkow; ++i) {

        if (stronaGrafu[i] == 0) {

            stronaGrafu[i] = 1;

            if (!dfsDwudzielnoscGrafu(graf, stronaGrafu, liczbaSasiadow, i)) {

                printf("F\n");
                delete[] stronaGrafu;
                return;
            }
        }
    }

    printf("T\n");
    delete[] stronaGrafu;
}

void koloryWierzcholkowB(int** graf, int* liczbaSasiadow, int* kolejnoscTab, int liczbaWieszcholkow) {

    int* kolory = new int[liczbaWieszcholkow]();
    int* koloryZajete = new int[liczbaWieszcholkow]();
    int kolor, sasiad;

    for (int i = 0; i < liczbaWieszcholkow; i++) {

        for (int j = 0; j < liczbaSasiadow[kolejnoscTab[i]]; j++) {

            sasiad = graf[kolejnoscTab[i]][j] - 1;

            if (kolory[sasiad] != 0) {
                koloryZajete[kolory[sasiad] - 1] = 1;
            }
        }

        kolor = 1;

        while (kolor <= liczbaWieszcholkow && koloryZajete[kolor - 1]) {
            kolor++;
        }

        kolory[kolejnoscTab[i]] = kolor;

        for (int j = 0; j < liczbaSasiadow[kolejnoscTab[i]]; j++) {

            sasiad = graf[kolejnoscTab[i]][j] - 1;

            if (kolory[sasiad] != 0) {
                koloryZajete[kolory[sasiad] - 1] = 0;
            }
        }
    }

    for (int i = 0; i < liczbaWieszcholkow; i++) {
        printf("%d ", kolory[i]);
    }
    printf("\n");

    delete[] kolory;
    delete[] koloryZajete;
}

void wczytywanieGrafu() {
    int liczba_grafow, liczbaWieszcholkow, liczbaSasiadow;
    long long int sumaKrawedzi = 0;
    std::cin >> liczba_grafow;

    for (int i = 0; i < liczba_grafow; i++) {

        std::cin >> liczbaWieszcholkow;

        sumaKrawedzi = 0;
        int* liczbaSasiadowTab = new int[liczbaWieszcholkow];
        int* liczbaSasiadowTab2 = new int[liczbaWieszcholkow];
        int* kolejnoscTab = new int[liczbaWieszcholkow];
        int** graf = new int* [liczbaWieszcholkow];

        for (int j = 0; j < liczbaWieszcholkow; j++) {

            std::cin >> liczbaSasiadow;

            sumaKrawedzi += liczbaSasiadow;
            liczbaSasiadowTab[j] = liczbaSasiadow;
            liczbaSasiadowTab2[j] = liczbaSasiadow;
            kolejnoscTab[j] = j;
            graf[j] = new int[liczbaSasiadow];

            for (int k = 0; k < liczbaSasiadow; k++) {
                std::cin >> graf[j][k];
            }
        }

        ciagStopniowy(liczbaSasiadowTab, kolejnoscTab, liczbaWieszcholkow);
        liczbySkladoweSpojnosci(graf, liczbaSasiadowTab2, liczbaWieszcholkow);
        dwudzielnoscGrafu(graf, liczbaSasiadowTab2, liczbaWieszcholkow);
        printf("?\n?\n");
        koloryWierzcholkowA(graf, liczbaSasiadowTab2, liczbaWieszcholkow);
        koloryWierzcholkowB(graf, liczbaSasiadowTab2, kolejnoscTab,liczbaWieszcholkow);
        printf("?\n?\n");
        dopelnienieGrafu(liczbaWieszcholkow, (sumaKrawedzi / 2));


        delete[] liczbaSasiadowTab;
        delete[] liczbaSasiadowTab2;
        delete[] kolejnoscTab;

        for (int j = 0; j < liczbaWieszcholkow; j++) {
            delete[] graf[j];
        }

        delete[] graf;
        
    }
}
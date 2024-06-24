#include "Stos.h"

Stos::Stos() : gora(nullptr) {}

void Stos::push(int liczba) {
    elementStruktury* nowy = new elementStruktury(liczba);
    if (gora == nullptr) {
        gora = nowy;
    }
    else {
        nowy->nastepny = gora;
        gora = nowy;
    }
}

int Stos::pop() {
    if (gora != nullptr) {
        int liczba = gora->liczba;
        elementStruktury* tmp = gora->nastepny;
        delete gora;
        gora = tmp;
        return liczba;
    }
    return -1;
}

bool Stos::czy_nie_pusta() const {
    return gora != nullptr;
}

Stos::~Stos() {
    while (gora != nullptr) {
        elementStruktury* tmp = gora->nastepny;
        delete gora;
        gora = tmp;
    }
}

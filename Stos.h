#pragma once
struct elementStruktury {
    int liczba;
    elementStruktury* nastepny;

    elementStruktury(int liczba = 0)
        :nastepny(nullptr), liczba(liczba) {
    }
};

class Stos {
    elementStruktury* gora;

public:
    Stos();
    void push(int liczba);
    int pop();
    bool czy_nie_pusta() const;
    ~Stos();
};


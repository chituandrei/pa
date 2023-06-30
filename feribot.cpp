#include <bits/stdc++.h>

using namespace std;

ifstream f("feribot.in");
ofstream g("feribot.out");

long int verifica_sol(vector<long> v, long int mij, int k, int n) {
    long int nrf = 1, total = 0;
    // Daca nu are loc o singura masina pe feribot
    // solutia nu este buna
    for (int i = 0; i < n; i++) {
        if (v[i] > mij)
            return -1;
        /* Daca am urcat nr maxim de masini pe feribot
           cresc numarul de feribot-uri si adaug v[i] pe feribotul viitor
           daca nu urc masina pe feribotul curent */
        if (total + v[i] > mij) {
            nrf++;
            total = v[i];
        } else {
            total += v[i];
        }
        // Daca nu mi-au ajuns feriboturile sa urc totate masinile returnez -1
        if (nrf > k) {
            return -1;
        }
    }
    // Returnez 1 daca am ajuns la final adica am urcat toate masinile
    return 1;
}
int main() {
    int n, k;
    long int sol = LLONG_MAX, in, sf, mij, maxim = 0;

    f >> n >> k;

    vector<long> v(n);

    for (int i = 0; i < n; i++)
        f >> v[i], maxim += v[i];

    // in este calculat daca as avea varianta minima
    // adica maxim / k pe fiecare feribot
    in = maxim / k + 1;
    // sf este maximul, daca am un singur feribot si urc toate masinile pe el.
    sf = maxim;

    // Cautare binare de la maxim / k + 1 -> maxim (Solutiile posibile)
    while (in <= sf) {
        // Aleg mijlocul
        mij = (in + sf) / 2;

        // Verific daca solutia este buna
        long val = verifica_sol(v, mij, k, n);

        /* Daca solutia a fost buna, iau minimul dintre solutia pe care
           am gasit-o si solutia pe care o aveam deja
           si caut alta solutie in stanga, adica o solutie mai mica
           daca nu merg in stanga, caut o solutie mai mare */
        if (val == 1) {
            sol = min(sol, mij);
            sf = mij - 1;
        } else {
            in = mij + 1;
        }
    }
    g << sol;
}

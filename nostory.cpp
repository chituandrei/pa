#include <bits/stdc++.h>

using namespace std;

int64_t SolveTask1(const vector<int>& a, const vector<int>& b) {
    long long sol = 0;
    vector<int> c;

    // Adaug toate elementele din a si b in vectorul c
    for (int i = 0; i < a.size(); i++) {
        c.push_back(a[i]);
        c.push_back(b[i]);
    }
    // sortez vectorul c
    sort(c.begin(), c.end());

    // iau ultimele n numere din vectorul c si le adun(am mutari nelimitate)
    for (int i = c.size() - 1; i >= c.size() - a.size(); i--)
        sol += c[i];

    return sol;
}

int64_t SolveTask2(const vector<int>& a, const vector<int>& b, int moves) {
    long long sol = 0;
    int apr[100005] = {
        0
    };
    vector<pair<int, int> > c;

    for (int i = 0; i < a.size(); i++) {
        c.push_back(make_pair(a[i], i));
        c.push_back(make_pair(b[i], i));
    }

    sort(c.begin(), c.end());

    // Pana aici am construit din nou vectorul c ca la subpunctul a)
    // iau un step care imi spune unde ma aflu exact in vectorul c)
    int step = c.size() - 1;
    int nr = 0;

    /* cat timp am miscari pe care le pot face, iar 
       nr simbolizeaza cate numere am adunat
       astfel nr trebuie sa fie diferit de n, nr numere pe care
       trebuie sa l gasesc 
       Apr simbolizeaza daca pozitia elemntului curent a fost
       sau nu adaugata Daca am 1 2 3 
                               4 5 6 si adaug 6, stiu ca pt
        a adauga 3 am nevoie sa fac o mutare deci tin cont
        de pozitie
       */

    while (moves > 0 && nr != a.size()) {
        // Daca elementul pe care l caut  apare
        // deci pozitia este deja adaugata scad miscarile
        if (apr[c[step].second] == 1)
            moves--;

        // Ma asigur ca acum cand adaug elementul
        // il bag si in vectorul de aparitii
        apr[c[step].second] = 1;

        // adaug la solutie maximul
        sol += c[step].first;

        // continui in vector si numarul de numere adaugate creste
        step--;
        nr++;
    }

    if (nr == a.size()) {
        return sol;
    } else {
        while (nr != a.size()) {
            if (apr[c[step].second] == 0) {
                nr++;
                sol += c[step].first;
            }
        apr[c[step].second] = 1;
        step--;
        }
    }

    return sol;
}

vector<int> ReadVector(istream& is, int size) {
    vector<int> vec(size);
    for (auto& num : vec) {
        is >> num;
    }
    return vec;
}

int main() {
    ifstream fin("nostory.in");
    ofstream fout("nostory.out");

    int task;
    fin >> task;

    int n, moves;

    if (task == 1) {
        fin >> n;
    } else {
        fin >> n >> moves;
    }

    auto a = ReadVector(fin, n);
    auto b = ReadVector(fin, n);

    auto res = task == 1 ? SolveTask1(a, b) : SolveTask2(a, b, moves);
    fout << res << "\n";

    return 0;
}

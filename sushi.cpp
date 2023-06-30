#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int task1(int n, int m, int x, vector<int>& p, vector<vector<int> >& g) {
    int k = n * x;
    vector<vector<int> > dp(m + 1, vector<int>(k + 1, 0));
    vector<int> grades(m + 1);
    /* Calculez grades adica vectorul care imi spune
       Cat castig cand adaug un obiect iar p simbolizeaza
       greutatea unui obiect deci avem de rezolvat problema
       rucsacului */
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            grades[i] += g[j][i];

    for (int i = 1; i <= m; ++i) {
        for (int j = 0; j <= k; ++j) {
            dp[i][j] = dp[i - 1][j];
            // in dp[i][j] retin maximul
            // vad daca pot sa adaug obiectul daca greutatea lui
            // nu depaseste
            if (j - p[i - 1] >= 0) {
                // si iau maximul anterior daca il pot adauga si adaug
                // valoarea din grades care simbolizeaza castigul
                dp[i][j] = max(dp[i][j], dp[i - 1][j - p[i - 1]]
				+ grades[i - 1]);
			}
		}
    }
    return dp[m][k];
}

int task2(int n, int m, int x, vector<int>& p, vector<vector<int> >& g) {
    int k = n * x;
    vector<vector<int> > dp(m + 1, vector<int>(k + 1, 0));
    vector<int> grades(m + 1);

    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            grades[i] += g[j][i];

    for (int i = 1; i <= m; ++i) {
        for (int j = 0; j <= k; ++j) {
            dp[i][j] = dp[i - 1][j];

            /* acelasi algoritm ca la primul task doar ca acum avem
               un if in plus sa vedem daca ar fi mai bine
               sa adaugam de 2 ori obiectul curent
               oricum iau maximul dintre ele deci daca 
               nu ar fi mai bine max() nu ar schimba valoarea
               dp[i][j] */
            if (j - p[i - 1] >= 0) {
                dp[i][j] = max(dp[i][j], dp[i - 1][j - p[i - 1]]
				+ grades[i - 1]);
			}

            if (j - 2 * p[i - 1] >= 0) {
                dp[i][j] = max(dp[i][j], dp[i - 1][j - 2 * p[i - 1]]
				+ 2 * grades[i - 1]);
			}
        }
    }
    return dp[m][k];
}

int task3(int n, int m, int x, vector<int>& p, vector<vector<int> >& g) {
    int k = n * x;
    vector<vector<vector<int> > > dp(m + 1,
		vector<vector<int> >(k + 1, vector<int>(n + 1, 0)));
    vector<int> grades(m + 1);

    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            grades[i] += g[j][i];
    /*
        Pastram algoritmul de la task2 si adaugam o noua dimensiune in matrice
        Dimensiunea t ne spune cate obiecte avem in "rucsac" . La pozitia [m][k][1]
        avem maximul care se poate obtine cu 1 element ales
    */
    for (int i = 1; i <= m; ++i) {
        for (int j = 0; j <= k; ++j)
            for (int t = 1; t <= n; t++) {
                /* 
                 facem un for in plus deci complexitatea creste
                 adica pentru fiecare solutie calculata calculam cu cate obiecte
                 se poate obtine
                */

                // luam maximul precedent
                dp[i][j][t] = dp[i - 1][j][t];

                /* 
                  daca pot sa adaug obiectul i-1
                  fac acelasi lucru ca la 2, dar vreau sa iau maximul
                  dintre dimensiunea rucsacului - 1 pentru ca nu am acel obiect adaugat
                */ 
                if (j - p[i - 1] >= 0) {
                    dp[i][j][t] = max(dp[i][j][t],
					dp[i - 1][j - p[i - 1]][t - 1]
					+ grades[i - 1]);
				}
                /* 
                  daca pot sa adaug obiectul i-1 de doua ori
                  fac acelasi lucru ca la 2, dar  vreau sa iau maximul
                  dintre dimensiunea rucsacului - 2 pentru ca nu am acele obiecte adaugate
                  am o conditie in plus sa nu ies din vector adica daca vreau o solutie
                  cu un singur "element" in rucsac, nu pot adauga 2 elemente
                */ 
                if (j - 2 * p[i - 1] >= 0 && t >= 2) {
                    dp[i][j][t] = max(dp[i][j][t],
					dp[i - 1][j - 2 * p[i - 1]][t - 2]
					+ 2 * grades[i - 1]);
				}
            }
    }
    return dp[m][k][n];
}

int main() {
    freopen("sushi.in", "r", stdin);
    freopen("sushi.out", "w", stdout);

    int task, n, m, x;

    vector<int> prices;
    vector<vector<int> > grades;

    cin >> task;
    cin >> n >> m >> x;

    prices.assign(m, 0);
    grades.assign(n, vector<int>(m, 0));

    for (int i = 0; i < m; ++i) {
        cin >> prices[i];
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> grades[i][j];
        }
    }

    int ans = -1;

    switch (task) {
    case 1:
        ans = task1(n, m, x, prices, grades);
        break;
    case 2:
        ans = task2(n, m, x, prices, grades);
        break;
    case 3:
        ans = task3(n, m, x, prices, grades);
        break;
    default:
        cout << "wrong task number" << endl;
    }

    cout << ans << endl;

    return 0;
}

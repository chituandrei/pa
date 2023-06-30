#include <bits/stdc++.h>

using namespace std;

const int MOD = 1000000007;

int type1(int x, int y) {
	x++;
	vector<vector<int>> m(x+2, vector<int>(y+2, 0));
    /*
        Calculez combinari de x+1 luate cate y.
        Am format o matrice pe foaie si am observat ca pot face
        o matrice si linia anterioara imi da rezultatul pentru linia 
        actuala, asa ca am descoperit recurenta m[i][j] = m[i-1][j]
        + m[i-1][j-1]
    */
    for (int i = 0; i <= x; i++)
        m[i][1] = 1;

    for (int i = 2; i <= x+1; i++)
        for (int j = 2; j <= y+1; j++)
            m[i][j] = (m[i-1][j] % MOD + m[i-1][j-1] % MOD) % MOD;

    return m[x+1][y+1];
}

int type2(int x, int y) {
	vector<vector<long long>> m(x+2, vector<long long>(y+2, 0));

	for (int i = 1; i <= x+1; i++)
		m[i][1] = 1;

	for (int i = 1; i <= x+1; i++)
		m[i][2] = i;

	m[1][3] = 1;

    /*
        Am generat cu backtrack toate posibilitatile si am observat aceeasi recurenta
        ca la task 1 doar ca vreau sa iau in calcul 3 elemente de pe linia precedenta
    */
    for (int i = 2; i <= x+1; i++)
        for (int j = 3; j <= y+1; j++)
            m[i][j] = (m[i-1][j] % MOD + m[i-1][j-1] % MOD +
					   m[i-1][j-2] % MOD) % MOD;

	return m[x+1][y+1];
}


int main() {
    freopen("semnale.in", "r", stdin);
    freopen("semnale.out", "w", stdout);

    int sig_type, x, y;

    cin >> sig_type >> x >> y;

    switch (sig_type) {
    case 1:
        cout << type1(x, y);
        break;
    case 2:
        cout << type2(x, y);
        break;
    default:
        cout << "wrong task number" << endl;
    }

    return 0;
}

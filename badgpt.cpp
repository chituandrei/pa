#include <bits/stdc++.h>

using namespace std;

const int MODULO = 1000000007;

void fibonacci(unsigned long long m[2][2], unsigned long long n) {
  if (n == 1)
    return;
  /*
    calculez fibonacci de n
  */
  unsigned long long x, y, z, t;
  /*
     copia matricei m am nevoie de ea pt cazul 
     in care am de ridicat la putere impara
  */
  int cm[2][2];

  cm[0][0] = 1;
  cm[0][1] = 1;
  cm[1][0] = 1;
  cm[1][1] = 0;
  /*
   merg recursiv din n/2 in n/2 pt a avea complexitate logaritmica
   adica daca am de calculat m la a 9 a calculez m la a 4-a * m la a 4 a * cm si merg recursiv 
   pe m la a 4 a in m la a 2-a * m la a 2 a
  */
  fibonacci(m, n / 2);

  // inmultesc matricele ca sa calez m * m
  x = m[0][0] * m[0][0] % MODULO + m[0][1] * m[1][0] % MODULO;
  y = m[0][0] * m[0][1] % MODULO + m[0][1] * m[1][1] % MODULO;
  z = m[1][0] * m[0][0] % MODULO + m[1][1] * m[1][0] % MODULO;
  t = m[1][0] * m[0][1] % MODULO + m[1][1] * m[1][1] % MODULO;
  m[0][0] = x;
  m[0][1] = y;
  m[1][0] = z;
  m[1][1] = t;

  // daca am cazul pe impar trebuie sa mai inmultsc
  // cu copia matricei initiale a lui m
  if (n % 2 == 1) {
    x = m[0][0] * cm[0][0] % MODULO + m[0][1] * cm[1][0] % MODULO;
    y = m[0][0] * cm[0][1] % MODULO + m[0][1] * cm[1][1] % MODULO;
    z = m[1][0] * cm[0][0] % MODULO + m[1][1] * cm[1][0] % MODULO;
    t = m[1][0] * cm[0][1] % MODULO + m[1][1] * cm[1][1] % MODULO;
    m[0][0] = x;
    m[0][1] = y;
    m[1][0] = z;
    m[1][1] = t;
  }
}

int main() {
  ifstream f("badgpt.in");
  ofstream g("badgpt.out");

  char c;
  unsigned long long nr, sol = 1;
  unsigned long long m[2][2];

  // citesc doar caracterele u si n si inmultesc rezulatele in modulo
  // celelalte caractere nu ma intereseaza
  while (f >> c >> nr)
    if ((c == 'u' || c == 'n') && nr != 1) {
      m[0][0] = 1;
      m[0][1] = 1;
      m[1][0] = 1;
      m[1][1] = 0;

      fibonacci(m, nr);
      sol = sol * m[0][0] % MODULO;
    }

  g << sol;

  f.close();
  g.close();
}

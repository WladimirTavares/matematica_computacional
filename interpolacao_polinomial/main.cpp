#include "interpolacao.h"
#include <iostream>
using namespace std;

int main()
{
  int n;
  vector <t_ponto> pontos;

  cin >> n;

  for(int i = 0; i < n; i++){
    t_ponto p;
    cin >> p.x >> p.y;
    cout << p.x << p.y << endl;

    pontos.push_back(p);
  }

  vector <LD> coef = vandermonde_coeficiente(pontos);

  for(int i = 0; i < n; i++){
    cout << fixed << setprecision(10) <<  poly_eval(coef, pontos[i].x) << endl;
  }
}

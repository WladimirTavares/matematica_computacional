#include <iostream>
#include <vector>
#include <algorithm>
#include "Matriz.h"

typedef struct {
  LD x, y;
} t_ponto;


vector <LD> vandermonde_coeficiente(vector <t_ponto> pontos){

  int n = pontos.size();

  MATRIX M(n,n);

  vector <LD> b;

  b.resize(n);

  for(int i = 0; i < n; i++){
    for(int j = 0; j < n; j++){
      double x = pontos[i].x;
      M[i][j] = pow(x, j);
    }
  }

  for(int i = 0; i < n; i++){
    b[i] = pontos[i].y;
  }

  M.show();

  vector <LD> coef = solve(M, b);

  for(int i = 0; i < n; i++)
    cout << "x[" << i << "] = " << coef[i] << endl;


  return coef;


}


LD poly_eval( vector <LD> coef, LD x){
  LD res = coef[coef.size() - 1];
  for(int i = coef.size() - 2; i >= 0; i--){
    res = res*x;
    res = res+coef[i];
  }
  return res;
}


LD L(vector <t_ponto> pontos, int i, LD x);
LD Lagrange(vector <t_ponto> pontos, LD x);
//LD Newton(vector <t_ponto> pontos, LD x);



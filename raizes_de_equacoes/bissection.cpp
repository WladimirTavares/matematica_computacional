#include <iostream>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <limits.h>
#include <queue>
#include <vector>
#pragma argsused
#define INFO

using namespace std;

double f1(double x){
  return 2*x - cos(x);
}

double _f1(double x){
  return 2 + sin(x);
}

double f2(double x){
  return pow(x,3) - 9*x + 3;
}

double _f2(double x){
  return 3*pow(x,2) - 9;
}

double f3(double x){
  return 2*pow(x,3) - 4*pow(x,2) + 3*x;
}

double _f3(double x){
  return 6*pow(x,2) - 8*x + 3;
}


double f4(double x){
  return pow(x,3) - x - 2;
}

double _f4(double x){
  return 3*pow(x,2) - 1;
}

double f5(double x){
  return pow(x,5) - 10*pow(x,4) + 40*pow(x,3) - 80*pow(x,2) + 80*x- 30;
}

double _f5(double x){
  return 5*pow(x,4) - 40*pow(x,3) + 120*pow(x,2) - 160*x + 80;
}


typedef struct {
  double x;
  int num_iter;
  double a,b;
  double erro;
}t_info;


void print_info(t_info info){
  cout << "x             = " << info.x << endl;
  cout << "iterations    = " << info.num_iter << endl;
  cout << "Intervalo     = (" << info.a << "," << info.b << ")" <<endl;
  cout << "Erro absoluto = " << info.erro << endl;
}


void imprimelinhabissecao(int k,
                          double a,
                          double b,
                          double xk,
                          double (*f)(double)
                          ){
   printf("%3d %8.5f %8.5f %8.5f %8.5f %8.5f\n",
          k, a, b, xk, f(xk), b - a);
}


t_info bissecao(double a,
                double b,
                double epsilon,
                int itermax,
                double (*f)(double)
                ){
   t_info info;
   int k;
   double xk;


   #ifdef INFO
   printf("Resolucao pelo Metodo da Bissecao \n");
   printf("-------------------------------------------------\n");
   printf("%3s %8s %8s %8s %8s %8s\n", "k" , "ak", "bk", "xk", "f(xk)", "bk-ak");
   printf("-------------------------------------------------\n");
   #endif

   k = 0;
   xk = (a + b)/2;
   imprimelinhabissecao(k, a, b, xk, f);
   while (1){
     if( (b - a < epsilon) || (fabs(f(xk)) < epsilon)  || (k > itermax) ) break;

     if (f(a) * f(xk) < 0){
        b = xk;
     }
     else{
        a = xk;
     }
     xk = (a + b)/2;
     k = k + 1;
     #ifdef INFO
     imprimelinhabissecao(k, a, b, xk, f);
     #endif'
   }


   info.x         = xk;
   info.num_iter  = k;
   info.a         = a;
   info.b         = b;
   info.erro      = f(xk);

   return info;
}



vector < pair<double,double> > isolating(double (*f)(double),
               double  s,
               double  t,
               double passo
               ){
  double xant, xprox;
  vector < pair<double,double> > roots;


  xant = s;
  while( xant < t){
    xprox = xant + passo;
    //cout << "(" << xant <<" , " << xprox << ")" << endl;
    if( f(xant)*f(xprox) < 0){
      roots.push_back( make_pair(xant, xprox) );
    }
    xant = xprox;
  }

  return roots;


}



int main(int argc, char* argv[])
{
    double a, b, delta, epsilon, x;
    int max_iter;
    double (*f)(double);
    double (*_f)(double);



    int opcao;
    while(1){
      cout << "Escolha a funcao =" << endl;
      cout << "1 - f(x) = 2x - cos(x)" << endl ;
      cout << "2 - f(x) = x^3 - 9x + 3" << endl;
      cout << "3 - f(x) = 2x^3 - 4x^2 + 3x" << endl;
      cout << "4 - f(x) = x^3 - x - 2" << endl;
      cout << "5 - f(x) = x^5 - 10 x^4 + 40x^3 - 80x^2 + 80x - 30" << endl;

      cout << "Opcao : ";
      cin >> opcao;

      bool valida = false;
      for(int i = 1; i <= 5; i++){
        if( opcao == i){
          valida = true;
        }
      }
      if(valida) break;
    }

    switch(opcao){
      case 1: f = f1; _f = _f1; break;
      case 2: f = f2; _f = _f2; break;
      case 3: f = f3; _f = _f3; break;
      case 4: f = f4; _f = _f4; break;
      case 5: f = f5; _f = _f5; break;
    }


    do{
      cout << "Fase de Isolamento:" << endl;
      cout << "1 - sim" << endl ;
      cout << "2 - nao" << endl;
      cout << "Opcao: ";
      cin >> opcao;
      if( opcao != 1 && opcao != 2){
        cout << "Opcao invalida" << endl;
      }
    }while(opcao != 1 && opcao != 2);

    if(opcao==1){
      vector < pair<double,double> > roots;
      do{
        cout << "Fase de isolamento " << endl;
        cout << "limite inferior = ";
        cin  >> a;
        cout << "limite superior = ";
        cin  >> b;
        cout << "passo = ";
        cin >> delta;


        roots = isolating(f, a, b, delta);

        cout << "intervalos das raizes" << endl;
        for(int i = 0; i < roots.size(); i++){
          cout << "(" << roots[i].first << "," << roots[i].second << ")" << endl;
        }
      }while( roots.size() == 0 );
    }

    cout << "Entre com o extremo esquerdo do intervalo = ";
    cin >> a;
    cout << "Entre com o extremo direito do intervalo = ";
    cin >> b;
    if( f(a) * f(b) < 0 ){
      cout << "Entre com a precisao requerida = ";
      cin >> epsilon;
      cout << "Entre com o numero de maximo de iteracoes = ";
      cin >> max_iter;
      t_info info;
      info = bissecao(a, b, epsilon, max_iter, f);
      cout << "Resolucao pelo Metodo da Bissecao" << endl;
      print_info(info);
      cout << endl << endl;
    }else{
      cout << "Intervalo invalido" << endl;
    }

    return 0;
}




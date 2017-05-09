#define MATRIZ_H_INCLUDED

#include <math.h> // fabs
#include <iostream> // std:: cin,cout,fixed
#include <iomanip> // std::setprecision
#include <vector>

using namespace std;

typedef double LD;

const LD EPS = 1e-8;

class MATRIX
{
 private:
    vector< vector<LD> > a;

 public:
    int n,m;
    bool falha;
    MATRIX(int x, int y, LD v=0.0);
    LD Gauss();
    vector<LD> operator*(vector<LD> v);
    MATRIX operator*(MATRIX M1);
    vector<LD>& operator [](int i) { return a[i]; }
    void show();

};

LD det(MATRIX &M);
vector <LD> solve(MATRIX& M, vector<LD> b);



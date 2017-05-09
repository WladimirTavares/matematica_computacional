#include <math.h> // fabs
#include <iostream> // std:: cin,cout,fixed
#include <iomanip> // std::setprecision
#include <vector>
#include "Matriz.h"
using namespace std;

MATRIX:: MATRIX(int x, int y, LD v)
{
    n=x;
    m=y;
    a.resize(n);
    for(int i=0; i<n; i++)
        a[i].resize(m, v);
}

LD MATRIX::Gauss()
{
    LD det=1.0;

    falha = false;

    for(int i=0;i<n;i++){

        if( fabs(a[i][i]) < EPS ){
            n = 0;
            return -1;
        }

        det*=a[i][i];

        for(int j=i+1; j<n; j++){
            LD r = a[j][i]/a[i][i];

            for(int k=i; k<m; k++){
                a[j][k]= a[j][k] - r*a[i][k];
            }

        }

    }

    return det;
}

// assume v is of size m
vector<LD> MATRIX::operator*(vector<LD> v)
{
    vector<LD> rv(n, 0.0);
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            rv[i]+=a[i][j]*v[j];
    return rv;
}


MATRIX MATRIX::operator*(MATRIX M1)
{
    MATRIX R(n, M1.m);
    for(int i=0;i<n;i++)
        for(int j=0;j<M1.m;j++)
            for(int k=0;k<m;k++)
                R.a[i][j]+=a[i][k]*M1.a[k][j];
    return R;
}

void MATRIX::show()
{
    cout << "MATRIX = " << endl;
    cout << "[" << endl;
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            LD elem = a[i][j];
            cout << fixed << setprecision(5) << elem << " ";
        }
        cout << endl;
    }
    cout << "]" << endl;
}

LD det(MATRIX &M)
{
    MATRIX M1=M;

    LD r=M1.Gauss();

    if(M1.n==0)
        return 0.0;

    return r;
}



vector <LD> solve(MATRIX& M, vector<LD> b){
 int n = M.n, m = M.m;
 MATRIX T(n,m+1);


 for(int i=0;i<n;i++)
    for(int j=0;j<n;j++)
        T[i][j]=M[i][j];

 for(int i=0;i<n;i++)
    T[i][n] = b[i];

 T.Gauss();

 T.show();

 vector <LD> x;

 x.resize(M.n);

 for(int i = T.n-1; i >= 0; i--)
 {
   x[i] = T[i][M.n];

   for(int j = i+1; j < T.n; j++){
    x[i] -= T[i][j]*x[j];
   }

   if( fabs(T[i][i]) > EPS )
        x[i] /= T[i][i];
   else
        x.clear();
 }

 return x;

}




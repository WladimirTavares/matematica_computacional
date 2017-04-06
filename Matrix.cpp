#include <math.h> // fabs
#include <iostream> // std:: cin,cout,fixed
#include <iomanip> // std::setprecision
#include <vector>

using namespace std;

typedef long double LD;
LD EPS = 1e-8;

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

    //Transforma em uma matriz triangular superior
    //LD GaussParcialPivot();
    //Transforma em uma matriz diagonal
    //LD GaussJordan();
    //Transforma na matriz inversa
    //int inversa();



};



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
        if( a[i][i] < EPS ){
            falha = true;
            return -1;
        }
        det*=a[i][i];

        for(int j=i+1; j<n; j++){
            LD r = a[j][i]/a[i][i];

            for(int k=i; k<m; k++){
                a[j][k]= a[j][k] - r*a[i][k];
            }

        }

        //cout << "Passo " << i+1 << endl;
        //show();

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

// compute the determinant of M
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




int main(){
    int n,m;

    cin >> n >> m;

    MATRIX M(n,m);

    vector <LD> b;

    b.resize(n);

    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            cin >> M[i][j];

    for(int i = 0; i < n; i++)
        cin >> b[i];

    M.show();

    vector <LD> x = solve(M, b);

    for(int i = 0; i < n; i++)
        cout << "x[" << i << "] = " << x[i] << endl;




}

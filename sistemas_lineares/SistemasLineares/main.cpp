#include "Matriz.h"
#include <iostream>

using namespace std;

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

    return 0;


}

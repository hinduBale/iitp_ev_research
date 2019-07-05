#include<bits/stdc++.h>
#include <fstream>

using namespace std;

int main()
{
    int nodes, edges, a, b, weight, i = 0;
    int A[100], B[100], W[100];
    ifstream ifile;
    ifile.open("graph_input.txt");
    ifile >> nodes >> edges;
    while(!(ifile.eof()))
    {
        ifile >> a >> b >> weight;
        A[i] = a;
        B[i] = b;
        W[i] = weight;
        ++i;
    }
    for(int i = 0; i < edges; i++)
        cout << A[i] << " " << B[i] << " " << W[i] << endl;
    return 0;
}

#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip> 

using namespace std;

struct programer{
    int kval;
    int plata;
    double odnos;
};

double sortiraj(const vector<programer> &a, int pocetak, int kraj){
    double max = 0;
    for(int i = pocetak; i <= kraj; i++){
        if (a[i].odnos > max)max = a[i].odnos;
    }
    //cout << "Max je: " << max << '\n';
    return max;
}

int main(){

    int n; cin >> n;
    vector<programer>a(n);
    
    for(int i = 0; i < n; i++){
        int k, p; cin >> k >> p; 
        a[i].kval = k; a[i].plata = p; a[i].odnos = (double)p / k;
    }

    int k; cin >> k;
    
    sort(a.begin(), a.end(), [](programer b, programer c){
        return b.odnos < c.odnos;
    });

    //for(int i = 0; i < a.size(); i++)
       // cout << fixed << setprecision(2) << a[i].odnos << " ";

    //cout << "\n";

    vector<double>b(n, 0);
    for(int i = 0; i <= n-k; i++){
        for(int j = i; j < i+k; j++){b[i] += a[j].kval;}
        //cout << "B[i] je: " << b[i] << '\n';
        //cout << "Max je: " << sortiraj(a, i, i+(k-1)) << '\n';
        b[i] = b[i] * sortiraj(a, i, i+(k-1));
        //cout << "B[i] je: " << b[i] << '\n';
        //if (b[i] == 0)b.erase(b.begin() + i);
    }


    //make_heap(b.begin(), b.end());
    //sort_heap(b.begin(), b.begin() + k);
    sort(b.begin(), b.begin() + k);

    //while(b[0] == 0)b.erase(b.begin());    

    //cout << "B vektor: " << '\n';
    for(int i = 0; i < b.size(); i++)
        cout << fixed << setprecision(2) << b[i] << " ";
    //cout << fixed << setprecision(2) << b[0];

}
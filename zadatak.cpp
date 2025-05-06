#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip> 
#include <queue>

using namespace std;

struct programer{
    int kval;
    int plata;
    double odnos;
};

double sortiraj(const vector<programer> &a, int pocetak, int kraj){ //Trazimo najveci odnos od i do k i vracamo taj odnos
    double max = 0;
    for(int i = pocetak; i <= kraj; i++){
        if (a[i].odnos > max)max = a[i].odnos;
    }
    
    return max;
}

int main(){

    int n; cin >> n; //Broj prijavljenih
    vector<programer>a(n);
    
    for(int i = 0; i < n; i++){
        int k, p; cin >> k >> p; 
        a[i].kval = k; a[i].plata = p; a[i].odnos = (double)p / k;
    }

    int k; cin >> k; //Broj koji firma zeli da zaposli
    
    sort(a.begin(), a.end(), [](programer b, programer c){ //Sortiramo po rastucem odnosu
        return b.odnos < c.odnos;
    });

    priority_queue<double, vector<double>, greater<double>> pq; //Pravimo red sa prioritetom koji ce redjati po rastucem redosledu
    double sum = 0;

    for(int i = 0; i <= n-k; i++){
        for(int j = i; j < i+k; j++){sum += a[j].kval;} //Racunamo sumu kvaliteta od i do k
        sum = sum * sortiraj(a, i, i+(k-1)); //Mnozimo sumu sa najveci odnos od programera izmedju i i k pozicije
        pq.push(sum); sum = 0; //Ubacujemo konacnu sumu u red sa prioritetom i vracamo sumu na 0 za sledece racunanje
    }

    cout << fixed << setprecision(2) << pq.top(); //Ispisujemo vrh pq-a koji sadrzi nase konacno resenje


}
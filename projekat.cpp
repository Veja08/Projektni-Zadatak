#include <iostream>
#include <raylib.h>
#include <vector>

using namespace std;

#define sirina 7
#define visina 7

struct polje{
    int x;
    int y;
    int vrednost;
    bool posecen = false;
};

vector<vector<polje>> mapa(visina, vector<polje>(sirina));
vector<vector<int>>memo(visina, vector<int>(sirina, -1));

int iX = 85; int iY = 50;
int red = 0; int kolona = 0; int sum = 0;
bool stop = false;
vector<char> direkcije;

void ispisi_mapu(){

    for(int i = 0; i < visina; i++){
        for(int j = 0; j < sirina; j++){
            cout << mapa[i][j].vrednost << " ";}
        cout << "\n";}
}
/*
void popuni_polja_u_mapi(int i, int j){
    int broj = rand() % 101;
    cout << i << " " <<  j << '\n';
    if (j >= sirina-1){mapa[i][j] = broj; popuni_polja_u_mapi(i+1, 0);}
    if (i >= visina-1)return;
    mapa[i][j] = broj;
    popuni_polja_u_mapi(i, j+1);
}
*/

void popuni_polja_u_mapi(){
    for(int i = 0; i < visina; i++){
        for(int j = 0; j < sirina; j++){
            
            int broj = rand() % 100 + 1;
            mapa[i][j].vrednost = broj;
        }
    }

}

int najzbir(int n, int r, int k) {
    // vec izracunato
    if ( memo[r][k] != -1 ){
        return memo[r][k]; }
    // nije izracunato...
    // cilj?
    if ( r == 0 && k == 0 )
        return memo[0][0] = mapa[0][0].vrednost;
    // gore ili levo?
    int gore = 0, levo = 0;
    // moze li gore?
    if ( r > 0 ){gore = mapa[r][k].vrednost + najzbir(n, r - 1, k); 
    }
    // moze li levo?
    if ( k > 0 ){levo = mapa[r][k].vrednost + najzbir(n, r, k - 1);
    }
    // prvi red?
    if ( r == 0) return memo[0][k] = levo;
    // prva kolona?
    if ( k == 0 ) return memo[r][0] = gore;

    return memo[r][k] = max( gore, levo);

}

void rekonstruisi_put(int r, int k) {
    if (r == 0 && k == 0) return;

    if (r > 0 && memo[r][k] == mapa[r][k].vrednost + memo[r-1][k]) {
        rekonstruisi_put(r - 1, k);
        direkcije.push_back('D'); // Dole
    }
    else if (k > 0 && memo[r][k] == mapa[r][k].vrednost + memo[r][k-1]) {
        rekonstruisi_put(r, k - 1);
        direkcije.push_back('R'); // Desno
    }
}

void napravi_prozor(){
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Lov Na Blago");

    SetTargetFPS(60);
    SetWindowIcon(LoadImage("assets/mediteran.png"));

}

int main(){

    srand(time(0));
    popuni_polja_u_mapi();
    ispisi_mapu();
    napravi_prozor();
    cout << "Najbolji put iznosi: " << najzbir(visina, visina-1, visina-1) << '\n';
    rekonstruisi_put(visina-1, visina-1);
    cout << "Velicina vektora je: " << direkcije.size() << '\n';
    for(int i = 0; i < direkcije.size(); i++)cout << char(direkcije[i]) << " ";
    cout << '\n';
    
    while (!WindowShouldClose() && !stop) {
        if (IsKeyPressed(KEY_RIGHT) && iX < 685){iX += 100; kolona++;}
        else if (IsKeyPressed(KEY_DOWN) && iY < 500){iY += 75; red++;}
        if (mapa[red][kolona].posecen == false){sum += mapa[red][kolona].vrednost; mapa[red][kolona].posecen = true;}
        BeginDrawing();
        ClearBackground(RAYWHITE);
        for(int i = 0; i < visina; i++){
            for(int j = 0; j < sirina; j++){
                DrawRectangle(85 + (100 * i), 50 + (75 * j), 40, 40, RED);
                mapa[i][j].x = 85 + (100 * i); mapa[i][j].y = 50 + (75 * j);
                DrawText(TextFormat("%i", mapa[j][i].vrednost), 95 + (100 * i), 60 + (75 * j), 20, BLACK);
            }
        }
        DrawText(TextFormat("%i", sum), 10, 10, 20, BLACK);
        
        DrawCircle(iX, iY, 10, BLUE);
        EndDrawing();
        if (iX >= 685 && iY >= 500)stop = true;
        
    }
    cout << "Van while" << '\n';
    int lX = 85; int lY = 50;
    while(!direkcije.empty())
    {
        BeginDrawing();
        if(direkcije[0] == 'R'){
            DrawLine(lX, lY, lX + 100, lY, GREEN);
            lX += 100;
        }
        else if(direkcije[0] == 'D'){
            DrawLine(lX, lY, lX, lY + 50, GREEN);
            lY += 50;
        }
        direkcije.erase(direkcije.begin());
        EndDrawing();
        WaitTime(2.0);

    }
    CloseWindow();
    /*
    for(int i = 0; i < visina; i++){
            for(int j = 0; j < sirina; j++){
                cout << i << " " << j << ": " << mapa[i][j].x << " " << mapa[i][j].y << '\n'; 
            }}
    */
    return 0;
    
}
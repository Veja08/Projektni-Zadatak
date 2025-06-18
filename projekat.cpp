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
int lX = 85; int lY = 50;
int maxSum = 0;
vector<char> direkcije;

void ispisi_mapu(){
    for(int i = 0; i < visina; i++){
        for(int j = 0; j < sirina; j++){
            cout << mapa[i][j].vrednost << " ";}
        cout << "\n";}
}


void popuni_polja_u_mapi(){
    for(int i = 0; i < visina; i++){
        for(int j = 0; j < sirina; j++){
            int broj = rand() % 100 + 1; //Nasumicno izabran broj od 1 do 100, koji se skladisti u matricu "mapa" na ij poziciji
            mapa[i][j].vrednost = broj;
        }
    }

}

int najzbir(int n, int r, int k) { //Funkcija koja racuna vrednost najboljeg puta kroz koji moze da se prodje
    
    if ( memo[r][k] != -1 ){
        return memo[r][k]; }

    if ( r == 0 && k == 0 )
        return memo[0][0] = mapa[0][0].vrednost;
    
    int gore = 0, levo = 0;
    
    if ( r > 0 ){gore = mapa[r][k].vrednost + najzbir(n, r - 1, k); 
    }
    if ( k > 0 ){levo = mapa[r][k].vrednost + najzbir(n, r, k - 1);
    }
    
    if ( r == 0) return memo[0][k] = levo;
    if ( k == 0 ) return memo[r][0] = gore;

    return memo[r][k] = max( gore, levo);

}

void rekonstruisi_put(int r, int k) { //Funkcija koja ide kroz memo niz i pamti putanju tako sto skladisti u vektor "direkcije" D, ako se islo na dole, ili R, ako se islo desno
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

void napravi_prozor(){ //Funkcija koja pravi prozor
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Lov Na Blago");

    SetTargetFPS(60);
    SetWindowIcon(LoadImage("assets/mediteran.png"));

}

int main(){

    srand(time(0)); //Ovo pisemo kako bi svaki put kad se pokrene program dobili razlicite vrednosti u matrici
    popuni_polja_u_mapi();
    ispisi_mapu();
    napravi_prozor();
    maxSum = najzbir(visina, visina - 1, visina - 1);
    cout << "Najbolji put iznosi: " << najzbir(visina, visina-1, visina-1) << '\n';
    rekonstruisi_put(visina-1, visina-1);

    vector<Vector2> linijaTacke;
    int tx = 85;
    int ty = 75;
    linijaTacke.push_back({(float)tx, (float)ty});
    for (char d : direkcije) {
        if (d == 'R') tx += 100;
        else if (d == 'D') ty += 75;
        linijaTacke.push_back({(float)tx, (float)ty});
    }

    cout << "Velicina vektora je: " << direkcije.size() << '\n';
    for(int i = 0; i < direkcije.size(); i++)cout << char(direkcije[i]) << " ";
    cout << '\n';
    
    while (!WindowShouldClose() && !stop) { //Glavna petlja programa, vrti sve dok ne postoji razlog za zatvaranje prozora, ili dok stop nije jednak true
        if (IsKeyPressed(KEY_RIGHT) && iX < 685){iX += 100; kolona++;} //Provera da li je pritisnuta desna strelica, ako jeste X kordinata igraca se poveca
        else if (IsKeyPressed(KEY_DOWN) && iY < 500){iY += 75; red++;} //Provera da li je pritisnuta donja strelica, ako jeste Y kordinata igraca se poveca
        if (mapa[red][kolona].posecen == false){sum += mapa[red][kolona].vrednost; mapa[red][kolona].posecen = true;} //Provera da li je trenutno polje na kome se igrac nalazi vec posecen, ako jeste suma se povecava za njegovu vrednost i oznacava se kao posecen
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawRectangle(iX-3, iY-3, 46, 46, BLACK); //Crtanje igraca
        for(int i = 0; i < visina; i++){ //Dupla petlja koja crta "mapu", vrednost polja
            for(int j = 0; j < sirina; j++){
                DrawRectangle(85 + (100 * i), 50 + (75 * j), 40, 40, RED);
                mapa[i][j].x = 85 + (100 * i); mapa[i][j].y = 50 + (75 * j); 
                DrawText(TextFormat("%i", mapa[j][i].vrednost), 95 + (100 * i), 60 + (75 * j), 20, BLACK);
            }
        }
        DrawText(TextFormat("%i", sum), 10, 10, 20, BLACK);
        
        EndDrawing();
        if (iX >= 685 && iY >= 500)stop = true;
        
    }
    cout << "Van while" << '\n';
    cout << sum << '\n';
    
    float t = 0;
    while (!WindowShouldClose() && t < 10.0f) {
        t += GetFrameTime(); // meri proteklo vreme u sekundama
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Tvoja Suma:", 75, 150, 40, BLACK);
        DrawText(TextFormat("%i", sum), 200, 200, 50, BLACK);
        DrawText("Maksimalna Suma:", 400, 150, 40, BLACK);
        DrawText(TextFormat("%i", maxSum), 500, 200, 50, BLACK);
        DrawText(TextFormat("Prikazujem put za: %f", 10.0 - t), 250, 400, 20, BLACK);
        EndDrawing();
    }

    while(!WindowShouldClose() && !direkcije.empty())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawRectangle(85-3, 50-3, 46, 46, BLACK);
        //Crtanje mape
        for(int i = 0; i < visina; i++){
            for(int j = 0; j < sirina; j++){
                DrawRectangle(85 + (100 * i), 50 + (75 * j), 40, 40, RED);
                DrawText(TextFormat("%i", mapa[j][i].vrednost), 95 + (100 * i), 60 + (75 * j), 20, BLACK);
            }
        }

        //Crtanje igraca na cilju
        DrawRectangle(iX-3, iY-3, 46, 46, BLACK);

        //Crtanje najbolje putanje, putanje koja donosi najvecu vrednost
        for (int i = 1; i < linijaTacke.size(); i++) {
            DrawLineV(linijaTacke[i-1], linijaTacke[i], GREEN);
        }

        EndDrawing();

    }

    CloseWindow();

    return 0;
    
}
// Labirinto Simples.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <conio.h>
#include <Windows.h>

using namespace std;
// Macros
// Setas de direção
#define RIGHT 77
#define LEFT  75
#define UP    72
#define DOWN  80
// Dimensões da matriz labirinto
#define LIN   10
#define COL   20

// Enumerated das cores para fundo preto
enum cores {
    colorBlack     = 0,
    colorDarkBlue  = 1,
    colorDarkGreen = 2,
    colorLightBlue = 3,
    colorDarkRed   = 4,
    colorMagenta   = 5,
    colorOrange    = 6,
    colorLightGray = 7,
    colorGray      = 8,
    colorBlue      = 9,
    colorGreen     = 10,
    colorCyan      = 11,
    colorRed       = 12,
    colorPink      = 13,
    colorYellow    = 14,
    colorWhite     = 15,
};

// __________________  Protótipos das Funções  ________________
unsigned char getCode();
void desenharLabirinto(string lab[][COL]);
void right(string lab[][COL], int l, int& c);
void left(string lab[][COL], int l, int& c);
void up(string lab[][COL], int& l, int c);
void down(string lab[][COL], int& l, int c);

int main()
{
    string labirinto[LIN][COL] =
    {
        //0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16  17  18  19
        {"#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#"}, // 0
        {"#","#"," "," "," "," "," "," "," "," "," ","#","#","#","#","#","#","#","#","#"}, // 1
        {"#","#"," ","#","#","#","#","#","#","#"," "," ","#","#","#","#","#","#"," ","F"}, // 2
        {"#","#"," ","#","#","#","#","#","#","#","#"," "," "," "," "," ","#","#"," ","#"}, // 3
        {"#"," "," ","#","#","#","#","#","#","#","#"," ","#","#","#"," ","#","#"," ","#"}, // 4
        {"#"," ","#","#","#","#","#"," ","#","#","#"," ","#","#","#"," ","#","#"," ","#"}, // 5
        {"#"," "," "," ","#","#","#"," ","#","#","#"," ","#"," ","#"," ","#","#"," ","#"}, // 6
        {"#","#","#"," "," "," "," "," ","#","#","#"," ","#"," ","#","#","#","#"," ","#"}, // 7
        {" "," "," "," ","#","#","#","#","#","#","#"," "," "," "," "," "," "," "," ","#"}, // 8
        {"#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#"}, // 9
    };

    string jog = "@";           // Símbolo que se desloca no labirinto
    int lin = 8, col = 0;       // Coordenadas do inicio do jogo
    unsigned char key;          // Para conter o código da seta de direção
    labirinto[lin][col] = jog;  // Coloca o jogador nas coordenadas iniciais

    SetConsoleOutputCP(1252);
    // loop para fazer o percurso no labirinto
    do
    {
        system("cls");
        desenharLabirinto(labirinto);
        cout << "\n\n\tUse as setas direcionais para se deslocar no labirinto:   ";
        key = getCode();
        switch (key)
        {
        case LEFT: left(labirinto, lin, col); break;
        case RIGHT: right(labirinto, lin, col); break;
        case UP: up(labirinto, lin, col); break;
        case DOWN: down(labirinto, lin, col); break;
        }
        if (lin == 2 && col == 19) {
            system("cls");
            desenharLabirinto(labirinto);
            break;
        }
    } while (true);
    
    HANDLE hconsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hconsole, colorYellow);
    cout << "\n\t\tParabéns! Ganhou...." << endl;
    SetConsoleTextAttribute(hconsole, colorWhite);
    cout << "\n\n\tPrima tecla para sair!   ";
    _getch();
    cout << "\n\n\n";
    return 0;
}


// ________________  Funções do programa   ____________________
// Obtem o código da tecla premida
unsigned char getCode() 
{
    unsigned char key = _getch();

    /*  As setas direcionais não existem no código ASCII
    *   São necessárias duas leituras para obter o código da seta
    *   O 1º getch() retorna um pré-código (0 ou 224)
    *   O 2º getch() permite obter a 2ª parte do código
    *   (72 cima, 80 baixo, 77 direita, 75 esquerda)
    */
    if (key == 0 || key == 224) {
        key = _getch();
        /*cout << (int)key << "  " << key << endl;*/
    }
    return key;
}

// __________________________________________________________
// Desenha o labirinto
void desenharLabirinto(string lab[][COL]) {
    HANDLE hconsole;
    hconsole = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleTextAttribute(hconsole, colorGreen);
    cout << endl;
    for (int i = 0; i < LIN; i++)
    {
        cout << "\t\t";
        for (int j = 0; j < COL; j++)
        {
            if (lab[i][j] == "@") {
                SetConsoleTextAttribute(hconsole, colorRed);
                cout << lab[i][j];
                SetConsoleTextAttribute(hconsole, colorGreen);
            }
            else {               
                cout << lab[i][j];
            }
        }
        cout << endl;
    }
    SetConsoleTextAttribute(hconsole, colorWhite);
}

// ________________________________________________________
// Desloca para a direita
void right(string lab[][COL], int l, int& c) 
{
    if (c < COL - 1) {
        if (lab[l][c + 1] == " " || lab[l][c + 1] == "F") {
            lab[l][c] = " ";            // limpa o boneco
            lab[l][++c] = "@";          // Coloca o boneco na nova coordenada
        }
    }
}
 
// ________________________________________________________
// Desloca para a esquerda
void left(string lab[][COL], int l, int& c) 
{
    if (lab[l][c - 1] == " ") {
        lab[l][c] = " ";
        lab[l][--c] = "@";
    }
}

// ________________________________________________________
// Desloca para cima
void up(string lab[][COL], int& l, int c) 
{
    if (lab[l - 1][c] == " ") {
        lab[l][c] = " ";
        lab[--l][c] = "@";
    }
}


// ________________________________________________________
// Desloca para baixo
void down(string lab[][COL], int& l, int c)
{
    if (lab[l + 1][c] == " ") {
        lab[l][c] = " ";
        lab[++l][c] = "@";
    }
}

 
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

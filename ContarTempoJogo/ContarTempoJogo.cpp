// ContarTempoJogo.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>
#include <conio.h>

using namespace std;

#define RIGHT 77
#define LEFT  75
#define UP    72
#define DOWN  80
#define ESC   27


// __________________________________________________________________
void gotoxy(int x, int y);
void desenharRetangulo();
unsigned char getCode();


int main()
{
    clock_t t_inicial, t_atual, duracao = 0;
    int tempoLimite = 10, tempoFalta = 0;
    unsigned char key;

    t_inicial = clock();     // Inicia a contagem do tempo

    while (true)
    {
        system("cls");
        t_atual = clock();
        duracao = (t_atual - t_inicial) / CLOCKS_PER_SEC;
        tempoFalta = tempoLimite - duracao;

        gotoxy(5, 1);
        cout << "\n\tFaltam: " << tempoFalta << " segundos" << endl;
        gotoxy(8, 5);
        desenharRetangulo();

        cout << "\n\tPrima tecla direcional ou outra.   ";

        while (_kbhit()) {
            t_atual = clock();
            key = getCode();
            gotoxy(5, 12);
            switch (key)
            {
            case UP: cout << "\n\tUP = " << (int)key << "  " << key << endl; break;
            case DOWN: cout << "\n\tDOWN = " << (int)key << "  " << key << endl; break;
            case LEFT: cout << "\n\tLEFT= " << (int)key << "  " << key << endl; break;
            case RIGHT: cout << "\n\tRIGHT = " << (int)key << "  " << key << endl; break;
            default: cout << "\n\t" << (int)key << "  " << key << endl; break;
            }

            duracao = (t_atual - t_inicial) / CLOCKS_PER_SEC;
            tempoFalta = tempoLimite - duracao;

            gotoxy(5, 1);
            cout << "\n\tFaltam: " << tempoFalta << " segundos" << endl;
            if (duracao >= tempoLimite)
                break;
            
        }
        if (duracao >= tempoLimite)
            break;
        Sleep(1000);
    }
    gotoxy(0, 15);
}

// _____________________________________________________________________
// Para posicionar o cursor nas coordenadas x e y (x - horizontal (coluna), y - vertical (linha)
void gotoxy(int x, int y) 
{
    COORD c;        // Struct que contém as coordenadas do cursor
    c.X = x;        // coluna - começa em 0
    c.Y = y;        // linha  - começa em 0
    HANDLE hconsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hconsole, c);
}

// ____________________________________________________________________
void desenharRetangulo() 
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            cout << "#";
        }
        cout << "\n\t";
    }
}

// _______________________________________________________________
unsigned char getCode() {
    unsigned char key = _getch();

    /*  As setas direcionais não existem no código ASCII
    *   São necessárias duas leituras para obter o código da seta
    *   O 1º getch() retorna um pré-código (0 ou 224)
    *   O 2º getch() permite obter a 2ª parte do código
    *   (72 cima, 80 baixo, 77 direita, 75 esquerda)
    */
    if (key == 0 || key == 224) {
        key = _getch();
        cout << (int)key << "  " << key << endl;
    }
    return key;
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

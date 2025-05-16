// Arrow Keys.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <conio.h>


#define RIGHT 77
#define LEFT  75
#define UP    72
#define DOWN  80
#define ESC   27

using namespace std;

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

int main()
{
    unsigned char key;
        
    do
    {
        cout << "\n\tPrima tecla direcional ou outra. ESC para sair   ";
        key = getCode();
        switch (key)
        {
        case UP: cout << "\n\tUP = " << (int)key << "  " << key << endl; break;
        case DOWN: cout << "\n\tDOWN = " << (int)key << "  " << key << endl; break;
        case LEFT: cout << "\n\tLEFT= " << (int)key << "  " << key << endl; break;
        case RIGHT: cout << "\n\tRIGHT = " << (int)key << "  " << key << endl; break;
        default: cout << "\n\t" << (int)key << "  " << key << endl; break;
        }
    } while (key != ESC);
    
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

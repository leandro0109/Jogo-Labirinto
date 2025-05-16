// Menus Multiplos.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>
#include <conio.h>

using namespace std;

#define UP    72
#define DOWN  80
#define ENTER 13

#define colorDarkGreen  2
#define colorWhite     15

// ______________________________________________________
int menuPrincipal(HANDLE hc);
void menuOpcoes(HANDLE hc, int op, string st1, string st2, string st3);
int menuNivelDificuldade(HANDLE hc);
string menuSimbolo(HANDLE hc);
unsigned char getCode();

int main()
{
    SetConsoleOutputCP(1252);
    HANDLE hconsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int opcao = 1, nivel = 1;
    string jog = ">";          // símbolo por defeito
    bool continuar = true;

    do
    {
    inicio: 
        opcao = menuPrincipal(hconsole);  
        if (opcao == 1)
            nivel = menuNivelDificuldade(hconsole);
        else if (opcao == 2) {
            jog = menuSimbolo(hconsole);
            goto inicio;
        }
        else
            continuar = false;

        if (continuar) {
            system("cls");
            switch (nivel) {
            case 1: cout << "\n\tLabirinto Iniciante" /*labirintoIniciante(lin,col,jog)*/ << endl; _getch(); break;
            case 2: cout << "\n\tLabirinto Intermédio" /*labirintoIntermedio(lin,col,jog)*/ << endl; _getch(); break;
            case 3: cout << "\n\tLabirinto Avançado" /*labirintoAvancado(lin,col,jog)*/ << endl; _getch(); break;
            }
        }
    } while (continuar);
    cout << "\n\n\tFim de Programa" << endl;
    return 0;
}

// _________________________________________________________________________________
int menuPrincipal(HANDLE hc) 
{
    unsigned char key;
    int op = 1;

    // Imprime as opções
    system("cls");
    SetConsoleTextAttribute(hc, colorDarkGreen);
    cout << "\n\tIniciar Jogo" << endl;
    SetConsoleTextAttribute(hc, colorWhite);
    cout << "\n\tEscolher Símbolo" << endl;
    cout << "\n\tTerminar Jogo" << endl;
    do
    {
        cout << "\n\n\tUse as setas direcionais verticais para escolher a opção:    ";
        key = getCode();
        switch (key)
        {
        case UP:  op == 1 ? op = 1 : op--; break;   // Sobe no menu
        case DOWN: op == 3 ? op = 3 : op++; break;  // Desce no menu
        }
        menuOpcoes(hc, op, "\n\tIniciar Jogo", "\n\tEscolher Símbolo", "\n\tTerminar Jogo");
    } while (key != ENTER);
    return op;
}

// _______________________________________________________________________
// Usado para todos os submenus 
void menuOpcoes(HANDLE hc, int op, string st1, string st2, string st3) 
{
    // Coloca cor verde na opção selecionada
    switch (op)
    {
    case 1:
        system("cls");
        SetConsoleTextAttribute(hc, colorDarkGreen);
        cout <<  st1 << endl;
        SetConsoleTextAttribute(hc, colorWhite);
        cout << st2 << endl;
        cout << st3 << endl;
        break;
    case 2:
        system("cls");
        SetConsoleTextAttribute(hc, colorWhite);
        cout << st1 << endl;     
        SetConsoleTextAttribute(hc, colorDarkGreen);
        cout << st2 << endl;
        SetConsoleTextAttribute(hc, colorWhite);
        cout << st3 << endl;
        break;
    case 3:
        system("cls");
        SetConsoleTextAttribute(hc, colorWhite);
        cout << st1 << endl;      
        cout << st2 << endl;
        SetConsoleTextAttribute(hc, colorDarkGreen);
        cout << st3 << endl;
        SetConsoleTextAttribute(hc, colorWhite);
        break;
    }
}

// ______________________________________________________________________________
int menuNivelDificuldade(HANDLE hc) 
{
    unsigned char key;
    int op = 1;

    system("cls");
    // Imprime as opções
    SetConsoleTextAttribute(hc, colorDarkGreen);
    cout << "\n\tIniciante" << endl;
    SetConsoleTextAttribute(hc, colorWhite);
    cout << "\n\tIntermédio" << endl;
    cout << "\n\tAvançado" << endl;
    do
    {
        cout << "\n\n\tUse as setas direcionais verticais para escolher a opção:    ";
        key = getCode();
        switch (key)
        {
        case UP:  op == 1 ? op = 1 : op--; break;   // Sobe no menu
        case DOWN: op == 3 ? op = 3 : op++; break;  // Desce no menu
        }
        menuOpcoes(hc, op, "\n\tIniciante", "\n\tIntermédio", "\n\tAvançado");
    } while (key != ENTER);
    return op;
}

// ______________________________________________________________________________
string menuSimbolo(HANDLE hc)
{
    unsigned char key;
    string simbolo;
    int op = 1;
    system("cls");
    // Imprime as opções
    SetConsoleTextAttribute(hc, colorDarkGreen);
    cout << "\n\t> (default)" << endl;
    SetConsoleTextAttribute(hc, colorWhite);
    cout << "\n\t@" << endl;
    cout << "\n\tO" << endl;
    do
    {
        cout << "\n\n\tUse as setas direcionais verticais para escolher a opção:    ";
        key = getCode();
        switch (key)
        {
        case UP:  op == 1 ? op = 1 : op--; break;   // Sobe no menu
        case DOWN: op == 3 ? op = 3 : op++; break;  // Desce no menu
        }
        menuOpcoes(hc, op, "\n\t> (default)", "\n\t@", "\n\tO");      
        simbolo = (op == 1) ? ">" : (op == 2) ? "@" : "O";      // Atribui o simbolo correspondente à opção escolhida
    } while (key != ENTER);
    return simbolo;
}





// ________________________________________________________________________________
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

// ContarTempo.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>

using namespace std;

int main()
{
    // clock_t:   Tipo aritmético (long) para representar o tempo baseado no clock do processador
    //            Armazena a contagem dos ticks de cada clock do sistema (CPU)
    //            Se o tempo decorrido exceder o valor máximo é devolvido o valor -1
    // CLOCKS_PER-SEC - Para converter o nº de ciclos (tics) do clock do CPU para segundos

    clock_t t_inicial, t_atual, duracao = 0;

    int tempoLimite = 5, tempoFalta = 0;

    t_inicial = clock();     // Inicia a contagem do tempo

    while (true)
    {
        system("cls");
        t_atual = clock();
        duracao = (t_atual - t_inicial) / CLOCKS_PER_SEC;
        tempoFalta = tempoLimite - duracao;
        cout << "\n\tFaltam: " << tempoFalta << " segundos" << endl;
        if (duracao >= tempoLimite)
            break;
        Sleep(1000);    // Espera 1000 ms (1 s)
    }
    cout << "\n\tTempo decorrido:   " << duracao << " segundos" << endl;
    return 0;
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

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
#define ENTER 13
// Dimensões da matriz
#define LIN   10
#define COL   20

// Enumerated das cores para fundo preto
enum cores {
	color_black = 0,
	color_dark_blue = 1,
	color_dark_green = 2,
	color_light_blue = 3,
	color_dark_red = 4,
	color_magenta = 5,
	color_orange = 6,
	color_light_gray = 7,
	color_gray = 8,
	color_blue = 9,
	color_green = 10,
	color_cyan = 11,
	color_red = 12,
	color_pink = 13,
	color_yellow = 14,
	color_white = 15
};

// __________________ Prótotipos das Funções ___________________

unsigned char getCode();
void desenharLabirinto(string labirinto[][COL], string jog, int nivel);
void right(string labirinto[][COL], int lin, int& col, int& vidas, string jog);
void left(string labirinto[][COL], int lin, int& col, int& vidas, string jog);
void up(string labirinto[][COL], int& lin, int col, int& vidas, string jog);
void down(string labirinto[][COL], int& lin, int col, int& vidas, string jog);
void pisarArmadilha(string labirinto[][COL], int& lin, int col, int& vidas);
int menuPrincipal(HANDLE hc);
void menuOpcoes(HANDLE hc, int op, string st1, string st2, string st3);
int menuNivelDificuldade(HANDLE hc);
string menuSimbolo(HANDLE hc);
void gotoxy(int x, int y);

int main()
{
	SetConsoleOutputCP(1252);

	HANDLE hconsole = GetStdHandle(STD_OUTPUT_HANDLE);

	// Variáveis menus opções
	int opcao = 1, nivel = 1;
	string jog = ">";          // símbolo por defeito
	bool continuar = true;
	int op = 1;                // Seleciona a opção do menu

	resetgame:
	// Varáveis para contar limite de tempo
	clock_t t_inicial = 0, t_atual = 0, duracao = 0;
	int tempoLimite = 60, tempoFalta = 0;
	t_inicial = clock();

	// Labirinto
	string labirinto[LIN][COL] =
	{
		//0   1   2   3   4   5   6   7   8   9   10  11  12  13  14  15  16  17  18  19
		{"#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#" }, // 0
		{"#"," "," "," "," ","#","!"," "," "," ","#","!","#"," "," "," ","#","!"," ","F" }, // 1
		{"#"," ","#","#"," ","#","#","#","#"," ","#"," ","#"," ","#"," ","!","#"," ","#" }, // 2
		{"#","!"," "," "," "," "," "," ","#"," ","#"," "," "," ","#"," ","#","#"," ","#" }, // 3
		{"#","#","#","#"," ","!","#"," ","#"," ","#"," ","#"," ","#"," "," "," "," ","#" }, // 4
		{"#"," ","!"," "," ","#","#"," ","#"," ","#"," ","#"," ","#"," ","#","#","!","#" }, // 5
		{"#","#"," ","#"," ","#","#"," ","!"," "," "," ","!"," ","!"," "," "," "," ","#" }, // 6
		{"#","#","#","#"," ","#","!"," ","#"," ","#"," ","#"," ","#","#","#","#"," ","#" }, // 7
		{" "," "," "," "," ","#"," "," "," "," ","!"," "," "," "," "," "," "," "," ","#" }, // 8
		{"#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#","#" }, // 9
	};

	int vidas = 3;				// Nr de vidas do jogador
	int lin = 8, col = 0;       // Coordenadas do inicio do jogo
	unsigned char key;          // Para conter o código da seta de direção
	labirinto[lin][col] = jog;  // Coloca o jogado nas coordenadas iniciais

	// Loop principal das opções e do jogo
	do
	{
	inicio:
		opcao = menuPrincipal(hconsole);
		if (opcao == 1)
			nivel = menuNivelDificuldade(hconsole);
		else if (opcao == 2) {
			jog = menuSimbolo(hconsole);	// Atualiza simbolo do jogador
			labirinto[lin][col] = jog;		// Atualiza o novo simbolo do jogador para as coordenadas iniciais
			goto inicio;
		}
		else
			continuar = false;

		if (continuar) {
			// Começa o jogo no nivel selecionado pelo jogador 
			switch (nivel)
			{
			case 1:
				do
				{
					system("cls");
					desenharLabirinto(labirinto, jog, nivel);
					cout << "\n\n\tUse as setas direcionais para se deslocar no labirinto:    ";
					key = getCode();
					switch (key)
					{
					case LEFT:  left(labirinto, lin, col, vidas, jog); break;
					case RIGHT: right(labirinto, lin, col, vidas, jog); break;
					case UP:    up(labirinto, lin, col, vidas, jog); break;
					case DOWN:  down(labirinto, lin, col, vidas, jog); break;
					}
					if (lin == 1 && col == 19)
					{
						system("cls");
						desenharLabirinto(labirinto, jog, nivel);
						break;
					}

				} while (true); break;
			case 2:
				do
				{
					system("cls");
					desenharLabirinto(labirinto, jog, nivel);
					SetConsoleTextAttribute(hconsole, color_dark_red);
					cout << "\n\n\t!ATENÇÃO: ESTE NIVEL CONTÊM ARMADILHAS INVISIVEIS!    ";
					SetConsoleTextAttribute(hconsole, color_white);
					cout << "\n\n\tUse as setas direcionais para se deslocar no labirinto:    ";
					key = getCode();
					switch (key)
					{
					case LEFT:  left(labirinto, lin, col, vidas, jog); break;
					case RIGHT: right(labirinto, lin, col, vidas, jog); break;
					case UP:    up(labirinto, lin, col, vidas, jog); break;
					case DOWN:  down(labirinto, lin, col, vidas, jog); break;
					}
					if (lin == 1 && col == 19 || vidas == 0)
					{
						system("cls");
						desenharLabirinto(labirinto, jog, nivel);
						break;
					}

				} while (true); break;
			case 3:
				do
				{
					system("cls");
					t_atual = clock();
					duracao = (t_atual - t_inicial) / CLOCKS_PER_SEC;
					tempoFalta = tempoLimite - duracao;
					desenharLabirinto(labirinto, jog, nivel);
					SetConsoleTextAttribute(hconsole, color_dark_red);
					cout << "\n\n\t!ATENÇÃO: ESTE NIVEL CONTÊM ARMADILHAS INVISIVEIS E TEMPO LIMITE!    ";
					SetConsoleTextAttribute(hconsole, color_orange);
					cout << "\n\t\tTem: " << tempoFalta << " segundos para encontrar a saida!" << endl;
					SetConsoleTextAttribute(hconsole, color_white);
					cout << "\n\n\tUse as setas direcionais para se deslocar no labirinto:    ";

					while (_kbhit())
					{
						t_atual = clock();
						key = getCode();

						switch (key)
						{
						case LEFT:  left(labirinto, lin, col, vidas, jog); break;
						case RIGHT: right(labirinto, lin, col, vidas, jog); break;
						case UP:    up(labirinto, lin, col, vidas, jog); break;
						case DOWN:  down(labirinto, lin, col, vidas, jog); break;
						}

						duracao = (t_atual - t_inicial) / CLOCKS_PER_SEC;
						tempoFalta = tempoLimite - duracao;

						if (duracao >= tempoLimite)
							break;
					}

					if (duracao >= tempoLimite)
						break;

					if (lin == 1 && col == 19 || vidas == 0)
					{
						system("cls");
						desenharLabirinto(labirinto, jog, nivel);
						break;
					}
				} while (true); break;
			}
			// Verifica se o jogador venceu ou perdeu e imprime resultados
			if (vidas > 0 && (duracao < tempoLimite))
			{
				system("cls");
				SetConsoleTextAttribute(hconsole, color_yellow);
				cout << "\n\tParabéns! Ganhou...." << endl;
				SetConsoleTextAttribute(hconsole, color_white);
				cout << "\n\n\tPrima tecla para sair!   ";
				_getch();
			}
			else if (duracao >= tempoLimite)
			{
				system("cls");
				SetConsoleTextAttribute(hconsole, color_yellow);
				cout << "\n\tPerdeu o jogo... Excedeu o tempo limite :(" << endl;
				SetConsoleTextAttribute(hconsole, color_white);
				cout << "\n\n\tPrima tecla para sair!   ";
				_getch();
			}
			else if (vidas <= 0)
			{
				system("cls");
				SetConsoleTextAttribute(hconsole, color_red);
				cout << "\n\tPerdeu o jogo... Sem vidas restantes :(" << endl;
				SetConsoleTextAttribute(hconsole, color_white);
				cout << "\n\n\tPrima tecla para sair!   ";
				_getch();
			}
			goto resetgame;	// Volta ao inicio do código para resetar as variáveis do labirinto, vidas, posição do jogador e temporizador
		}
	} while (continuar);

	cout << "\n\n\tO programa irá ser encerrado em breve... Até à próxima!" << endl;

	cout << "\n\n";
	return 0;
}

// __________________ Funções do programa _____________________

// Obtem o código da tecla premida
unsigned char getCode()
{
	unsigned char key = _getch();
	// cout << (int)key << "   " << key << endl;   // Conversão para inteiro vai buscar  o código ASCII
	// As setas direcionais não existem no código ASCII
	// São necessárias duas leituras para obter o código da seta
	// O primeiro getch() retorna um pre-código que é igual em todas as teclas que nao fazem parte do ASCII (0 ou 224)
	// O segundo getch() permite obter a segunda parte do código 
	// (72 cima, 80 baixo, 77 direita, 75 esquerda)
	if (key == 0 || key == 224)
	{
		key = _getch();
		cout << (int)key << "   " << key << endl;
	}
	return key;
}

// ____________________________________________________________
// Desenhar o labirinto1
void desenharLabirinto(string labirinto[][COL], string jog, int nivel)
{
	HANDLE hconsole;
	hconsole = GetStdHandle(STD_OUTPUT_HANDLE);

	if (nivel == 1)
	{
		SetConsoleTextAttribute(hconsole, color_green);
		for (int i = 0; i < LIN; i++)
		{
			cout << "\t\t\t";
			for (int j = 0; j < COL; j++)		// Loop para substituir 
			{
				if (labirinto[i][j] == "!")
					labirinto[i][j] = "#";		// Substitui as armadilhas do mapa do nivel 1 por paredes
			}
			for (int x = 0; x < COL; x++)
			{
				if (labirinto[i][x] == jog)
				{
					SetConsoleTextAttribute(hconsole, color_red);
					cout << labirinto[i][x];
					SetConsoleTextAttribute(hconsole, color_green);
				}
				else
				{
					cout << labirinto[i][x];
				}
			}
			cout << endl;
		}
		SetConsoleTextAttribute(hconsole, color_white);
	}
	else
	{
		SetConsoleTextAttribute(hconsole, color_green);
		for (int i = 0; i < LIN; i++)
		{
			cout << "\t\t\t";
			for (int j = 0; j < COL; j++)
			{
				if (labirinto[i][j] == jog)
				{
					SetConsoleTextAttribute(hconsole, color_red);
					cout << labirinto[i][j];
					SetConsoleTextAttribute(hconsole, color_green);
				}
				else if (labirinto[i][j] == "!")
					cout << " ";					// Desenha a armadilha como sendo um espaço vazio, de forma a tornar a armadilha "invisivel"
				else
				{
					cout << labirinto[i][j];
				}
			}
			cout << endl;
		}
		SetConsoleTextAttribute(hconsole, color_white);
	}
}

// ____________________________________________________________
// Desloca para a direita
void right(string labirinto[][COL], int lin, int& col, int& vidas, string jog)
{
	if (labirinto[lin][col + 1] == " " || labirinto[lin][col + 1] == "F")
	{
		labirinto[lin][col] = " ";      // Limpa o boneco na casa que estava anteriormente no lab1
		labirinto[lin][++col] = jog;    // Atualiza a nova posição do boneco no lab1
	}
	else if (labirinto[lin][col + 1] == "!")
	{
		labirinto[lin][col] = " ";      // Limpa o boneco na casa que estava anteriormente
		labirinto[lin][++col] = jog;	 // Atualiza a nova posição do boneco para a posição da armadilha
		pisarArmadilha(labirinto, lin, col, vidas);
	}
}

// ____________________________________________________________
// Desloca para a esquerda
void left(string labirinto[][COL], int lin, int& col, int& vidas, string jog)
{
	if (labirinto[lin][col - 1] == " ")
	{
		labirinto[lin][col] = " ";      // Limpa o boneco na casa que estava anteriormente no lab1
		labirinto[lin][--col] = jog;    // Atualiza a nova posição do boneco no lab1
	}
	else if (labirinto[lin][col - 1] == "!")
	{
		labirinto[lin][col] = " ";      // Limpa o boneco na casa que estava anteriormente
		labirinto[lin][--col] = jog;	 // Atualiza a nova posição do boneco para a posição da armadilha
		pisarArmadilha(labirinto, lin, col, vidas);
	}
}

// ____________________________________________________________
// Desloca para cima
void up(string labirinto[][COL], int& lin, int col, int& vidas, string jog)
{
	if (labirinto[lin - 1][col] == " ")
	{
		labirinto[lin][col] = " ";      // Limpa o boneco na casa que estava anteriormente no lab1
		labirinto[--lin][col] = jog;    // Atualiza a nova posição do boneco no lab1
	}
	else if (labirinto[lin - 1][col] == "!")
	{
		labirinto[lin][col] = " ";      // Limpa o boneco na casa que estava anteriormente
		labirinto[--lin][col] = jog;	 // Atualiza a nova posição do boneco para a posição da armadilha
		pisarArmadilha(labirinto, lin, col, vidas);
	}
}

// ____________________________________________________________
// Desloca para baixo
void down(string labirinto[][COL], int& lin, int col, int& vidas, string jog)
{
	if (labirinto[lin + 1][col] == " ")
	{
		labirinto[lin][col] = " ";      // Limpa o boneco na casa que estava anteriormente no lab1
		labirinto[++lin][col] = jog;    // Atualiza a nova posição do boneco no lab1
	}
	else if (labirinto[lin + 1][col] == "!")
	{
		labirinto[lin][col] = " ";      // Limpa o boneco na casa que estava anteriormente
		labirinto[++lin][col] = jog;	// Atualiza a nova posição do boneco para a posição da armadilha
		pisarArmadilha(labirinto, lin, col, vidas);
	}
}

// _______________________________________________________________________________
// Reduz as vidas do jogador e informa que caiu em uma armadilha
void pisarArmadilha(string labirinto[][COL], int& lin, int col, int& vidas)
{
	vidas--;						// Atualiza o nr de vidas do jogador
	HANDLE hconsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hconsole, color_magenta);
	cout << "\n\t\tUps! Pisou em uma armadilha...\n\t\tVidas restantes: " << vidas;
	SetConsoleTextAttribute(hconsole, color_white);
	Sleep(1500);					 // Dá tempo ao jogador para ver as vidas restantes
}

// _________________________________________________________________________________
int menuPrincipal(HANDLE hc)
{
	unsigned char key;
	int op = 1;

	// Imprime as opções
	system("cls");
	SetConsoleTextAttribute(hc, color_dark_green);
	cout << "\n\tIniciar Jogo" << endl;
	SetConsoleTextAttribute(hc, color_white);
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
		SetConsoleTextAttribute(hc, color_dark_green);
		cout << st1 << endl;
		SetConsoleTextAttribute(hc, color_white);
		cout << st2 << endl;
		cout << st3 << endl;
		break;
	case 2:
		system("cls");
		SetConsoleTextAttribute(hc, color_white);
		cout << st1 << endl;
		SetConsoleTextAttribute(hc, color_dark_green);
		cout << st2 << endl;
		SetConsoleTextAttribute(hc, color_white);
		cout << st3 << endl;
		break;
	case 3:
		system("cls");
		SetConsoleTextAttribute(hc, color_white);
		cout << st1 << endl;
		cout << st2 << endl;
		SetConsoleTextAttribute(hc, color_dark_green);
		cout << st3 << endl;
		SetConsoleTextAttribute(hc, color_white);
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
	SetConsoleTextAttribute(hc, color_dark_green);
	cout << "\n\tIniciante" << endl;
	SetConsoleTextAttribute(hc, color_white);
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
	SetConsoleTextAttribute(hc, color_dark_green);
	cout << "\n\t> (default)" << endl;
	SetConsoleTextAttribute(hc, color_white);
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

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

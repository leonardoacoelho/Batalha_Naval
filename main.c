#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#define LINHAS 11
#define COLUNAS 11

char mapFrontPlayer[LINHAS][COLUNAS], mapFrontBot[LINHAS][COLUNAS];
char mapBackPlayer[LINHAS][COLUNAS], mapBackBot[LINHAS][COLUNAS];

int maxBarcos = 5, playerHit, botHit, playerShot, botShot, i = 0, j = 0;
int tentativasBot[100], tentativasPlayer[100];

void PrintMap(char mapa[LINHAS][COLUNAS])
{
    for(int i = 0; i < LINHAS; i++)
    {
        for(int j = 0; j < COLUNAS; j++)
        {
            printf("%c ", mapa[i][j]);
        }
        printf("\n");
    }
}

void Iniciar()
{
    for(int i=0; i < LINHAS; i++)
    {
        for(int j=0; j < COLUNAS; j++)
        {
            if(i > 0 && j > 0)
            {
                mapFrontPlayer[i][j] = '~';
                mapBackPlayer[i][j] = '~';
                mapFrontBot[i][j] = '~';
                mapBackBot[i][j] = '~';
            }
            else if(i > 0 && j == 0)
            {
                char lin = 64;
                lin += i;
                mapFrontPlayer[i][j] = lin;
                mapBackPlayer[i][j] = lin;
                mapFrontBot[i][j] = lin;
                mapBackBot[i][j] = lin;
            }
            else if(i == 0 && j > 0)
            {
                sprintf(&mapFrontPlayer[i][j], "%d", j);
                sprintf(&mapBackPlayer[i][j], "%d", j);
                sprintf(&mapFrontBot[i][j], "%d", j);
                sprintf(&mapBackBot[i][j], "%d", j);
            }
        }
    }
}

void SetPlayerShips(char mapFront[LINHAS][COLUNAS], char mapBack[LINHAS][COLUNAS])
{
    srand(time(NULL));
    int contador = 0;
    while(contador < maxBarcos)
    {
        int x = rand() % LINHAS;
        if(x == 0)
            x = 1;

        int y = rand() % COLUNAS;
        if(y == 0)
            y = 1;

        if(mapBack[x][y] != 'B')
        {
            contador++;
            mapFront[x][y] = 'B';
            mapBack[x][y] = 'B';
        }
    }
}

void SetBotShips(char mapBack[LINHAS][COLUNAS])
{
    srand(time(NULL));
    int contador = 0;
    while(contador < maxBarcos)
    {
        int x = rand() % LINHAS;
        if(x == 0)
            x = 1;

        int y = rand() % COLUNAS;
        if(y == 0)
            y = 1;

        if(mapBack[x][y] != 'B')
        {
            contador++;
            mapBack[x][y] = 'B';
        }
    }
}

int AtirarPlayer()
{
    char xS;
    int y, x;
    printf("\nEscolha onde atirar com as coordenadas (o ultimo numero '1' equivale a 10 (dez)): ");
    scanf("%s %d", &xS, &y);

    if(xS == 'a' || xS == 'A')
        x = 1;
    else if(xS == 'b' || xS == 'B')
        x = 2;
    else if(xS == 'c' || xS == 'C')
        x = 3;
    else if(xS == 'd' || xS == 'D')
        x = 4;
    else if(xS == 'e' || xS == 'E')
        x = 5;
    else if(xS == 'f' || xS == 'F')
        x = 6;
    else if(xS == 'g' || xS == 'G')
        x = 7;
    else if(xS == 'h' || xS == 'H')
        x = 8;
    else if(xS == 'i' || xS == 'I')
        x = 9;
    else if(xS == 'j' || xS == 'J')
        x = 10;
    else
        return 4;

    for(int saveI = 0; saveI <= j; saveI++)
    {
        if(tentativasPlayer[saveI] == mapFrontBot[x][y])
        {
            printf("Esta coordenada ja foi lançada, entre com um valida: ");
            scanf("%s %d", &xS, &y);
        }
    }

    if(mapBackBot[x][y] == 'B')
    {
        mapBackBot[x][y] = 'X';
        mapFrontBot[x][y] = 'X';
        tentativasPlayer[j] = mapFrontBot[x][y];
        j++;

        return 1;
    }
    else if (mapBackBot[x][y] == '~')
    {
        mapBackBot[x][y] = 'O';
        mapFrontBot[x][y] = 'O';
        tentativasPlayer[j] = mapFrontBot[x][y];
        j++;

        return 2;
    }
    else
        return 3;
}

int AtirarBot()
{
    srand(time(NULL));
    int x = rand() % LINHAS;
    if(x == 0)
        x = 1;
    int y = rand() % COLUNAS;
    if(y == 0)
        y = 1;

    for(int saveI = 0; saveI <= i; saveI++)
    {
        if(tentativasBot[saveI] == mapBackPlayer[x][y])
        {
            x = rand() % LINHAS;
            y = rand() % COLUNAS;
        }
    }

    if(mapBackPlayer[x][y] == 'B')
    {
        mapBackPlayer[x][y] = 'X';
        mapFrontPlayer[x][y] = 'X';
        tentativasBot[i] = mapBackPlayer[x][y];
        i++;

        return 1;
    }
    else if (mapBackPlayer[x][y] == '~')
    {
        mapBackPlayer[x][y] = 'O';
        mapFrontPlayer[x][y] = 'O';
        tentativasBot[i] = mapBackPlayer[x][y];
        i++;

        return 2;
    }
}

void ClearScreen()
{
    system("cls");
}

void Maps()
{
    printf("Suas Embarcacoes: ");
    printf("Afundadas: %d/%d \n\n", botHit, maxBarcos);
    PrintMap(mapFrontPlayer);
    printf("\nSeus Tiros: ");
    printf("Quantidade de acertos: %d/%d \n\n", playerHit, maxBarcos);
    PrintMap(mapFrontBot);
}

int main()
{
    Iniciar();

    SetPlayerShips(mapFrontPlayer, mapBackPlayer);
    SetBotShips(mapBackBot);

    while(1)
    {
        Maps();

        playerShot = AtirarPlayer();

        ClearScreen();

        if(playerShot == 1)
        {
            printf("======================================\n");
            printf("Parabens, voce afundou uma embarcacao!\n");
            printf("======================================\n");
            printf("\n\nPressione qualquer tecla para continuar...");
            playerHit += playerShot;
            getch();
        }
        else if(playerShot == 2)
        {
            printf("======================================\n");
            printf("Tiro na agua!\n");
            printf("======================================\n");
            printf("\n\nPressione qualquer tecla para continuar...");
            getch();
        }
        else
        {
            printf("======================================\n");
            printf("Coordenada Invalida!\n");
            printf("======================================\n");
            printf("\n\nPressione qualquer tecla para continuar...");
            getch();
        }

        ClearScreen();

        printf("======================================\n");
        printf("Eh a vez de seu oponente!\n");
        printf("======================================\n");
        printf("\n\nPressione qualquer tecla para continuar...");
        getch();

        ClearScreen();

        botShot = AtirarBot();

        if(botShot == 1)
        {
            printf("======================================\n");
            printf("Bot says: I hit one of your boats!\n");
            printf("======================================\n");
            printf("\n\nPressione qualquer tecla para continuar...");
            botHit += botShot;
            getch();
        }
        else if(botShot == 2)
        {
            printf("======================================\n");
            printf("Bot says: I missed my shot!\n");
            printf("======================================\n");
            printf("\n\nPressione qualquer tecla para continuar...");
            getch();
        }

        ClearScreen();

        if(botHit == 5 || playerHit == 5)
            break;
    }
    if(botHit == 5)
        printf("Que pena, voce perdeu!");
    else if(playerHit == 5)
        printf("Parabens, voce afundou todas as embarcacoes inimigas!");

    return 0;
}

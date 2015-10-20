//Anton G�rd�lv 930930-8030

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

#define GameHeigth 5 //�ndra f�r att �ndra planens storlek
#define GameWidth 5 //�ndra f�r att �ndra planens storlek


char PrintBoard(char GameBoard[GameHeigth][GameWidth]);
char PlayerMove(char GameBoard[GameHeigth][GameWidth]);
char ComputerMove(char GameBoard[GameHeigth][GameWidth]);
void CheckWin(char GameBoard[GameHeigth][GameWidth]);



int main()
{
    char GameBoard[GameHeigth][GameWidth] = {" "};  //Skapar plan-arrayen
    int NumberOfTurns = 0,Starter;  //Antal rundor, vem som startar
    int MaxRounds = GameHeigth*GameWidth;   //Antal maxrundor=bredd*h�jd

    unsigned seed;
    seed = (unsigned)time(NULL); //Seed f�r random
    srand(seed);
    Starter = 1+(rand()%2);



    if(Starter==1) //Om spelaren ska b�rja
	{
        printf("You start!\n");
        for(; ; ) //Manuellt exitad loop
        {
        PrintBoard(GameBoard); //Skriv ut planen
        PlayerMove(GameBoard); //Be spelaren l�gga ut en mark�r
        CheckWin(GameBoard); //Kolla om n�gon vunnit
        NumberOfTurns++;

			 if(NumberOfTurns == MaxRounds) //Om antalet rundor = maxrundor avsluta spelet
			 {
				   printf("Draw!");
				  break;
			 }

        ComputerMove(GameBoard); //Slumpa en position �t datorn
        CheckWin(GameBoard); //Kolla om n�gon vunnit
        NumberOfTurns++;

        }
    }
    else if(Starter==2)	//Om datorn ska b�rja
    {
        printf("Ai starts!\n");
        for(; ; )
        {
        ComputerMove(GameBoard);
        CheckWin(GameBoard);
        NumberOfTurns++;
			 if(NumberOfTurns == MaxRounds)
			 {
				  printf("Draw");
				  break;
			 }
        PrintBoard(GameBoard);
        PlayerMove(GameBoard);
        CheckWin(GameBoard);
        NumberOfTurns++;


        }

    }

    return 0;
}

char PrintBoard(char GameBoard[GameHeigth][GameWidth])  //Funktion f�r att skriva ut planen
{
    int i,j,x = 0;
    printf("\nx");
    for(x=0; x!=GameWidth;x++){ //Skriver ut spelplanens bredd

        if(x == GameWidth-1) //Om det �r det sista talet som ska skrivas ut
        {
            printf("| %d |",x+1);
        }
        else
        {
            printf("| %d ",x+1);
        }
    }

    for (i = 0; i != GameHeigth; i++)
    {
        printf("\n%d", i + 1); //Skriv ut radnummer

        for(j = 0; j != GameWidth; j++)
        {
            if(j == GameWidth-1) //Om det �r den sista rutan som ska skrivas ut, skriv ut rutans inneh�ll + st�ng rutan
            {
                printf("| %c |",GameBoard[i][j]);
            }
            else //Annars skriv ut rutans inneh�ll
            {
                printf("| %c ", GameBoard[i][j]);
            }
        }


    }
    return GameBoard; //Returnera planen

}

char PlayerMove(char GameBoard[GameHeigth][GameWidth])  //Funktion f�r att placera ut anv�ndarens val
{

  int x, y;

    printf("\nEnter X,Y coordinates for your move(EX: 1 1): ");
    fflush(stdin);
    scanf("%d", &x); //Scannar in x + y koordinater
    scanf("%d", &y);
    x-- ,y--; //Tar bort 1 fr�n b�da talen s� de kommer in p� r�tt plats i arrayen


    if(GameBoard[x][y]=='X'||GameBoard[x][y]=='O') //Om positionen spelaren angett �r upptagen
    {
        printf("Invalid move, try again.\n");
        PlayerMove(GameBoard);
    }
    else //Om positionen inte �r upptagen placera ut spelarens mark�r
        GameBoard[x][y] = 'X';

    return GameBoard;

}

char ComputerMove(char GameBoard[GameHeigth][GameWidth]) //Funktion f�r att placera ut datorns mark�r
{
    int ComputerX,ComputerY,Selected = 0;
    unsigned seed;
    seed = (unsigned)time(NULL); //Seed f�r random
    srand(seed);


	while(Selected == 0)
	{
	ComputerX = 1+(rand()%GameHeigth);//Slumpar ett tal mellan 1 och gameheigth
    ComputerY = 1+(rand()%GameWidth);   //Slumpar ett tal mellan 1 och gamewidth
    ComputerX--,ComputerY--; //Tar bort 1 fr�n b�da talen s� de kommer in p� r�tt plats i arrayen

    if(GameBoard[ComputerX][ComputerY]!='X'||GameBoard[ComputerX][ComputerY]!='O') //Om platsen �r upptagen
    {
        GameBoard[ComputerX][ComputerY] = 'O';
		Selected = 1;
        
    }
    
	}
    return;
}


void CheckWin(char GameBoard[GameHeigth][GameWidth])    //Funktion f�r att kolla om n�gon vunnit
{
    int i = 0,j = 0;
    for(i = 0;i<GameHeigth;i++) //Upprepa f�r h�jden
    {
        for(j = 0;j<GameWidth;j++) //Upprepa f�r bredden
        {
            if(GameBoard[i][j]==GameBoard[i+1][j]&&GameBoard[i+1][j]==GameBoard[i+2][j])    //Om n�gon f�r 3 i rad vertikalt
            {
                if(GameBoard[i][j]=='X')    //Om anv�ndaren vinner
                {
                    PrintBoard(GameBoard);  //Skriv ut planen
                    printf("\nYou beat the computer, congratulations!\n");
                    system("PAUSE");
                    exit(0);
                }
                else if(GameBoard[i][j]=='O')   //Om datorn vinner
                {
                    PrintBoard(GameBoard);
                    printf("\nThe computer beat you.");
                    system("PAUSE");
                    exit(0);

                }
            }
            else if(GameBoard[i][j]==GameBoard[i][j+1]&&GameBoard[i][j+1]==GameBoard[i][j+2])   //Om n�gon f�r 3 i rad horisontellt
            {
                if(GameBoard[i][j]=='X')
                {
                    PrintBoard(GameBoard);
                    printf("\nYou beat the computer, congratulations!\n");
                    system("PAUSE");
                    exit(0);
                }
                else if(GameBoard[i][j]=='O')
                {
                    PrintBoard(GameBoard);
                    printf("\nThe computer beat you.");
                    system("PAUSE");
                    exit(0);

                }
            }
            else if(GameBoard[i][j]==GameBoard[i+1][j+1]&&GameBoard[i+1][j+1]==GameBoard[i+2][j+2])    //Om n�gon f�r 3 i rad diagonellt ner�t
            {

                if(GameBoard[i][j]=='X')
                {
                    PrintBoard(GameBoard);
                    printf("\nYou beat the computer, congratulations!\n");
                    system("PAUSE");
                    exit(0);
                }
                else if(GameBoard[i][j]=='O')
                {
                    PrintBoard(GameBoard);
                    printf("\nThe computer beat you.");
                    system("PAUSE");
                    exit(0);

                }
            }
            else if(j>1&&GameBoard[i][j]==GameBoard[i+1][j-1]&&GameBoard[i+1][j-1]==GameBoard[i+2][j-2])    //Om n�gon f�r 3 i rad diagonellt upp�t, kan ge felaktigt utslag om i �r mindre �n 1
            {
                if(GameBoard[i][j]=='X')
                {
                    PrintBoard(GameBoard);
                    printf("\nYou beat the computer, congratulations!\n");
                    system("PAUSE");
                    exit(0);
                }
                else if(GameBoard[i][j]=='O')
                {
                    PrintBoard(GameBoard);
                    printf("\nThe computer beat you.\n");
                    system("PAUSE");
                    exit(0);
                }
            }
        }
    }
    return;
}

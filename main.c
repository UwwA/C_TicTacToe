//Anton Gärdälv 930930-8030

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

#define GameHeigth 5 //Ändra för att ändra planens storlek
#define GameWidth 5 //Ändra för att ändra planens storlek


char PrintBoard(char GameBoard[GameHeigth][GameWidth]);
char PlayerMove(char GameBoard[GameHeigth][GameWidth]);
char ComputerMove(char GameBoard[GameHeigth][GameWidth]);
void CheckWin(char GameBoard[GameHeigth][GameWidth]);



int main()
{
    char GameBoard[GameHeigth][GameWidth] = {" "};  //Skapar plan-arrayen
    int NumberOfTurns = 0,Starter;  //Antal rundor, vem som startar
    int MaxRounds = GameHeigth*GameWidth;   //Antal maxrundor=bredd*höjd

    unsigned seed;
    seed = (unsigned)time(NULL); //Seed för random
    srand(seed);
    Starter = 1+(rand()%2);



    if(Starter==1) //Om spelaren ska börja
	{
        printf("You start!\n");
        for(; ; ) //Manuellt exitad loop
        {
        PrintBoard(GameBoard); //Skriv ut planen
        PlayerMove(GameBoard); //Be spelaren lägga ut en markör
        CheckWin(GameBoard); //Kolla om någon vunnit
        NumberOfTurns++;

			 if(NumberOfTurns == MaxRounds) //Om antalet rundor = maxrundor avsluta spelet
			 {
				   printf("Draw!");
				  break;
			 }

        ComputerMove(GameBoard); //Slumpa en position åt datorn
        CheckWin(GameBoard); //Kolla om någon vunnit
        NumberOfTurns++;

        }
    }
    else if(Starter==2)	//Om datorn ska börja
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

char PrintBoard(char GameBoard[GameHeigth][GameWidth])  //Funktion för att skriva ut planen
{
    int i,j,x = 0;
    printf("\nx");
    for(x=0; x!=GameWidth;x++){ //Skriver ut spelplanens bredd

        if(x == GameWidth-1) //Om det är det sista talet som ska skrivas ut
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
            if(j == GameWidth-1) //Om det är den sista rutan som ska skrivas ut, skriv ut rutans innehåll + stäng rutan
            {
                printf("| %c |",GameBoard[i][j]);
            }
            else //Annars skriv ut rutans innehåll
            {
                printf("| %c ", GameBoard[i][j]);
            }
        }


    }
    return GameBoard; //Returnera planen

}

char PlayerMove(char GameBoard[GameHeigth][GameWidth])  //Funktion för att placera ut användarens val
{

  int x, y;

    printf("\nEnter X,Y coordinates for your move(EX: 1 1): ");
    fflush(stdin);
    scanf("%d", &x); //Scannar in x + y koordinater
    scanf("%d", &y);
    x-- ,y--; //Tar bort 1 från båda talen så de kommer in på rätt plats i arrayen


    if(GameBoard[x][y]=='X'||GameBoard[x][y]=='O') //Om positionen spelaren angett är upptagen
    {
        printf("Invalid move, try again.\n");
        PlayerMove(GameBoard);
    }
    else //Om positionen inte är upptagen placera ut spelarens markör
        GameBoard[x][y] = 'X';

    return GameBoard;

}

char ComputerMove(char GameBoard[GameHeigth][GameWidth]) //Funktion för att placera ut datorns markör
{
    int ComputerX,ComputerY,Selected = 0;
    unsigned seed;
    seed = (unsigned)time(NULL); //Seed för random
    srand(seed);


	while(Selected == 0)
	{
	ComputerX = 1+(rand()%GameHeigth);//Slumpar ett tal mellan 1 och gameheigth
    ComputerY = 1+(rand()%GameWidth);   //Slumpar ett tal mellan 1 och gamewidth
    ComputerX--,ComputerY--; //Tar bort 1 från båda talen så de kommer in på rätt plats i arrayen

    if(GameBoard[ComputerX][ComputerY]!='X'||GameBoard[ComputerX][ComputerY]!='O') //Om platsen är upptagen
    {
        GameBoard[ComputerX][ComputerY] = 'O';
		Selected = 1;
        
    }
    
	}
    return;
}


void CheckWin(char GameBoard[GameHeigth][GameWidth])    //Funktion för att kolla om någon vunnit
{
    int i = 0,j = 0;
    for(i = 0;i<GameHeigth;i++) //Upprepa för höjden
    {
        for(j = 0;j<GameWidth;j++) //Upprepa för bredden
        {
            if(GameBoard[i][j]==GameBoard[i+1][j]&&GameBoard[i+1][j]==GameBoard[i+2][j])    //Om någon får 3 i rad vertikalt
            {
                if(GameBoard[i][j]=='X')    //Om användaren vinner
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
            else if(GameBoard[i][j]==GameBoard[i][j+1]&&GameBoard[i][j+1]==GameBoard[i][j+2])   //Om någon får 3 i rad horisontellt
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
            else if(GameBoard[i][j]==GameBoard[i+1][j+1]&&GameBoard[i+1][j+1]==GameBoard[i+2][j+2])    //Om någon får 3 i rad diagonellt neråt
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
            else if(j>1&&GameBoard[i][j]==GameBoard[i+1][j-1]&&GameBoard[i+1][j-1]==GameBoard[i+2][j-2])    //Om någon får 3 i rad diagonellt uppåt, kan ge felaktigt utslag om i är mindre än 1
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
